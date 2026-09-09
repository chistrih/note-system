#pragma once
#include <string>
#include <iostream>

class Note {
private:
    std::string id;
    std::string title;
    std::string createdAt;

public:
    Note(const std::string& id, const std::string& title, const std::string& createdAt)
        : id(id), title(title), createdAt(createdAt) {}

    virtual ~Note() = default;

    virtual void display() const = 0;

    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getCreatedAt() const { return createdAt; }

    void setTitle(const std::string& newTitle) { title = newTitle; }
    virtual void setContent(const std::string& newContent) = 0; 
};
