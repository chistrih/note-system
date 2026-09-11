#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <chrono>
#include <ctime>
#include <memory>
#include "NoteManager.h"
#include "TextNote.h"
#include "Colors.h"

class ConsoleCRUDHandler {
private:
    NoteManager manager;

    void pause() {
        std::cout << "\n" << Color::DIM << "Press Enter to return to the menu..." << Color::RESET;
        std::string dummy;
        std::getline(std::cin, dummy);
    }

public:
    void run() {
        bool running = true;
        while (running) {
            std::cout << Color::CLEAR; 
            
            std::cout << Color::BOLD << "--- CLI Note System ---" << Color::RESET << "\n";
            std::cout << "1. Create Note\n2. Read All Notes\n3. Update Note\n4. Delete Note\n5. Exit\n";
            std::cout << Color::YELLOW << ">> Select an option: " << Color::RESET;
            
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: 
                    handleCreateNote(); 
                    pause(); 
                    break;
                case 2: 
                    handleReadNotes(); 
                    pause(); 
                    break;
                case 3: 
                    handleUpdateNote(); 
                    pause(); 
                    break;
                case 4: 
                    handleDeleteNote(); 
                    pause(); 
                    break;
                case 5: 
                    std::cout << Color::GREEN << "Goodbye!\n" << Color::RESET;
                    running = false; 
                    break;
                default: 
                    std::cout << Color::RED << "Invalid choice. Try again.\n" << Color::RESET;
                    pause();
            }
        }
    }

    void handleCreateNote() {
        std::string title, content;

        std::string id = manager.generateNextId();
        std::cout << "Creating Note ID: " << Color::CYAN << id << Color::RESET << "\n";

        std::cout << "Enter Title: "; std::getline(std::cin, title);
        std::cout << "Enter Text Content: "; std::getline(std::cin, content);

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* local_time = std::localtime(&now_time);
        
        char timeBuffer[80];
        std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", local_time);
        std::string date(timeBuffer);

        manager.addNote(std::unique_ptr<TextNote>(new TextNote(id, title, date, content)));
        std::cout << Color::GREEN << "Note added successfully!\n" << Color::RESET;
    }

    void handleReadNotes() { manager.displayAllNotes(); }

    void handleUpdateNote() {
        std::string id;
        std::cout << Color::YELLOW << "Enter Note ID to Update: " << Color::RESET;
        std::getline(std::cin, id);

        std::cout << "What would you like to update?\n";
        std::cout << "1. Title\n";
        std::cout << "2. Content\n";
        std::cout << Color::YELLOW << "Select an option: " << Color::RESET;
        
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
                std::cout << Color::GREEN << "Note title updated successfully!\n" << Color::RESET;
            } else {
                std::cout << Color::RED << "Note ID not found.\n" << Color::RESET;
            }
        } 
        else if (choice == 2) {
            std::string newContent;
            std::cout << "Enter New Content: ";
            std::getline(std::cin, newContent);
            
            if (manager.updateNoteContent(id, newContent)) {
                std::cout << Color::GREEN << "Note content updated successfully!\n" << Color::RESET;
            } else {
                std::cout << Color::RED << "Note ID not found.\n" << Color::RESET;
            }
        } 
        else {
            std::cout << Color::RED << "Invalid choice. Returning to main menu.\n" << Color::RESET;
        }
    }

    void handleDeleteNote() {
        std::string id;
        std::cout << Color::YELLOW << "Enter ID of note to delete: " << Color::RESET;
        std::getline(std::cin, id);

        if (manager.deleteNote(id)) {
            std::cout << Color::GREEN << "Note #" << id << " deleted successfully.\n" << Color::RESET;
        } else {
            std::cout << Color::RED << "Error: Note ID not found.\n" << Color::RESET;
        }
    }
};
