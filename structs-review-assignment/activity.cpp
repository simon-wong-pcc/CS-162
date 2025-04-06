#include <cstring>
#include <fstream>
#include <iostream>
#include "activity.h"

using namespace std;

void printItem(Activity activity, ostream& outStream = cout) {
    outStream << activity.name << ";"; 
    outStream << activity.location << ";"; 
    outStream << activity.level << ";";
    outStream << activity.rating << ";";

    if (&outStream == &cout) {
        outStream << typeToString(activity.type) << "\n";
    } else {
        outStream << activity.type << "\n";
    }

}

const char* typeToString(ActivityType type){
    switch (type) {
        case ActivityType::Athletics:   return "Athletics";
        case ActivityType::Food:        return "Food";
        case ActivityType::Arts:        return "Arts";
        case ActivityType::Games:       return "Games";
        case ActivityType::Others:      return "Others";
        default:                        return "Error";
    }
}

void insertItem(ActivityList& activityList, Activity& activity) {
    int i = activityList.size;
    // Loop while i > 0 and while activity.name comes before
    while (i > 0 && strcmp(activity.name, activityList.list[i - 1].name) < 0) {
        activityList.list[i] = activityList.list[i - 1];
        i--;
    }

    activityList.list[i] = activity;
    activityList.size++;
}

void removeItem(ActivityList& activityList, int index) {
    for (int i = index; i < activityList.size; i++) {
        activityList.list[i] = activityList.list[i + 1];
    }

    activityList.size--;
}

void listItems(ActivityList& activityList) {
    if (activityList.size <= 0) {
        cout << "Error: No activies found!\n";
        return;
    }

    for (int i = 0; i < activityList.size; i++) {
        cout << i + 1 << ". ";
        printItem(activityList.list[i]);
    }
}

void listItemsByLocation(ActivityList& activityList, char* filter) {
    if (activityList.size <= 0) {
        cout << "Error: No activies found!\n";
        return;
    }

    for (int i = 0, j = 1; i < activityList.size; i++) {
        if (strstr(activityList.list[i].location, filter) != nullptr) {
            cout << j++ << ". ";
            printItem(activityList.list[i]);
        }
    }
}

void listItemsByType(ActivityList& activityList, int filter) {
    if (activityList.size <= 0) {
        cout << "Error: No activies found!\n";
        return;
    }

    for (int i = 0, j = 1; i < activityList.size; i++) {
        if (activityList.list[i].type == (ActivityType) filter) {
            cout << j++ << ". ";
            printItem(activityList.list[i]);
        }
    }
}

void searchItems(ActivityList& activityList, char* name) {
    if (activityList.size <= 0) {
        cout << "Error: No activies found!\n";
        return;
    }

    bool foundActivity = false;

    for (int i = 0; i < activityList.size; i++) {
        if (strstr(activityList.list[i].name, name) != nullptr) {
            cout << "Activity Found!" << endl;
            foundActivity = true;
            cout << i + 1 << ".";
            printItem(activityList.list[i]);
        }
    }

    if (!foundActivity) {
        cout << "Activity not found!!" << endl;
    }
}

// name;location;level;rating;type

void loadFromFile(const char* filename, ActivityList& activityList) {
    ifstream file("activities.txt");

    Activity newActivity;

    // Peek to check for EOF
    file.peek();

    // Check peek against -1 to prevent seg fault from empty line
    while (!file.eof() && file.peek() != -1) {

        file.getline(newActivity.name, MAX_CHAR, ';');

        file.getline(newActivity.location, MAX_CHAR, ';');

        file.getline(newActivity.level, MAX_CHAR, ';');

        file >> newActivity.rating;
        file.ignore(5, ';');

        file >> (int&) newActivity.type;
        file.ignore(5, '\n');

        insertItem(activityList, newActivity);
    }

    file.close();
}

void saveToFile(ActivityList& activityList, const char* filename) {
    ofstream file("activities.txt");

    for (int i = 0; i < activityList.size; i++) {
        printItem(activityList.list[i], file);
    }

    file.close();
}