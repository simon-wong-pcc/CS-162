#pragma once
#include <iostream>

const int MAX_ACTIVITIES = 30;
const int MAX_CHAR = 51;

enum ActivityType {
    Athletics, Food, Arts, Games, Others
};

enum FilterParameter {
    Location, Type
};

typedef struct {
    char name[MAX_CHAR];
    char location[MAX_CHAR];
    char level[MAX_CHAR];
    int rating;
    ActivityType type;
} Activity;

typedef struct {
    Activity list[MAX_ACTIVITIES];
    int size;
} ActivityList;

void printItem(Activity activity, std::ostream& outStream);
const char* typeToString(ActivityType type);

void insertItem(ActivityList& activityList, Activity& activity);
void removeItem(ActivityList& activityList, int index);
void listItems(ActivityList& activityList);
void listItemsByLocation(ActivityList& activityList, char* filter);
void listItemsByType(ActivityList& activityList, int filter);
void searchItems(ActivityList& activityList, char* name);

void loadFromFile(const char* filename, ActivityList& activityList);
void saveToFile(ActivityList& activityList, const char* filename);