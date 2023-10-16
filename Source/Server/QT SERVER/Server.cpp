#include "Server.h"

Server::Server(QObject* parent)
    : QObject(parent)
{
    server = new QTcpServer(this);
    QObject::connect(server, SIGNAL(newConnection()), this, SLOT(onServerNewConnection()));
    server->listen(QHostAddress::AnyIPv4, 6969);

}

void Server::onServerNewConnection()
{
    qDebug() << "Un client s'est connecte !";
    QTcpSocket* client = server->nextPendingConnection();
    QObject::connect(client, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QObject::connect(client, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
}

void Server::onClientDisconnected()
{
    QTcpSocket* obj = qobject_cast<QTcpSocket*>(sender());
    QObject::disconnect(obj, SIGNAL(readyRead()), this, SLOT(onClientReadyRead()));
    QObject::disconnect(obj, SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
    obj->deleteLater();
}

void Server::onClientReadyRead()
{

    QTcpSocket* client = qobject_cast<QTcpSocket*>(sender());

    // Si il y a un client.
    if (client) {
        // On lit tout son message.
        QByteArray requestData = client->readAll();
        // Puis on le convertie en QString pour le traiter.
        QString request = QString::fromUtf8(requestData).trimmed();
        QString response;



        // Permet de définir 3 expressions régulières qui sont les 3 requêtes envoyés par le client.
        QRegularExpression ExpTd("^Td\\d{2}\\?$");
        // Permet de comparer l'expression régulière avec la requête du client.
        QRegularExpressionMatch Td = ExpTd.match(request);

        QRegularExpression ExpTf("^Tf\\d{2}\\?$");
        QRegularExpressionMatch Tf = ExpTf.match(request);

        QRegularExpression ExpHr("^Hr\\d{2}\\?$");
        QRegularExpressionMatch Hr = ExpHr.match(request);


        // Si la requête du client corespond à une des trois expressions.

        if (Td.hasMatch() || Tf.hasMatch() || Hr.hasMatch()) {
            QString sensorNumber = request.mid(2, 2);

            // Générez la température aléatoire en degrés Celsius de -20.0 degré à 40.0 degrès.
            srand(time(NULL));
            // Générer des nombres aléatoires pour chaque unité
            float centiemes = rand() % 10;     // Entre 0 et 9
            float diziemes = rand() % 10;      // Entre 0 et 9
            float dizaines = rand() % 6;        // Entre 0 et 6
            float unites = rand() % 10;         // Entre 0 et 9

            // Additionner les unités et diviser par 100 pour obtenir la température
            double temperatureCelsius = unites + dizaines * 10 + diziemes / 10 + centiemes / 100;
          

            // Ajuster la plage de -20.00 à 40.00
            temperatureCelsius = -20.00 + temperatureCelsius;
            

            // Convertissez la température en degrés Fahrenheit
            float temperatureFahrenheit = (temperatureCelsius * 9 / 5) + 32;

            // Si on demande la température en degré Celcius.
            if (request.startsWith("Td")) {
                if (temperatureCelsius >= 0.00) {
                    response = QString("Td%1,+%2").arg(sensorNumber).arg(temperatureCelsius, 0, 'f', 2);
                }
                else {
                    response = QString("Td%1,%2").arg(sensorNumber).arg(temperatureCelsius, 0, 'f', 2);
                }
            }
            // Si on demande la température en degré Farhenheit.
            else if (request.startsWith("Tf")) {
                if (temperatureFahrenheit >= 0.00) {
                    response = QString("Tf%1,%2").arg(sensorNumber).arg(temperatureFahrenheit, 0, 'f', 2);
                }
                else {
                    response = QString("Tf%1,%2").arg(sensorNumber).arg(temperatureFahrenheit, 0, 'f', 2);
                }
                
            }
            // Si on demande l'hydromédtrie.
            else if (request.startsWith("Hr")) {
                // Simulez l'hygrométrie (comprise entre 00.0 et 99.9)
                float humidity = rand() % 1000;
                humidity /= 10.00;
                response = QString("Hr%1,%2").arg(sensorNumber).arg(humidity, 0, 'f', 1);
            }
        }
        else {
            response = "Commande non reconnue";
        }

        // On envoie la réponse au client et à notre console.
        client->write(response.toUtf8());
        qDebug() << response;
    }
}

Server::~Server() {
    delete(server);
}

