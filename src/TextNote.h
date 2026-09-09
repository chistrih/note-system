#pragma once
#include "Note.h"

class TextNote : public Note {
private:
    std::string textContent;

public:
    TextNote(const std::string& id, const std::string& title, const std::string& category,
             const std::vector<std::string>& tags, const std::string& createdAt, const std::string& content)
        : Note(id, title, category, tags, createdAt), textContent(content) {}

    void display() const override {
        std::cout << "\n========================================\n";
        std::cout << "[Text Note] ID: " << getId() << "\nTitle: " << getTitle()
                  << "\nCategory: " << getCategory() << "\nCreated: " << getCreatedAt() << "\nTags: ";
        for (const auto& tag : getTags()) std::cout << "#" << tag << " ";
        std::cout << "\n----------------------------------------\n";
        std::cout << textContent << "\n========================================\n";
    }

    void setContent(const std::string& newContent) { textContent = newContent; }
};
