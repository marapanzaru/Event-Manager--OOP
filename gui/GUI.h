#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QMainWindow>
#include <QString>
#include <QTimer>
#include "service/Service.h"
#include "domain/Event.h"
#include <QLabel>
#include <QShortcut>


class AdminWindow;
class UserWindow;


class RoleSelectionWindow : public QMainWindow {
    Q_OBJECT

private:
    Service& serv;
    QPushButton* adminButton;
    QPushButton* userButton;
    QLabel* titleLabel;

public:
    RoleSelectionWindow(Service& serv);
    void initGUI();
    void connectSignalsAndSlots();
    void openAdminWindow();
    void openUserWindow();
    void chooseFileType();
};


class AdminWindow : public QMainWindow {
    Q_OBJECT

private:
    Service& serv;

    QListWidget* allEvents;
    QLineEdit* lineTitle;
    QLineEdit* lineDescription;
    QLineEdit* lineDate;
    QLineEdit* lineTime;
    QLineEdit* linePeople;
    QLineEdit* lineLink;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* backButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QShortcut* undoShortcut;
    QShortcut* redoShortcut;

public:
    AdminWindow(Service& serv, QWidget* parent = nullptr);
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();


    void addButtonHandler();
    void deleteButtonHandler();
    void updateButtonHandler();
    void populateFieldsFromSelection();
    void backButtonHandler();
};


class UserWindow : public QMainWindow {
    Q_OBJECT

private:
    Service& serv;
    Event currentEvent;

    QComboBox* monthCombo;
    QPushButton* filterButton;
    QLabel* eventDetailsLabel;
    QTextEdit* eventDetails;
    QPushButton* addToMyListButton;
    QPushButton* openLinkButton;
    QPushButton* nextEventButton;
    QListWidget* myEventsList;
    QPushButton* removeMyEventButton;
    QPushButton* openListButton;
    QPushButton* backButton;
    QPushButton* watchListButton;


    std::vector<Event> filteredEvents;
    int currentEventIndex;

public:
    UserWindow(Service& serv, QWidget* parent = nullptr);
    void initGUI();
    void populateMyEventsList();
    void showEventDetails(const Event& event);
    void connectSignalsAndSlots();
    ///void updateMyEventDetailsDisplay();


    void openWatchListWindow();
    void loadFilteredEvents();
    void showCurrentEvent();
    void nextEventHandler();
    void myEventSelected(QListWidgetItem* item);
    void addToMyListHandler();
    void removeFromMyListHandler();
    void openLinkHandler();
    void openFileHandler();
    void backButtonHandler();
};