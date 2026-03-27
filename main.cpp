#include <QApplication>
#include "gui/GUI.h"
#include "repository/repository.h"
#include "repository/RepositoryExceptions.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    EventRepository repo("event.txt");

    EventValidator validator;


    FileEventlist* eventList = nullptr;


    Service service(repo, eventList, validator);


    RoleSelectionWindow mainWindow(service);
    mainWindow.show();


    return app.exec();


}
