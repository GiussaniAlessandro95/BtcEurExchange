/* Nome: Alessandro
 * Cognome: Giussani
 * Progetto: btc_eur_exchange
 * Descrizione: Realizzare un'applicazione desktop (usando plain Qt-Gui, non QML) in cui si mostra il valore attuale del cambio bitcoin/euro aggiornandolo ogni 10 secondi
 * Data pubblicazione: 29/10/2017
 *
 * main.cpp
*/
#include "httprequest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HttpRequest w;

    w.show();
    return a.exec();
}
