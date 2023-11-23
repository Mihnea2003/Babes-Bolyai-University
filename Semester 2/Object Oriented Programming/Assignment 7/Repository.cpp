//
// Created by bro_b on 3/29/2023.
//
#include "Repository.h"
#include "errors.h"
#include <fstream>
#include <algorithm>



Repository::Repository(std::string fileName)
{
    this->fileName = fileName;
}

void Repository::loadEntitiesFromFile()
{
    if (!fileName.empty())
    {
        Tutorial fileTutorial;
        std::ifstream fileIn(fileName);
        while (fileIn >> fileTutorial)
        {
            if (std::find(administratorList.begin(), administratorList.end(), fileTutorial) == administratorList.end())
            {
                administratorList.push_back(fileTutorial);
            }
        }
        fileIn.close();
    }
}

void Repository::writeEntitiesToFile()
{
    if (!fileName.empty())
    {
        std::ofstream fileOut(fileName);
        for (auto tutorial : administratorList)
        {
            fileOut << tutorial << "\n";
        }
        fileOut.close();
    }
}

Tutorial Repository::findTutorialRepo(std::string title)
{
    for (auto i : administratorList)
    {
        if (i.getTitle() == title)
        {
            return i;
        }
    }
    throw ValueError("Tutorial not found !");
}

void Repository::addTutorialRepo(Tutorial tutorial)
{
    try
    {
        Tutorial t = findTutorialRepo(tutorial.getTitle());
        throw RepoError("This tutorial already exists !");
    }
    catch (ValueError)
    {
        this->administratorList.push_back(tutorial);
        this->writeEntitiesToFile();
    }
}


void Repository::deleteTutorialRepo(std::string title)
{
    auto it = std::remove_if(administratorList.begin(), administratorList.end(), [title](Tutorial t) { return (t.getTitle() == title); });
    if (it == administratorList.end())
    {
        throw RepoError("Tutorial does not exist !");
    }
    administratorList.pop_back();
    this->writeEntitiesToFile();
}

void Repository::updateTutorialRepo(std::string title, Tutorial newTutorial)
{
    int k = 0;
    for (auto i : administratorList)
    {
        if (i.getTitle() == title)
        {
            administratorList.at(k) = newTutorial;
            return;
        }
        k++;
    }
    throw RepoError("Tutorial does not exist !");
}

std::vector<Tutorial> Repository::getTutorialsList() const
{
    return this->administratorList;
}

std::string Repository::getfilename() const {
    return this->fileName;
}

Repository::~Repository() = default;