#include <iostream>
#include "main.h"

using namespace std;

int main() {

    TaskList taskList;
    cout << "Here" << endl;
    taskList.read("tasks.txt");

    cout << "Welcome!\n";
    cout << "This program will help you manage your tasks for this Space Station.\n\n";

    do {
        printMenu();
    } while (!handleInput(taskList));

    taskList.write("tasks.txt");

    cout << "Tasks written to file! Thank you for using my program!!";

}

void printMenu() {
    cout << "\nPick an option from below:\n\n";
    cout << "(a)Add a new task\n";
    cout << "(b)List tasks by name\n";
    cout << "(c)List tasks by Type\n";
    cout << "(d)Search by task name\n";
    cout << "(e)Remove tasks by index\n";
    cout << "(q)Quit\n" << endl;    
}

bool handleInput(TaskList& taskList) {

    char userSelection;
    bool exitSignal = false;

    cin >> userSelection;
    cin.ignore(100, '\n');

    switch (userSelection) {
    case 'a': // Add
        addTask(taskList);
        break;
    case 'b': // List
        taskList.print();
        break;
    case 'c': // List by type
        listTypeTasks(taskList);
        break;
    case 'd': // Search
        searchTask(taskList);
        break;
    case 'e': // Remove
        removeTask(taskList);
        break;
    case 'q': // Quit
        exitSignal = true;
        break;
    default:
        cout << "Invalid option!! Please try again!" << endl;
    }

    return exitSignal;
}

void addTask(TaskList& taskList){
    if (taskList.getSize() >= MAX_ARR_SIZE) {
        cout << "Error: Max size reached!" << endl;
        return;
    }

    Task task = getUserTask();
    taskList.insert(task);

    cout << "\nTask added!\n\n";

    taskList.print();
}


void listTypeTasks(TaskList& taskList){
    TaskType type = (TaskType) getUserInt("Enter Type number(0-Operations, 1-Maintenance, 2-Inventory, 3-Communications, and 4-Others): ", 0, 4);
    taskList.printByType(type);
}

void searchTask(TaskList& taskList){
    char str[MAX_STRLEN];
    getUserString(str, "Enter task name: ");
    taskList.search(str);
}

void removeTask(TaskList& taskList){
    if (taskList.getSize() <= 0) {
        cout << "Error: No tasks in list!" << endl;
        return;
    }

    taskList.print();
    cout << "\n";
    int idx = getUserInt("Enter index of task to remove: ", 1, taskList.getSize());
    taskList.remove(idx - 1);
    cout << "Task Removed!\n";
    taskList.print();
}


Task getUserTask() {

    Task out;

    char stemp[MAX_STRLEN];
    int itemp;

    itemp = getUserInt("Enter the day of the task (whole numbers between 1 and 30): ", 1, 30);
    out.setDay(itemp);

    getUserString(stemp, "Enter the task name (50 characters or less): ");
    out.setName(stemp);

    getUserString(stemp, "Enter the person’s name (50 characters or less): ");
    out.setPerson(stemp);

    itemp = getUserInt("Enter the number of hours (whole numbers between 1 and 10): ", 1, 10);
    out.setDuration(itemp);

    itemp = getUserInt("Enter the task type 0-Operations, 1-Maintenance, 2-Inventory, 3-Communications, and 4-Others): ", 0, 4);
    out.setType((TaskType) itemp);

    return out;
}

void getUserString(char* string, const char* prompt) {
    do {
        cout << prompt;
        cin.getline(string, MAX_STRLEN);
        if (cin.fail()) {
            cout << "Invalid Input! Must be less than " << MAX_STRLEN - 1 << " characters!" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (cin.fail());
}

int getUserInt(const char* prompt, int lower, int upper) {
    int out;

    do {
        cout << prompt;
        cin >> out;
        cin.ignore(5, '\n');

        if (cin.fail() || out < lower || out > upper) {
            cout << "Error! Enter a number between " << lower << " and " << upper << "!\n";
            out = lower - 1;
            cin.clear();
        }
    } while (out < lower || out > upper);

    return out;
}
