#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHeaderView>
#include "models/EventTableModel.h"

#include "service/Service.h"

class WatchListWindow : public QWidget {
    Q_OBJECT
private:
    QTableView* tableView;
    EventTableModel* model;
    Service& service;

public:
    explicit WatchListWindow(Service& service, QWidget* parent = nullptr);
    void loadData();
};
