#include <QApplication>
#include "gui/GUI.h"
#include "repository/repository.h"
#include "repository/RepositoryExceptions.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    EventRepository repo(R"(C:\Users\Gica11\CLionProjects\Event-manager-OOP\data\event.txt)");

    EventValidator validator;


    FileEventlist* eventList = nullptr;


    Service service(repo, eventList, validator);


    RoleSelectionWindow mainWindow(service);
    mainWindow.show();


    return app.exec();


}