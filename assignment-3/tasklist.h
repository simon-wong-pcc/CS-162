#pragma once
#include "task.h"

const int MAX_ARR_SIZE = 30;

class TaskList {
public:

    TaskList();

    TaskList(const TaskList& other);

    ~TaskList();

    TaskList& operator=(const TaskList& other);

    void insert(Task task);
    void remove(int index);

    Task& at(int index) const;

    void print();
    void printByType(TaskType type);
    void search(char* filter);

    void read(const char* filename);
    void write(const char* filename);

    int getSize () { return size; }

private:
    struct Node {
        Task data;
        Node* next;
    };

    Node* head = nullptr;
    int size = 0;
};