#include <fstream>
#include <iostream>
#include <cstring>
#include "tasklist.h"

using namespace std;

TaskList::TaskList() {

}

TaskList::TaskList(const TaskList& other) {
    size = other.size;

    head = new Node();
    head->data = other.head->data;

    Node* prev = head;

    for (int i = 0; i < size; i++) {
        Node* n = new Node();
        n->data = other.at(i);
        n->next = nullptr;

        prev->next = n;
        prev = n;
    }
}

TaskList::~TaskList() {
    for (Node* n = head; n != nullptr; ) {
        Node* tmp = n;
        n = n->next;
        delete tmp;
    }
}

TaskList& TaskList::operator=(const TaskList& other) {
    for (Node* n = head; n != nullptr; n = n->next) {
        Node* tmp = n;
        n = n->next;
        delete tmp;
    }

    head = new Node();
    head->data = other.head->data;

    Node* prev = head;

    for (int i = 0; i < size; i++) {
        Node* n = new Node();
        n->data = other.at(i);
        n->next = nullptr;

        prev->next = n;
        prev = n;
    }


    return *this;
}

void TaskList::insert(Task task)
{

    Node* n = new Node();
    n->data = task;
    n->next = nullptr;

    Node* prev = nullptr;
    Node* curr = head;

    while (curr != nullptr && strcmp(task.getPerson(), curr->data.getPerson()) > 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == nullptr) {
        head = n;
    } else {
        prev->next = n;
    }

    n->next = curr;

    size++;
}

void TaskList::remove(int index)
{
/*    Node* prev = nullptr;
    Node* curr = head;

    for (int i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    delete curr;

    size--;*/
}

Task& TaskList::at(int index) const {
    Node* n = head;

    for (int i = 0; i < index; i++) {
        n = n->next;
    }

    return n->data;
}

void TaskList::print()
{
    for(int i = 0; i < size; i++) {
        cout << i + 1 << ". ";
        at(i).print(cout);
    }
}

void TaskList::printByType(TaskType type)
{
    for(int i = 0, j = 1; i < size; i++) {
        if (at(i).getType() == type) {
            cout << j++ << ". ";
            at(i).print(cout);
        }
    }
}

void TaskList::search(char* filter)
{
    bool found = false;

    for(int i = 0, j = 1; i < size; i++) {
        if (strstr(at(i).getName(), filter) != nullptr) {
            found = true;
            cout << j++ << ". ";
            at(i).print(cout);
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
}

void TaskList::write(const char* filename)
{
    ofstream ofs;
    ofs.open(filename);

    for (int i = 0; i < size; i++) {
        at(i).print(ofs, false);
    }

    ofs.close();
}