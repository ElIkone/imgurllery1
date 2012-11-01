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
#include "wmain.h"
#include "ui_wmain.h"

WMain::WMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WMain)
{
    ui->setupUi(this);

    netAccessMan = new QNetworkAccessManager(this);

    connect(netAccessMan, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));

    xmlContainer= new QTextEdit(0);
    downloadList = new QStringList();


download("http://imgur.com/r/aww.xml");
}

WMain::~WMain()
{
    delete downloadList;
    delete xmlContainer;
    delete ui;
}

void WMain::download(QString item){
    qDebug() << "Downloading: " << item;
    QUrl url(item);
    QNetworkRequest request(url);
    netAccessMan->get(request);
}

void WMain::downloadFinished(QNetworkReply *reply)
{
    qDebug() << "Dowload has finished";

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QVariant redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if (redir.isValid())
    {
        QUrl url = redir.toUrl();
        qDebug() << "must go to:" << url;

        if (url.isRelative())
        {
            url.setScheme(reply->url().scheme());
            url.setEncodedHost(reply->url().encodedHost());
        }

        QNetworkRequest req(url);
        netAccessMan->get(req);
        reply->deleteLater();
        return;
    }
    qDebug() << "ContentType:" << reply->header(QNetworkRequest::ContentTypeHeader).toString();

    downloadedItem = reply->readAll();
    if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("image")){
        QPixmap pixmap;
        pixmap.loadFromData(downloadedItem);

        //pixmap.save("test.jpg");
        //ui->statusBar->showMessage(reply->url().path());
        pixmap.save(reply->url().path().mid(1));
        //pixmap=pixmap.scaled(720,1280,Qt::KeepAspectRatio);
        ui->lblMain->setPixmap(pixmap);
    }else if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("xml")){
        qDebug() << "GOT XML";
        QString xml=downloadedItem;

        while (xml.indexOf("<hash>")!=-1){
            int first=xml.indexOf("<hash>")+6;
            int last=xml.indexOf("</hash>")-first;
            downloadList->append(xml.mid(first,last));
            xml=xml.mid(first+last+7);
        }

        while (!downloadList->isEmpty()){
            download("http://i.imgur.com/"+downloadList->first()+".jpg");
            downloadList->removeFirst();
            //sleep (5)
        }

    }

    reply->deleteLater();
}
