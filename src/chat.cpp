#include "chat.h"

Chat::Chat(QWidget *parent) : QWidget(parent)
{
    chatW = new QWebView(this);
}

void Chat::setHTML(const QString &_html)
{
    html = _html;
    chatW->setHtml(html);
}

QWebPage *Chat::page()
{
    return chatW->page();
}
