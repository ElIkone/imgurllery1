/*******************************************************************************
**                                                                            **
**                                                                            **
**                                 By Ikone                                   **
**                            %YEAR%                                          **
**                                                                            **
**                                                                            **
**                                                                            **
**                                                                            **
*******************************************************************************/
#ifndef WMAIN_H
#define WMAIN_H

#include <QMainWindow>
#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QtXml>

namespace Ui {
    class WMain;
}

class WMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WMain(QWidget *parent = 0);
    ~WMain();

private:
    Ui::WMain *ui;
    QNetworkAccessManager *netAccessMan;
    QByteArray downloadedItem;
    QTextEdit *xmlContainer;
    QStringList *downloadList;

private slots:
    void download(QString item);
    void downloadFinished(QNetworkReply *reply);
};

#endif // WMAIN_H
