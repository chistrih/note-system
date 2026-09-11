#pragma once
#include "Note.h"
#include "TextNote.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <iostream>

class NoteManager {
private:
    std::vector<std::unique_ptr<Note>> notes;
    int nextId = 1;

public:
    std::string generateNextId() {
        return std::to_string(nextId++);
    }

    void addNote(std::unique_ptr<Note> note) {
        notes.push_back(std::move(note));
    }

    void displayAllNotes() const {
        if (notes.empty()) {
            std::cout << "No notes found.\n";
            return;
        }
        for (const auto& note : notes) {
            note->display();
        }
    }

    Note* findNoteById(const std::string& id) const {
        for (const auto& note : notes) {
            if (note->getId() == id) return note.get();
        }
        return nullptr;
    }

    bool updateNoteTitle(const std::string& id, const std::string& newTitle) {
        Note* note = findNoteById(id);
        if (note != nullptr) {
            note->setTitle(newTitle);
            return true;
        }
        return false;
    }

    bool updateNoteContent(const std::string& id, const std::string& newContent) {
        Note* note = findNoteById(id);
        if (note != nullptr) {
            note->setContent(newContent);
            return true;
        }
        return false;
    }

    bool deleteNote(const std::string& id) {
        auto initialSize = notes.size();
        notes.erase(std::remove_if(notes.begin(), notes.end(),
            [&id](const std::unique_ptr<Note>& note) {
                return note->getId() == id;
            }), notes.end());
        return notes.size() < initialSize;
    }
};
