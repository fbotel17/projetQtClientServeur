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
    ui->reponseServ->setText("Réponse du serveur : " + str);
}

void ClientQt::onSendCelClicked(){

    QString num = ui->numCapteur->text();

    if (num.isEmpty()) {

        ui->messErreur->setText("Erreur, la zone de texte est vide.");
    } else {
        bool ok;

        int intValue = num.toInt(&ok);

        if (ok) {
            ui->messErreur->hide();
            QString cel = "Td";
            QByteArray data = cel.toUtf8();
            QByteArray data2 = num.toUtf8();


            socket->write(data+data2);
        } else {
            ui->messErreur->setText("Erreur, la zone de texte ne contient pas un entier valide.");

        }
    }


}

void ClientQt::onSendFarClicked(){
    QString num = ui->numCapteur->text();

    if (num.isEmpty()) {

        ui->messErreur->setText("Erreur, la zone de texte est vide.");
    } else {
        bool ok;

        int intValue = num.toInt(&ok);

        if (ok) {
            QString far = "Tf";
            QByteArray data = far.toUtf8();
            QByteArray data2 = num.toUtf8();

            socket->write(data+data2);


        } else {
            ui->messErreur->setText("Erreur, la zone de texte ne contient pas un entier valide.");

        }
    }

}

void ClientQt::onSendHygClicked(){
    QString num = ui->numCapteur->text();

    if (num.isEmpty()) {

        ui->messErreur->setText("Erreur, la zone de texte est vide.");
    } else {
        bool ok;

        int intValue = num.toInt(&ok);

        if (ok) {
            QString hyg = "Hr";
            QByteArray data = hyg.toUtf8();
            QByteArray data2 = num.toUtf8();
            socket->write(data+data2);


        } else {
            ui->messErreur->setText("Erreur, la zone de texte ne contient pas un entier valide.");

        }
    }


}

