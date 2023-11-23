#ifndef CARMANAGERGUI_CAR_H
#define CARMANAGERGUI_CAR_H

#include <iostream>
#include <vector>

using namespace std;


class Car {
private:
    std::string manufacturer;
    std::string model;
    int yearOfFabrication;
    std::string colour;
public:
    Car() : manufacturer{""}, model{""}, yearOfFabrication{}, colour{""} {}
    Car(std::string manufacturer, std::string model, int yearOfFabrication, std::string colour);
    std::string get_manufacturer() const {return this->manufacturer;}
    std::string get_model() const {return this->model;}
    int get_yearOfFabrication() const {return this->yearOfFabrication;}
    std::string get_colour() const {return this->colour;}

    std::string toString();
    ~Car() = default;
    static vector<string> tokenize(string str, char delimiter);
    friend istream& operator>>(istream& is, Car& c);
};


#endif //CARMANAGERGUI_CAR_H
