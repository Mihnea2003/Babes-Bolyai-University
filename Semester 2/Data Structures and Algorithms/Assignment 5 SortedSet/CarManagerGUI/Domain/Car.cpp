#include "Car.h"
#include <sstream>

Car::Car(std::string manufacturer, std::string model, int yearOfFabrication, std::string colour) {
    this->manufacturer = manufacturer;
    this->model = model;
    this->yearOfFabrication = yearOfFabrication;
    this->colour = colour;
}

std::string Car::toString() {
    std::stringstream stream;
    stream << this->manufacturer << "|" << this->model << "|" << this->yearOfFabrication << "|" << this->colour << std::endl;
    return std::string(stream.str());
}

vector<string> Car::tokenize(string str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}

istream &operator>>(istream &input, Car &c) {
    string line;
    getline(input, line);
    vector<string> tokens = Car::tokenize(line, '|');
    if (tokens.size() != 4)
        return input;
    c.manufacturer = tokens[0];
    c.model = tokens[1];
    c.yearOfFabrication = stoi(tokens[2]);
    c.colour = tokens[3];
    return input;
}
