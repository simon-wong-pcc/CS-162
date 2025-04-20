#include "task.h"

Task::Task() : day(-1), duration(-1), type((TaskType)-1) {
    strcpy(this->name, "Unknown");
    strcpy(this->person, "Unknown");    
}

Task::Task(int day, const char* name, const char* person, int duration, TaskType type) :
    day(day), duration(duration), type(type)    
{
    strcpy(this->name, name);
    strcpy(this->person, person);
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