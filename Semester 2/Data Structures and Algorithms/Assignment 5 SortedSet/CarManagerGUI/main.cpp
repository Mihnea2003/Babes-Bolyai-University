#include <QApplication>
#include <QPushButton>
#include "../CarManagerGUI/GUI/gui.h"
#include "../CarManagerGUI/Service/Services.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repo repository;
    Services service(repository);
    gui gui1{service};
    gui1.show();

    return QApplication::exec();
}
