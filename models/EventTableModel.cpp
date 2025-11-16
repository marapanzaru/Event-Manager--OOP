#include "EventTableModel.h"

EventTableModel::EventTableModel(const std::vector<Event>& events, QObject* parent)
    : QAbstractTableModel(parent), events(events) {}

int EventTableModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(events.size());
}

int EventTableModel::columnCount(const QModelIndex&) const {
    return 6;
}

QVariant EventTableModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole || !index.isValid())
        return {};

    const Event& ev = events.at(index.row());
    switch (index.column()) {
        case 0: return QString::fromStdString(ev.getTitle());
        case 1: return QString::fromStdString(ev.getDescription());
        case 2: return QString::fromStdString(ev.getDate());
        case 3: return QString::fromStdString(ev.getTime());
        case 4: return QString::number(ev.getPeople());
        case 5: return QString::fromStdString(ev.getLink());
        default: return {};
    }
}

QVariant EventTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Title";
            case 1: return "Description";
            case 2: return "Date";
            case 3: return "Time";
            case 4: return "Attendees";
            case 5: return "Link";
            default: return {};
        }
    }
    return {};
}

void EventTableModel::setEvents(const std::vector<Event>& newEvents) {
    beginResetModel();
    events = newEvents;
    endResetModel();
}

