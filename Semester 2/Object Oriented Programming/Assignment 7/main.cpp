#include <iostream>
#include "UI.h"
#include "Tests.h"


int main()
{
    std::string filename = "tutorials.txt";
    Repository repo = Repository(filename);
    Service service = Service(repo);


    repo.loadEntitiesFromFile();
    //runAllTests();
    UserRepository userRepo = UserRepository("nothing.txt");
    UserService userService = UserService(userRepo);

    UI ui = UI(service,userService);
    ui.run();
    repo.writeEntitiesToFile();
}