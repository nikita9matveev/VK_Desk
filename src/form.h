#ifndef FORM_H
#define FORM_H

#include <QWebView>
#include <QWebPage>

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>
#include <QDateTime>

#include <QPointer>
#include <QFile>
#include "vkconnect.h"
#include <crypt.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget* parent = 0, QSharedPointer<vkConnect> _vk = QSharedPointer<vkConnect>());
    ~Form();

    //методы нужны для получения родных размеров окна, а не присвоенных после инициализации
    int getW();
    int getH();

public slots:
    void ready();
private slots:

    void on_b_sent_clicked();

    void on_progressBar_valueChanged(int value);

    void checkNewMsg();

    void on_home_clicked();

    void on_l_contacts_itemClicked(QListWidgetItem* item);

    void on_dialogButton_clicked();

    void on_dialogButton_2_clicked();

    void on_profileButton_clicked();

    void on_wallButton_clicked();

private:
    //QListWidgetItem * serchById(const QString & id);
    //void profile(QString from, QString _id, int status, QString lastActivity);

    Ui::Form* ui;
    QSharedPointer<vkConnect> vk;

    int w;
    int h;
    QJsonObject friends;
    QJsonObject lastMessages;
    QString lastMsgID;

    QListWidgetItem* currentItem;
    QString from;
    QString currentDiaolg;
    QString currentID;
    int status;
    QString line;

    ///базовый интерфейс
    QString basicHTML;
    QString CSS;   

    ///интерфейс чата
    QString chatOther;
    QString chatSelf;
    QString chatMenu;
    QString chatHTML;
    QString chatMiddle;
    QString chatEmpty;

    ///интерфейс профиля
    QString profileHTML;
    QString profileMiddle;
    QString profileMenu;
    QString profilePhoto;
    QString profileInfo;

    ///интерфейс стены
    QString wallHTML;
    QString wallMiddle;
    QString wallMenu;
    QString wallPost;
    QString wallRepost;
    QString wallPostFinal;
    QString wallRepostFinal;
    QString wallEmpty;

    QPointer<QTimer> timer;

    //QString photoOther;
    //crypt* cr;


};

#endif // FORM_H
