#include "myqtextedit.h"
#include "ui_myqtextedit.h"

myQTextEdit::myQTextEdit(QWidget *parent) :
    QTextEdit(parent),
    ui(new Ui::myQTextEdit)
{
}

void myQTextEdit::setPB(QPushButton *_pb)
{
    pb = _pb;
}

myQTextEdit::~myQTextEdit()
{
    delete ui;
}

void myQTextEdit::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
        pb->click();   //maybe pressed() or released()
        setFocus(Qt::OtherFocusReason);        
    default:
          QTextEdit::keyPressEvent(event);
    }
}
