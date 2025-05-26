#include <fstream>
#include <iostream>
#include <cstring>
#include "tasklist.h"

using namespace std;

TaskList::TaskList() {
    arr = new Task[capacity];
}

TaskList::TaskList(const TaskList& other) {
    capacity = other.capacity;
    size = other.size;
    arr = new Task[capacity];

    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

TaskList::~TaskList() {
    delete[] arr;
}

TaskList& TaskList::operator=(const TaskList& other) {
    delete[] arr;

    capacity = other.capacity;
    size = other.size;
    arr = new Task[capacity];

    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

void TaskList::insert(Task task)
{
    if (size + 1 > capacity) {
        increaseCapacity();
    }

    int i = size;
    // Loop while i > 0 and while activity.person comes before
    while (i > 0 && strcmp(task.getPerson(), arr[i - 1].getPerson()) < 0) {
        arr[i] = arr[i - 1];
        i--;
    }

    arr[i] = task;
    size++;
}

void TaskList::remove(int index)
{
    for (int i = index; i < size; i++) {
        arr[i] = arr[i + 1];
    }

    size--;
}

void TaskList::print()
{
    for(int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        arr[i].print(cout);
    }
}

void TaskList::printByType(TaskType type)
{
    for(int i = 0, j = 1; i < size; i++) {
        if (arr[i].getType() == type) {
            cout << j++ << ". ";
            arr[i].print(cout);
        }
    }
}

void TaskList::search(char* filter)
{
    bool found = false;

    for(int i = 0, j = 1; i < size; i++) {
        if (strstr(arr[i].getName(), filter) != nullptr) {
            found = true;
            cout << j++ << ". ";
            arr[i].print(cout);
        }
    }

    if (!found) {
        cout << "Activity not found!\n";
    }
}

void TaskList::read(const char* filename)
{
    ifstream ifs;
    ifs.open(filename);

    Task task;

    int itemp;
    char stemp[MAX_STRLEN];

    ifs >> itemp;
    ifs.ignore(5, ';');
    task.setDay(itemp);

    int i = 0;

    while (!ifs.eof()) {

        ifs.getline(stemp, 100, ';');
        task.setName(stemp);
        
        ifs >> itemp;
        ifs.ignore(5, ';');
        task.setDuration(itemp);

        ifs.getline(stemp, 100, ';');
        task.setPerson(stemp);

        ifs >> itemp;
        ifs.ignore(5, '\n');
        task.setType((TaskType)itemp);

        insert(task);

        ifs >> itemp;
        ifs.ignore(5, ';');
        task.setDay(itemp);

    }

    ifs.close();

    this->print();
}

void TaskList::write(const char* filename)
{
    ofstream ofs;
    ofs.open(filename);

    for (int i = 0; i < size; i++) {
        arr[i].print(ofs, false);
    }

    ofs.close();
}

void TaskList::increaseCapacity() {

    capacity *= 2;
    Task* newArr = new Task[capacity];

    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
}