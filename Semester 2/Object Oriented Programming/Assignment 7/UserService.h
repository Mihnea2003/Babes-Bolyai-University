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
    UserRepository* repo;

public:
    UserService(UserRepository &repo);

    void add(std::string title, std::string presenter,std::string duration, int likes, std::string Link);

    void remove(std::string title);

    /// <summary>
    /// This function chooses the type of the file where the watching list will be stored.
    /// </summary>
    /// <param name="fileType">; the given file type</param>
    void chooseRepositoryType(int fileType);

    std::vector<Tutorial> getWatchList();

};