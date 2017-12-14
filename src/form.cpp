#include "form.h"
#include "ui_form.h"
#include "QDebug"
#include <QRadioButton>
//#include <qmath.h>

Form::Form(QWidget *parent, QSharedPointer<vkConnect> _vk) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    vk = _vk;
    w = this->width();
    h = this->height();

    ui->t_edit->setPB(ui->b_sent);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);

    QPixmap logo(":/logo/logo_form.png");
    ui->label_2->setPixmap(logo);

    QPixmap home(":/home.png");
    QSize homeSize(81, 81);
    ui->home->setIcon(home);
    ui->home->setIconSize(homeSize);

    QPixmap send(":/send.png");
    QSize sendSize(30, 30);
    ui->b_sent->setIcon(send);
    ui->b_sent->setIconSize(sendSize);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(checkNewMsg()));

    //--------BASIC---------
    QFile fbhtml(":/basichtml.html");
    if (!fbhtml.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    QByteArray barray = fbhtml.readAll();
    basicHTML = QString::fromUtf8(barray);
    fbhtml.close();

    //------STYLE--------
    QFile fStyle(":/style.css");
    if (!fStyle.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fStyle.readAll();
    CSS = QString::fromUtf8(barray);
    fStyle.close();

    //------CHAT-MENU-------
    QFile fMenu(":/chatMenu.html");
    if (!fMenu.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fMenu.readAll();
    chatMenu = QString::fromUtf8(barray);
    fMenu.close();

    //-----CHAT-OTHER-------
    QFile fOther(":/chatOther.html");                               //сообщения собеседника
    if (!fOther.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fOther.readAll();
    chatOther = QString::fromUtf8(barray);
    fOther.close();

    //------CHAT-SELF-------
    QFile fSelf(":/chatSelf.html");                                 //мои сообщения
    if (!fSelf.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fSelf.readAll();
    chatSelf = QString::fromUtf8(barray);
    fSelf.close();

    //-------PageMenu--------
    QFile fprofileMenu(":/profileMenu.html");                                 //запись на стене
    if (!fprofileMenu.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fprofileMenu.readAll();
    profileMenu = QString::fromUtf8(barray);
    //qDebug() << profileMenu << "profileMenu";
    fprofileMenu.close();

    //-------PagePhoto-------
    QFile fPagePhoto(":/profilePhoto.html");                                 //фото профиля
    if (!fPagePhoto.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fPagePhoto.readAll();
    profilePhoto = QString::fromUtf8(barray);
    fPagePhoto.close();

    //-------pageInfo-------
    QFile fPageInfo(":/profileInfo.html");                                 //инфа+контакты профиля
    if (!fPageInfo.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fPageInfo.readAll();
    profileInfo = QString::fromUtf8(barray);
    fPageInfo.close();

    //-------wallMenu-------
    QFile fwallMenu(":/wallMenu.html");                                 //запись на стене
    if (!fwallMenu.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fwallMenu.readAll();
    wallMenu = QString::fromUtf8(barray);
    //qDebug() << wallMenu << "wallMenu";
    fwallMenu.close();

    //-------wallPost-------
    QFile fwallPost(":/wallPost.html");                                 //запись на стене
    if (!fwallPost.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fwallPost.readAll();
    wallPost = QString::fromUtf8(barray);
    fwallPost.close();

    //-------wallRepost-------
    QFile fwallRepost(":/wallRepost.html");                                 //репост записи на стене
    if (!fwallRepost.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fwallRepost.readAll();
    wallRepost = QString::fromUtf8(barray);
    fwallRepost.close();

    QFile fwallEmpty(":/wallEmpty.html");                                 //репост записи на стене
    if (!fwallEmpty.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fwallEmpty.readAll();
    wallEmpty = QString::fromUtf8(barray);
    fwallEmpty.close();

    QFile fchatEmpty(":/chatEmpty.html");                                 //репост записи на стене
    if (!fchatEmpty.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
    barray = fchatEmpty.readAll();
    chatEmpty = QString::fromUtf8(barray);
    fchatEmpty.close();

    //-------CRYPT-------
    //cr = new crypt();
}


Form::~Form()
{
    delete ui;
    delete timer;
    //delete cr;
}

int Form::getW(){
    return w;
}

int Form::getH(){
    return h;
}

void Form::ready()
{
    ui->chat->hide();
    ui->page->hide();
    ui->wall->hide();
    ui->home->hide();
    ui->newMes->hide();

    if(!vk->isLogin()) return;  //проверка на вход
    friends = vk->friendList(vk->getUserId());  //загрузка друзей

    int progress = 0;
    int count = friends["count"].toInt();  //кол-во друзей
    ui->progressBar->setMaximum(count);

    QJsonArray friendIds = friends["items"].toArray();  //IDs друзей
    QJsonArray friendArray = vk->getUsers(friendIds);   //расширенная инфа о друзьях
    for(int i = 0; i < count; i++){        //загрузка инфы о друзьях в список контактов
        QListWidgetItem* frItem = new QListWidgetItem; //имя, фамилия
        QString FLName = friendArray[i].toObject()["first_name"].toString() + " " +friendArray[i].toObject()["last_name"].toString();
        frItem->setData(Qt::DisplayRole, FLName);
        if (friendArray[i].toObject()["online"].toInt())
            frItem->setForeground(Qt::green);
        ui->l_contacts->addItem(frItem); //добавление в список контактов ФИ

        QString statusTip = QString::number(friendArray[i].toObject()["id"].toInt()); //ID пользователя(статус)
        ui->l_contacts->item(i)->setStatusTip(statusTip); //добавление в список контактов ID
        progress++;
        ui->progressBar->setValue(progress); //отображение загрузки
    }
    //вид - загрузка диалога(последние сообщения и отправитель)
    lastMessages = vk->lastMessages();
    lastMsgID = QString::number(lastMessages["response"].toObject()["items"].toArray()[0].toObject()["id"].toInt());
    vk->stats();
    timer->start(4000);     //каждые 4 секунды сигнал таймаут - проверка на новые сообщения
    qDebug() << "ready";

    emit on_home_clicked();
}

void Form::on_progressBar_valueChanged(int value)
{
    if(value == ui->progressBar->maximum()) {
        ui->progressBar->hide();   //setVisible(false)
        ui->home->show();
    }
}

void Form::on_b_sent_clicked()
{
    QString other_id = currentItem->statusTip(); //статус контакта(элемента списка)
    QString msg = ui->t_edit->toPlainText();    //текст сообщения
    if(msg.isEmpty()) return;
    QString msgView = msg;
//    try{
//        if(ui->chb_encode->checkState() == Qt::Checked){  //если установлена галочка шифрования
//            std::string str = crypt::genKey(other_id);
//            std::string encrStr = cr->myCrypt(msg.toStdString(), str, str, true);
//            msg = QString("--dec") + QString(encrStr.c_str());
//            //std::string decrStr = cr->myCrypt(encrStr, str, str, false);    //decoding str
//            //qDebug() << QString(decrStr.c_str());                           //test

//        }
//    }
//    catch(const std::exception &ex){
//        qDebug() << QString(ex.what());  //пояснение
//    }
//    catch(...){
//        qDebug() << "error with encode";
//    }

    vk->sendMsg(msg, other_id);  //отправка сообщения

    ui->t_edit->clear(); //очистка текст филд

    int index = chatHTML.indexOf("</ol>");  //поиск места для вставки интерфейса
    ui->chat->setHTML(chatHTML.insert(index, chatSelf.arg(msgView, QDateTime(QDateTime::currentDateTime()).toString(), vk->getUserPhoto50(), "")));  //вставка в эту позицию текста сообщения, времени, фото
}

void Form::checkNewMsg()
{
    ui->newMes->hide();
    lastMessages = vk->lastMessages(lastMsgID);
    if(!vk->hasNewMsgs(lastMessages))
        return;
    //корректность json ответа проверяется в классе vkConnect
    QJsonArray array = lastMessages["response"].toObject()["items"].toArray(); //записываем сообщения и инфу о них
    lastMsgID = QString::number(array[0].toObject()["id"].toInt());

    /// добавить QString newMes = messages.getbyid(lastMsgID); сделать лейбл, в него выводить (текст сообщения["body"], от кого["user_id"], время)


    if(currentItem != nullptr && currentItem->text() == currentDiaolg){
        bool my;
        for(int i = 0; i < array.size(); i++) {
                if(QString::number(array[i].toObject()["user_id"].toInt()) == currentItem->statusTip()) { //статус контакта(элемента списка)
                    my = true;
                }
        }
        if(my) {
            //vk->markAsRead(array);
            on_dialogButton_clicked();
            //qDebug()<<"New message||| in";
        }
        ui->t_edit->setFocus();  //фокус в поле ввода
    }
    else {
        ui->newMes->show();
        qDebug()<< "Vam prishlo novoe soobshchenie! out" << endl;  //когда не в диалоге
    }
    return;
}

//QListWidgetItem * Form::serchById(const QString &id)
//{
//    int number = ui->l_contacts->count();
//    for(int i{0}; i < number; i++){
//        if(ui->l_contacts->item(i)->statusTip() == id) return ui->l_contacts->item(i);
//    }
//    return Q_NULLPTR;
//}

void Form::on_l_contacts_itemClicked(QListWidgetItem *item)
{
    ui->chat->hide();
    ui->wall->hide();
    ui->page->show();
    ui->dialogButton->show();

    currentItem = item;
    from = item->text();
    status = vk->getLastActivity(ui->l_contacts->currentItem()->statusTip().toInt())["online"].toInt();
    currentID = ui->l_contacts->currentItem()->statusTip();

    currentDiaolg.clear(); //очистка стрингов
    profileMiddle.clear();

    QDateTime timeActive;
    QString lastActivity = timeActive.fromTime_t(vk->getLastActivity(ui->l_contacts->currentItem()->statusTip().toInt())["time"].toInt()).toString(); //последняя активность

    if (status)
        line = "online";
    else line = "Last activity: " + lastActivity;

    QJsonObject page = vk->getUserPage(currentID);

    int s = page["sex"].toInt();
    QString sex;
    if (2 == s)
        sex = QString("мужской");
    if (1 == s)
        sex = QString("женский");
    if (!s)
        sex = QString("не указано");
    QString place;
    if(!page["country"].toObject()["title"].toString().isEmpty())
        place = page["country"].toObject()["title"].toString() + ", " + page["city"].toObject()["title"].toString() + "<br>";
    else
        place = "";
    QString sp;
    switch (page["relation"].toInt()) {
    case 1:
        sp = QString("Не в браке");
    case 2:
        sp = QString("В отношениях");
    case 3:
        sp = QString("Помолвлен(а)");
    case 4:
        sp = QString("В браке");
    case 5:
        sp = QString("Всё сложно");
    case 6:
        sp = QString("в активном поиске");
    case 7:
        sp = QString("Влюблен(а)");
    case 8:
        sp = QString("В гражданском браке");
    case 0:
        sp = QString("не указано");
        break;
    default:
        break;
    }
    QString univer;
    if(!page["university_name"].toString().isEmpty())
        univer = page["university_name"].toString() + ", " + page["faculty_name"].toString() + " " + page["graduation"].toInt();
    else
        univer = "";
    profileMiddle += profilePhoto.arg(page["photo_200"].toString());
    profileMiddle += profileInfo.arg(sex, page["bdate"].toString().isEmpty() ? QString("Не указано") : page["bdate"].toString(),
            sp, page["domain"].toString(), line, place, univer)
            .arg(page["mobile_phone"].toString().isEmpty() ? QString("Не указано") : page["mobile_phone"].toString(),
            page["home_phone"].toString().isEmpty() ? QString("Не указано") : page["home_phone"].toString(),
            page["skype"].toString().isEmpty() ? QString("Не указано") : page["skype"].toString(),
            page["instagram"].toString().isEmpty() ? QString("Не указано") : page["instagram"].toString(),
            page["facebook"].toString().isEmpty() ? QString("Не указано") : page["facebook"].toString(),
            page["twitter"].toString().isEmpty() ? QString("Не указано") : page["twitter"].toString(),
            page["site"].toString().isEmpty() ? QString("Не указано") : page["site"].toString(), page["status"].toString().isEmpty() ? QString("") : "Статус:\n" + page["status"].toString());
    qDebug() << "Статус:\n" + page["status"].toString();

    profileHTML = basicHTML.arg(CSS).arg(profileMenu.arg(from, line, profileMiddle));
    ui->page->setHTML(profileHTML);
}

void Form::on_home_clicked()
{
    ui->dialogButton->hide();
    ui->chat->hide();
    ui->wall->hide();
    ui->page->show();

    currentDiaolg.clear(); //очистка стрингов
    profileMiddle.clear();
    //chatMiddle.clear();

    currentItem = 0;
    currentID = vk->getUserId();
    from = vk->myName();
    status = 1;
    line = "online";

    QJsonObject page = vk->getUserPage(currentID);

    int s = page["sex"].toInt();
    QString sex;
    if (2 == s)
        sex = QString("мужской");
    if (1 == s)
        sex = QString("женский");
    if (!s)
        sex = QString("не указано");
    QString place;
    if(!page["country"].toObject()["title"].toString().isEmpty())
        place = page["country"].toObject()["title"].toString() + ", " + page["city"].toObject()["title"].toString() + "<br>";
    else
        place = "";

    QString sp;
    int relation = page["relation"].toInt();

    switch (relation) {
    case 1:
        sp = QString("Не в браке");
    case 2:
        sp = QString("В отношениях");
    case 3:
        sp = QString("Помолвлен(а)");
    case 4:
        sp = QString("В браке");
    case 5:
        sp = QString("Всё сложно");
    case 6:
        sp = QString("в активном поиске");
    case 7:
        sp = QString("Влюблен(а)");
    case 8:
        sp = QString("В гражданском браке");
    case 0:
        sp = QString("не указано");
        break;
    default:
        break;
    }

    QString univer;
    if(!page["university_name"].toString().isEmpty())
        univer = page["university_name"].toString() + ", " + page["faculty_name"].toString() + " " + page["graduation"].toInt();
    else
        univer = "";

    profileMiddle += profilePhoto.arg(page["photo_200"].toString());

    profileMiddle += profileInfo.arg(sex, page["bdate"].toString().isEmpty() ? QString("Не указано") : page["bdate"].toString(),
            sp, page["domain"].toString(), line, place, univer)
            .arg(page["mobile_phone"].toString().isEmpty() ? QString("Не указано") : page["mobile_phone"].toString(),
            page["home_phone"].toString().isEmpty() ? QString("Не указано") : page["home_phone"].toString(),
            page["skype"].toString().isEmpty() ? QString("Не указано") : page["skype"].toString(),
            page["instagram"].toString().isEmpty() ? QString("Не указано") : page["instagram"].toString(),
            page["facebook"].toString().isEmpty() ? QString("Не указано") : page["facebook"].toString(),
            page["twitter"].toString().isEmpty() ? QString("Не указано") : page["twitter"].toString(),
            page["site"].toString().isEmpty() ? QString("Не указано") : page["site"].toString(), page["status"].toString().isEmpty() ? QString("") : "Статус:\n" + page["status"].toString());
            qDebug() << "Статус:\n" + page["status"].toString();
    profileHTML = basicHTML.arg(CSS, profileMenu.arg(from, line, profileMiddle));
    ui->page->setHTML(profileHTML);
}

void Form::on_dialogButton_2_clicked()
{
    emit on_dialogButton_clicked();
}

void Form::on_profileButton_clicked()
{
    if (currentItem)
        emit on_l_contacts_itemClicked(currentItem);
    else
        emit on_home_clicked();
}

void Form::on_dialogButton_clicked()
{
        ui->page->hide();
        ui->wall->hide();
        ui->chat->show();
        currentDiaolg = currentItem->text();

        if(!ui->t_edit->isEnabled() && !ui->b_sent->isEnabled()){ //если не активны поле ввода, кнопка отправки сообщения
            ui->t_edit->setEnabled(true);     //установка
            ui->b_sent->setEnabled(true);     //в активное состояние
        }

        chatMiddle.clear();    //

        QJsonObject obj =  vk->dialogHistory(currentItem->statusTip());   //загрузка диалога с выбранным контактом
        QJsonArray msgArray = obj["items"].toArray();
        QString time;
        QString photo_130 = "<img src=\"%1\" alt=\"\">";           //фото
        QJsonObject other = vk->getUser(ui->l_contacts->currentItem()->statusTip()); //расширенные данные контакта по ID

        int out;
        QString body;

        for(int i = msgArray.size()-1; i > -1 ; i--){
            QString photo;
            if(!msgArray[i].toObject()["photo_130"].toString().isEmpty())
                photo = photo_130.arg(msgArray[i].toObject()["photo_130"].toString());
            body = msgArray[i].toObject()["body"].toString();
            out = msgArray[i].toObject()["out"].toInt(); //0 - получено, 1 - отправлено

    //        try{
    //            if(body.indexOf("--dec") != -1) {
    //                //qDebug() << "decoding...";
    //                body = body.remove("--dec");
    //                std::string str;
    //                if(out == 1) {
    //                    //если я отослал, то ключ - ид получателя
    //                     str = crypt::genKey(ui->l_contacts->currentItem()->statusTip());
    //                }
    //                else{
    //                    str = crypt::genKey(vk->getUserId());
    //                }
    //                //qDebug() << QString(str.c_str());
    //                if(!body.isEmpty()) {
    //                    std::string decrStr = cr->myCrypt(body.toStdString(), str, str, false);
    //                    body = QString(decrStr.c_str());
    //                }

    //                //qDebug() << "body" <<body;
    //            }
    //        }
    //        catch(const std::exception &ex){
    //            qDebug() << QString(ex.what());
    //        }
    //        catch(...){
    //            qDebug() << "error with decode";
    //        }

            time = QDateTime::fromTime_t(msgArray[i].toObject()["date"].toInt()).toString();
            if(!out) {
                chatMiddle += chatOther.arg(body, time, other["photo_50"].toString(), photo);
            }
            else {
                chatMiddle += chatSelf.arg(body, time, vk->getUserPhoto50(), photo);
            }
        }
        if(chatMiddle.isEmpty()) {
            chatMiddle = chatEmpty;
        }
        chatHTML = basicHTML.arg(CSS, chatMenu.arg(from, line, chatMiddle));
        ui->chat->setHTML(chatHTML);
}

void Form::on_wallButton_clicked()
{
    ui->page->hide();
    ui->wall->show();
    currentDiaolg.clear(); //очистка стрингов
    wallMiddle.clear();    //

    if(!currentItem)
        ui->dialogButton_2->hide();
    else
        ui->dialogButton_2->show();

    QJsonArray wallArray = vk->getUserWall(currentID);
    QString _idsPost, _idsGroupRepost = NULL, _idsUserRepost = NULL;
    int repostIndexGroup[10], repostIndexUser[10];
    int groupCounter = 0, userCounter = 0;
    QString postDate[postShowCount], postText[postShowCount], postPhoto[postShowCount], repostPhoto[postShowCount];
    for(int i = 0; i < wallArray.size(); i++) {
        if(i)
            _idsPost += ",";
        _idsPost += QString::number(wallArray[i].toObject()["from_id"].toInt());
        postDate[i] = QDateTime::fromTime_t(wallArray[i].toObject()["date"].toInt()).toString();
        postText[i] = wallArray[i].toObject()["text"].toString();

        QJsonArray attachments = wallArray[i].toObject()["attachments"].toArray();
        if (!attachments.isEmpty()) {
            for (int j = 0; j < attachments.size(); j++) {
                if(attachments[j].toObject()["type"].toString()=="photo") {
                    postPhoto[i] += QString("<img src=%1 alt=\"\"><br>").arg('"'+attachments[j].toObject()["photo"].toObject()["photo_604"].toString()+'"');
                }
            }
        }
        if(!wallArray[i].toObject()["copy_history"].toArray().isEmpty()) {
            if(wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["owner_id"].toInt() < 0) {
                if(groupCounter++)
                    _idsGroupRepost += ",";               
                repostIndexGroup[groupCounter] = i;
                _idsGroupRepost += QString::number(abs(wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["owner_id"].toInt()));
            }
            else {
                if(userCounter++)
                    _idsUserRepost += ",";
                repostIndexUser[userCounter] = i;
                _idsUserRepost += QString::number(wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["owner_id"].toInt());
            }
            QJsonArray repostAttachments = wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["attachments"].toArray();
            if(!repostAttachments.isEmpty()) {
                for (int j = 0; j < repostAttachments.size(); j++) {
                    if(repostAttachments[j].toObject()["type"].toString()=="photo") {
                        repostPhoto[i] += QString("<img src=\"%1\" alt=\"\"><br>").arg(repostAttachments[j].toObject()["photo"].toObject()["photo_604"].toString());
                    }
                }
            }
        }
    }
    QJsonArray postAuthors = vk->getPostAuthors(_idsPost);
    QJsonArray repostGroupName, repostUserName;
    if(!_idsGroupRepost.isEmpty())
        repostGroupName = vk->getGroupsInfo(_idsGroupRepost);
    if(!_idsUserRepost.isEmpty())
        repostUserName = vk->getPostAuthors(_idsUserRepost);

    qDebug() << "-------START OF WALL--------";

    for(int i = 0; i < wallArray.size();i++) {
        if (!wallArray[i].toObject()["copy_history"].toArray().isEmpty()) {
            if(wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["owner_id"].toInt() < 0)
                for(int j=0; j<repostGroupName.size();j++) {
                    if(abs(wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["owner_id"].toInt())==repostGroupName[j].toObject()["id"].toInt()) {
                        wallRepostFinal = wallRepost.arg(repostGroupName[j].toObject()["name"].toString(),
                                wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["text"].toString(),
                                repostPhoto[i]);
                        break;
                    }
                }
            else
                for (int j=0; j < repostUserName.size(); j++) {
                    if(wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["owner_id"].toInt()
                            == repostUserName[j].toObject()["id"].toInt()) {
                        wallRepostFinal = wallRepost.arg(repostUserName[j].toObject()["first_name"].toString() + " "
                                + repostUserName[j].toObject()["last_name"].toString(),
                                wallArray[i].toObject()["copy_history"].toArray()[0].toObject()["text"].toString(),
                                repostPhoto[i]);
                        break;
                    }
                }
        }
        else
            wallRepostFinal = "";
        for (int j = 0; j < postAuthors.size(); j++) {
            if (wallArray[i].toObject()["from_id"].toInt() == postAuthors[j].toObject()["id"].toInt()) {
                wallPostFinal = wallPost.arg(wallRepostFinal, postAuthors[j].toObject()["first_name"].toString() + " "
                       + postAuthors[j].toObject()["last_name"].toString(), postDate[i], postText[i],
                       postPhoto[i], postAuthors[j].toObject()["photo_50"].toString());

                qDebug() << wallPostFinal << "wallPostFinal" << i;
                break;
            }
        }
        wallMiddle = wallPostFinal + wallMiddle;
    }
    if(wallMiddle.isEmpty()) {
        wallMiddle = wallEmpty;
    }
    wallHTML = basicHTML.arg(CSS, wallMenu.arg(from, line, wallMiddle));
    ui->wall->setHTML(wallHTML);
}
