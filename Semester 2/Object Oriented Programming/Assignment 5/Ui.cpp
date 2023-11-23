//
// Created by bro_b on 3/29/2023.
//
#include "UI.h"
#include "errors.h"

void UI::handleAdd()
{
    std::string title, presenter,link,duration;
    int like;

    std::cout << "Please input the title: ";
    std::getline(std::cin, title);

    std::cout << "Please input the presenter: ";
    std::getline(std::cin, presenter);

    std::cout << "Please input the duration: ";
    std::getline(std::cin, duration);

    std::cout << "Please input the like: ";
    std::cin >> like;
    std::cin.get();
    if (std::cin.fail())
    {
        std::cout << "Invalid input! \n";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        return;
    }

    std::cout << "Please input the link: ";
    std::getline(std::cin, link);

    try
    {
        this->adminService.addTutorialServ(title, presenter,duration, like, link);
        std::cout << "Tutorial added successfully !\n";
    }
    catch (RepoError err)
    {
        std::cout << err.what() << '\n';
    }
}

void UI::handleRemove()
{
    std::string title;

    std::cout << "Please input the title: ";
    std::getline(std::cin, title);

    try
    {
        this->adminService.removeTutorialServ(title);
        std::cout << "Tutorial removed successfully !\n";
    }
    catch (RepoError err)
    {
        std::cout << err.what() << '\n';
    }
}

void UI::handleUpdate()
{
    std::string title, newPresenter,newDuration, newLink;
    int newLike;

    std::cout << "Please input the title of the tutorial you want to update: ";
    std::getline(std::cin, title);

    std::cout << "Please input the new presenter: ";
    std::getline(std::cin, newPresenter);

    std::cout << "Please input the new likes: ";
    std::cin >> newLike;
    std::cin.get();
    if (std::cin.fail()|| newLike<0)
    {
        std::cout << "Invalid input!\n";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        return;
    }

    std::cout << "Please input the new link: ";
    std::getline(std::cin, newLink);

    try
    {
        this->adminService.updateTutorialServ(title, newPresenter,newDuration, newLike, newLink);
        std::cout << "Tutorial updated successfully !\n";
    }
    catch (RepoError err)
    {
        std::cout << err.what() << '\n';
    }
}

void UI::printTutorials()
{
    std::vector<Tutorial> arr = this->adminService.getTutorialsList();
    for (auto i : arr)
    {
        std::cout << i << '\n';
    }
}
void UI::printWatchList()
{
    std::vector<Tutorial> arr = this->userService.getWatchList();
    for (auto i : arr)
    {
        std::cout << i << '\n';
    }
}
void UI::handleWatchAll()
{
    std::vector<Tutorial> arr = this->adminService.getTutorialsList();
    std::string presenter;
    std::cout << "Please input presenter: ";
    std::getline(std::cin, presenter);
        for (auto i: arr) {
            if (presenter == i.getPresenter()) {
                std::cout << i << '\n';
                std::string command = std::string("start ").append(i.getLink());
                system(command.c_str());
                int addToWatchList;
                std::cout << "Add to watch list? (1.Yes/2.No):\n";
                std::cin >> addToWatchList;
                std::cin.get();
                if (addToWatchList == 1) {
                    try {
                        this->userService.add(i.getTitle(), i.getPresenter(), i.getDuration(), i.getLike(),
                                              i.getLink());
                    }
                    catch (RepoError err) {
                        std::cout << err.what() << '\n';
                    }
                }
                int next;
                std::cout << "Continue? (1.Yes/2.No):\n";
                std::cin >> next;
                std::cin.get();
                if (next != 1) {
                    break;
                }
            }else if (presenter.empty()){
                std::cout << i << '\n';
                std::string command = std::string("start ").append(i.getLink());
                system(command.c_str());
                int addToWatchList;
                std::cout << "Add to watch list? (1.Yes/2.No):\n";
                std::cin >> addToWatchList;
                std::cin.get();
                if (addToWatchList == 1) {
                    try {
                        this->userService.add(i.getTitle(), i.getPresenter(), i.getDuration(), i.getLike(),
                                              i.getLink());
                    }
                    catch (RepoError err) {
                        std::cout << err.what() << '\n';
                    }
                }
                int next;
                std::cout << "Continue? (1.Yes/2.No):\n";
                std::cin >> next;
                std::cin.get();
                if (next != 1) {
                    break;
                }
            }
        }
        }

void UI::handleRemoveWatchList()
{
    std::string title;

    std::cout << "Please input the title: ";
    std::getline(std::cin, title);

    try
    {
        this->userService.remove(title);
        std::cout << "Tutorial removed successfully !\n";
    }
    catch (RepoError err)
    {
        std::cout << err.what() << '\n';
    }
    int option;
    std::cout << "Would you like to give this video a like? 1.Yes/2.No\n";
    std::cin >> option;
    if (option == 1){
        std::vector<Tutorial> arr = this->adminService.getTutorialsList();
        for (auto i: arr){
            if( title == i.getTitle()){
                this->adminService.updateTutorialServ(title, i.getPresenter(),i.getDuration(), i.getLike()+1, i.getLink());;
            }
        }
    }


}


void UI::displayAdminMenu()
{
    std::cout << "1. Add tutorial \n";
    std::cout << "2. Remove tutorial \n";
    std::cout << "3. Update tutorial \n";
    std::cout << "4. Display tutorial \n";
    std::cout << "5. Exit \n";
    std::cout << "Please choose an option: ";
}
void UI::displayUserMenu()
{
    std::cout << "1. See the tutorials in the database having a given presenter \n";
    std::cout << "2. Display watching list \n";
    std::cout << "3. Remove a tutorial from the watch list \n";
    std::cout << "4. Exit\n";
    std::cout << "Please choose an option: ";
}

UI::UI(Service& adminService, UserService& userService) : adminService{ adminService }, userService{ userService } {}

void UI::run() {
    int option;
    std::cout << "1. Administrator mode\n";
    std::cout << "2. User mode\n";
    std::cout << "3. Exit\n\n";
    std::cout << "Please choose an option: ";
    std::cin >> option;
    if (option == 1) {
        while (true) {
            displayAdminMenu();
            std::cin >> option;
            std::cin.get();
            if (std::cin.fail()) {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                std::cin.ignore(256, '\n');
                return;
            }
            if (option == 1) {
                this->handleAdd();
            } else if (option == 2) {
                this->handleRemove();
            } else if (option == 3) {
                this->handleUpdate();
            } else if (option == 4) {
                this->printTutorials();
            } else if (option == 5) {
                return;
            } else {
                std::cout << "Invalid option! Try again!\n";
            }
        }
        }
        else  if (option == 2) {
        while (true) {
            displayUserMenu();
            std::cin >> option;
            std::cin.get();
            if (std::cin.fail()) {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                std::cin.ignore(256, '\n');
                return;
            }
            if (option == 1) {
                this->handleWatchAll();
            } else if (option == 2) {
                this->printWatchList();
            }else if (option == 3) {
                this->handleRemoveWatchList();
            }
            else if (option == 4) {
                return;
            }
        }
        }
        else
    {
        return;
    }
}
UI::~UI() = default;
