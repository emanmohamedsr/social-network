#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <windows.h>///sleep,color
#include <cstdlib>///system()

#include "frequencyMapping.h"
#include "HashTable.h"

class UserInterFace
{
private:
    HashTable HT;
    frequencyMapping FM;
    void activityOptions();
    void setActivity(User* Uptr);
    void deleteActivity(User* Uptr);
    void searchActivity(User* Uptr);
    void displayActivity(User* Uptr);
    void numberOfActivities(User* Uptr);

    void statisticslist();
public:
    UserInterFace();
    ~UserInterFace();

    void setColor(int color);
    void print(string text, bool newLine = true);
    void separator(int color);
    void Back(int x = 3);

    void NetWork_system();

    void statistics();
    void SignUP();
    void SignIN();

    void Deleting();
    void Display();

};

#endif // USERINTERFACE_H
