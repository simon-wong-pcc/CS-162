#pragma once
#include "activity.h"

void printMenu();
bool handleInput(ActivityList& activityList);

void addActivity(ActivityList& activityList);
void removeActivity(ActivityList& activityList);

void getUserString(char* string, const char* prompt);
int getUserRangedInt(int lowerBound, int upperBound, const char* prompt);
Activity getUserActivity();