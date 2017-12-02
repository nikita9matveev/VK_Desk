#ifndef CHAT_H
#define CHAT_H

#include <QWidget>
#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>
#include <QString>

class Chat : public QWidget
{
    Q_OBJECT
public:
    explicit Chat(QWidget* parent = 0);

    void setHTML(const QString& _html);

    QWebPage* page();

signals:

public slots:

private:
    QWebView* chatW;
    QString html;
};

#endif // CHAT_H
