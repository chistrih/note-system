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
        std::cout << "\n" << Color::CYAN << "========================================\n" << Color::RESET;
        std::cout << "[Note #" << Color::CYAN << Color::BOLD << getId() << Color::RESET 
					<< "]\nTitle: " << Color::CYAN << getTitle() << Color::RESET
        			<< "\nDate: " << Color::CYAN << getCreatedAt() << Color::RESET << "\n";
        std::cout << Color::CYAN << "----------------------------------------\n" << Color::RESET; 
        std::cout << "\n" << textContent << "\n" << Color::CYAN << "\n========================================\n" << Color::RESET << "\n";
    }

    void setContent(const std::string& newContent) override { textContent = newContent; }
};
