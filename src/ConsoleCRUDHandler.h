#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "NoteManager.h"
#include "Note.h"

class ConsoleCRUDHandler {
private:
    NoteManager manager;

public:
    // CREATE Handler
    void handleCreateNote() {
        std::string id, title, category, tagsInput, date, content;

        std::cout << "Enter Note ID: "; std::getline(std::cin, id);
        std::cout << "Enter Title: "; std::getline(std::cin, title);
        std::cout << "Enter Category: "; std::getline(std::cin, category);
        std::cout << "Enter Tags (comma-separated): "; std::getline(std::cin, tagsInput);
        std::cout << "Enter Date (YYYY-MM-DD): "; std::getline(std::cin, date);
        std::cout << "Enter Text Content: "; std::getline(std::cin, content);

        std::vector<std::string> tags;
        std::stringstream ss(tagsInput);
        std::string tag;
        while (std::getline(ss, tag, ',')) {
            if (!tag.empty()) tags.push_back(tag);
        }

        manager.addNote(new TextNote(id, title, category, tags, date, content));
    }

    // READ Handler
    void handleReadNotes() {
        manager.displayAllNotes();
    }

    // UPDATE Handler
    void handleUpdateNote() {
        std::string id, newTitle;
        std::cout << "Enter Note ID to Update: ";
        std::getline(std::cin, id);
        std::cout << "Enter New Title: ";
        std::getline(std::cin, newTitle);

        if (manager.updateNoteTitle(id, newTitle)) {
            std::cout << "Note title updated successfully!\n";
        } else {
            std::cout << "Note ID not found.\n";
        }
    }

    // DELETE Handler
    void handleDeleteNote() {
        std::string id;
        std::cout << "Enter ID of note to delete: ";
        std::getline(std::cin, id);

        if (manager.deleteNote(id)) {
            std::cout << "Note deleted successfully.\n";
        } else {
            std::cout << "Note ID not found.\n";
        }
    }
};
