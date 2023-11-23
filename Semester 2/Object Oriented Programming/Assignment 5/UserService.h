//
// Created by bro_b on 4/3/2023.
//

#pragma once
#include <string>
#include "Domain.h"
#include "UserRepository.h"
#include "DynamicArray.h"

class UserService
{
private:
    UserRepository& repo;

public:
    UserService(UserRepository &repo);

    void add(std::string title, std::string presenter,std::string duration, int likes, std::string Link);

    void remove(std::string title);

    std::vector<Tutorial> getWatchList();

};