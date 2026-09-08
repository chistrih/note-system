#pragma once
#include <string>
#include <vector>
#include <iostream>

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
