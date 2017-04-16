#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <stdio.h>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pBtn_clicked();

    void on_iBtn_clicked();

    void on_dBtn_clicked();

    void on_openBtn_clicked();

    void on_clearBtn_clicked();

    void showData();

    void on_sendBtn_clicked();

    void on_speedBtn_clicked();

    void on_dataShowTB_textChanged();

private:
    Ui::MainWindow *ui;
    QSerialPort *mySerialPort = new QSerialPort;
    void getSerialPortNames();
    void setGetValue();
    bool isopen = false;
    QTimer *timer = new QTimer;
};

#endif // MAINWINDOW_H
