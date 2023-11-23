#ifndef CARMANAGERGUI_GUI_H
#define CARMANAGERGUI_GUI_H

#include <QWidget>
#include "../Service/Services.h"


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget {
Q_OBJECT

public:
    explicit gui(Services &s, QWidget *parent = nullptr);

    ~gui() override;

private:
    Services& serv;
    Ui::gui *ui;

    void populateList();
    int get_selected_index();
    void get_by_manufacturer_filter();
    void connectSiganalsAndSlots();

    void set_font_qt_like_parameter();
};


#endif //CARMANAGERGUI_GUI_H
