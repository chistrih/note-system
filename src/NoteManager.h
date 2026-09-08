#pragma once
#include "Note.h"
#include <vector>
#include <algorithm>

class NoteManager {
private:
    std::vector<Note*> notes;

public:
    ~NoteManager() {
        for (auto* note : notes) {
            delete note;
        }
        notes.clear();
    }

    // CREATE Operation
    void addNote(Note* note) {
        notes.push_back(note);
        std::cout << "Note added successfully!\n";
    }

    // READ Operations
    void displayAllNotes() const {
        if (notes.empty()) {
            std::cout << "No notes found.\n";
            return;
        }
        for (const auto* note : notes) {
            note->display();
        }
    }

    Note* findNoteById(const std::string& id) const {
        for (auto* note : notes) {
            if (note->getId() == id) return note;
        }
        return nullptr;
    }

    // UPDATE Operation
    bool updateNoteTitle(const std::string& id, const std::string& newTitle) {
        Note* note = findNoteById(id);
        if (note != nullptr) {
            note->setTitle(newTitle);
            return true;
        }
        return false;
    }

    // DELETE Operation
    bool deleteNote(const std::string& id) {
        auto it = std::remove_if(notes.begin(), notes.end(), [&id](Note* note) {
            if (note->getId() == id) {
                delete note; // Free dynamically allocated memory
                return true;
            }
            return false;
        });

        if (it != notes.end()) {
            notes.erase(it, notes.end());
            return true;
        }
        return false;
    }
};
