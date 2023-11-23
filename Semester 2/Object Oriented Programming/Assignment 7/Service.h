//
// Created by bro_b on 3/29/2023.
//

#ifndef OOP_LAB4_SERVICE_H
#define OOP_LAB4_SERVICE_H
#pragma once
#include "Repository.h"

class Service {
private:
    Repository& repo;

public:
    /// <summary>
    /// Constructor for the administrator service.
    /// </summary>
    /// <param name="repo">: the repository</param>
    Service(Repository& repo);

    /// <summary>
    /// This function adds a tutorial to the repository. If a tutorial with the same title exists, it throws
    /// an exception.
    /// </summary>
    /// <param name="title">: the title of the tutorial to be added</param>
    /// <param name="presenter">: the presenter of the tutorial to be added</param>
    /// <param name="duration">: the duration of the tutorial to be added</param>
    /// <param name="like">: the likes of the tutorial to be added</param>
    /// <param name="Link">: the link of the tutorial to be added</param>
    void addTutorialServ(std::string title, std::string presenter, std::string duration, int like, std::string link);

    /// <summary>
    /// This function removes a tutorial from the repository. If a tutorial with the given title does not exist,
    /// it throws an exception.
    /// </summary>
    /// <param name="title">: the title of the tutorial to be removed</param>
    void removeTutorialServ(std::string title);

    /// <summary>
    /// This function updates a tutorial from the repository. If a tutorial with the given title does not exist,
    /// it throws an exception.
    /// </summary>
    /// <param name="title">: the title of the tutorial to be updated</param>
    /// <param name="newPresenter">: the new presenter</param>
    /// <param name="newDuration">: the new duration</param>
    /// <param name="newLike">: the new like</param>
    /// <param name="newLink">: the new link</param>
    void updateTutorialServ(std::string title, std::string newPresenter, std::string newDuration, int newLike, std::string newLink);

    /// <summary>
    /// This function gets the list of tutorials.
    /// </summary>
    /// <returns> the list of tutorials</returns>
    std::vector<Tutorial> getTutorialsList();

    std::string getFileNameService() const;

    void ReadtutorialsFile();

    void WritetutorialsFile();

    /// Destructor.
    ~Service();
};
#endif //OOP_LAB4_SERVICE_H
