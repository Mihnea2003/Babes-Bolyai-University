#include <iostream>
#include "UI.h"
#include "Tests.h"
#include <crtdbg.h>
#include <iostream>

int main()
{

    Repository repo = Repository("nothing.txt");
    Service service = Service(repo);
    service.addTutorialServ("How to REALLY learn C++", "The Cherno","8:12", 100, "https://www.youtube.com/watch?v=_zQqN5OYCCM");
    service.addTutorialServ("BEST WAY to make Desktop Applications in C++", "The Cherno","25:39", 150, "https://www.youtube.com/watch?v=vWXrFetSH8w");
    service.addTutorialServ("C++ Programming Course - Begin", "freeCodeCamp.org","59:00", 200, "https://www.youtube.com/watch?v=8jLOx1hD3_o");
    service.addTutorialServ("How I Would Learn To Code (If I Could Start Over)", "Namanh Kapur","30:00", 110, "https://www.youtube.com/watch?v=k9WqpQp8VSU");
    service.addTutorialServ("you will never ask about pointers again after watching this video", "Low Level Learning","15:15", 130, "https://www.youtube.com/watch?v=2ybLD6_2gKM");
    service.addTutorialServ("Introduction to Pointers | C Programming Tutorial", "Portfolio Courses","14:34", 80, "https://www.youtube.com/watch?v=2GDiXG5RfNE");
    service.addTutorialServ("Calugaritele", "Doru calota", "3:12",200, "https://www.youtube.com/watch?v=pTUZebhAx4c");
    service.addTutorialServ("Pass By Reference | C Programming Tutorial", "Portfolio Courses","10:55", 20, "https://www.youtube.com/watch?v=RecxQUUEOn4");
    service.addTutorialServ("Dynamic Memory Allocation | C Programming Tutorial", "Portfolio Courses","10:11", 0, "https://www.youtube.com/watch?v=R0qIYWo8igs");
    service.addTutorialServ("C_132 Introduction to Dynamic Memory Allocation in C | SMA vs DMA", "Jenny's Lectures CS IT ","22:33", 10, "https://www.youtube.com/watch?v=LQXueqsbxRU");


    //runAllTests();
    UserRepository userRepo = UserRepository("nothing.txt");
    UserService userService = UserService(userRepo);

    UI ui = UI(service,userService);
    ui.run();

}