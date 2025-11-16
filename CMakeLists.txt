cmake_minimum_required(VERSION 3.30)
project(Event-manager-OOP)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.9.0\\mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)



set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
include_directories(
        domain
        repository
        service
        gui
        models
        infrastructure
        data
)
add_executable(Event_manager-OOP
    infrastructure/CSVEventList.cpp
    infrastructure/CSVEventList.h
    domain/event.cpp
    domain/event.h
    data/event.txt
    infrastructure/EventList.cpp
    infrastructure/EventList.h
    domain/EventsValidator.cpp
    domain/EventsValidator.h
    infrastructure/FileEventList.cpp
    infrastructure/FileEventList.h
    gui/GUI.cpp
    gui/GUI.h
        infrastructure/HTMLEventList.cpp
    infrastructure/HTMLEventList.h
    main.cpp
    repository/repository.cpp
    repository/repository.h
    repository/RepositoryExceptions.cpp
    repository/RepositoryExceptions.h
    service/service.cpp
    service/service.h
        service/undo_redo.h
        models/EventTableModel.cpp
        models/EventTableModel.h
        gui/EventListWindow.cpp
        gui/EventListWindow.h
    data/events.csv
    data/events.html)
target_link_libraries(Event_manager-OOP PRIVATE Qt6::Widgets)