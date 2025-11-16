# Life After School — Event Manager
A C++ & Qt application for managing and organizing events.  
Built with a layered architecture, file persistence, custom undo/redo logic, and a complete Qt GUI.

---

##  Overview
**Life After School – Event Manager** is a desktop application that helps users browse, manage, and save events happening in their city.

The program supports:

- **Administrator Mode:** fully manage events
- **User Mode:** browse events one-by-one, filter by month, save them to a personal list
- **File Persistence:** events stored in text files
- **CSV/HTML Export:** user’s event list saved in chosen format
- **Undo/Redo:** implemented with inheritance & polymorphism
- **Qt GUI:** interactive interface for all features
- **QTableView Model:** custom model used to display events in a table

---

## ️ Features Implemented

###  Administrator Features
- Add new events
- Remove existing events
- Update event information
- View all events in a table
- Undo/Redo for add/remove/update
- Persistent storage via text file

###  User Features
- Browse events one at a time
- Filter events by month
- Open event links in a browser
- Add events to a personal watchlist
- Remove events from the watchlist
- Save list as **CSV** or **HTML**
- Open CSV in a text editor / HTML in browser
- View watchlist in a **QTableView** using a custom model

---

##  Graphical User Interface (Qt)
The application includes a modern, functional GUI created using Qt:

- Built using layouts 
- Admin and User windows
- Dynamic tables populated from files
- Dialogs and message boxes for interactions
- Separate Watchlist window using a `QAbstractTableModel`
- Undo/Redo buttons
- Keyboard shortcuts (`Ctrl+Z`, `Ctrl+Y`)
- Opening of external links

---

##  Architecture
The project follows a structured, layered architecture:
- domain → Entities (Event), Validators
- repository → Event repository using file storage
- service → Business logic, filtering, undo/redo
- gui → All Qt windows and interface logic
- models → QAbstractTableModel implementation
- infrastructure → CSV + HTML exporting logic
- data → Input text file with events

---
##  File Persistence
At startup, events are loaded from:
- data/events.txt
- All add/update/delete operations write back immediately using overloaded stream operators.

---
##  Undo / Redo
Undo/Redo is implemented using:

- Base abstract `UndoRedoAction`
- Derived classes (`AddOperation`, `DeleteOperation`, `UpdateOperation`)
- Two stacks inside the Service layer
- Invoked via:
  - Toolbar buttons
  - Shortcuts (`Ctrl+Z`, `Ctrl+Y`)

---
## Author

Project developed as part of Object-Oriented Programming course.

Designed to showcase C++, Qt, clean architecture, and GUI development skills.
