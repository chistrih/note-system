#pragma once
#include "Note.h"
#include "Colors.h"

class TextNote : public Note {
private:
    std::string textContent;

public:
    TextNote(const std::string& id, const std::string& title, const std::string& createdAt, const std::string& content)
        : Note(id, title, createdAt), textContent(content) {}

    void display() const override {
        std::cout << "\n" << Color::MAGENTA << "========================================" << Color::RESET << "\n";
        std::cout << "[Text Note] ID: " << Color::CYAN << Color::BOLD << getId() << Color::RESET 
                  << "\nTitle: " << Color::CYAN << getTitle() << Color::RESET
                  << "\nCreated: " << getCreatedAt() << "\n";
        std::cout << Color::MAGENTA << "----------------------------------------" << Color::RESET << "\n";
        std::cout << textContent << "\n";
        std::cout << Color::MAGENTA << "========================================" << Color::RESET << "\n";
    }

    void setContent(const std::string& newContent) override { textContent = newContent; }
};
