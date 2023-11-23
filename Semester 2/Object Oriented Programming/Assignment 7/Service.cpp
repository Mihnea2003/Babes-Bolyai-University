//
// Created by bro_b on 3/29/2023.
//
#include "service.h"
#include "errors.h"

Service::Service(Repository& repo) : repo{ repo } {}

void Service::addTutorialServ(std::string title, std::string presenter, std::string duration, int like, std::string Link)
{
    Tutorial t = Tutorial(title, presenter,duration, like, Link);
    try
    {
        this->repo.addTutorialRepo(t);
    }
    catch (RepoError err)
    {
        throw err;
    }
}

void Service::removeTutorialServ(std::string title)
{
    try
    {
        this->repo.deleteTutorialRepo(title);
    }
    catch (RepoError err)
    {
        throw err;
    }
}

void Service::updateTutorialServ(std::string title, std::string newPresenter, std::string newDuration,int newLike, std::string newLink)
{
    Tutorial newTutorial = Tutorial(title, newPresenter, newDuration, newLike, newLink);
    try
    {
        this->repo.updateTutorialRepo(title, newTutorial);
    }
    catch (RepoError err)
    {
        throw err;
    }
}

std::vector<Tutorial> Service::getTutorialsList()
{
    return this->repo.getTutorialsList();
}

std::string Service::getFileNameService() const {
    return this->repo.getfilename();
}

void Service::ReadtutorialsFile() {
    this->repo.loadEntitiesFromFile();
}

void Service::WritetutorialsFile() {
    this->repo.writeEntitiesToFile();
}

Service::~Service() = default;