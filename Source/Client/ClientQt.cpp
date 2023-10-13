#include "ClientQt.h"
#include "ui_ClientQt.h"

ClientQt::ClientQt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientQt)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));

}

ClientQt::~ClientQt()
{
    delete ui;
}

void ClientQt::onConnectButtonClicked(){
    QString ip = ui->IPLineEdit->text();
    QString port = ui->portLineEdit->text();

    bool ok;
    int portAsInt = port.toInt(&ok);
    if(ok){
        socket->connectToHost(ip, portAsInt);
    }

}

void ClientQt::onDisconnectButtonClicked(){

    socket->disconnectFromHost();

}

void ClientQt::onSocketConnected(){
    ui->connectionStatusLabel->setText("Status connexion : Connecté");
}

void ClientQt::onSocketDisconnected(){
    ui->connectionStatusLabel->setText("Status connexion : Déconnecté");
}

void ClientQt::onSendMessageButtonClicked(){
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QString message = ui->contenuMess->toPlainText();
        QByteArray data = message.toUtf8(); // Convertir le message en QByteArray
        socket->write(data + "\n");
    }
}

void ClientQt::onSocketReadyRead(){
    QByteArray data = socket->read(socket->bytesAvailable());
    QString str(data);
    ui->connectionStatusLabel->setText("Status connexion : Message reçu : " + str);
}

