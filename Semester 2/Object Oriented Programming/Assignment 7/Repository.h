//
// Created by bro_b on 3/29/2023.
//

#ifndef OOP_LAB4_REPOSITORY_H
#define OOP_LAB4_REPOSITORY_H
#pragma once
#include "Domain.h"
#include <vector>

class Repository {
private:
    std::vector<Tutorial> administratorList;
    std::string fileName;

public:
    /// <summary>
    /// This function loads the tutorials from the given file into the repository.
    /// </summary>
    void loadEntitiesFromFile();

    /// <summary>
    /// This function writes the tutorials from the repository into the given file.
    /// </summary>
    void writeEntitiesToFile();

    /// <summary>
    /// This is the constructor for the repository.
    /// </summary>
    /// <param name="fileName">: the given file from where we read tutorials and where we write tutorials</param>
    Repository(std::string fileName);

    /// <summary>
    /// This function finds a tutorial with the given name.
    /// </summary>
    /// <param name="title">: the given title of the tutorial</param>
    /// <returns>the title if it finds it, else throws an exception</returns>
    Tutorial findTutorialRepo(std::string title);

    /// <summary>
    /// This function adds a tutorial to the repository. It throws an exception if the tutorial already exists.
    /// </summary>
    /// <param name="tutorial">: the tutorial to be added</param>
    void addTutorialRepo(Tutorial tutorial);

    /// <summary>
    /// This function deletes a tutorial from the repository. It throws an exception if the tutorial does not
    /// exist.
    /// </summary>
    /// <param name="title">: the title of the tutorial to be deleted</param>
    void deleteTutorialRepo(std::string title);

    /// <summary>
    /// This function updates the informations about the tutorial with a given title. It throws an exception
    /// if the tutorial does not exist.
    /// </summary>
    /// <param name="title">: the title of the tutorial to be updated</param>
    /// <param name="newTutorial">: the new tutorial</param>
    void updateTutorialRepo(std::string title, Tutorial newTutorial);

    /// <summary>
    /// This function gets the tutorials list from the repository.
    /// </summary>
    /// <returns>the tutorials list</returns>
    std::vector<Tutorial> getTutorialsList() const;

    ///file getter
    std::string getfilename() const;

    /// Destructor.
    ~Repository();
};
#endif //OOP_LAB4_REPOSITORY_H
