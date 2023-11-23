#include "Tests.h"
#include "errors.h"
#include <cassert>
#include <sstream>

//
// Created by bro_b on 4/5/2023.
//
void testDomain(){
    Tutorial tutorial;
    assert(tutorial.getTitle() == "");
    assert(tutorial.getPresenter() == "");
    assert(tutorial.getDuration() == "");
    assert(tutorial.getLike() == 0);
    assert(tutorial.getLink() == "");
    Tutorial t("Title", "Presenter", "Duration", 5, "Link");
    assert(t.getTitle() == "Title");
    assert(t.getPresenter() == "Presenter");
    assert(t.getDuration() == "Duration");
    assert(t.getLike() == 5);
    assert(t.getLink() == "Link");
    Tutorial tutorial1("Title", "Presenter", "Duration", 5, "Link");
    Tutorial tutorial2(tutorial1);
    assert(tutorial2.getTitle() == "Title");
    assert(tutorial2.getPresenter() == "Presenter");
    assert(tutorial2.getDuration() == "Duration");
    assert(tutorial2.getLike() == 5);
    assert(tutorial2.getLink() == "Link");
    tutorial.setTitle("Title");
    tutorial.setPresenter("Presenter");
    tutorial.setDuration("Duration");
    tutorial.setLike(5);
    tutorial.setLink("Link");
    assert(tutorial.getTitle() == "Title");
    assert(tutorial.getPresenter() == "Presenter");
    assert(tutorial.getDuration() == "Duration");
    assert(tutorial.getLike() == 5);
    assert(tutorial.getLink() == "Link");
    Tutorial tutoria("Title", "Presenter", "Duration", 5, "Link");
    assert(tutoria.toString() == "Title: Title | Presenter: Presenter | Duration: Duration | Likes: 5 | Link: Link");
    Tutorial tutorial11("Title", "Presenter", "Duration", 5, "Link");
    Tutorial tutorial21;
    tutorial21 = tutorial11;
    assert(tutorial21.getTitle() == "Title");
    assert(tutorial21.getPresenter() == "Presenter");
    assert(tutorial21.getDuration() == "Duration");
    assert(tutorial21.getLike() == 5);
    assert(tutorial21.getLink() == "Link");
    Tutorial tutorial12("Title", "Presenter", "Duration", 5, "Link");
    Tutorial tutorial22("Title", "Presenter2", "Duration2", 2, "Link2");
    assert(tutorial12 == tutorial22);
    tutorial22.setTitle("Title2");
    assert(!(tutorial12 == tutorial22));
    Tutorial tutorial13("Title", "Presenter", "Duration", 5, "Link");
    std::stringstream ss;
    ss << tutorial1;
    Tutorial tutorial23;
    ss >> tutorial23;
    assert(tutorial13 == tutorial23);

}
void testDynamicArray(){
    // Create a dynamic array of integers with initial capacity of 5
    DynamicArray<int> arr(5);

    // Test the addElement method
    arr.addElement(1);
    arr.addElement(2);
    assert(arr.lengthGetter() == 2);
    assert(arr.capacityGetter() == 5);

    arr.addElement(3);
    arr.addElement(4);
    arr.addElement(5);
    assert(arr.lengthGetter() == 5);
    assert(arr.capacityGetter() == 5);

    arr.addElement(6);
    assert(arr.lengthGetter() == 6);
    assert(arr.capacityGetter() == 10);

    // Test the operator[] method
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 4);
    assert(arr[4] == 5);
    assert(arr[5] == 6);

    // Test the deleteElement method
    arr.deleteElement(3);
    assert(arr.lengthGetter() == 5);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);
    assert(arr[3] == 5);
    assert(arr[4] == 6);

    arr.deleteElement(0);
    assert(arr.lengthGetter() == 4);
    assert(arr[0] == 2);
    assert(arr[1] == 3);
    assert(arr[2] == 5);
    assert(arr[3] == 6);

    arr.deleteElement(3);
    assert(arr.lengthGetter() == 3);
    assert(arr[0] == 2);
    assert(arr[1] == 3);
    assert(arr[2] == 5);

    // Test the copy constructor and assignment operator
    DynamicArray<int> arr2(arr);
    assert(arr2.lengthGetter() == 3);
    assert(arr2[0] == 2);
    assert(arr2[1] == 3);
    assert(arr2[2] == 5);

    DynamicArray<int> arr3(10);
    arr3 = arr2;
    assert(arr3.lengthGetter() == 3);
    assert(arr3[0] == 2);
    assert(arr3[1] == 3);
    assert(arr3[2] == 5);

    // Test the elementsGetter method
    int* elements = arr3.elementsGetter();
    assert(elements[0] == 2);
    assert(elements[1] == 3);
    assert(elements[2] == 5);

}
void testRepo(){
    Repository repo("test.txt");

    // Test addTutorialRepo
    Tutorial t1("title1", "presenter1", "Duration1", 100, "link1");
    repo.addTutorialRepo(t1);
    assert(repo.getTutorialsList().size() == 1);

    // Test findTutorialRepo
    Tutorial foundTutorial = repo.findTutorialRepo("title1");
    assert(foundTutorial == t1);

    // Test deleteTutorialRepo
    repo.deleteTutorialRepo("title1");
    assert(repo.getTutorialsList().size() == 0);
    bool exceptionThrown = false;
    try {
        repo.deleteTutorialRepo("title1");
    }
    catch (const RepoError&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // Test updateTutorialRepo
    Tutorial t2("title2", "presenter2", "duration2", 200, "link2");
    repo.addTutorialRepo(t2);
    repo.updateTutorialRepo("title2", Tutorial("newTitle", "newPresenter", "newDuration", 100, "newLink"));
    foundTutorial = repo.findTutorialRepo("newTitle");
    assert(foundTutorial.getPresenter() == "newPresenter");
    exceptionThrown = false;
    try {
        repo.updateTutorialRepo("nonexistentTitle", t1);
    }
    catch (const RepoError&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    Repository repository("testfile.txt");
    Tutorial tutorial("Test Title", "Test Presenter", "Duration", 10, "Test Link");
    repository.addTutorialRepo(tutorial);
    try {
        repository.addTutorialRepo(tutorial); // try to add the same tutorial again
        assert(false); // should not reach this point
    }
    catch (const RepoError& e) {
        assert(std::string(e.what()) == "This tutorial already exists !");
    }
    catch (...) {
        assert(false); // should not catch any other exception
    }

    // Test writeEntitiesToFile
    repo.writeEntitiesToFile();
}
void testUserRepo(){
    // Create a UserRepository
    UserRepository userRepository("test_user_file.txt");

    // Create a Tutorial
    Tutorial tutorial("Test Title", "Test Presenter", "Duration", 100, "www.test.com");

    // Test adding a tutorial to the watch list
    userRepository.addTutorialUserRepo(tutorial);
    assert(userRepository.getWatchList().size() == 1);

    // Test adding a duplicate tutorial to the watch list
    try {
        userRepository.addTutorialUserRepo(tutorial);
        assert(false);
    }
    catch (const RepoError& e) {
        assert(e.what() == std::string("This tutorial already exists !"));
    }

    // Test finding a tutorial in the watch list
    Tutorial foundTutorial = userRepository.findTutorialUserRepo("Test Title");
    assert(foundTutorial.getTitle() == "Test Title");

    // Test deleting a tutorial from the watch list
    userRepository.deleteTutorialUserRepo("Test Title");
    assert(userRepository.getWatchList().size() == 0);

    // Test deleting a non-existent tutorial from the watch list
    try {
        userRepository.deleteTutorialUserRepo("Non-existent Tutorial");
        assert(false);
    }
    catch (const RepoError& e) {
        assert(e.what() == std::string("Tutorial does not exist !"));
    }

    // Clean up the test file
    remove("test_user_file.txt");
}
void testService(){
    // Create a repository with some initial data
    Repository repo("test.txt");
    Service service(repo);

    // Add a tutorial to the repository
    service.addTutorialServ("Title 1", "Presenter 1", "10:00", 0, "www.link1.com");

    // Test getTutorialsList
    std::vector<Tutorial> tutorials = service.getTutorialsList();
    assert(tutorials.size() == 1);
    assert(tutorials[0].getTitle() == "Title 1");
    assert(tutorials[0].getPresenter() == "Presenter 1");
    assert(tutorials[0].getDuration() == "10:00");
    assert(tutorials[0].getLike() == 0);
    assert(tutorials[0].getLink() == "www.link1.com");

    // Add another tutorial
    service.addTutorialServ("Title 2", "Presenter 2", "20:00", 0, "www.link2.com");

    // Test getTutorialsList again
    tutorials = service.getTutorialsList();
    assert(tutorials.size() == 2);

    // Test removeTutorialServ
    service.removeTutorialServ("Title 1");
    tutorials = service.getTutorialsList();
    assert(tutorials.size() == 1);
    assert(tutorials[0].getTitle() == "Title 2");

    // Test updateTutorialServ
    service.updateTutorialServ("Title 2", "Presenter 3", "30:00", 1, "www.link3.com");
    tutorials = service.getTutorialsList();
    assert(tutorials[0].getTitle() == "Title 2");
    assert(tutorials[0].getPresenter() == "Presenter 3");
    assert(tutorials[0].getDuration() == "30:00");
    assert(tutorials[0].getLike() == 1);
    assert(tutorials[0].getLink() == "www.link3.com");

    // Test RepoError
    try {
        service.addTutorialServ("Title 2", "Presenter 2", "20:00", 0, "www.link2.com");
        assert(false);  // Shouldn't get here
    }
    catch (RepoError& e) {
        assert(std::string(e.what()) == "This tutorial already exists !");
    }

    try {
        service.removeTutorialServ("Title 3");
        assert(false);  // Shouldn't get here
    }
    catch (RepoError& e) {
        assert(std::string(e.what()) == "Tutorial does not exist !");
    }

    try {
        service.updateTutorialServ("Title 3", "Presenter 3", "30:00", 1, "www.link3.com");
        assert(false);  // Shouldn't get here
    }
    catch (RepoError& e) {
        assert(std::string(e.what()) == "Tutorial does not exist !");
    }
}
void testUserService(){
    UserRepository repo("user_test.txt");
    UserService service(repo);

    // Test adding a tutorial to the watchlist
    service.add("title1", "presenter1", "duration1", 10, "link1");
    assert(service.getWatchList().size() == 1);
    assert(service.getWatchList()[0].getTitle() == "title1");

    // Test adding a tutorial with the same title to the watchlist (should throw RepoError)
    try {
        service.add("title1", "presenter2", "duration2", 20, "link2");
    }
    catch (RepoError& e) {
        assert(true); // RepoError should be thrown
    }
    assert(service.getWatchList().size() == 1);
    assert(service.getWatchList()[0].getPresenter() == "presenter1"); // Check that the original tutorial is still in the watchlist

    // Test removing a tutorial from the watchlist
    service.remove("title1");
    assert(service.getWatchList().size() == 0);

    // Test removing a tutorial that does not exist from the watchlist (should throw RepoError)
    try {
        service.remove("title1");
    }
    catch (RepoError& e) {
        assert(true); // RepoError should be thrown
    }
}
void runAllTests(){
    testDomain();
    testDynamicArray();
    testRepo();
    testUserRepo();
    testService();
    testUserService();
}