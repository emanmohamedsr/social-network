#include "User.h"

User::User():userName("NO$VALUE"), email("NO$VALUE"), phoneNumber("NO$VALUE")
{
}

User::~User()
{
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void User::getUser_SignUP()
{
    cout << "First Name: ";
    cin >> firstName;
    cout << "\nLast Name: ";
    cin >> lastName;
    do {
        cout << "\nUser Name: -> [1]Must be More Than (4) characters [2]No spaces !!\n  >>>";
        cin>> userName;
    } while (!userNameValidation(userName));
    do {
        cout << "\nEmail: -> [1]Must have (@) character [2]No spaces !!\n  >>>";
        cin>> email;
    } while (!emailValidation(email));
    do {
        cout << "\nPhone Number: -> [1]Must be (10) numbers [2]Numbers [3]No spaces!!\n  >>> +20 ";
        cin>> phoneNumber;
    } while (!phoneNumberValidation(phoneNumber));
}

void User::getUser_SignIN() {
    cout << "User Name: ";
    cin >> userName;
    cout << "Email: ";
    cin >> email;
    cout << "Phone Number: ";
    cin >> phoneNumber;
}

string User::getKey() const {
    return userName + email + phoneNumber;
}
string User::getUserName() const
{
    return userName;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool User::emailValidation(const string& s)
{
    bool flag = false;
    for (char c : s) {
        if (c == '@')
            flag = true;
    }
    return flag;
}

bool User::phoneNumberValidation(const string& s)
{
    const int expectedSize = 10;
    if (s.length() != expectedSize) return false;
    for (char c : s)
        if (c < '0' || c > '9')
            return false;
    return true;
}

bool User::userNameValidation(const string& s)
{
    return (s.length()>=5);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
bool User::displayActivities()
{
    return activities.displayQueue();
}

void User::addUserActivities(const string& activity)
{
    activities.enQueue(activity);
}

bool User::deleteUserActivity()
{
    return activities.deQueue();
}

bool User::searchUserActivity(const string& activity)
{
    return activities.search(activity);
}

string User::topActivity()
{
   return activities.Top();
}

size_t User::numberOfUserActivities()
{
    return activities.QueueSize();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
ostream& operator<<(ostream& out, const User& U) {
    out << "First Name: " << U.firstName << endl
        << "Last Name: " << U.lastName << endl
        << "User Name: " << U.userName << endl
        << "Email: " << U.email << endl
        << "Phone Number: " << U.phoneNumber << endl
        << "Activities ... ";
    if (!U.activities.displayQueue())
        out << "Still Empty, Try to \'SIGN_IN\' and have fun ;) ";
    out << endl;
    return out;
}

User& User::operator=(const User& other) {
    if (&other != this) {
        this->firstName = other.firstName;
        this->lastName = other.lastName;
        this->userName = other.userName;
        this->email = other.email;
        this->phoneNumber = other.phoneNumber;
        this->activities = other.activities;
    }
    return *this;
}

bool User::operator==(const User& other) const {
    return ((other.phoneNumber == this->phoneNumber)
           && (other.email == this->email)
           && (other.userName == this->userName));
}

bool User::operator<(const User& other) const {
    return (this->userName < other.userName);
}

bool User::operator>(const User& other) const {
    return (this->userName > other.userName);
}
