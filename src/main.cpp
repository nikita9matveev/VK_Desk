#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    QBrush br(Qt::TexturePattern);
    br.setTextureImage(QImage(":/back_blue.jpg"));
    QPalette plt = w.palette();
    plt.setBrush(QPalette::Background, br);
    w.setPalette(plt);

    w.show();

    return a.exec();
}
