#pragma once
#include "task.h"
#include "tasklist.h"

void printMenu();
bool handleInput(TaskList& tasklist);

void addTask(TaskList& taskList);
void listTypeTasks(TaskList& taskList);
void searchTask(TaskList& taskList);
void removeTask(TaskList& taskList);

Task getUserTask();
void getUserString(char* string, const char* prompt);
int getUserInt(const char* prompt, int lower, int upper);