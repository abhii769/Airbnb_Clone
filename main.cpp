#include <bits/stdc++.h>
#include <chrono>
using namespace std;

vector<vector<string>> customer_db;
vector<vector<string>> employee_db;
vector<vector<string>> room_db;
vector<vector<string>> manager_set;
vector<string> wb_row;

int rent = 100;
int max_days = 15;
int max_dues = 4000;
int min_rec = 70;
int def_rec = 100;
int max_rooms = 5;
int fine = 200;
int daytime = 60;
string manager_id = "roomSysMan", manager_pw = "MngPass";
void readfile1(string fname)
{
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            customer_db.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";
}
void readfile2(string fname)
{
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            employee_db.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";
}
void readfile3(string fname)
{
    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            room_db.push_back(row);
        }
    }
    else
        cout << "Could not open the file\n";
}
void readfile4(string fname)
{
    vector<string> row;
    string line, word;
    manager_set.clear();
    fstream file(fname, ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);
            manager_set.push_back(row);
        }
        rent = stoi(manager_set[0][0]);
        max_days = stoi(manager_set[0][1]);
        max_dues = stoi(manager_set[0][2]);
        min_rec = stoi(manager_set[0][3]);
        def_rec = stoi(manager_set[0][4]);
        max_rooms = stoi(manager_set[0][5]);
        fine = stoi(manager_set[0][6]);
        daytime = stoi(manager_set[0][7]);
    }
    else
        cout << "Could not open the file\n";
}
void writefile(vector<vector<string>> par, string fname)
{
    fstream fout(fname, ios::out);
    fout.clear();
    for (auto x : par)
    {
        for (auto y : x)
        {
            fout << y;
            if (y != x.back())
                fout << ",";
        }
        fout << "\n";
    }
}
class User
{

public:
    int user_type;
    string name;
    string id;
    int rooms;
    int user_rec;
    int due;
    virtual void display() = 0;
    void see_available_rooms();
    void see_my_rooms();
    void rent_room();
    void check_available();
    void clear_due();
};

void User::see_available_rooms()
{
    cout << "room Model : room ID\n";
    for (auto it : room_db)
    {
        if (it[2] == "not_rented")
        {
            cout << it[0] << " : " << it[1] << "\n";
        }
    }
}
void User::see_my_rooms()
{
    cout << "room Model : room ID : Days till due date\n";
    for (auto it : room_db)
    {
        if (it[3] == this->id && it[2] == "rented")
        {
            string duedate;
            if ((time(0) - stoll(it[4])) / daytime > max_days)
            {
                duedate = "Overdue";
            }
            else
            {
                duedate = to_string(max_days - ((time(0) - stoll(it[4])) / daytime));
            }
            cout << it[0] << " : " << it[1] << " : " << duedate << "\n";
        }
    }
}
void User::rent_room()
{
    if (this->due < max_dues && this->rooms < (int)((float)max_rooms * ((float)this->user_rec / (float)def_rec)) && this->user_rec >= min_rec)
    {
        string id;

        cout << "Enter ID of room : ";
        cin >> id;
        int f = 0;
        for (auto it=room_db.begin();it!=room_db.end();it++)
        {
            f=1;
            if ((*it)[1] == id)
            {
                f=1;
                if((*it)[2]=="not_rented"){
                    wb_row.clear();wb_row.push_back((*it)[0]);wb_row.push_back((*it)[1]);wb_row.push_back("rented");wb_row.push_back(this->id);wb_row.push_back(to_string(time(0)));
                    room_db.erase(it);
                    room_db.push_back(wb_row);
                    this->rooms++;
                cout<<"room rented successfully\n";break;
                }
                else {cout<<"room already rented\n";}
                }
                
            
        }
        if (!f)
        {
            cout << "Invalid room ID\n";
        }
    }
    else if (this->rooms < (int)((float)max_rooms * ((float)this->user_rec / (float)def_rec)) && this->user_rec >= min_rec)
    {
        cout << "Your high pending dues make you ineligible to rent more rooms\n";
    }
    else if (this->user_rec >= min_rec)
    {
        cout << "You have reached your limit for renting rooms\n";
    }
    else
    {
        cout << "Your previous record with the company makes you ineligible to rent rooms\n";
    }
}

void User::check_available()
{
    string id;
    cout << "Enter ID of the room : ";
    cin >> id;
    int f = 0;
    for (auto it : room_db)
    {
        if (it[1] == id)
        {
            f = 1;
            if (it[2] == "not_rented")
            {
                cout << "room is available\n";
            }
            else
            {
                cout << "room is not available\n";
            }
        }
    }
    if (!f)
    {
        cout << "Invalid room ID\n";
    }
}
void User::clear_due()
{
    cout << "Your total accumulated due is : " << this->due << "\n";
    this->due = 0;
    cout << "This does not include rent of currently rented rooms.\nYour dues are cleared.Thank you for using our room Rental System!!\n";
}

class Customer : public User
{
private:
    string password;

public:
    int user_type = 1;
    void display();
    void return_room();
    Customer(string name, string id, int cust_rec, int rooms, int due, string pw)
    {
        this->name = name;
        this->id = id;
        this->user_rec = cust_rec;
        this->rooms = rooms;
        this->due = due;
        this->password = pw;
    }
    ~Customer() {
        for(auto &it:customer_db){
            if(it[1]==this->id){
                it[2]=to_string(this->user_rec);it[3]=to_string(this->rooms);it[4]=to_string(this->due);
            break;
            }
        }
    }
};

void Customer::display()
{
    string a;


W:    cout << "-------------------------------------------------------\n";
    cout << "1. Press 1 to display Profile\n";
    cout << "2. Press 2 to see available rooms\n";
    cout << "3. Press 3 to see rented rooms\n";
    cout << "4. Press 4 to see availability of a specific room\n";
    cout << "5. Press 5 to rent a room\n";
    cout << "6. Press 6 to return a room\n";
    cout << "7. Press 7 to clear dues\n";
    cout << "8. Press 8 to exit\n";
    cout << "-------------------------------------------------------\n";
    cin >> a;
    
    if(a=="1"){
        cout << "Customer Profile : \n";
        cout << "Name:" << this->name << "  "
             << "ID:" << this->id << "  "
             << "Customer Record:" << this->user_rec << "  "
             << "No. of rooms rented:" << this->rooms << "  "
             << "Due:" << this->due << "\n";
        this->display();
    }
    else if(a=="2"){
        this->see_available_rooms();
        this->display();
    }
    else if(a=="3"){
        this->see_my_rooms();
        this->display();
    }
    else if(a=="4"){
        this->check_available();
        this->display();
    }
    else if(a=="5"){
        this->rent_room();
        this->display();
    }
    else if(a=="6"){
        this->return_room();
        this->display();
    }
    else if(a=="7"){
        this->clear_due();
        this->display();
    }
    else if(a=="8"){
        cout << "Thank You\n";
    }
    else {
        cout<<"Invalid Input\n";
        goto W;
    }
    
}

void Customer::return_room()
{
    string id;
    int cond = 7, input;
    

    cout << "Enter ID of room : ";
    cin >> id;
    cout << "Enter the condition of the room(0(worst)-10(perfect condition))\n";
    cin >> input;
    if (input >= 0 && input <= 10)
    {
        cond = input;
    }
    int f = 0;
    for (auto &it : room_db)
    {
        if (it[1] == id)
        {
            f = 1;
            if (it[2] == "rented" && it[3] == this->id)
            {

                it[2] = "not_rented";
                int accdue = 0;
                int accfine = 0;
                this->user_rec -= 2 * (9 - cond);
                if (max_days < (time(0) - stoll(it[4])) / daytime)
                {
                    accdue = max_days * rent;
                    accfine = (((time(0) - stoll(it[4])) / daytime) - max_days) * fine;
                    this->user_rec -= (((time(0) - stoll(it[4])) / daytime) - max_days);
                }
                else
                {
                    accdue = ((time(0) - stoll(it[4])) / daytime) * rent;
                }
                cout << "Rent to be paid for the room is : " << accdue << "\n";
                cout << "Fine to be paid is : " << accfine << "\n";
                this->due += accdue + accfine;
                cout << "room has been returned\n";
                this->rooms--;
                break;
            }
            else
            {
                cout << "room has not been rented by you\n";
                break;
            }
        }
    }
    if (!f)
    {
        cout << "Invalid room ID\n";
    }
}

class Employee : public User
{
private:
    string password;

public:
    int user_type = 2;
    void display();
    void return_room();
    Employee(string name, string id, int emp_rec, int rooms, int due, string pw)
    {
        this->name = name;
        this->id = id;
        this->user_rec = emp_rec;
        this->rooms = rooms;
        this->due = due;
        this->password = pw;
    }
    ~Employee() {
        for(auto &it:employee_db){
            if(it[1]==this->id){
                it[2]=to_string(this->user_rec);it[3]=to_string(this->rooms);it[4]=to_string(this->due);
            break;
            }
        }
    }
};

void Employee::display()
{
    string a;


X:    cout << "-------------------------------------------------------\n";
    cout << "1. Press 1 to display Profile\n";
    cout << "2. Press 2 to see available rooms\n";
    cout << "3. Press 3 to see rented rooms\n";
    cout << "4. Press 4 to see availability of a specific room\n";
    cout << "5. Press 5 to rent a room\n";
    cout << "6. Press 6 to return a room\n";
    cout << "7. Press 7 to clear dues\n";
    cout << "8. Press 8 to exit\n";
    cout << "-------------------------------------------------------\n";
    cin >> a;
    
    if(a=="1"){
        cout << "Employee Profile : \n";
        cout << "Name:" << this->name << "  "
             << "ID:" << this->id << "  "
             << "Employee Record:" << this->user_rec << "  "
             << "No. of rooms rented:" << this->rooms << "  "
             << "Due:" << this->due << "\n";
        this->display();
    }
    else if(a=="2"){
        this->see_available_rooms();
        this->display();
    }
    else if(a=="3"){
        this->see_my_rooms();
        this->display();
    }
    else if(a=="4"){
        this->check_available();
        this->display();
    }
    else if(a=="5"){
        this->rent_room();
        this->display();
    }
    else if(a=="6"){
        this->return_room();
        this->display();
    }
    else if(a=="7"){
        this->clear_due();
        this->display();
    }
    else if(a=="8"){
        cout << "Thank You\n";
    }
    else {
        cout<<"Invalid Input\n";
        goto X;
    }
    
}

void Employee::return_room()
{
    string id;
    int cond = 7, input;
    float frac=0.85;


    cout << "Enter ID of room : ";
    cin >> id;
    cout << "Enter the condition of the room(0(worst)-10(perfect condition))\n";
    cin >> input;
    if (input >= 0 && input <= 10)
    {
        cond = input;
    }
    int f = 0;
    for (auto &it : room_db)
    {
        if (it[1] == id)
        {
            f = 1;
            if (it[2] == "rented" && it[3] == this->id)
            {

                it[2] = "not_rented";
                int accdue = 0;
                int accfine = 0;
                this->user_rec -= 2 * (9 - cond);
                if (max_days < (time(0) - stoll(it[4])) / daytime)
                {
                    accdue = max_days * ((int)((float)rent * frac));
                    accfine = (((time(0) - stoll(it[4])) / daytime) - max_days) * fine;
                    this->user_rec -= (((time(0) - stoll(it[4])) / daytime) - max_days);
                }
                else
                {
                    accdue = ((time(0) - stoll(it[4])) / daytime) * ((int)((float)rent * frac));
                }
                cout << "Rent to be paid for the room is : " << accdue << "\n";
                cout << "Fine to be paid is : " << accfine << "\n";
                this->due += accdue + accfine;
                cout << "room has been returned\n";
                this->rooms--;
                break;
            }
            else
            {
                cout << "room has not been rented by you\n";
                break;
            }
        }
    }
    if (!f)
    {
        cout << "Invalid room ID\n";
    }
}

class Manager : public User
{
private:
    string password;

public:
    int user_type = 3;
    void display();
    void see_all_rooms();
    void see_all_customers();
    void see_all_employees();
    void change_settings();
    void add_customer();
    void upd_customer();
    void rm_customer();
    void add_employee();
    void upd_employee();
    void rm_employee();
    void add_room();
    void upd_room();
    void rm_room();
    void default_set();
};

void Manager::display()
{
    string a;


  Y:  cout << "-------------------------------------------------------\n";
    cout << "                    Manager's Menu                     \n";
    cout << "1. Press 1 to change System settings(rent,fine..etc)\n";
    cout << "2. Press 2 to see data of all rooms\n";
    cout << "3. Press 3 to see data of all customers\n";
    cout << "4. Press 4 to see data of all employees\n";
    cout << "5. Press 5 to modify the room database\n";
    cout << "6. Press 6 to modify the customer database\n";
    cout << "7. Press 7 to modify the employee database\n";
    cout << "8. Press 8 to exit\n";
    cout << "9. Press 9 to reset system settings\n";
    cout << "-------------------------------------------------------\n";
    cin >> a;
    string b;
    
    
    if(a=="1"){
        this->change_settings();
        this->display();
        }
    else if(a=="2"){
        this->see_all_rooms();
        this->display();
        }
    else if(a=="3"){
        this->see_all_customers();
        this->display();
        }
    else if(a=="4"){
        this->see_all_employees();
        this->display();
        }
    else if(a=="5"){
        cout << "1. Press 1 to add room\n";
        cout << "2. Press 2 to update room\n";
        cout << "3. Press 3 to remove room\n";
        cin >> b;
        if(b=="1"){
            this->add_room();
            }
        else if(b=="2"){
            this->upd_room();
            }
        else if(b=="3"){
            this->rm_room();
            }
        
        this->display();
        }
    else if(a=="6"){
        cout << "1. Press 1 to add Customer\n";
        cout << "2. Press 2 to update Customer\n";
        cout << "3. Press 3 to remove Customer\n";
        cin >> b;
        if(b=="1"){
            this->add_customer();
            }
        else if(b=="2"){
            this->upd_customer();
            }
        else if(a=="3"){
            this->rm_customer();
            }
        else {
            cout<<"Invalid input\n";
        }
        
        this->display();
        }
    else if(a=="7"){
        cout << "1. Press 1 to add Employee\n";
        cout << "2. Press 2 to update Employee\n";
        cout << "3. Press 3 to remove Employee\n";
        cin >> b;
        
        if(b=="1"){
            this->add_employee();
        }
        else if(b=="2"){
            this->upd_employee();
        }
        else if(b=="3"){
            this->rm_employee();
            
        }
        this->display();
        }
    else if(a=="8"){
        cout << "Thank You\n";
        }
    else if(a=="9"){
        this->default_set();
        this->display();
        }
    else{
        cout<<"Invalid Input\n";
        goto Y;
    }
}

void Manager::change_settings()
{
    wb_row.clear();
    vector<vector<string>> temp;
    int tem;
    cout << "Set rent per day : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set maximum rent duration(in days) : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set maximum allowed due : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set minimum allowed customer/employee record : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set default customer/employee record : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set maximum rooms allowed to be rented per person : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set fine per day : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    cout << "Set duration of a day(in seconds) for ease of simulation : ";
    cin >> tem;
    wb_row.push_back(to_string(tem));
    temp.push_back(wb_row);
    writefile(temp, "managersettings.csv");
    readfile4("managersettings.csv");
}

void Manager::see_all_rooms()
{
    cout << "room Model : room ID : Renter : Days till due date\n";
    for (auto it : room_db)
    {
        cout << it[0] << " : " << it[1] << " : ";
        if (it[2] == "rented")
        {
            cout << it[3] << " : ";
            if ((time(0) - stoll(it[4])) / daytime > max_days)
            {
                cout << "Overdue\n";
            }
            else
            {
                cout << to_string(max_days - ((time(0) - stoll(it[4])) / daytime)) << "\n";
            }
        }
        else
        {
            cout << "Not Rented\n";
        }
    }
    cout << "Total rooms : " << room_db.size() << "\n";
}

void Manager::see_all_customers()
{
    cout << "Customer Name : Customer ID : Customer Record : rooms Rented : Pending Due\n";
    for (auto it : customer_db)
    {
        cout << it[0] << " : " << it[1] << " : " << it[2] << " : " << it[3] << " : " << it[4] << "\n";
    }
    cout << "Total Customers : " << customer_db.size() << "\n";
}

void Manager::see_all_employees()
{
    cout << "Employee Name : Employee ID : Employee Record : rooms Rented : Pending Due\n";
    for (auto it : employee_db)
    {
        cout << it[0] << " : " << it[1] << " : " << it[2] << " : " << it[3] << " : " << it[4] << "\n";
    }
    cout << "Total Employees : " << employee_db.size() << "\n";
}

void Manager::add_customer()
{
    wb_row.clear();
    string n, id;
    cout << "Enter Customer Name : ";
    cin >> n;
    wb_row.push_back(n);
B:
    cout << "Enter Customer ID : ";
    cin >> id;
    for (auto it : customer_db)
    {
        if (it[1] == id)
        {
            cout << "ID already taken.\n";
            goto B;
        }
    }
    wb_row.push_back(id);
    wb_row.push_back(to_string(def_rec));
    wb_row.push_back(to_string(0));
    wb_row.push_back(to_string(0));
    wb_row.push_back(n + '@' + id);
    customer_db.push_back(wb_row);
}

void Manager::upd_customer()
{
    string id;wb_row.clear();string temp;
    cout<<"Enter ID of Customer : ";cin>>id;
    auto it=customer_db.begin();
    for(;it!=customer_db.end();it++){
        if((*it)[1]==id){break;}
    }
    if(it==customer_db.end()){cout<<"Invalid Customer ID\n";}
    else {
        cout<<"Enter new Name : ";cin>>temp;wb_row.push_back(temp);
        cout<<"Enter new Password : ";cin>>temp;wb_row.push_back((*it)[1]);
        wb_row.push_back((*it)[2]);wb_row.push_back((*it)[3]);wb_row.push_back((*it)[4]);wb_row.push_back(temp);
    customer_db.erase(it);customer_db.push_back(wb_row);
    }
}

void Manager::rm_customer()
{
    cout << "Enter Customer ID : ";
    cin >> id;int f=0;
    for (auto it = customer_db.begin(); it != customer_db.end(); it++)
    {f=1;
        if ((*it)[1] == id && stoi((*it)[3]) == 0)
        {
            cout<<"The due to be paid by the Customer is : "<<stoi((*it)[4])<<"\n";
            customer_db.erase(it);
            cout << "Customer Deleted\n";
            break;
        }
        else if((*it)[1] == id && stoi((*it)[3]) != 0){cout<<"Customer has rented rooms, and cannot be deleted\n";}
    }
    if(!f){cout<<"Invalid Customer ID\n";}
}
void Manager::add_employee()
{
    wb_row.clear();
    string n, id;
    cout << "Enter Employee Name : ";
    cin >> n;
    wb_row.push_back(n);
C:
    cout << "Enter Employee ID : ";
    cin >> id;
    for (auto it : customer_db)
    {
        if (it[1] == id)
        {
            cout << "ID already taken.\n";
            goto C;
        }
    }
    wb_row.push_back(id);
    wb_row.push_back(to_string(def_rec));
    wb_row.push_back(to_string(0));
    wb_row.push_back(to_string(0));
    wb_row.push_back(n + '@' + id);
    employee_db.push_back(wb_row);
}

void Manager::upd_employee()
{
    string id;wb_row.clear();string temp;
    cout<<"Enter ID of Employee : ";cin>>id;
    auto it=employee_db.begin();
    for(;it!=employee_db.end();it++){
        if((*it)[1]==id){break;}
    }
    if(it==employee_db.end()){cout<<"Invalid Employee ID\n";}
    else {
        cout<<"Enter new Name : ";cin>>temp;wb_row.push_back(temp);
        cout<<"Enter new Password : ";cin>>temp;wb_row.push_back((*it)[1]);
        wb_row.push_back((*it)[2]);wb_row.push_back((*it)[3]);wb_row.push_back((*it)[4]);wb_row.push_back(temp);
    employee_db.erase(it);employee_db.push_back(wb_row);
    }
}

void Manager::rm_employee()
{
    cout << "Enter Employee ID : ";
    cin >> id;int f=0;
    for (auto it = employee_db.begin(); it != employee_db.end(); it++)
    {f=1;
        if ((*it)[1] == id &&stoi((*it)[3]) == 0)
        {
            cout<<"The due to be paid by the Employee is : "<<stoi((*it)[4])<<"\n";
            employee_db.erase(it);
            cout << "Employee Deleted\n";
            break;
        }
        else if((*it)[1] == id && stoi((*it)[3]) != 0){cout<<"Employee has rented rooms, and cannot be deleted\n";}
    }
    if(!f){cout<<"Invalid Employee ID\n";}
}
void Manager::add_room()
{
    wb_row.clear();
    string n, id;
    cout << "Enter room Model : ";
    cin >> n;
    wb_row.push_back(n);
D:
    cout << "Enter room ID : ";
    cin >> id;
    for (auto it : room_db)
    {
        if (it[1] == id)
        {
            cout << "ID already taken.\n";
            goto D;
        }
    }
    wb_row.push_back(id);
    wb_row.push_back("not_rented");
    room_db.push_back(wb_row);
}

void Manager::upd_room()
{
    string id;wb_row.clear();string temp;
    cout<<"Enter ID of room : ";cin>>id;
    auto it=room_db.begin();
    for(;it!=room_db.end();it++){
        if((*it)[1]==id){break;}
    }
    if(it==room_db.end()){cout<<"Invalid room ID\n";}
    else {
        cout<<"Enter new Model : ";cin>>temp;wb_row.push_back(temp);wb_row.push_back((*it)[1]);
        cout<<"Enter new status(rented/not_rented) : ";cin>>temp;wb_row.push_back(temp);
        wb_row.push_back((*it)[3]);wb_row.push_back((*it)[4]);
    room_db.erase(it);room_db.push_back(wb_row);
    }
}

void Manager::rm_room()
{
    cout << "Enter room ID : ";
    cin >> id;
    for (auto it = room_db.begin(); it != room_db.end(); it++)
    {
        if ((*it)[1] == id && (*it)[2]=="not_rented")
        {
            room_db.erase(it);
            cout << "room Deleted\n";
            break;
        }
        else {cout<<"room has been rented or the ID is invalid\n";}
    }
}

void Manager::default_set()
{
    wb_row.clear();
    rent = 100;
    wb_row.push_back(to_string(100));
    max_days = 15;
    wb_row.push_back(to_string(15));
    max_dues = 4000;
    wb_row.push_back(to_string(4000));
    min_rec = 70;
    wb_row.push_back(to_string(70));
    def_rec = 100;
    wb_row.push_back(to_string(100));
    max_rooms = 5;
    wb_row.push_back(to_string(5));
    fine = 200;
    wb_row.push_back(to_string(200));
    daytime = 60;
    wb_row.push_back(to_string(60));
    vector<vector<string>> temp;
    temp.push_back(wb_row);
    writefile(temp, "managersettings.csv");
}

void display_menu()
{
    string a;


Z:    cout << "---------------------------------------\n";
    cout << "\nWelcome to the room Rental System!\n";
    cout << "1. Press 1 to log in as a Customer\n";
    cout << "2. Press 2 to log in as an Employee\n";
    cout << "3. Press 3 to log in as the Manager\n";
    cout << "4. Press 4 to exit\n";
    cout << "---------------------------------------\n";
    cin >> a;
    
    if (a == "1")
    {
        string id, pass;
        int f = 0;
        cout << "Enter Customer ID : ";
        cin >> id;
        cout << "Enter Your Password : ";
        cin >> pass;
        auto it = customer_db.begin();

        for (; it != customer_db.end(); it++)
        {
            if ((*it)[1] == id && (*it)[5] == pass)
            {
                Customer c((*it)[0], (*it)[1], stoi((*it)[2]), stoi((*it)[3]), stoi((*it)[4]), (*it)[5]);
                c.display();
            
                f = 1;
            }
            else if ((*it)[1] == id && (*it)[5] != pass)
            {
                cout << "Wrong Password\n";
                display_menu();
                f = 1;
            }
        }
        if (!f)
        {
            cout << "Invalid Customer ID\n";
            display_menu();
        }
    }
    else if (a == "2")
    {
        string id, pass;
        int f = 0;
        cout << "Enter Employee ID : ";
        cin >> id;
        cout << "Enter Your Password : ";
        cin >> pass;
        auto it = employee_db.begin();

        for (; it != employee_db.end(); it++)
        {
            if ((*it)[1] == id && (*it)[5] == pass)
            {
                Employee e((*it)[0], (*it)[1], stoi((*it)[2]), stoi((*it)[3]), stoi((*it)[4]), (*it)[5]);
                e.display();
                
                f = 1;
            }
            else if ((*it)[1] == id && (*it)[5] != pass)
            {
                cout << "Wrong Password\n";
                display_menu();
                f = 1;
            }
        }
        if (!f)
        {
            cout << "Invalid Employee ID\n";
            display_menu();
        }
    }
    else if (a == "3")
    {
        string id, pass;
        int f = 0;
        cout << "Enter Manager ID : ";
        cin >> id;
        cout << "Enter Your Password : ";
        cin >> pass;

        if (manager_id == id && manager_pw == pass)
        {
            Manager m;
            m.display();
            f = 1;
        }
        else if (manager_id == id && manager_pw != pass)
        {
            cout << "Wrong Password\n";
            display_menu();
            f = 1;
        }

        if (!f)
        {
            cout << "Invalid Manager ID\n";
            display_menu();
        }
    }
    else if (a == "4")
    {
        cout << "Thank You\n";
    }
    else
    {
        cout<<"Invalid input\n";
        goto Z;
    }
}

int main()
{
    readfile1("customers.csv");
    readfile2("employees.csv");
    readfile3("rooms.csv");
    readfile4("managersettings.csv");
    display_menu();
    writefile(customer_db, "customers.csv");
    writefile(employee_db, "employees.csv");
    writefile(room_db, "rooms.csv");

    return 0;
}
