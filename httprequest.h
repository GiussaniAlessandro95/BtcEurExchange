/* Nome: Alessandro
 * Cognome: Giussani
 * Progetto: btc_eur_exchange
 * Descrizione: Realizzare un'applicazione desktop (usando plain Qt-Gui, non QML) in cui si mostra il valore attuale del cambio bitcoin/euro aggiornandolo ogni 10 secondi
 * Data pubblicazione: 29/10/2017
 *
 * httprequest.h
*/
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#define APIURL "https://www.bitstamp.net/api/v2/ticker/btceur/"
#define TIMER 10000
#define KEYTOSRC "last"

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTimer>

namespace Ui {
class HttpRequest;
}

class HttpRequest : public QMainWindow
{
    Q_OBJECT

public:
    explicit HttpRequest(QWidget *parent = 0);
    ~HttpRequest();

private:
    Ui::HttpRequest *ui;
    QNetworkAccessManager *manager; //Manager
    QNetworkRequest request; //Richiesta
    QTimer *timer; //Timer

private slots:
    void startRequest(); //Inizio richiesta
    void endRequest(QNetworkReply *reply); //Fine richiesta + risposta
};

#endif // HTTPREQUEST_H
