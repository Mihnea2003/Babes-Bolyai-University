#ifndef CARMANAGERGUI_REPO_H
#define CARMANAGERGUI_REPO_H

#include "../Domain/Car.h"
#include <vector>
#include <iostream>
#include <string>

class Repo {
private:
    std::vector<Car> cars;
    void load_from_file();
public:
    Repo();
    ~Repo();
    std::vector<Car> get_all();
};


#endif //CARMANAGERGUI_REPO_H
