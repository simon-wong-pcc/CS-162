#pragma once
#include <cstring>
#include <iostream>

const int MAX_STRLEN = 51;

enum TaskType {
    Operations, Maintenance, Inventory, Communications, Others
};

class Task {
public:

    // Constructors

    Task();

    Task(int day, const char* name, const char* person, int duration, TaskType type);

    Task(const Task& other);

    ~Task();

    Task& operator=(const Task& other);

    // Functions

    void print(std::ostream& os = std::cout, bool showTypeName = true);

    // Getter and Setters

    const char* getName() { return name; }
    const char* getPerson() { return person; }
//    void getName(char* nameReturn) { strcpy(nameReturn, name); }
//    void getPerson(char* nameReturn) { strcpy(nameReturn, person); }
    int getDay() { return day; }
    int getDuration() { return duration; }
    TaskType getType() { return type; }

    void setName(const char* name);
    void setPerson(const char* name);
    void setDay(int day) { this->day = day; }
    void setDuration(int duration) { this->duration = duration; }
    void setType(TaskType type) { this->type = type; }

private:
    char* name = nullptr;
    char* person = nullptr;
    int day; // 1 - 30
    int duration;
    TaskType type;

    const char* printType();

};