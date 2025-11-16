 #include "GUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QDialog>
#include <QApplication>
#include <QTimer>
#include "HTMLEventList.h"
#include "CSVEventList.h"
#include "EventListWindow.h"


RoleSelectionWindow::RoleSelectionWindow(Service& serv) : serv{serv} {

    chooseFileType();

    this->initGUI();
    this->connectSignalsAndSlots();
}

void RoleSelectionWindow::chooseFileType() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Choose File Type");
    QVBoxLayout* layout = new QVBoxLayout(dialog);

    QLabel* label = new QLabel("Choose file type for your events list:");
    layout->addWidget(label);

    QRadioButton* csvRadio = new QRadioButton("CSV");
    QRadioButton* htmlRadio = new QRadioButton("HTML");
    csvRadio->setChecked(true);

    layout->addWidget(csvRadio);
    layout->addWidget(htmlRadio);

    QLabel* filenameLabel = new QLabel("Enter filename:");
    QLineEdit* filenameEdit = new QLineEdit("events.csv");
    layout->addWidget(filenameLabel);
    layout->addWidget(filenameEdit);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    connect(csvRadio, &QRadioButton::toggled, [filenameEdit](bool checked) {
        if (checked) {
            filenameEdit->setText("events.csv");
        }
    });
    connect(htmlRadio, &QRadioButton::toggled, [filenameEdit](bool checked) {
        if (checked) {
            filenameEdit->setText("events.html");
        }
    });

    if (dialog->exec() == QDialog::Accepted) {
        FileEventlist* userEventList = nullptr;

        if (csvRadio->isChecked()) {
            userEventList = new CSVEventlist();
        } else {
            userEventList = new HTMLEventlist();
        }

        userEventList->setFilename(filenameEdit->text().toStdString());
        serv = Service(serv.getRepo(), userEventList, EventValidator());
    }

    delete dialog;
}

void RoleSelectionWindow::initGUI() {
    setWindowTitle("Life After School Event Manager");
    resize(400, 300);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);


    titleLabel = new QLabel("Welcome to Life After School Event Manager");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);


    QLabel* selectLabel = new QLabel("Please select your role:");
    selectLabel->setAlignment(Qt::AlignCenter);
    QFont selectFont = selectLabel->font();
    selectFont.setPointSize(12);
    selectLabel->setFont(selectFont);
    mainLayout->addWidget(selectLabel);
    mainLayout->addSpacing(30);


    adminButton = new QPushButton("Admin");
    userButton = new QPushButton("User");

    QFont buttonFont;
    buttonFont.setPointSize(12);

    adminButton->setFont(buttonFont);
    userButton->setFont(buttonFont);

    adminButton->setMinimumHeight(50);
    userButton->setMinimumHeight(50);

    mainLayout->addWidget(adminButton);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(userButton);
    mainLayout->addStretch();
}

void RoleSelectionWindow::connectSignalsAndSlots() {
    QObject::connect(adminButton, &QPushButton::clicked, this, &RoleSelectionWindow::openAdminWindow);
    QObject::connect(userButton, &QPushButton::clicked, this, &RoleSelectionWindow::openUserWindow);
}

void RoleSelectionWindow::openAdminWindow() {
    AdminWindow* adminWindow = new AdminWindow(serv, this);
    adminWindow->show();
    this->hide();
}

void RoleSelectionWindow::openUserWindow() {
    UserWindow* userWindow = new UserWindow(serv, this);
    userWindow->show();
    this->hide();
}


AdminWindow::AdminWindow(Service& serv, QWidget* parent) : QMainWindow(parent), serv{serv} {
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void AdminWindow::initGUI() {
    setWindowTitle("Admin - Life After School Event Manager");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* adminLabel = new QLabel("Admin Panel - All Events");
    QFont labelFont = adminLabel->font();
    labelFont.setPointSize(14);
    labelFont.setBold(true);
    adminLabel->setFont(labelFont);
    adminLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(adminLabel);

    allEvents = new QListWidget{};
    mainLayout->addWidget(allEvents);

    QFormLayout* formLayout = new QFormLayout{};
    lineTitle = new QLineEdit{};
    lineDescription = new QLineEdit{};
    lineDate = new QLineEdit{};
    lineTime = new QLineEdit{};
    linePeople = new QLineEdit{};
    lineLink = new QLineEdit{};

    formLayout->addRow("Title", lineTitle);
    formLayout->addRow("Description", lineDescription);
    formLayout->addRow("Date (yyyy-mm-dd)", lineDate);
    formLayout->addRow("Time (HH:MM)", lineTime);
    formLayout->addRow("People", linePeople);
    formLayout->addRow("Link", lineLink);
    mainLayout->addLayout(formLayout);

    QHBoxLayout* adminButtons = new QHBoxLayout{};
    addButton = new QPushButton("Add");
    deleteButton = new QPushButton("Delete");
    updateButton = new QPushButton("Update");
    adminButtons->addWidget(addButton);
    adminButtons->addWidget(deleteButton);
    adminButtons->addWidget(updateButton);
    mainLayout->addLayout(adminButtons);


    backButton = new QPushButton("Back to Role Selection");
    undoButton= new QPushButton("Undo");
    redoButton = new QPushButton("Redo");
    undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    mainLayout->addWidget(backButton);
    mainLayout->addWidget(undoButton);
    mainLayout->addWidget(redoButton);
}

void AdminWindow::populateList() {
    allEvents->clear();
    auto events = serv.getAllEvents();

    for (const auto& e : events) {
        QString display = QString::fromStdString(
            e.getTitle() + " | " + e.getDescription() + " | " +
            e.getDate() + " | " + e.getTime() + " | " +
            std::to_string(e.getPeople()) + " | " + e.getLink());
        allEvents->addItem(display);
    }
}

void AdminWindow::connectSignalsAndSlots() {
    QObject::connect(addButton, &QPushButton::clicked, this, &AdminWindow::addButtonHandler);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &AdminWindow::deleteButtonHandler);
    QObject::connect(updateButton, &QPushButton::clicked, this, &AdminWindow::updateButtonHandler);
    QObject::connect(allEvents, &QListWidget::itemSelectionChanged, this, &AdminWindow::populateFieldsFromSelection);
    QObject::connect(backButton, &QPushButton::clicked, this, &AdminWindow::backButtonHandler);
    connect(undoButton, &QPushButton::clicked, this, [this]() {
    try {
        serv.undo();
        populateList();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Failed", e.what());
    }
});

    connect(redoButton, &QPushButton::clicked, this, [this]() {
        try {
            serv.redo();
            populateList();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Redo Failed", e.what());
        }
    });
    connect(undoShortcut, &QShortcut::activated, this, [this]() {
    try {
        serv.undo();
        populateList();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Failed", e.what());
    }
});
    connect(redoShortcut, &QShortcut::activated, this, [this]() {
    try {
        serv.redo();
        populateList();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo Failed", e.what());
    }
});
}

void AdminWindow::addButtonHandler() {
    try {
        serv.addEvent(
            lineTitle->text().toStdString(),
            lineDescription->text().toStdString(),
            lineDate->text().toStdString(),
            lineTime->text().toStdString(),
            std::stoi(linePeople->text().toStdString()),
            lineLink->text().toStdString()
        );
        this->populateList();


        lineTitle->clear();
        lineDescription->clear();
        lineDate->clear();
        lineTime->clear();
        linePeople->clear();
        lineLink->clear();

        QMessageBox::information(this, "Success", "Event added successfully!");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminWindow::deleteButtonHandler() {
    try {
        std::string title = lineTitle->text().toStdString();
        if (title.empty()) {
            QMessageBox::warning(this, "Warning", "Please select an event to delete.");
            return;
        }

        serv.removeEvent(title);
        this->populateList();


        lineTitle->clear();
        lineDescription->clear();
        lineDate->clear();
        lineTime->clear();
        linePeople->clear();
        lineLink->clear();

        QMessageBox::information(this, "Success", "Event deleted successfully!");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminWindow::updateButtonHandler() {
    try {
        std::string title = lineTitle->text().toStdString();
        if (title.empty()) {
            QMessageBox::warning(this, "Warning", "Please select an event to update.");
            return;
        }

        serv.updateEvent(
            title,
            lineDescription->text().toStdString(),
            lineDate->text().toStdString(),
            lineTime->text().toStdString(),
            std::stoi(linePeople->text().toStdString()),
            lineLink->text().toStdString()
        );

        this->populateList();
        lineTitle->clear();
        lineDescription->clear();
        lineDate->clear();
        lineTime->clear();
        linePeople->clear();
        lineLink->clear();

        QMessageBox::information(this, "Success", "Event updated successfully!");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void AdminWindow::populateFieldsFromSelection() {
    QListWidgetItem* selectedItem = allEvents->currentItem();
    if (!selectedItem) {
        return;
    }

    QString fullText = selectedItem->text();
    QStringList parts = fullText.split(" | ");

    if (parts.size() >= 6) {
        lineTitle->setText(parts[0]);
        lineDescription->setText(parts[1]);
        lineDate->setText(parts[2]);
        lineTime->setText(parts[3]);
        linePeople->setText(parts[4]);
        lineLink->setText(parts[5]);
    }
}

void AdminWindow::backButtonHandler() {

    if (parentWidget()) {
        parentWidget()->show();
    }

    this->close();
}


UserWindow::UserWindow(Service& serv, QWidget* parent) : QMainWindow(parent), serv{serv}, currentEventIndex{0} {
    this->initGUI();
    this->loadFilteredEvents();
    this->populateMyEventsList();
    this->connectSignalsAndSlots();
}

void UserWindow::initGUI() {
    setWindowTitle("User - Life After School Event Manager");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* userLabel = new QLabel("User Panel - Browse Events");
    QFont labelFont = userLabel->font();
    labelFont.setPointSize(14);
    labelFont.setBold(true);
    userLabel->setFont(labelFont);
    userLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(userLabel);


    QHBoxLayout* filterLayout = new QHBoxLayout{};
    monthCombo = new QComboBox{};
    QStringList months = { "All Months", "01", "02", "03", "04", "05", "06",
                           "07", "08", "09", "10", "11", "12" };
    monthCombo->addItems(months);
    filterButton = new QPushButton("Filter");

    filterLayout->addWidget(new QLabel("Month:"));
    filterLayout->addWidget(monthCombo);
    filterLayout->addWidget(filterButton);
    mainLayout->addLayout(filterLayout);


    eventDetailsLabel = new QLabel("Current Event:");
    mainLayout->addWidget(eventDetailsLabel);

    eventDetails = new QTextEdit{};
    eventDetails->setReadOnly(true);
    eventDetails->setMinimumHeight(150);
    mainLayout->addWidget(eventDetails);

    QHBoxLayout* eventNavLayout = new QHBoxLayout{};
    addToMyListButton = new QPushButton("Add to My Events");
    openLinkButton = new QPushButton("Open Event Link");
    nextEventButton = new QPushButton("Next Event >");

    eventNavLayout->addWidget(addToMyListButton);
    eventNavLayout->addWidget(openLinkButton);
    eventNavLayout->addWidget(nextEventButton);
    mainLayout->addLayout(eventNavLayout);


    QLabel* myEventsLabel = new QLabel("My Events:");
    myEventsLabel->setFont(labelFont);
    mainLayout->addWidget(myEventsLabel);

    myEventsList = new QListWidget{};
    mainLayout->addWidget(myEventsList);

    QHBoxLayout* userButtons = new QHBoxLayout{};
    removeMyEventButton = new QPushButton("Remove Selected");
    openListButton = new QPushButton("Open My Events File");
    userButtons->addWidget(removeMyEventButton);
    userButtons->addWidget(openListButton);
    mainLayout->addLayout(userButtons);


    backButton = new QPushButton("Back to Role Selection");
    watchListButton= new QPushButton("Watch List");
    mainLayout->addWidget(watchListButton);
    mainLayout->addWidget(backButton);
}

void UserWindow::connectSignalsAndSlots() {
    QObject::connect(filterButton, &QPushButton::clicked, this, &UserWindow::loadFilteredEvents);
    QObject::connect(nextEventButton, &QPushButton::clicked, this, &UserWindow::nextEventHandler);
    QObject::connect(addToMyListButton, &QPushButton::clicked, this, &UserWindow::addToMyListHandler);
    QObject::connect(openLinkButton, &QPushButton::clicked, this, &UserWindow::openLinkHandler);
    QObject::connect(myEventsList, &QListWidget::itemClicked, this, &UserWindow::myEventSelected);
    QObject::connect(removeMyEventButton, &QPushButton::clicked, this, &UserWindow::removeFromMyListHandler);
    QObject::connect(openListButton, &QPushButton::clicked, this, &UserWindow::openFileHandler);
    QObject::connect(backButton, &QPushButton::clicked, this, &UserWindow::backButtonHandler);
    QObject::connect(watchListButton, &QPushButton::clicked, this, &UserWindow::openWatchListWindow);

}
void UserWindow::openWatchListWindow() {
    auto* window = new WatchListWindow(serv);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}
void UserWindow::loadFilteredEvents() {

    filteredEvents.clear();
    currentEventIndex = 0;

    QString selectedMonth = monthCombo->currentText();
    std::string monthStr = selectedMonth == "All Months" ? "" : selectedMonth.toStdString();


    filteredEvents = serv.getEventsByMonth(monthStr);


    if (!filteredEvents.empty()) {
        showCurrentEvent();
    } else {
        eventDetails->clear();
        eventDetails->setText("No events found for the selected month.");
    }
}

void UserWindow::showCurrentEvent() {
    if (filteredEvents.empty()) {
        eventDetails->setText("No events available.");
        return;
    }

    if (currentEventIndex >= filteredEvents.size()) {
        currentEventIndex = 0;
    }


    const Event& event = filteredEvents[currentEventIndex];
    showEventDetails(event);
}

void UserWindow::nextEventHandler() {
    if (filteredEvents.empty()) {
        return;
    }


    currentEventIndex = (currentEventIndex + 1) % filteredEvents.size();
    showCurrentEvent();
}

void UserWindow::populateMyEventsList() {
    myEventsList->clear();

    auto events = serv.getUserEvents();

    for (const auto& e : events) {
        QString display = QString::fromStdString(
            e.getTitle() + " | " + e.getDescription() + " | " +
            e.getDate() + " | " + e.getTime() + " | " +
            std::to_string(e.getPeople()) + " | " + e.getLink());
        QListWidgetItem* item = new QListWidgetItem(display);
        item->setData(Qt::UserRole, QString::fromStdString(e.getTitle()));
        myEventsList->addItem(item);
    }
}

void UserWindow::showEventDetails(const Event& event) {
    QString details = QString("Title: %1\n"
                     "Description: %2\n"
                     "Date: %3\n"
                     "Time: %4\n"
                     "People Going: %5\n"
                     "Link: %6")
                    .arg(QString::fromStdString(event.getTitle()))
                    .arg(QString::fromStdString(event.getDescription()))
                    .arg(QString::fromStdString(event.getDate()))
                    .arg(QString::fromStdString(event.getTime()))
                    .arg(QString::number(event.getPeople()))
                    .arg(QString::fromStdString(event.getLink()));

    eventDetails->setText(details);
    currentEvent = event;
}



void UserWindow::myEventSelected(QListWidgetItem* item) {
    if (!item) {
        return;
    }

    QString title = item->data(Qt::UserRole).toString();
    const auto& events = serv.getUserEvents();

    auto it = std::find_if(events.begin(), events.end(),
                         [&title](const Event& e) {
                             return e.getTitle() == title.toStdString();
                         });

    if (it != events.end()) {
        showEventDetails(*it);
    }
}
void UserWindow::addToMyListHandler() {
    try {
        if (filteredEvents.empty() || currentEventIndex >= filteredEvents.size()) {
            QMessageBox::warning(this, "Warning", "Please select an event first.");
            return;
        }

        const Event& event = filteredEvents[currentEventIndex];
        serv.addToUserList(event);


        int savedIndex = currentEventIndex;


        QString selectedMonth = monthCombo->currentText();
        std::string monthStr = selectedMonth == "All Months" ? "" : selectedMonth.toStdString();
        filteredEvents = serv.getEventsByMonth(monthStr);


        if (!filteredEvents.empty()) {
            currentEventIndex = std::min(savedIndex, static_cast<int>(filteredEvents.size() - 1));
            showCurrentEvent();
        }

        this->populateMyEventsList();

        QMessageBox::information(this, "Success", "Event added to your list!");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
void UserWindow::removeFromMyListHandler() {
    QListWidgetItem* selectedItem = myEventsList->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Warning", "Please select an event to remove.");
        return;
    }

    try {
        QString title = selectedItem->data(Qt::UserRole).toString();
        serv.removeFromUserList(title.toStdString());


        int savedIndex = currentEventIndex;


        QString selectedMonth = monthCombo->currentText();
        std::string monthStr = selectedMonth == "All Months" ? "" : selectedMonth.toStdString();
        filteredEvents = serv.getEventsByMonth(monthStr);


        if (!filteredEvents.empty()) {
            currentEventIndex = std::min(savedIndex, static_cast<int>(filteredEvents.size() - 1));
            showCurrentEvent();
        }

        this->populateMyEventsList();

        QMessageBox::information(this, "Success", "Event removed from your list!");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
void UserWindow::openLinkHandler() {
    if (filteredEvents.empty() || currentEventIndex >= filteredEvents.size()) {
        QMessageBox::warning(this, "Warning", "Please select an event first.");
        return;
    }

    const Event& event = filteredEvents[currentEventIndex];
    QDesktopServices::openUrl(QUrl(QString::fromStdString(event.getLink())));
}

void UserWindow::openFileHandler() {
    try {
        serv.saveToFile();
        serv.openFile();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void UserWindow::backButtonHandler() {

    if (parentWidget()) {
        parentWidget()->show();
    }

    this->close();
}