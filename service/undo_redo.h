// UndoAction.h
#pragma once
#include "domain/event.h"
#include "repository/repository.h"
#include <memory>

class UndoAction {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~UndoAction() = default;
};

class AddUndoAction : public UndoAction {
    EventRepository& repo;
    Event event;

public:
    AddUndoAction(EventRepository& r, const Event& e) : repo(r), event(e) {}
    void undo() override { repo.remove(event.getTitle()); }
    void redo() override { repo.add(event); }
};

class RemoveUndoAction : public UndoAction {
    EventRepository& repo;
    Event event;

public:
    RemoveUndoAction(EventRepository& r, const Event& e) : repo(r), event(e) {}
    void undo() override { repo.add(event); }
    void redo() override { repo.remove(event.getTitle()); }
};

class UpdateUndoAction : public UndoAction {
    EventRepository& repo;
    Event oldEvent;
    Event newEvent;

public:
    UpdateUndoAction(EventRepository& r, const Event& oldE, const Event& newE)
        : repo(r), oldEvent(oldE), newEvent(newE) {}

    void undo() override { repo.update(oldEvent); }
    void redo() override { repo.update(newEvent); }
};
