#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "NoteManager.h"
#include "TextNote.h"

class ConsoleCRUDHandler {
private:
    NoteManager manager;

public:
    void run() {
        bool running = true;
        while (running) {
            std::cout << "\n--- CLI Note System ---\n";
            std::cout << "1. Create Note\n2. Read All Notes\n3. Update Note Title\n4. Delete Note\n5. Exit\n";
            std::cout << "Select an option: ";
            
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear(); // Clear error state
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: handleCreateNote(); break;
                case 2: handleReadNotes(); break;
                case 3: handleUpdateNote(); break;
                case 4: handleDeleteNote(); break;
                case 5: running = false; break;
                default: std::cout << "Invalid choice. Try again.\n";
            }
        }
    }

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

        // Use std::make_unique to safely create and pass the pointer
        manager.addNote(std::unique_ptr<TextNote>(new TextNote(id, title, category, tags, date, content)));
    }

    void handleReadNotes() { manager.displayAllNotes(); }

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
