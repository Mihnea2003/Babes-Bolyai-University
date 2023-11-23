//
// Created by bro_b on 3/29/2023.
//

#ifndef OOP_LAB4_UI_H
#define OOP_LAB4_UI_H
#pragma once
#include "service.h"
#include "userService.h"

class UI {
private:
    Service& adminService;
    UserService& userService;

    /// <summary>
    /// This function handles adding a tutorial. It is used in administrator mode.
    /// </summary>
    void handleAdd();

    /// <summary>
    /// This function handles removing a tutorial. It is used in administrator mode.
    /// </summary>
    void handleRemove();

    /// <summary>
    /// This function handles updating a tutorial. It is used in administrator mode.
    /// </summary>
    void handleUpdate();

    /// <summary>
    /// This function prints the tutorials from the administrator repository.
    /// </summary>
    void printTutorials();

    /// <summary>
    /// This function prints the tutorials from the watch list.
    /// </summary>
    void printWatchList();

    /// <summary>
    /// This function handles removing a tutorial. It is used in administrator mode.
    /// </summary>
    void handleRemoveWatchList();


    /// <summary>
    /// This function handles watching tutorials by displaying all tutorials from the repository or displaying just by a presenter.
    /// </summary>
    void handleWatchAll();


    /// <summary>
    /// This function displays the administrator mode menu.
    /// </summary>
    void displayAdminMenu();

    /// <summary>
    /// This function displays the user mode menu.
    /// </summary>
    void displayUserMenu();

public:
    /// <summary>
    /// Constructor for the UI.
    /// </summary>
    /// <param name="adminService">: the administrator mode service</param>
    UI(Service& adminService, UserService& userService);

    /// <summary>
    /// This function starts the application.
    /// </summary>
    void run();

    /// Destructor.
    ~UI();

};
#endif //OOP_LAB4_UI_H
