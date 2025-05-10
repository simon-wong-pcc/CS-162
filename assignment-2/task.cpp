#include "task.h"

Task::Task() : day(-1), duration(-1), type((TaskType)-1) {
    const char* defaultStr = "Unknown";
    
    setName(defaultStr);
    setPerson(defaultStr);
}

Task::Task(int day, const char* name, const char* person, int duration, TaskType type) :
    day(day), duration(duration), type(type)    
{
    setName(name);
    setPerson(person);
}

Task::Task(const Task& other) {
    day = other.day;
    duration = other.duration;
    type = other.type;

    setName(other.name);
    setPerson(other.person);
}

Task::~Task() {
    delete[] name;
    delete[] person;
}

Task& Task::operator=(const Task& other) {
    day = other.day;
    duration = other.duration;
    type = other.type;

    setName(other.name);
    setPerson(other.person);

    return *this;
}

void Task::setName(const char* name) {
    delete[] this->name; 
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

void Task::setPerson(const char* name) {
    delete[] person; 
    person = new char[strlen(name) + 1];
    strcpy(person, name);
}

void Task::print(std::ostream& os /*  = cout*/, bool showTypeName /*= true*/) {
    os << day << ";";
    os << name << ";";
    os << duration << ";";
    os << person << ";";
    if (showTypeName) {
        os << printType() << "\n";
    } else {
        os << type << "\n";
    }
}

const char* Task::printType() {
    switch(type) {
        case TaskType::Communications: return "Communications";
        case TaskType::Inventory: return "Inventory";
        case TaskType::Maintenance: return "Maintenance";
        case TaskType::Operations: return "Operations";
        case TaskType::Others: return "Others";
        default: return "Err";
    }
}