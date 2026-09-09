#pragma once
#include "Note.h"
#include <vector>
#include <memory>
#include <algorithm>

class NoteManager {
private:
    // Upgraded to smart pointers for automatic memory safety
    std::vector<std::unique_ptr<Note>> notes;
    int nextID = 1; // Track ID for auto-generation

public:
	// Generate ID and increments the counter
	std::string generateNextID() {
		return std::to_string(nextID++);
	}

    void addNote(std::unique_ptr<Note> note) {
        notes.push_back(std::move(note));
        std::cout << "Note added successfully!\n";
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
        
        // The erase-remove idiom natively handles memory deletion with unique_ptr
        notes.erase(std::remove_if(notes.begin(), notes.end(),
            [&id](const std::unique_ptr<Note>& note) {
                return note->getId() == id;
            }), notes.end());

        return notes.size() < initialSize;
    }
};
