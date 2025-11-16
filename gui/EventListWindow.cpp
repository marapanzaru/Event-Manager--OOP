
#include "EventListWindow.h"


WatchListWindow::WatchListWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    model = new EventTableModel({}, this);
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    layout->addWidget(tableView);
    setLayout(layout);

    loadData();
}

void WatchListWindow::loadData() {
    model->setEvents(service.getUserEvents());
}
