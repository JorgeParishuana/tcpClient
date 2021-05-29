#include "tcpclient.h"
#include "ui_tcpclient.h"

TCPClient::TCPClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCPClient)
{
    ui->setupUi(this);
    qTcpSocket = new QTcpSocket(this);
    in.setDevice(qTcpSocket);

    //ConnectBotones
    connect(ui->btn_salir,&QAbstractButton::clicked,this,&QWidget::close);
        //Send
    connect(ui->btn_send,&QAbstractButton::clicked,this,&TCPClient::requestMessage);

    //Connect Listo para leer => show error
    connect(qTcpSocket,&QIODevice::readyRead,this,&TCPClient::readMessage);
    //connect(qTcpSocket,&QAbstractSocket::error,this,&TCPClient::showError);
}

TCPClient::~TCPClient()
{
    delete ui;
}
void TCPClient::requestMessage(){
    qInfo()<<"request Message";
    QString ipAddress = ui->ln_ip->text();
    QString port = ui->ln_port->text();
    qTcpSocket->connectToHost(ipAddress,port.toInt());
    qInfo()<<"ip: "+ipAddress + ", port : " + port;
}

void TCPClient::readMessage(){
    qInfo()<<"readMessage";
    in.startTransaction();
    QString message;
    in>>message;
    if(!in.commitTransaction()){
        qInfo()<<"Error al captarString dataString error";
        return;
    }
    ui->lbl_message->setText(message);
}

void TCPClient::showError(QAbstractSocket::SocketError socketError){
    qInfo()<<"show error";
    switch(socketError) {
        case 0:
            qInfo()<<"Conexión rechazada";
            break;
        case 1:
            qInfo()<<"El servidor cerro la conexión";
        break;
        default:
            qInfo()<<"Error no detectado :)";
    }
}
