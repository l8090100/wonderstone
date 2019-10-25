#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QThread>


//一个包的长度信息
#define REAL_LEN 64//有效数据最大长度
#define HDR_LEN 8//包头长度（固定不变）

//处理照片数据的状态标志（目前没用到--留待以后扩展）
//照片数据分为三部分（begin + 有效数据 +end）
#define BEGIN 0x01//开始处理照片--接收到含有begin的包
#define END 0x02//照片数据接收完毕--接收到含有end的包
#define READING 0x03//正在处理照片数据--照片的实际有效数据

//读串口的状态标志--每个包分为两部分读取（包头+有效数据）
#define READ_HDR 0x01//读取包头
#define READ_DATA 0x02//读取有效数据

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void initSerial(QSerialPortInfo info);//串口初始化
    void readSerial();//子线程真正的处理函数--在没有结束程序的时候是死循环
    void setFlag(bool flag);//更新isStop标志

    //读取指定长度的数据，但是返回的是本次读取到的实际字节数
    //实际读取的字节数可能比length小
    int readFrameData(unsigned int length);
    void handleHead(); //处理包头数据
    void handlePhoto();//处理图片的有效数据

signals:
    void isDone(QByteArray tmp);//接收到完整的包头以后给主线程发送的信号--携带包头数据

public slots:

private:

    bool isStop;//控制子线程的处理函数是否结束
    //8. IODevice及其子类对象都不应该跨线程调用
    //所以子线程声明/初始化该类对象的时候需要显示指定其父对象
    //通常其父对象就是将要被放入子线程的对象，所以只需要在构造函数中将其父对象指定为this指针即可
    QSerialPort *serial;//串口对象指针
    QFile  dst;//目标文件--图片文件

    unsigned int cnt_read;//总的已读取的字节数（只针对完整读取指定长度的数据包）
    unsigned int cnt_need;//还需要的字节数（只针对完整读取指定长度的数据包）
    unsigned int data_need;//每一个包的有效数据的总长度
    unsigned int cnt;//串口接收到的所有有效数据的字节数（针对读取图片的整个过程）

    QByteArray read_data;//总的已读取的数据（只针对完整读取指定长度的数据包）

    //缓冲区，当读取的有效数据累计满32*64的时候在进行写入文件操作，减少写文件的次数，以提高速度
    QByteArray my_stream;


    int photo_state;//读取图片的操作状态（暂时没用到）--对应BEGIN/READING/END
    int serial_state;//读取串口的状态（读取包头/读取有效数据--对应READ_HDR/READ_DATA）

    //为了以后扩展系统--一个协调器可能接收来自多个终端节点的数据
    int node_type;//节点类型（判断当前数据包是哪一种类型的节点发过来的）
    int node_id;//节点序号（同类节点有可能有多个）
    unsigned int seqnb;//当前数据包的序号
    unsigned int pkt_cnt;//读取到图片有效数据的包的个数--满32个就进行一次写入操作

    bool FAIL_FLAG;//读取的数据包是否发生丢失或者重复
};

#endif // MYTHREAD_H
