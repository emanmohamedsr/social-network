#ifndef USER_H
#define USER_H

#include "Queue.h"

class User {
private:
    string firstName;
    string lastName;
    string userName;
    string email;
    string phoneNumber;
    Queue<string> activities;
public:
    User();
    ~User();

    void getUser_SignUP();
    void getUser_SignIN();
    string getKey() const;
    string getUserName() const;

    bool emailValidation(const string& s);
    bool phoneNumberValidation(const string& s);
    bool userNameValidation(const string& s);

    bool displayActivities();
    void addUserActivities(const string& activity);
    bool deleteUserActivity();
    bool searchUserActivity(const string& activity);
    string topActivity();
    size_t numberOfUserActivities();

    User& operator=(const User& other);
    bool operator==(const User& other) const;
    bool operator<(const User& other) const;
    bool operator>(const User& other) const;

    friend ostream& operator<<(ostream& out, const User& U);
};

#endif // USER_H
