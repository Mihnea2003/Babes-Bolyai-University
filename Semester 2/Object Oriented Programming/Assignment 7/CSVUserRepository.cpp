//
// Created by bro_b on 5/5/2023.
//

#include "CSVUserRepository.h"
#include <fstream>

CSVUserRepository::CSVUserRepository( std::string CSVfileName)  {
    this->fileName = CSVfileName;
}

void CSVUserRepository::addTutorialUserRepo(Tutorial tutorial)
{
    this->watchList.push_back(tutorial);
    this->writeToFile();
}

std::vector<Tutorial> CSVUserRepository::getwatchList()
{
    return this->watchList;
}

std::string CSVUserRepository::getFileName()
{
    return this->fileName;
}

void CSVUserRepository::writeToFile()
{
    std::ofstream fileOut(fileName);
    if (!watchList.empty())
    {
        for (auto tutorial : watchList)
        {
            fileOut << tutorial << "\n";
        }
    }
    fileOut.close();
}

CSVUserRepository::~CSVUserRepository() = default;