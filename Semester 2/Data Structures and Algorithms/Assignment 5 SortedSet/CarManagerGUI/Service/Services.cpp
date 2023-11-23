#include "Services.h"

vector<Car> Services::get_all() {
    return this->repo.get_all();
}

int Services::get_cars_number_manufacturer(string manufacturer) {
    int count = 0;
    for(auto car : this->repo.get_all()) {
        if(car.get_manufacturer() == manufacturer) {
            count = 0;
        }
    }
    return count;
}

vector<Car> Services::get_cars_manufacturer(string manufacturer) {
    vector<Car> aux_cars;
    for(auto car : this->repo.get_all()) {
        if(car.get_manufacturer() == manufacturer) {
            aux_cars.push_back(car);
        }
    }
    return aux_cars;
}
