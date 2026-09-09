#pragma once
#include "Note.h"

class TextNote : public Note {
private:
    std::string textContent;

public:
    TextNote(const std::string& id, const std::string& title, const std::string& createdAt, const std::string& content)
        : Note(id, title, createdAt), textContent(content) {}

    void display() const override {
        std::cout << "\n========================================\n";
        std::cout << "[Note #" << getId() << "]\nTitle: " << getTitle()
                  << "\nDate: " << getCreatedAt() << "\n";
        std::cout << "----------------------------------------\n";
        std::cout << textContent << "\n========================================\n";
    }

    void setContent(const std::string& newContent) override { textContent = newContent; }
};
