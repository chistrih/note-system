#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <ctime>
#include <iomanip>
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
                std::cin.clear();
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
        std::string title, content;

        std::string id = manager.generateNextID();
        std::cout << "Note #" << id << "\n";

        std::cout << "Enter Title: "; std::getline(std::cin, title);
        std::cout << "Enter Text Content: "; std::getline(std::cin, content);
        
        // Auto-generate the local date and time
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* local_time = std::localtime(&now_time);
        
        char timeBuffer[80];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", local_time);
        std::string date(timeBuffer);

        manager.addNote(std::unique_ptr<TextNote>(new TextNote(id, title, date, content)));
    }

    void handleReadNotes() { manager.displayAllNotes(); }

    void handleUpdateNote() {
        std::string id, newTitle;
        std::cout << "Enter Note ID to Update: ";
        std::getline(std::cin, id);
        
        std::cout << "1. Title\n";
        std::cout << "2. Content\n";
        std::cout << "Select an option: ";
        
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::string newTitle;
            std::cout << "Enter New Title: ";
            std::getline(std::cin, newTitle);
            
            if (manager.updateNoteTitle(id, newTitle)) {
                std::cout << "Note title updated successfully!\n";
            } else {
                std::cout << "Note ID not found.\n";
            }
        } 
        else if (choice == 2) {
            std::string newContent;
            std::cout << "Enter New Content: ";
            std::getline(std::cin, newContent);
            
            if (manager.updateNoteContent(id, newContent)) {
                std::cout << "Note content updated successfully!\n";
            } else {
                std::cout << "Note ID not found.\n";
            }
        } 
        else {
            std::cout << "Invalid choice. Returning to main menu.\n";
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
