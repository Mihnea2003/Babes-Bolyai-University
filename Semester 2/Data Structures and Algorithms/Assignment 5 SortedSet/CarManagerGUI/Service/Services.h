#ifndef CARMANAGERGUI_SERVICES_H
#define CARMANAGERGUI_SERVICES_H

#include "../Repository/Repo.h"
#include <vector>
#include <iostream>

using namespace std;

class Services {
private:
    Repo &repo;
public:
    Services(Repo &r) : repo{ r } {}
    ~Services() = default;
    vector<Car> get_all();

    int get_cars_number_manufacturer(string manufacturer);
    vector<Car> get_cars_manufacturer(string manufacturer);
};


#endif //CARMANAGERGUI_SERVICES_H
