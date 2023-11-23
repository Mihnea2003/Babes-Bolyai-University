//
// Created by bro_b on 5/5/2023.
//
#include "HTMLUserRepository.h"
#include <fstream>

HTMLUserRepository::HTMLUserRepository(std::string HTMLfileName)
{
    this->fileName = HTMLfileName;
}

void HTMLUserRepository::addTutorialUserRepo(Tutorial tutorial)
{
    this->watchList.push_back(tutorial);
    this->writeToFile();
}

std::vector<Tutorial> HTMLUserRepository::getwatchList()
{
    return this->watchList;
}

std::string HTMLUserRepository::getFileName()
{
    return this->fileName;
}

void HTMLUserRepository::writeToFile()
{
    std::ofstream fileOut(fileName);
    fileOut << "<!DOCTYPE html>\n<html><head><title>Watch list</title></head><body>\n";
    fileOut << "<table border=\"1\">\n";
    fileOut << "<tr><td>Title</td><td>Presenter</td><td>Duration</td><td>Likes</td><td>Link</td></tr>\n";
    for (auto tutorial : watchList)
    {
        fileOut << "<tr><td>" << tutorial.getTitle() << "</td><td>" << tutorial.getPresenter() << "</td><td>" << tutorial.getDuration() << "</td><td>"
                << std::to_string(tutorial.getLike()) << "</td>" << "<td><a href = \"" << tutorial.getLink()
                << "\">" << tutorial.getLink() << "</a></td></tr>\n";
    }
    fileOut << "</table></body></html>";
    fileOut.close();
}

HTMLUserRepository::~HTMLUserRepository() = default;