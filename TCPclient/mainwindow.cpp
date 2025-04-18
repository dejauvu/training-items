#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socketState = false;
    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readyreadslot()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnectslot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_send_clicked()
{
    QString str;
    str = ui->textEdit_send->toPlainText();
    QByteArray data = str.toLocal8Bit();
    tcpSocket->write(data);
}

void MainWindow::readyreadslot()
{
    QByteArray data = tcpSocket->readAll();
    QString str;
    str = QString::fromLocal8Bit(data);
    ui->textBrowser->append(str);

}

void MainWindow::disconnectslot()
{
    ui->textBrowser->append("服务器掉线");
}

void MainWindow::on_pushButton_listen_clicked()
{
    qDebug() << "尝试连接到服务器：";
    QString ip = ui->lineEdit_ip_2->text();
    quint16 port = ui->lineEdit_port_2->text().toInt();
    if(!socketState)
    {
        tcpSocket->connectToHost(QHostAddress(ip),port);
        if(!tcpSocket->waitForConnected(30000))
        {
            qDebug()<<"连接失败";
            return;
        }
        else
        {
            ui->pushButton_listen->setText("断开连接");
            socketState = true;
        }
    }
    else
    {
        tcpSocket->close();
        ui->pushButton_listen->setText("开始连接");
        socketState = false;
    }

}
