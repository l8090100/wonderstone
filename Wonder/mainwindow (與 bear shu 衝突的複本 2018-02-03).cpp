#include "mainwindow.h"
#include "systempage.h"
#include "showpage.h"
#include "datapage.h"
#include "boardpage.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QFileDialog>

SystemPage *MainWindow::systemPage;
ShowPage *MainWindow::showPage;
BoardPage *MainWindow::boardPage;
DataPage *MainWindow::dataPage;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    systemPage = new SystemPage();
    showPage = new ShowPage();
    boardPage = new BoardPage();
    dataPage = new DataPage();
    ui->Main_stackedWidget->addWidget(showPage);
    ui->Main_stackedWidget->addWidget(boardPage);
    ui->Main_stackedWidget->addWidget(dataPage);
    ui->Main_stackedWidget->addWidget(systemPage);
    ui->Main_stackedWidget->setCurrentIndex(3);
    connect(dataPage->get_cueList_Table(), SIGNAL(clicked(const QModelIndex &)), showPage, SLOT(showMotorData2(const QModelIndex &)));

    connect(&m_heart,&QTimer::timeout,this,&MainWindow::heartTimeOut);
    m_heart.setInterval(100);
    //全局线程的创建
    m_thread = new ThreadFromQThread(this);
    connect(m_thread,&ThreadFromQThread::message  ,this,&MainWindow::receiveMessage);
    connect(m_thread,&ThreadFromQThread::progress ,this,&MainWindow::progress);
//    connect(m_thread,&QThread::finished  ,this,&MainWindow::onQThreadFinished);

    m_heart.start();

}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::on_Show_Button_clicked()
{
    ui->Main_stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_Board_Button_clicked()
{
    ui->Main_stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Data_Button_clicked()
{
    ui->Main_stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_System_Button_clicked()
{
   ui->Main_stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_Show_AllMin_Button_clicked()
{
    serial->write("T1JGF\n");serial->write("T3JGF\n");
}

void MainWindow::on_Show_AllHome_Button_clicked()
{
    serial->write("T1JG0\n");serial->write("T3JG0\n");
}


void MainWindow::on_actionOpen_Project_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Project"), ".", tr("DataBase Files(*.db)"));
       if(path.length() == 0) {
               QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
       } else {
               QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
       }
}

void MainWindow::progress(int val)
{
    showPage->mb->at(0)->setDelay(val);
//    ui->progressBar->setValue(val);
}

void MainWindow::receiveMessage(const QString &str)
{
//    ui->textBrowser->append(str);
}

void MainWindow::heartTimeOut()
{
    static int s_heartCount = 0;
    ++s_heartCount;
    if(s_heartCount > 100)
    {
        s_heartCount = 0;
    }
    showPage->mb->at(0)->setDestination(s_heartCount);
//    ui->progressBar_heart->setValue(s_heartCount);
}
