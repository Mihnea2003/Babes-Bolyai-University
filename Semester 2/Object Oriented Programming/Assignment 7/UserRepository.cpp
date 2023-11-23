//
// Created by bro_b on 4/3/2023.
//
#include "UserRepository.h"
#include "errors.h"
#include <fstream>
#include <algorithm>
UserRepository::UserRepository(std::string fileName)
{
    this->fileName = fileName;
}

void UserRepository::writeEntitiesToFile()
{
    if (!fileName.empty())
    {
        std::ofstream fileOut(fileName);
        for (auto tutorial : watchList)
        {
            fileOut << tutorial << "\n";
        }
        fileOut.close();
    }
}


Tutorial UserRepository::findTutorialUserRepo(std::string title)
{
    for (auto i : watchList)
    {
        if (i.getTitle() == title)
        {
            return i;
        }
    }
    throw ValueError("Tutorial not found !");
}

void UserRepository::addTutorialUserRepo(Tutorial tutorial)
{
    try
    {
        Tutorial t = findTutorialUserRepo(tutorial.getTitle());
        throw RepoError("This tutorial already exists !");
    }
    catch (ValueError)
    {
        this->watchList.push_back(tutorial);
        this->writeEntitiesToFile();
    }
}

void UserRepository::deleteTutorialUserRepo(std::string title)
{
    auto it = std::remove_if(watchList.begin(), watchList.end(), [title](Tutorial t) { return (t.getTitle() == title); });
    if (it == watchList.end())
    {
        throw RepoError("Tutorial does not exist !");
    }
    watchList.pop_back();
    this->writeEntitiesToFile();
}

std::vector<Tutorial> UserRepository::getWatchList() const
{
    return this->watchList;
}

UserRepository::~UserRepository() = default;
