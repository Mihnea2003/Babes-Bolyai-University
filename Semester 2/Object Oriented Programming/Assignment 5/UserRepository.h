//
// Created by bro_b on 4/3/2023.
//

#pragma once
#include "Domain.h"
#include <vector>
#include <string>


class UserRepository {
protected:
    std::vector<Tutorial> watchList;
    std::string fileName;

public:
    /// <summary>
    /// This is the constructor for the repository.
    /// </summary>
    /// <param name="fileName">: the given file from where we read tutorials and where we write tutorials</param>
    UserRepository(std::string fileName);

    /// <summary>
    /// This function writes the tutorials from the repository into the given file.
    /// </summary>
    void writeEntitiesToFile();


    /// <summary>
    /// This function finds a tutorial with the given name.
    /// </summary>
    /// <param name="title">: the given title of the tutorial</param>
    /// <returns>the title if it finds it, else throws an exception</returns>
    Tutorial findTutorialUserRepo(std::string title);

    /// <summary>
    /// This function adds a tutorial to the repository. It throws an exception if the tutorial already exists.
    /// </summary>
    /// <param name="tutorial">: the tutorial to be added</param>
    void addTutorialUserRepo(Tutorial tutorial);

    /// <summary>
    /// This function deletes a tutorial from the repository. It throws an exception if the tutorial does not
    /// exist.
    /// </summary>
    /// <param name="title">: the title of the tutorial to be deleted</param>
    void deleteTutorialUserRepo(std::string title);

    /// <summary>
    /// This function gets the tutorials list from the repository.
    /// </summary>
    /// <returns>the tutorials list</returns>
    std::vector<Tutorial> getWatchList() const;

    /// Destructor.
    ~UserRepository();
};