#pragma once
#include "task.h"

const int MAX_ARR_SIZE = 30;

class TaskList {
public:

    void insert(Task task);
    void remove(int index);

    void print();
    void printByType(TaskType type);
    void search(char* filter);

    void read(const char* filename);
    void write(const char* filename);

    int getSize () { return size; }

private:
    Task arr[MAX_ARR_SIZE];
    int size = 0;
};