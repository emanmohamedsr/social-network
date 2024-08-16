#include "UserInterFace.h"

UserInterFace::UserInterFace() {}
UserInterFace::~UserInterFace() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UserInterFace::setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void UserInterFace::print(string text, bool newLine)
{
    cout << text << (newLine ? "\n" : " ");
}

void UserInterFace::separator(int color)
{
    int x = 80;
    setColor(color);
    for (auto i = 0; i < x; ++i)
    {
        cout << "_";
    }
    setColor(15);
    cout << endl;
}

void UserInterFace::Back(int x)
{
    cout << "\t\t";
    for (auto i = 0; i < x; ++i)
    {
        cout << ". ";
        Sleep(400);
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UserInterFace::NetWork_system()
{
    system("cls");
    setColor(13);
    print("\t\tWELCOME TO OUR NETWORK SYSTEM \x03");
    print("\t\t__________________________________\n");
    setColor(15);
    print("HOW CAN WE HELP YOU \x03 ....");
    print("1) SIGN UP ");
    print("2) SIGN IN ");
    print("3) DELETE ACCOUNT");
    print("4) REPORTING ");
    print("5) STATISTICS ");
    print("0) CLOSE ");
    print("YOUR CHOICE! ", false);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UserInterFace::statisticslist(){
    system("cls");
    setColor(6);
    print("\t\tGOOD OVERVIEW ABOUT ACTIVITIES \x03");
    print("\t\t_______________________________\n");
    setColor(15);
    print("1) TRENDY ACTIVITY ");
    print("2) LEAST COMMON ACTIVITY ");
    print("3) ASK ABOUT ACRIVITY");
    print("0) CLOSE ");
    print("YOUR CHOICE! ", false);
}

void UserInterFace::statistics(){
    string ac;
    int ch;
    while (true)
    {
        statisticslist();
        cin >> ch;
        separator(6);

        switch (ch){
        case 1:{
            cout <<" Most Common Activity: "<< FM.maxFrequency() << endl;
            separator(6);
            cout << "  \t";
            Back(3);
            break;
        }
        case 2:{
            cout << " Least Common Activity: " << FM.minFrequency() << endl;
            separator(6);
            cout << "  \t";
            Back(3);
            break;
        }
        case 3: {
            cout << "Enter Activity Name: ";
            cin >> ac;
            cout << "There is/are  " << FM.search(ac) <<"   User/s interact with it " << endl;
            separator(6);
            cout << "  \t";
            Back(3);
            break;
        }
        case 0: {
            print("EXIT");
            separator(6);
            cout << "  \t";
            Back(3);
            return;
        }
        default: {
            print("InValid Choice, Have another try :) ");
            separator(6);
            cout << "  \t";
            Back(3);
            break;
        }
        }
    }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UserInterFace::Deleting()
{
    system("cls");
    setColor(12);
    cout << "\t\tREMOVING " << endl
        << "\t\t________" << endl;
    setColor(15);

    User* Uptr = HT.Search();
    if(Uptr){
        size_t s = Uptr->numberOfUserActivities();
        for (size_t i = 0; i < s; i++) {
            FM.Delete(Uptr->topActivity());
            Uptr->deleteUserActivity();
        }
        HT.Detete(*Uptr);
    }
    else
        cout<<"Oops, Not Seem An Recorded Account"<<endl;

    separator(12);
    Back(3);
}

void UserInterFace::Display()
{
    system("cls");
    setColor(14);
    cout << "\t\tREPORTING" << endl
        << "\t\t_________" << endl;
    setColor(15);

    HT.Dispaly();

    separator(14);
    system("pause");
}

void UserInterFace::SignIN()
{
    system("cls");
    setColor(11);
    cout << "\t\tOPEN YOUR ACCOUNT " << endl
        << "\t\t__________________ " << endl;
    setColor(15);
    string ac;
    bool flag;
    User* Uptr;
    Uptr = HT.Search();
    (Uptr ? flag = 1 : flag = 0);
    if (flag) {
        int ch;
        while (true) {
            system("cls");
            cout << "\t\x03 ";
            setColor(11);
            cout << "<<<<< Welcome Back " << Uptr->getUserName() << " >>>>>";
            setColor(15);
            cout<< " \x03";
            cout << endl;
            activityOptions();
            cin >> ch;
            separator(11);
            switch (ch)
            {
            case 1: {
                setActivity(Uptr);
                break;
            }
            case 2: {
                deleteActivity(Uptr);
                break;
            }
            case 3: {
                searchActivity(Uptr);
                break;
            }
            case 4: {
                displayActivity(Uptr);
                break;
            }
            case 5: {
                numberOfActivities(Uptr);
                break;
            }
            case 0:
                print("EXIT");
                separator(11);
                cout << "  \t";
                Back(3);
                return;
            default:
                print("InValid Choice, Have another try :) ");
                separator(11);
                cout << "  \t";
                Back(3);
            }
        }
    }
    else
        cout<<"Oops, Not Seem An Recorded Account"<<endl;
    separator(11);
    Back(3);
}

void UserInterFace::SignUP()
{
    system("cls");
    setColor(9);
    cout << "\t\tADD NEW ACCOUNT " << endl
        << "\t\t________________ " << endl;
    setColor(15);

    HT.Insert();

    separator(9);
    Back(3);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void UserInterFace::activityOptions()
{
    print("[1] Add Activity   ");
    print("[2] Delete Activity");
    print("[3] Search Activity");
    print("[4] Display Activities");
    print("[5] Number of Activities");
    print("[0] EXIT ");
    print("Your Choice... ", false);
}

void UserInterFace::setActivity(User* Uptr) {
    string ac;
    cout << "Enter The Activity Name: ";
    cin >> ac;
    Uptr->addUserActivities(ac);
    FM.insert(ac);
    print("SUCCESS :)");
    separator(11);
    cout << "    \t";
    Back(3);
}

void UserInterFace::deleteActivity(User* Uptr){
    if (!Uptr->numberOfUserActivities())
        print("Empty, Add some activities first");
    else {
        FM.Delete(Uptr->topActivity());
        Uptr->deleteUserActivity();
        print("SUCCESS :)");
    }
    separator(11);
    cout << "  \t";
    Back(3);
}

void UserInterFace::searchActivity(User* Uptr) {
    string ac;
    cout << "Enter The Activity Name: ";
    cin >> ac;
    if (!Uptr->searchUserActivity(ac))
        print("NOT FOUND :(");
    else
        cout << "FOUND :) " << endl;
    separator(11);
    cout << "  \t";
    Back(3);
}

void UserInterFace::displayActivity(User* Uptr) {
    if (!Uptr->displayActivities())
        print("Empty, Add some activities first");
    separator(11);
    cout << "  \t";
    Back(3);
}

void UserInterFace::numberOfActivities(User* Uptr) {
    cout << "Number Of Activities is : " <<
        Uptr->numberOfUserActivities() << endl;
    separator(11);
    cout << "  \t";
    Back(3);
}
