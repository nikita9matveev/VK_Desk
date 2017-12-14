#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    // настройка кодека для корректной обработки русских букв
    QTextCodec *codec1 = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec1);
    QTextCodec::setCodecForTr(codec1);
    QTextCodec::setCodecForCStrings(codec1);

    QBrush br(Qt::TexturePattern);
    br.setTextureImage(QImage(":/back_blue.jpg"));
    QPalette plt = w.palette();
    plt.setBrush(QPalette::Background, br);
    w.setPalette(plt);

    w.show();

    return a.exec();
}
