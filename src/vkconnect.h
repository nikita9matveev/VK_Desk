#ifndef VKCONNECT_H
#define VKCONNECT_H

#include <QtDebug>

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

#include <QEventLoop>
#include "lib/QJsonObject.h"
#include "lib/QJsonValue.h"
#include "lib/QJsonDocument.h"
#include "lib/QJsonArray.h"

#include <QSharedPointer>
#include <QPointer>
#include <QLabel>

const int msgShowCount = 200;
const int postShowCount = 20;

class vkConnect: public QObject
{
    Q_OBJECT
public:
    explicit vkConnect();
    ~vkConnect();

    ///данные для подключения установлены и актуальны?
    bool isLogin();
    ///есть новые сообщения?
    bool hasNewMsgs(const QJsonObject &obj);
    ///возвращенный url корректен?
    bool isCorrectLogin(const QString &str);
    ///установить статус пользователя "online"
    bool setOnline();

    int setUsername(QString name);
    int setManager(QPointer<QNetworkAccessManager> man);
    int sendMsg(const QString& _msg, const QString &_id);

    ///получить всю необходимую инфу о профиле пользователя
    QJsonObject getUserPage(QString id);
    ///получить ID текущего пользователя
    int myID();
    ///получить имя текущего пользователя
    QString myName();
    ///получить id пользователя
    QString getUserId();
    ///получить ссылку на фото
    QString getUserPhoto50();
    ///получить друзей онлайн
    QJsonObject friendsOnline();
    ///получить список друзей
    QJsonObject friendList(QString _id);
    ///получить последние 10 сообщений
    QJsonObject lastMessages(QString last_id = "");
    ///получить последние 50 сообщений диалога
    QJsonObject dialogHistory(const QString& user_id);

    ///статистика приложения
    void stats();
    ///последняя активность пользователя(онлайн)
    QJsonObject getLastActivity(int id);
    ///отметить сообщения как прочитанные
    void markAsRead(const QJsonArray &message_ids);
    ///получить информацию о пользователе и забить его имя в лейбл
    void getUserInfo(QString _id, QLabel *_label);
    ///получить ИМЯ ФАМИЛИЮ пользователя
    QJsonObject getUser(const QString &name);
    ///получить инфу о пользователях по IDs
    QJsonArray getUsers(const QJsonArray& _ids);
    ///получить название группы по id
    QJsonArray getGroupsInfo(QString group_ids);
    ///получить стену пользователя
    QJsonArray getUserWall(QString _id);
    ///получить автора записи на стене
    QJsonArray getPostAuthors(QString _ids);
signals:
    ///сообщить об ошибке
    void replyError(const QString& str);

public slots:
    void acceptLogin(QUrl* query);

private:
    bool connected;
    QPointer<QNetworkAccessManager> manager;
    QString apiProtocol;
    QString version;
    QString expires_in;
    QString appId;
    QString id;
    QString username;
    QString token;
    QString photo_50;

    ///получить QJsonObject из строки
    QJsonObject ObjectFromString(const QString& in);
    ///отправить запрос и получить ответ. in -  url
    QJsonObject sentRequest(const QString& in);
    ///ответ нас устраивает?
    bool isReplyCorrect(const QJsonObject& obj);

};

#endif // VKCONNECT_H
