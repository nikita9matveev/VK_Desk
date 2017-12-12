#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QCloseEvent>
#include <QUrl>

#include "lib/QJsonArray.h"
#include "lib/QJsonDocument.h"
#include "lib/QJsonObject.h"
#include "lib/QJsonValue.h"

#include <QStackedLayout>
#include <QSharedPointer>
#include <QPointer>

#include "vkconnect.h"
#include "form.h"
#include "w_login.h"
#include "error_dialog.h"

namespace Ui {
class Widget;
}

/*!
 * \brief The Widget class
 *
 * Основной класс. Отвечает за глобальные объекты, держит основные окна и при
 * необходимости выводит нужные.
 */
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    /*!
     * \brief void on_login();
     *
     * Вызывается в случае успешного подключения. Испускает ready().
     */
    void on_login();
    /*!
     * \brief void on_error()
     * \param error_string Сообщение об ошибке
     *
     * вызывается в случае возникновения ошибки. Зыкрывает главное окно по нажатии ОК.
     */
    void on_error(const QString & string);
    /*!
     * \brief void on_content_resized(width, height)
     * \param width новая ширина окна
     * \param height новая высота окна
     *
     * слот принимает сигналы на изменение размеров главного окна
     */
    void on_content_resized(int _width, int _height);

signals:
    ///Сигнал. Испускается в случае готовности передачи данных дочернему окну (form)
    void ready();
private:
    ///индекс текущего окна
    int currentIndex;
    ///интерфейс
    Ui::Widget *ui;
    ///менеджер интернет подключения
    QPointer<QNetworkAccessManager> manager;
    ///класс подключения к серверу вк
    QSharedPointer<vkConnect> vk;
    ///класс хранения окон
    QPointer<QStackedLayout> l;
    ///класс окна подключения
    QPointer<w_login>  w_log;
    ///класс окна приложения
    QPointer<Form> form;
    ///класс диалогового окна ошибок
    QPointer<error_dialog> errorD;
};

#endif // WIDGET_H
