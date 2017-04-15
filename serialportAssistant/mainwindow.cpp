#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    //初始化UI中的参数
    getSerialPortNames();//获取当前串口并添加到UI中
    ui->baudRateCbx->setCurrentIndex(3);//默认设置波特率为9600
    //
    //数据位设置，略去

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showData()));
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pBtn_clicked()
{

}

void MainWindow::on_iBtn_clicked()
{

}

void MainWindow::on_dBtn_clicked()
{

}


void MainWindow::on_speedBtn_clicked()
{

}


void MainWindow::on_openBtn_clicked()
{
    //先调用设置串口参数的函数
    setGetValue();
    mySerialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(ui->openBtn->text()=="打开串口")
    {
        //打开串口并设置读写模式
        bool com = mySerialPort->open(QIODevice::ReadWrite);
        if(com)
        {
            timer->start(100);
            ui->statusBar->showMessage("串口打开成功",3000);
            isopen = true;
            ui->openBtn->setText("关闭串口");
        }
        else
        {
            ui->statusBar->showMessage("串口打开失败",3000);
            isopen = false;
        }
    }
    else {
        if(mySerialPort->isOpen())
        {
            timer->stop();
            mySerialPort->close();
        }
        ui->openBtn->setText("打开串口");
        ui->statusBar->showMessage("串口已经关闭",3000);
    }
}

void MainWindow::on_sendBtn_clicked()
{
    if(isopen)
    {
        if(!ui->sendLineEdit->text().isEmpty())
        {
            QString sendStr = ui->sendLineEdit->text();
            QByteArray sdata;
            sdata.append(sendStr);
            mySerialPort->write(sdata,sdata.length());

        }
        else
        {
            ui->statusBar->showMessage("请输入要发送的数据",3000);
        }
    }
    else
    {
        ui->statusBar->showMessage("请先打开串口",3000);
    }
}


void MainWindow::on_clearBtn_clicked()
{
    ui->dataShowTB->setText("");
}

void MainWindow::getSerialPortNames()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialPortCbx->addItem(info.portName());
    }
}

void MainWindow::setGetValue()
{
    //设置串口号
    QString comname = ui->serialPortCbx->currentText();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        if(info.portName()==comname)
        {
            mySerialPort->setPortName(info.systemLocation());
        }
    }

    //设置波特率
    qint32 baudIndex = ui->baudRateCbx->currentIndex();
    switch(baudIndex)
    {
    case 0:
        mySerialPort->setBaudRate(QSerialPort::Baud1200,QSerialPort::AllDirections);
        break;
    case 1:
        mySerialPort->setBaudRate(QSerialPort::Baud2400,QSerialPort::AllDirections);
        break;
    case 2:
        mySerialPort->setBaudRate(QSerialPort::Baud4800,QSerialPort::AllDirections);
        break;
    case 3 :
        mySerialPort->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
        break;
    case 4:
        break;
    default :
    //    mySerialPort->setBaudRate(QSerialPort::UnknownBaud,QSerialPort::AllDirections);
        break;

    }
}

void MainWindow::showData()
{
    QByteArray showdata = mySerialPort->readAll();
    QString show = "";
    show += QString(showdata);
    ui->dataShowTB->setText(show+ui->dataShowTB->toPlainText());
}





















