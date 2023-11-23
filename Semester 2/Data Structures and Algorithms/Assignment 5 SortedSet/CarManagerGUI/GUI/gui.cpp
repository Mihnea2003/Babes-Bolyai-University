// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>


gui::gui(Services &s, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), serv{ s } {
    ui->setupUi(this);

    this->populateList(); ///important for populating the list after gui()
    this->connectSiganalsAndSlots();
}

gui::~gui() {
    delete ui;
}

void gui::populateList() {
    this->ui->carList->clear();
    vector <Car> allCars = this->serv.get_all();
    ///now sort the cars by manufacturer
    sort(allCars.begin(), allCars.end(), [](const Car &c1, const Car &c2) {
        return c1.get_manufacturer() < c2.get_manufacturer();
    });

    for(auto &c : allCars)
        this->ui->carList->addItem(QString::fromStdString(c.get_manufacturer() + "|" + c.get_model()));
}

void gui::connectSiganalsAndSlots() {
    QObject::connect(this->ui->buttonManufacturer, &QPushButton::clicked, this, &gui::get_by_manufacturer_filter);
    QObject::connect(this->ui->buttonSetColour, &QPushButton::clicked, this, &gui::set_font_qt_like_parameter);

}

void gui::get_by_manufacturer_filter() {
    string manufacturer = this->ui->inputManufacturer->text().toStdString();
    if(manufacturer.empty())
    {
        QMessageBox::critical(this, "Error", "No manufacturer given!");
        return;
    }
    vector<Car> cars_result = this->serv.get_cars_manufacturer(manufacturer);
    this->ui->carList2->clear();

    for(auto &c : cars_result)
        this->ui->carList2->addItem(QString::fromStdString(c.get_manufacturer() + "|" + c.get_model()));

    this->ui->carList2->addItem(QString::fromStdString("Total: " + to_string(cars_result.size())));

}

int gui::get_selected_index() {
    QModelIndexList selectedIndexes = this->ui->carList->selectionModel()->selectedIndexes();
    if(selectedIndexes.size() == 0)
    {
        this->ui->inputManufacturer->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void gui::set_font_qt_like_parameter() {

    this->ui->carList3->clear();
    //iterate over each car object
    for (const auto& car : this->serv.get_all()) {
        auto carItem = new QListWidgetItem();

        // Set the text of the item to display the car's details
        QString carDetails = QString::fromStdString(car.get_manufacturer()) + " " +
                             QString::fromStdString(car.get_model());
        carItem->setText(carDetails);

        // Set the background color of the item based on the car's colour
        QString backgroundColor = QString::fromStdString(car.get_colour());
        carItem->setBackground(QColor(backgroundColor));

        // Add the car item to the carList widget
        this->ui->carList3->addItem(carItem);
    }
}


