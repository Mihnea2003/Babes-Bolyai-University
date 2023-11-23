//
// Created by bro_b on 5/5/2023.
//

#ifndef OOP_LAB4_HTMLUSERREPOSITORY_H
#define OOP_LAB4_HTMLUSERREPOSITORY_H
#pragma once
#include "userRepository.h"

class HTMLUserRepository : public UserRepository {
public:
    /// <summary>
    /// Constructor for HTMLUserRepository.
    /// </summary>
    /// <param name="HTMLfileName">: the given HTML file name</param>
    HTMLUserRepository(std::string HTMLfileName);

    /// <summary>
    /// This function adds the given tutorial to the watch list.
    /// </summary>
    /// <param name="tutorial">: the tutorial to be added</param>
    void addTutorialUserRepo(Tutorial tutorial) override;

    /// <summary>
    /// This function gets the watch list.
    /// </summary>
    /// <returns>: the watch list</returns>
    std::vector<Tutorial> getwatchList() override;

    /// <summary>
    /// This function gets the HTML file name.
    /// </summary>
    /// <returns> the HTML file name</returns>
    std::string getFileName() override;

    /// <summary>
    /// This function writes the watch list into the given file.
    /// </summary>
    void writeToFile() override;

    /// Destructor.
    ~HTMLUserRepository() override;
};
#endif //OOP_LAB4_HTMLUSERREPOSITORY_H
