//
// Created by bro_b on 4/3/2023.
//
#include "userService.h"
#include "errors.h"


UserService::UserService(UserRepository &repo) : repo(repo) {
    this->repo = repo;
}

void UserService::add(std::string title, std::string presenter, std::string duration, int likes, std::string Link)
{
    Tutorial t = Tutorial(title, presenter, duration, likes, Link);
    try
    {
        this->repo.addTutorialUserRepo(t);
    }
    catch (RepoError err)
    {
        throw err;
    }
}
void UserService::remove(std::string title)
{
    try
    {
        this->repo.deleteTutorialUserRepo(title);
    }
    catch (RepoError err)
    {
        throw err;
    }
}

std::vector<Tutorial> UserService::getWatchList()
{
    return this->repo.getWatchList();
}
