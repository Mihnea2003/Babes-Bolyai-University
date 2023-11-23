#include "Repo.h"
#include <fstream>

Repo::Repo() {
    this->load_from_file();
}

Repo::~Repo() {}

vector<Car> Repo::get_all() {
    return this->cars;
}

void Repo::load_from_file() {
    ifstream file("D:/UBB/Semester 2/OOP/CarManagerGUI/cmake-build-debug/input.txt");
    Car current_car;
    this->cars.clear();
    while(file >> current_car)
        this->cars.push_back(current_car);

    file.close();

}
