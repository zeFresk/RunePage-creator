#include "fenetre.h"
#include <QApplication>

int main(int argc, char *argv[]) // so much code here !
{
    QApplication a(argc, argv);

    Fenetre w;
    w.show();

    return a.exec();
}
