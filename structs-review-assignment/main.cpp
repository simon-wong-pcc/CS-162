#include <iostream>
#include <cstring>
#include "main.h"
#include "activity.h"
using namespace std;

int main() {

    ActivityList activityList;
    activityList.size = 0;

    loadFromFile("activities.txt", activityList);

    cout << "Welcome!\nThis program will help you manage your activities." << endl;

    do {
        printMenu();
    } while (!handleInput(activityList));

    saveToFile(activityList, "activities.txt");
    cout << "Activities written to file! Thank you for using my program!!";

    return 0;
}

void printMenu() {
    cout << "\nPick an option from below: \n\n";
    cout << "(a)Add a new activity" << "\n";
    cout << "(b)List activities by name" << "\n";
    cout << "(c)List activities by location" << "\n";
    cout << "(d)List activities by Type" << "\n";
    cout << "(e)Remove an activity" << "\n";
    cout << "(f)Search by activity name" << "\n";
    cout << "(q)Quit\n" << endl;
}

bool handleInput(ActivityList& activityList) {

    bool exitFlag = false;

    char input;

    cin >> input;
    cin.clear();
    cin.ignore(100, '\n');

    switch (tolower(input)) {

    case 'a':
        addActivity(activityList);
        break;
    case 'b':
        listItems(activityList);
        break;
    case 'c': {
        char location[MAX_CHAR];
        getUserString(location, "Enter location name: ");
        listItemsByLocation(activityList, location);
        break; }
    case 'd': {
        int type = getUserRangedInt(0, 4, "Enter type number (0-Athletics, 1-Food, 2-Arts, 3-Games, and 4-Others): ");
        listItemsByType(activityList, type);
        break; }
    case 'e':
        removeActivity(activityList);
        break;
    case 'f':
        char searchFilter[MAX_CHAR];
        getUserString(searchFilter, "Enter the activity name(50 characters or less) : ");
        searchItems(activityList, searchFilter);
        break;
    case 'q':
        exitFlag = true;
        break;
    default:
        cout << "Invalid option!! Please try again!" << endl;
        break;
    }

    return exitFlag;
}

void addActivity(ActivityList& activityList) {
    if (activityList.size >= MAX_ACTIVITIES) {
        cout << "Error: Too many activites!\n";
        return;
    }

    Activity newActivity = getUserActivity();
    insertItem(activityList, newActivity);
    cout << "Activity Added!" << endl;
    listItems(activityList);
}

void removeActivity(ActivityList& activityList) {
    if (activityList.size <= 0) {
        cout << "Error: No activies found!\n";
        return;
    }

    listItems(activityList);

    int index = getUserRangedInt(1, activityList.size, "Pick the index to remove: ");
    removeItem(activityList, index - 1);
    cout << "Activity Removed!" << endl;
    listItems(activityList);
}


Activity getUserActivity() {
    Activity newActivity;

    getUserString(newActivity.name, "Enter the activity name (50 characters or less): ");

    getUserString(newActivity.location, "Enter the activity location (50 characters or less): ");

    getUserString(newActivity.level, "Enter the activity level (50 characters or less): ");

    newActivity.rating = getUserRangedInt(0, 10, "Enter the activity rating: ");

    newActivity.type = (ActivityType) getUserRangedInt(0, 4, "Enter type number (0-Athletics, 1-Food, 2-Arts, 3-Games, and 4-Others): ");

    return newActivity;
}

void getUserString(char* string, const char* prompt) {
    do {
        cout << prompt;
        cin.getline(string, MAX_CHAR);
        if (cin.fail()) {
            cout << "Invalid Input! Must be less than 50 characters!" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (cin.fail());
}

int getUserRangedInt(int lowerBound, int upperBound, const char* prompt) {
    int userInt = lowerBound - 1;
    
    do {
        cout << prompt;
        cin >> userInt;
        if (cin.fail()) {
            cout << "Invalid Input!! Enter an integer between " << lowerBound << " and " << upperBound << "!" << endl;
            userInt = lowerBound - 1;
        }
        cin.clear();
        cin.ignore(100, '\n');
    } while (userInt < lowerBound || userInt > upperBound);

    return userInt;
}