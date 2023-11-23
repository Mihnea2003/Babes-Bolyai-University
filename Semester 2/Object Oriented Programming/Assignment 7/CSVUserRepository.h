//
// Created by bro_b on 5/5/2023.
//

#ifndef OOP_LAB4_CSVUSERREPOSITORY_H
#define OOP_LAB4_CSVUSERREPOSITORY_H
#pragma once
#include "UserRepository.h"

class CSVUserRepository : public UserRepository {
public:
    /// <summary>
    /// Constructor for CSVUserRepository
    /// </summary>
    /// <param name="CSVfileName">: the given CSV file name</param>
    CSVUserRepository(std::string fileName, std::string CSVfileName);

    /// <summary>
    /// This function adds a tutorial to the watch list.
    /// </summary>
    /// <param name="tutorial">: the tutorial to be added</param>
    void addTutorialUserRepo(Tutorial tutorial) override;


    /// <summary>
    /// This function gets the watch list.
    /// </summary>
    /// <returns>: the watch list</returns>
    std::vector<Tutorial> getwatchList() override;

    /// <summary>
    /// This function gets the CSV file name.
    /// </summary>
    /// <returns> the CSV file name</returns>
    std::string getFileName() override;

    /// <summary>
    /// This function writes the watch list into the given file.
    /// </summary>
    void writeToFile() override;

    /// Destructor.
    ~CSVUserRepository() override;
};
#endif //OOP_LAB4_CSVUSERREPOSITORY_H
