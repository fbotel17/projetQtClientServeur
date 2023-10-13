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
    ui->reponseServ->setText("Réponse du serveur : " + str);
}

void ClientQt::onSendCelClicked(){

    QString num = ui->numCapteur->text();

    if (num.isEmpty()) {
        ui->messErreur->show();

        ui->messErreur->setText("Erreur, la zone de texte est vide.");
    } else {

        bool ok;
        int intValue = num.toInt(&ok);

        if (ok) {
            if (intValue > 99 || intValue<0) {
                ui->messErreur->show();

                ui->messErreur->setText("Erreur, le nombre de capteur n'est pas compris entre 0 et 99.");
            } else {
                ui->messErreur->hide();
                QString cel = "Td";

                if (intValue < 10) {
                    num = QString::number(intValue, 10).rightJustified(2, '0');
                }

                QByteArray data = cel.toUtf8();
                QByteArray data2 = num.toUtf8();
                socket->write(data + data2 + "?");
            }
        } else {
            ui->messErreur->show();

            ui->messErreur->setText("Erreur, la zone de texte ne contient pas un entier valide.");
        }
    }
}

void ClientQt::onSendFarClicked(){
    QString num = ui->numCapteur->text();

    if (num.isEmpty()) {
        ui->messErreur->show();

        ui->messErreur->setText("Erreur, la zone de texte est vide.");
    } else {
        bool ok;

        int intValue = num.toInt(&ok);

        if (ok) {
            if (intValue > 99 || intValue<0) {
                ui->messErreur->show();

                ui->messErreur->setText("Erreur, le nombre de capteur n'est pas compris entre 0 et 99.");
            } else {
                ui->messErreur->hide();
                QString far = "Tf";


                if (intValue < 10) {
                    num = QString::number(intValue, 10).rightJustified(2, '0');
                }

                QByteArray data = far.toUtf8();
                QByteArray data2 = num.toUtf8();

                socket->write(data+data2+"?");
            }


        } else {
            ui->messErreur->show();

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
            if (intValue > 99 || intValue<0) {
                ui->messErreur->show();

                ui->messErreur->setText("Erreur, le nombre de capteur n'est pas compris entre 0 et 99.");
            } else {
                ui->messErreur->hide();
                QString hyg = "Hr";


                if (intValue < 10) {
                    num = QString::number(intValue, 10).rightJustified(2, '0');
                }
                QByteArray data = hyg.toUtf8();
                QByteArray data2 = num.toUtf8();
                socket->write(data+data2+"?");
            }


        } else {
            ui->messErreur->setText("Erreur, la zone de texte ne contient pas un entier valide.");

        }
    }


}

