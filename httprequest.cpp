/* Nome: Alessandro
 * Cognome: Giussani
 * Progetto: btc_eur_exchange
 * Descrizione: Realizzare un'applicazione desktop (usando plain Qt-Gui, non QML) in cui si mostra il valore attuale del cambio bitcoin/euro aggiornandolo ogni 10 secondi
 * Data pubblicazione: 29/10/2017
 *
 * httprequest.cpp
*/
#include "httprequest.h"
#include "ui_httprequest.h"
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>

HttpRequest::HttpRequest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttpRequest)
{
    ui->setupUi(this);

    startRequest(); //Prima richiesta

    //Nuovo oggetto Qtimer
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(startRequest()));
    timer->start(TIMER);
}

HttpRequest::~HttpRequest()
{
    delete ui;
    delete manager;
}

void HttpRequest::endRequest(QNetworkReply *reply) {
    reply->deleteLater();

    QString btc = NULL;
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute); //Inserisco in una variabile lo status della richiesta

    if(statusCode.toInt() == 200 || reply->error() == QNetworkReply::NoError){
        //Connessione stabilita, nessun errore trovato
        QByteArray data = reply->readAll(); //Leggo dati all'interno della risposta
        if (!data.isEmpty()){
            //dati valorizzati
            QJsonParseError j_err; //Classe QT che segnala se sono stati trovati errori durante il parsing Json
            QJsonDocument j_doc = QJsonDocument::fromJson(data, &j_err); //Leggo Json
            if (j_err.error == 0){
                //Nessun errore trovato a leggere Json
                QJsonObject j_obj = j_doc.object(); //Incapsulo Json
                QJsonValue val = j_obj.value(KEYTOSRC); //Cerco la key "last"
                if (!val.isUndefined()){
                    //Key trovata
                    btc = val.toString(); //Inserisco valore in una variabile QString
                }
            }
        }
    }
    if (btc != NULL)
        //btc valorizzata
        ui->Output->setText(btc); //Nell'oggetto Output del form httprequest.ui, stampo il valore di btc
    else
        //btc non valorizzata: Connessione non stabilita or errore json or chiave non trovata
        ui->Output->setText("none"); //Per praticità stampo il valore "none"

    return; //Libero la memoria utilizzata da reply
}

void HttpRequest::startRequest(){

    //Nuovo oggetto manager
    manager = new QNetworkAccessManager();
    request.setUrl(QUrl(APIURL)); //Imposto l'url dell'API
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(endRequest(QNetworkReply*))); //conn
    manager->get(request); //Metodo GET
}
