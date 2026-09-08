#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

// ==========================================
// 1. DATA STRUCTURES & CLASS INTERFACE
// ==========================================

class Note {
private:
    std::string id;
    std::string title;
    std::string category;
    std::vector<std::string> tags;
    std::string createdAt;

public:
    Note(const std::string& id, const std::string& title, const std::string& category,
         const std::vector<std::string>& tags, const std::string& createdAt)
        : id(id), title(title), category(category), tags(tags), createdAt(createdAt) {}

    virtual ~Note() {}

    // READ Interface
    virtual void display() const = 0;

    // Getters & Setters for UPDATE operations
    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getCategory() const { return category; }
    std::vector<std::string> getTags() const { return tags; }
    std::string getCreatedAt() const { return createdAt; }

    void setTitle(const std::string& newTitle) { title = newTitle; }
    void setCategory(const std::string& newCategory) { category = newCategory; }
    void setTags(const std::vector<std::string>& newTags) { tags = newTags; }
};

// Example TextNote Concrete Class used in Creation & Reading
class TextNote : public Note {
private:
    std::string textContent;

public:
    TextNote(const std::string& id, const std::string& title, const std::string& category,
             const std::vector<std::string>& tags, const std::string& createdAt, const std::string& content)
        : Note(id, title, category, tags, createdAt), textContent(content) {}

    // READ Operation
    void display() const override {
        std::cout << "\n========================================\n";
        std::cout << "[Text Note] ID: " << getId() << "\nTitle: " << getTitle()
                  << "\nCategory: " << getCategory() << "\nCreated: " << getCreatedAt() << "\nTags: ";
        for (const auto& tag : getTags()) std::cout << "#" << tag << " ";
        std::cout << "\n----------------------------------------\n";
        std::cout << textContent << "\n========================================\n";
    }

    // UPDATE Operation
    void setContent(const std::string& newContent) { textContent = newContent; }
};

// ==========================================
// 2. CORE CRUD LOGIC (NoteManager)
// ==========================================

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

// ==========================================
// 3. CLI HANDLERS FOR CRUD
// ==========================================

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
