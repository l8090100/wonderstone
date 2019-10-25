#include "mythread.h"
#include <QDateTime>

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    //记录读取状态相关变量的初始化
    cnt_read = 0;
    cnt_need = 0;
    photo_state = BEGIN;//默认状态是开始读取图片（暂时没用到）
    serial_state = READ_HDR;//默认状态是读取包头的状态
    data_need = 0;
    node_id = 0;
    node_type = 0;
    cnt = 0;
    seqnb = 0;
    FAIL_FLAG = false;//默认没有失败
    pkt_cnt = 0;
    isStop = false;//默认是false--不退出子线程处理函数
}

void MyThread::initSerial(QSerialPortInfo info)
{
    serial = new QSerialPort(this);
    if(serial->isOpen())//先关闭
        serial->close();
    serial->setPort(info);//设置串口号--就是从下拉框选择的串口号
    serial->open(QIODevice::ReadWrite);         //读写打开
    serial->setBaudRate(QSerialPort::Baud38400);  //波特率
    serial->setDataBits(QSerialPort::Data8); //数据位
    serial->setParity(QSerialPort::NoParity);    //无奇偶校验
    serial->setStopBits(QSerialPort::OneStop);   //停止位
    serial->setFlowControl(QSerialPort::NoFlowControl);  //无控制

    readSerial();//实际意义的子线程处理函数

}

//将QByteArray类型的数据转换为int类型
int bytesToInt(QByteArray bytes) {
    int addr = bytes[0] & 0x000000FF;
    addr |= ((bytes[1] << 8) & 0x0000FF00);
    addr |= ((bytes[2] << 16) & 0x00FF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
}

//读取指定长度串口数据（实际不一定能读取指定的长度）
//实际读取到的字节数 小于等于 给定的长度
int MyThread::readFrameData(unsigned int length)
{
    QByteArray tmp_data;//存放本次读取到的临时数据
    int cnt_tmp;//存放本次读取到的临时长度

    cnt_need = length - cnt_read;//更新当前还需要读取的字节数
    tmp_data = serial->read(cnt_need);//本次读取的数据
    if(tmp_data.isEmpty())//如果读取空内容直接返回-1表示读取错误
        return -1;

    cnt_tmp = tmp_data.length();//获取本次读取到的字节数
    cnt_read +=  cnt_tmp;//已经读取的总字节数（只针对读取一个指定长度的数据包）
    read_data += tmp_data;//已经读取的数据（只针对读取一个指定长度的数据包）

    return cnt_tmp;//返回本次读取的实际字节数
}

//处理包头
void MyThread::handleHead()
{
    static unsigned int seq_old = 0;//记录上一次读取到的数据包的序号

    //能够执行这个函数说明已经读完了指定包头长度的数据（表示读完了包头），要进行第二部分指定长度的数据读取了（有效数据的读取）


    //将记录读取状态的相关变量清零
    cnt_read = 0;
    cnt_need = 0;

    //读完头部数据下一个状态应该是读取有效数据--切换状态
    serial_state = READ_DATA;

    //获取包头里的有用信息
    node_type = bytesToInt(read_data.mid(0,1));//节点类型
    node_id = bytesToInt(read_data.mid(1,1));//节点id
    data_need = bytesToInt(read_data.mid(7,1));//有效数据的长度--很重要
    seqnb = bytesToInt(read_data.mid(6,1))*256 + bytesToInt(read_data.mid(5,1));//该数据包的序号--也很重要

    //如果该数据包序号和上一个数据包序号相等--读重复了
    if(seqnb == seq_old)
    {
        FAIL_FLAG = true;//重复--读失败的标志置位--该数据包将不会写入图片文件
        qDebug()<<"seqnb err..********************************";
    }
    else if(seqnb - seq_old > 1)//如果该数据包序号比上一个数据包序号大于等于2，表示中间丢了数据包
    {
        //虽然读取失败了，但是该数据包是需要写入图片文件的，所以失败标志复位--要写入该数据包到图片文件
        FAIL_FLAG = false;

        //计算丢失的数据包个数
        int need_pkt = seqnb - seq_old;
        QByteArray errData(64*(need_pkt-1),0);//构造一个和丢失的所有数据包总和一样大、全0的数据包

        my_stream += errData;//将上述构造的数据包加到缓冲区
        dst.write(my_stream);//将缓冲区所有数据写入图片文件
        my_stream.clear(); //清空缓冲区
        pkt_cnt = 0;//记录缓冲区是否满32*64的变量清零--表示重新计数（此时缓冲区已经没有数据了）

    }
    else {//既没有重复读取也没有丢失数据包
        FAIL_FLAG = false;
    }
    seq_old = seqnb;//更新旧的数据包序号

    //发送信号给主线程--更新UI界面（携带包头数据）
    emit isDone(read_data);

    //清空读取到的数据（只针对读取一个指定长度的数据包）
    read_data.clear();
}


//处理图片实际数据
void  MyThread::handlePhoto()
{

    //能够执行这个函数说明已经读完了一个数据包的效数据，要进行下一个数据包的数据读取了（又要从包头开始读取）

    //记录读取状态的变量清零--以便下一个指定长度的读取
    cnt_read = 0;
    cnt_need = 0;

    serial_state = READ_HDR;//更新串口读取状态--立马要读取下一个数据包的包头了

    //if(photo_state == END && strcmp("end\r\n",str_tmp) == 0)
    //if(strcmp("end",str_tmp) == 0)
    if(read_data.contains("end"))//如果读取到的有效数据包含end--表示读取到图片结束
    {
        if(dst.isOpen())//关闭图片文件
            dst.close();

        //打印调试信息
        qDebug()<<"end";
        qDebug()<<cnt;

        //清空相关缓冲区和--准备读取下一个数据包了
        //（只针对读取一个指定长度的数据包）已读取的数据清空
        read_data.clear();

        //缓冲区清空
        my_stream.clear();
        photo_state = BEGIN;//更新图片的读取状态（暂时没用到）

        data_need = 0;//图片的有效数据长度清零
        cnt = 0;//读取到的所有有效数据清零

        return ;//直接返回--后面的没必要再执行了
    }

    //if(photo_state == BEGIN && strcmp("begin\r\n",str_tmp) == 0)
    //if(strcmp("begin\r\n",str_tmp) == 0)
    if(read_data.contains("begin"))//如果读取到的有效数据包含begin--表示准备开始读取图片
    {

        //将系统当前时间作为图片的文件名
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间

        //设置显示格式,注意QFile的文件名不能有：（冒号）等特殊字符
        QString str = time.toString("yyyy-MM-dd-hh-mm-ss");
        str += ".jpg";

        qDebug()<<str;
        if(dst.isOpen())
            dst.close();

        dst.setFileName(str);//将时间作为文件名
        //QDir::currentPath()
        bool isOK = dst.open(QIODevice::WriteOnly|QIODevice::Append); //打开文件
        if(isOK == false)//打开失败
        {
            qDebug()<<"dst.open err";
// //this->close();
        }

        //清空相关缓冲区和--准备读取下一个数据包了
        read_data.clear();
        data_need = 0;

        photo_state = READING;//更新图片读取状态（暂时没用到）

        return ;//直接返回--后面的没必要再执行了
    }
    //if(photo_state == READING)//读取图片的实际有效数据
    {
        cnt += read_data.length();//累加图片的有效数据

        //如果重复了--不会写入当前数据包到图片文件
        if(FAIL_FLAG == true)
        {
            //清空已读取到的数据（但不清空缓冲区--实际不重复的有效数据没有满32*64）--准备读取下一个数据包的数据
            read_data.clear();
            data_need = 0;//有效数据长度清零
            return;//直接返回
        }
// //qDebug()<<"==========>"<<seqnb;
        pkt_cnt++;//记录不重复的有效数据包的个数
        my_stream += read_data;//不重复的有效数据包累加到缓冲区

        //如果当前数据包的有效长度小于给定的有效数据包的长度的宏定义--表示是最后一个数据包
        if(data_need < REAL_LEN)
        {
            photo_state = END;//更新图片读取状态（暂时没用到）
            dst.write(my_stream);//将当前缓冲区的数据写入图片文件
            my_stream.clear();//清空缓冲区
            pkt_cnt = 0;//记录不重复有效数据包的个数清零
        }

        //还没有读取完毕，但是缓冲区已经满了32*64（这里的64是一个数据包里有效数据的最大长度--对应宏定义REAL_LEN）
        if(pkt_cnt == 32)
        {
            pkt_cnt = 0;//记录不重复有效数据包的个数清零
            dst.write(my_stream);//将当前缓冲区的数据写入图片文件
            my_stream.clear();//清空缓冲区
        }


        //已读取的数据清空（只针对读取一个指定长度的数据包）
        read_data.clear();
        data_need = 0;//图片的有效数据长度清零
    }

}

//读取串口数据--真正子线程处理函数
void MyThread::readSerial()
{
    int ret = 0;//记录每次实际读取的字节数
    while(!isStop)
    {

        //while(this->serial->waitForReadyRead(10))
        //一定要调用这个函数，否则串口不会发出readyRead信号（或者说即使发了也没有去捕获），也就什么都不能读取了
        if(this->serial->waitForReadyRead(10) == false)
            qDebug() << "子线程号：========================"<< QThread::currentThread() ;

        if(serial->bytesAvailable() >= 1)//有可读数据再去读
        {
            switch(serial_state)
            {

            case READ_HDR://读包头
                ret = readFrameData(HDR_LEN);//目标是读取HDR_LEN个字节的数据
                if(ret == -1)//读取错误
                {
                    return;
                }

                if(HDR_LEN == cnt_read)//已读取到的字节数和目标长度相等
                    handleHead();//处理头部数据
                break;

            case READ_DATA://读有效数据
                if(node_type == 1)//如果是图像节点的数据（不再判断节点--目前只有一个节点的数据）
                {
                    ret = readFrameData(data_need);//读取有效长度（从包头获取）的数据
                    if(ret == -1)//读取错误
                    {
                        return;
                    }

                    if(data_need == cnt_read)//已读取到的字节数和目标长度相等
                        handlePhoto();//处理有效数据
                }

                break;
            default:
                break;

            }
        }

    }
}

void MyThread::setFlag(bool flag)
{
    isStop = flag;

    //5. 子线程中声明、初始化的对象在子线程中析构，
    //利用deleteLater该函数可很好解决多线程释放对象
    serial->deleteLater();
    qDebug() << "stop";
}
