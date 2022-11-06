#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;
string id, password;
int i = 0;
char ch,check_ad='0';

//function to check if the file is empty or not
bool empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

class customer
{
    protected:
        string* fname, * lname, * address, * contact;
        string *CustType;
        int CustID;

    public:
        customer()
        {
            fname = new string;
            lname = new string;
            address = new string;
            contact = new string;
            CustType = new string;
        }

        customer(const customer &o)
        {
            fname = new string;
            lname = new string;
            address = new string;
            contact = new string;
            CustType = new string;
        }

        string getCustType()
        {
            return *CustType;
        }

        void setCustType(string a)
        {
            *CustType = a;
        }

        string getfname()
        {
            return *fname;
        }

        string getlname()
        {
            return *lname;
        }

        string getaddress()
        {
            return *address;
        }

        string getcont()
        {
            return *contact;
        }

        int getCustID()
        {
            return CustID;
        }

        void setfname()
        {
            cout << "Enter customer's first name: ";
            getline(cin, *fname);
        }

        void setlname()
        {
            cout << "Enter customer's last name: ";
            getline(cin, *lname);
        }

        void setaddress()
        {
            cout << "Enter " << *fname << *lname << "'s address: ";
            getline(cin, *address);
        }

        void setcont()
        {
            cout << "Enter customer's contact number: ";
            getline(cin, *contact);
        }

        void setcusid()
        {
            srand(time(0));
            int a;
            char check;

            if(*CustType == "R")
            {
                ifstream i("Customer_R.txt");

                while(check=='0' || CustID < 100)
                {
                    CustID = rand()%1000 + 1;

                    i >> a;

                    if(CustID == a)
                    {
                        check = '0';
                    }
                    
                    else
                        check = '1';
                };
            }

            else
            {
                ifstream i("Customer_C.txt");

                while(check=='0' || CustID < 100)
                {
                    CustID = rand()%1000 + 1;

                    i >> a;

                    if(CustID == a)
                    {
                        check = '0';
                    }
                    
                    else
                        check = '1';
                };
            }
        }

        virtual void calcbill() = 0;
        virtual void display() = 0;

        ~customer()
        {
            delete fname;
            delete lname;
            delete address;
            delete contact;
            delete CustType;
        }
};

class Resedentialcustomer :public customer
{
    float* fan, * bulbs, * tv, *bill;
    int *hours;

    public:
        Resedentialcustomer()
        {
            fan = new float;
            bulbs = new float;
            tv = new float;
            hours = new int[3];
            bill = new float;
        }

        Resedentialcustomer(const Resedentialcustomer &o)
        {
            fan = new float;
            bulbs = new float;
            tv = new float;
            hours = new int[3];
            bill = new float;
        }

        float gettv()
        {
            return *tv;
        }

        float getbulbs()
        {
            return *bulbs;
        }

        float getfan()
        {
            return *fan;
        }

        void calcbill()
        {
            Resedentialcustomer RC;
            fstream inp("R_rates.txt", ios::in);
            float a, b, c;
            inp >> a;
            inp >> b;
            inp >> c;
            inp.close();

            *bill = (a * hours[0]) + (b * hours[1]) + (c * hours[2]);
        }

        float getbill()
        {
            return *bill;
        }

        void setratefan(float a)
        {
            *fan = a;
        }

        void setratebulbs(float b)
        {
            *bulbs = b;
        }

        void setratetv(float c)
        {
            *tv = c;
        }

        void sethours()
        {
            cout << "Enter hours consumed by fan: " << endl;
            cin >> hours[0];
            cout << "Enter hours consumed by bulbs: " << endl;
            cin >> hours[1];
            cout << "Enter hours consumed by tv: " << endl;
            cin >> hours[2];
        }

        void gethours()
        {
            cout << "Enter hours consumed by fan: " << hours[0] << endl;
            cout << "Enter hours consumed by bulbs: " << hours[1] << endl;
            cout << "Enter hours consumed by tv: " << hours[2] << endl;
        }

        void change_R_rate()
        {
            char ch;
            do
            {
                cout << "Which appliances rates do you want to change:" << endl;
                cout << "1. Ceiling Fans" << endl;
                cout << "2. Television" << endl;
                cout << "3. Light Bulb" << endl;
                fflush(stdin);
                cin >> ch;
                fflush(stdin);
            } while (ch < '0' || ch > '3');

            switch (ch)
            {
                case'1':
                {
                    cout << "Enter the new rate: ";
                    cin >> *fan;

                    ofstream o("R_rates.txt", ios::trunc);
                    o << *fan << endl;
                    o << *bulbs << endl;
                    o << *tv;
                    o.close();

                    break;
                }

                case'2':
                {
                    cout << "Enter the new rate: ";
                    cin >> *bulbs;

                    ofstream o("R_rates.txt", ios::trunc);
                    o << *fan << endl;
                    o << *bulbs << endl;
                    o << *tv;
                    o.close();

                    break;
                }

                case'3':
                {
                    cout << "Enter the new rate: ";
                    cin >> *tv;

                    ofstream o("R_rates.txt", ios::trunc);
                    o << *fan << endl;
                    o << *bulbs << endl;
                    o << *tv;
                    o.close();

                    break;
                }

                default:
                    break;
            }
        }

        void display()
        {
            ifstream i("R_rates.txt");

            float a, b, c;
            i >> a;
            i >> b;
            i >> c;
            i.close();

            cout << "Rate for fan is: " << a << " per unit" << endl;
            cout << "Rate for bulbs is: " << b << " per unit" << endl;
            cout << "Rate for television is: " << c << " per unit" << endl;

            system("PAUSE");
        }

        ~Resedentialcustomer()
        {
            delete fan;
            delete bulbs;
            delete tv;
            delete hours;
            delete bill;
        }

    friend class Admin;
};

class Commercialcustomer :public customer
{
    protected:
        float* oven, * f_process, * microwave, * printer, * computer , *bill;
        int *hours;

    public:
        Commercialcustomer()
        {
            oven = new float;
            f_process = new float;
            microwave = new float;
            printer = new float;
            computer = new float;
            hours = new int[5];
            bill = new float;
        }

        Commercialcustomer(const Commercialcustomer &o)
        {
            oven = new float;
            f_process = new float;
            microwave = new float;
            printer = new float;
            computer = new float;
            hours = new int[5];
            bill = new float;
        }

        void setrateoven(float a)
        {
            *oven = a;
        }

        void setratefp(float b)
        {
            *f_process = b;
        }

        void setratemv(float c)
        {
            *microwave = c;
        }

        void setrateprinter(float d)
        {
            *printer = d;
        }

        void setratecomp(float e)
        {
            *computer = e;
        }

        void sethoursR()
        {
            cout << "Enter hours consumed by oven: " << endl;
            cin >> hours[0];
            cout << "Enter hours consumed by food processor: " << endl;
            cin >> hours[1];
            cout << "Enter hours consumed by microwave: " << endl;
            cin >> hours[2];
        }

        void gethoursR()
        {
            cout << "Enter hours consumed by oven: " << hours[0] << endl;
            cout << "Enter hours consumed by food processor: " << hours[1] << endl;
            cout << "Enter hours consumed by microwave: " << hours[2] << endl;
        }

        void calcbill()
        {
            Commercialcustomer CC;
            fstream inp("C_rates.txt", ios::in);
            float a, b, c;
            inp >> a;
            inp >> b;
            inp >> c;
            inp.close();

            *bill = (a * hours[0]) + (b * hours[1]) + (c * hours[2]);
        }

        void calcbillO()
        {
            Commercialcustomer CC;
            fstream inp("C_rates.txt", ios::in);
            float a, b, c, d, e;
            inp >> a;
            inp >> b;
            inp >> c;
            inp >> d;
            inp >> e;
            inp.close();

            *bill = (d * hours[3]) + (e * hours[4]);
        }

        float getbill()
        {
            return *bill;
        }

        void sethoursO()
        {
            cout << "Enter hours consumed by computer: " << endl;
            cin >> hours[3];
            cout << "Enter hours consumed by printer: " << endl;
            cin >> hours[4];
        }

        void gethoursO()
        {
            cout << "Enter hours consumed by computer: " << hours[3] << endl;
            cout << "Enter hours consumed by printer: " << hours[4] << endl;
        }

        void change_R_rate()
        {
            char ch;

            do
            {
                system("CLS");
                cout << "Which appliances do you want to change the rates of?" << endl;
                cout << "1. Oven" << endl;
                cout << "2. Food Processor" << endl;
                cout << "3. Microwave" << endl;
                fflush(stdin);
                cin >> ch;
                fflush(stdin);
            } while (ch <= '0' || ch > '3');

            if (ch == '1')
            {
                cout << "Enter the new rate: ";
                cin >> *oven;

                ofstream o("C_rates.txt", ios::trunc);
                o << *oven << endl;
                o << *f_process << endl;
                o << *microwave << endl;
                o << *computer << endl;
                o << *printer;
                o.close();
            }

            else if (ch == '2')
            {
                cout << "Enter the new rate: ";
                cin >> *f_process;

                ofstream o("C_rates.txt", ios::trunc);
                o << *oven << endl;
                o << *f_process << endl;
                o << *microwave << endl;
                o << *computer << endl;
                o << *printer;
                o.close();
            }

            else if (ch == '3')
            {
                cout << "Enter the new rate: ";
                cin >> *microwave;

                ofstream o("C_rates.txt", ios::trunc);
                o << *oven << endl;
                o << *f_process << endl;
                o << *microwave << endl;
                o << *computer << endl;
                o << *printer;
                o.close();
            }

            else
            {
                cout << "Task Failed Succesfully";
            }
        }

        void display()
        {
            float a, b, c;
            
            ifstream i("C_rates.txt");
            i >> a;
            i >> b;
            i >> c;

            cout << "The rate of Oven is: " << a << " per unit" << endl;
            cout << "The rate of Food Processor is: " << b << " per unit" << endl;
            cout << "The rate of Microwave is: " << c << " per unit" << endl;

            system("PAUSE");
        }

        void change_O_rate()
        {
            char ch;

            do
            {
                system("CLS");
                cout << "Which appliances do you want to change the rates of?" << endl;
                cout << "1. Printer" << endl;
                cout << "2. Computer" << endl;
                fflush(stdin);
                cin >> ch;
                fflush(stdin);
            } while (ch <= '0' || ch > '3');

            if (ch == '1')
            {
                cout << "Enter the new rate: ";
                cin >> *printer;

                ofstream o("C_rates.txt", ios::trunc);
                o << *oven << endl;
                o << *f_process << endl;
                o << *microwave << endl;
                o << *computer << endl;
                o << *printer;
                o.close();
            }

            else if (ch == '2')
            {
                cout << "Enter the new rate: ";
                cin >> *computer;

                ofstream o("C_rates.txt", ios::trunc);
                o << *oven << endl;
                o << *f_process << endl;
                o << *microwave << endl;
                o << *computer << endl;
                o << *printer;
                o.close();
            }

            else
            {
                cout << "Task Failed Successfully";
            }
        }

        void display_O()
        {
            float a, b, c, d, e;

            ifstream i("C_rates.txt");
            i >> a;
            i >> b;
            i >> c;
            i >> d;
            i >> e;

            cout << "The rate of Printer is: " << d << " per unit" << endl;
            cout << "The rate of Computer is: " << e << " per unit" << endl;

            system("PAUSE");
        }

        ~Commercialcustomer()
        {
            delete oven;
            delete f_process;
            delete microwave;
            delete computer;
            delete printer;
            delete bill;
        }
};

class Admin
{
    string  adminID, password;

public:
    Admin()
    {

    }

    void setid(string id)
    {
        adminID = id;
    }

    void setpass(string pword)
    {
        password = pword;
    }

    string getid()
    {
        return adminID;
    }

    string getpass()
    {
        return password;
    }

    int cust_check(string s1, string s2)
    {
        if(adminID.compare(s1)!=0 || password.compare(s2)!=0)
        {
            return 0;
        }

        else if(adminID.compare(s1)==0 || password.compare(s2)==0)
        {
            return 1;
        }

        return 0;
    }
};

void RC_options()
{   
    Resedentialcustomer RC;
    fstream inp("R_rates.txt", ios::in);
    float a, b, c;
    inp >> a;
    inp >> b;
    inp >> c;
    RC.setratefan(a);
    RC.setratebulbs(b);
    RC.setratetv(c);
    inp.close();

    do
    {
        system("CLS");
        cout << "What do you want to do?" << endl;
        cout << "1. Change the rates" << endl;
        cout << "2. Display the rates" << endl;
        cin >> ch;
    } while (ch <= '0' || ch > '2');

    switch (ch)
    {
        case'1':
        {
            system("CLS");
            RC.change_R_rate();
            break;
        }

        case '2':
        {
            system("CLS");
            RC.display();
            break;
        }
    }
}

void CC_option()
{
    Commercialcustomer CC;
    fstream inp("C_rates.txt", ios::in);
    float a, b, c, d, e;
    inp >> a;
    inp >> b;
    inp >> c;
    inp >> d;
    inp >> e;
    CC.setrateoven(a);
    CC.setratemv(b);
    CC.setratefp(c);
    CC.setratecomp(d);
    CC.setrateprinter(e);
    inp.close();

    do
    {
        system("CLS");
        cout << "What do you want to do?" << endl;
        cout << "1. Change the rates & Display the rates for Restaurant: " << endl;
        cout << "2. Change the rates & Display the rates for Office: " << endl;
        cin >> ch;
    } while (ch <= '0' || ch > '2');

    switch (ch)
    {
        case'1':
        {
            do
            {
                system("CLS");
                cout << "What do you want to do?" << endl;
                cout << "1. Change the rates" << endl;
                cout << "2. Display the rates" << endl;
                cin >> ch;
            } while (ch <= '0' || ch > '2');

            if (ch == '1')
            {
                system("CLS");
                CC.change_R_rate();
            }

            else if (ch == '2')
            {
                system("CLS");
                CC.display();
            }

            break;
        }

        case '2':
        {
            do
            {
                system("CLS");
                cout << "What do you want to do?" << endl;
                cout << "1. Change the rates" << endl;
                cout << "2. Display the rates" << endl;
                cin >> ch;
            } while (ch <= '0' || ch > '2');

            if (ch == '1')
            {
                system("CLS");
                CC.change_O_rate();
            }

            else if (ch == '2')
            {
                system("CLS");
                CC.display_O();
            }

            break;
        }
    }
}

void RegisterCust()
{
    do
    {
        cout << "Whom do you want to register:" << endl;
        cout << "1. Residential Customer" << endl;
        cout << "2. Commercial Customer" << endl;
        cin >> ch;
    } while (ch <= '0' || ch > '2');

    if(ch == '1')
    {
        Resedentialcustomer obj;
        fflush(stdin);
        obj.setfname();
        fflush(stdin);
        obj.setlname();
        fflush(stdin);
        obj.setCustType("R");
        fflush(stdin);
        obj.setcusid();
        fflush(stdin);
        obj.setaddress();
        fflush(stdin);
        obj.setcont();
        fflush(stdin);
        obj.sethours();
        fflush(stdin);
        obj.calcbill();
        fflush(stdin);
        cout << "This is the customer's ID: " << obj.getCustID() << endl;
        system("PAUSE");

        ofstream o("Customer_R.txt",ios::app);
        o << obj.getCustID() << endl;
        o << obj.getfname() << " " << obj.getlname() << endl;
        o << obj.getaddress() << endl;
        o << obj.getcont() << endl;
        o << obj.getCustType() << endl;
        o << obj.getbill() << endl;
        o.close();
    }

    else if (ch == '2')
    {
        Commercialcustomer obj;

        do
        {
            system("CLS");
            cout << "What do you want to register for?" << endl;
            cout << "1. Restaurant" << endl;
            cout << "2. Office" << endl;
            cin >> ch;
        } while (ch <= '0' || ch > '2');

        if(ch == '1')
        {
            fflush(stdin);
            obj.setfname();
            fflush(stdin);
            obj.setlname();
            fflush(stdin);
            obj.setcusid();
            fflush(stdin);
            obj.setaddress();
            fflush(stdin);
            obj.setcont();
            fflush(stdin);
            obj.sethoursR();
            fflush(stdin);
            obj.setCustType("CR");
            fflush(stdin);
            obj.calcbill();
            fflush(stdin);
            cout << "This is the customer's ID: " << obj.getCustID() << endl;
            system("PAUSE");

            ofstream o("Customer_C.txt",ios::app);
            o << obj.getCustID() << endl;
            o << obj.getfname() << " " << obj.getlname() << endl;
            o << obj.getaddress() << endl;
            o << obj.getcont() << endl;
            o << obj.getCustType() << endl;
            o << obj.getbill() << endl;
            o.close();
        }

        else if (ch == '2')
        {
            fflush(stdin);
            obj.setfname();
            fflush(stdin);
            obj.setlname();
            fflush(stdin);
            obj.setcusid();
            fflush(stdin);
            obj.setaddress();
            fflush(stdin);
            obj.setcont();
            fflush(stdin);
            obj.sethoursO();
            fflush(stdin);
            obj.setCustType("CO");
            fflush(stdin);
            obj.calcbillO();
            fflush(stdin);
            cout << "This is the customer's ID: " << obj.getCustID() << endl;
            system("PAUSE");

            ofstream o("Customer_C.txt",ios::app);
            o << obj.getCustID() << endl;
            o << obj.getfname() << " " << obj.getlname() << endl;
            o << obj.getaddress() << endl;
            o << obj.getcont() << endl;
            o << obj.getCustType() << endl;
            o << obj.getbill() << endl;
            o.close();
        }
    }
}

void optionlist()
{
    do
    {
        system("CLS");
        cout << "What do you want to do?: " << endl;
        cout << "1. To Change or Display Rates for Resedential Customer" << endl;
        cout << "2. To Change or Display Rates for Commercial Customer" << endl;
        cout << "3. Register a new customer" << endl;
        cin >> ch;
    } while (ch <= '0' || ch > '4');

    switch (ch)
    {
        case'1':
        {
            system("CLS");
            RC_options();
            break;
        }

        case'2':
        {
            system("CLS");
            CC_option();
            break;
        }

        case '3':
        {
            system("CLS");
            RegisterCust();
            break;
        }

        default:
            break;
    }
}

void emptyadmin()
{
    system("CLS");
    cout << "It seems that you are the new admin!" << endl;
    cout << "Enter your ID: ";
    fflush(stdin);
    getline(cin, id);
    cout << "Enter your password: ";
    fflush(stdin);
    getline(cin, password);
    Admin A;
    A.setid(id);
    A.setpass(password);

    fstream o("Admin.txt", ios::out);
    o << id << endl;
    o << password;
    o.close();

    optionlist();
}

void savedadmin()
{
    system("CLS");
    Admin B;

    cout << "First you have to Login!" << endl;

    fflush(stdin);
    cout << "Enter your ID: ";
    getline(cin,id);
    B.setid(id);

    fflush(stdin);
    cout << "Enter your password: ";
    getline(cin,password);
    B.setpass(password);

    ifstream in("Admin.txt",ios::in);
    string s1,s2;
    in >> s1;
    in >> s2;
    in.close();

    if(B.cust_check(s1,s2) == 1)
    {
        cout << "You have successfully logged in!" << endl;;
        system("PAUSE");
        optionlist();
    }

    else
    {
        cout << "Incorrect ID or password!";
    }

}

int main()
{
	char ch;

    do
    {
        do
        {
            system("CLS");
            cout << "What do you want to login as?:" << endl;
            cout << "1. Admin" << endl;
            cout << "2. Customer" << endl;
            cout << "3. Exit Program"<<endl;
            cin >> ch;
        } while (ch <= '0' || ch > '3');

        if(ch=='3')
        {
            exit(0);
        }

        else
        {
            switch (ch)
            {
                case '1':
                {
                    ifstream in("Admin.txt",ios::in);

                    if(empty(in))
                    {
                        emptyadmin();
                    }

                    else
                    {
                        savedadmin();
                    }

                    break;
                }

                case'2':
                {
                    string ID,checkID;
                    char a;

                    system("CLS");
                    cout << "Welcome Dear Customer!" << endl;
                    system("PAUSE");

                    do
                    {
                        system("CLS");
                        cout << "Enter which type of cutomer are you:" << endl;
                        cout << "1. Residential" << endl;
                        cout << "2. Commercial Restaraunt" << endl;
                        cout << "3. Commercial Office" << endl;
                        cin >> a;
                    } while (a <= '0' || a > '3');

                    switch(a)
                    {
                        case'1':
                        {
                            string CuCh="R";
                            char c='0';
                            ifstream in("Customer_R.txt",ios::in);
                            fflush(stdin);
                            cout << "Enter your ID to get your bill: ";
                            getline(cin,ID);

                            do
                            {
                                getline(in,checkID);

                                if(ID == checkID)
                                {
                                    c='1';
                                    string a, b, c, d, e;

                                    getline(in,a);
                                    getline(in,b);
                                    getline(in,c);
                                    getline(in,d);
                                    getline(in,e);

                                    if(d==CuCh)
                                    {
                                        system("CLS");
                                        cout << "------------------Final Bill------------------" << endl;
                                        cout << "Name: " << a << endl;
                                        cout << "ID: " << ID << endl;
                                        cout << "Customer Type: Resedential" << endl;
                                        cout << "Address: " << b << endl;
                                        cout << "Contact: " << c << endl;
                                        cout << "Total Bill: " << e << endl;
                                        cout << "----------------------------------------------" << endl;
                                        system("PAUSE");
                                        break;
                                    }

                                    else
                                    {
                                        c='0';
                                        continue;
                                    }
                                }

                                else
                                {
                                    c='0';
                                    continue;
                                }

                            } while (!in.eof());

                            if(c=='0')
                            {
                                in.close();
                                cout << "ID not find!" << endl;
                                system("PAUSE");
                                break;
                            }

                            else
                            {
                                in.close();
                                break;
                            }
                        }

                        case'2':
                        {
                            string CuCh="CR";
                            char c='0';
                            ifstream in("Customer_C.txt",ios::in);
                            fflush(stdin);
                            cout << "Enter your ID to get your bill: ";
                            getline(cin,ID);

                            do
                            {
                                getline(in,checkID);

                                if(ID == checkID)
                                {
                                    c='1';
                                    string a, b, c, d, e;

                                    getline(in,a);
                                    getline(in,b);
                                    getline(in,c);
                                    getline(in,d);
                                    getline(in,e);
                                
                                    if(d==CuCh)
                                    {
                                        c='1';
                                        system("CLS");
                                        cout << "------------------Final Bill------------------" << endl;
                                        cout << "Name: " << a << endl;
                                        cout << "ID: " << ID << endl;
                                        cout << "Customer Type: Commercial Restaraunt" << endl;
                                        cout << "Address: " << b << endl;
                                        cout << "Contact: " << c << endl;
                                        cout << "Total Bill: " << e << endl;
                                        cout << "----------------------------------------------" << endl;
                                        system("PAUSE");
                                        break;
                                    }

                                    else
                                    {
                                        c='0';
                                        continue;
                                    }
                                }

                                else
                                {
                                    c='0';
                                    continue;
                                }

                            } while (!in.eof());

                            if(c=='0')
                            {
                                in.close();
                                cout << "ID not find!" << endl;
                                system("PAUSE");
                                break;
                            }

                            else
                            {
                                in.close();
                                break;
                            }
                        }

                        case'3':
                        {
                            string CuCh="CO";
                            char c='0';
                            ifstream in("Customer_C.txt",ios::in);
                            fflush(stdin);
                            cout << "Enter your ID to get your bill: ";
                            getline(cin,ID);

                            do
                            {
                                getline(in,checkID);

                                if(ID == checkID)
                                {
                                    c='1'; 
                                    string a, b, c, d, e;

                                    getline(in,a);
                                    getline(in,b);
                                    getline(in,c);
                                    getline(in,d);
                                    getline(in,e);

                                    if(d==CuCh)
                                    {
                                        c='1';
                                        system("CLS");
                                        cout << "------------------Final Bill------------------" << endl;
                                        cout << "Name: " << a << endl;
                                        cout << "ID: " << ID << endl;
                                        cout << "Customer Type: Commercial Office" << endl;
                                        cout << "Address: " << b << endl;
                                        cout << "Contact: " << c << endl;
                                        cout << "Total Bill: " << e << endl;
                                        cout << "----------------------------------------------" << endl;
                                        system("PAUSE");
                                        break;
                                    }
                                }

                                else
                                {
                                    c='0';
                                    continue;
                                }

                            } while (!in.eof());

                            if(c=='0')
                            {
                                in.close();
                                cout << "ID not find!" << endl;
                                system("PAUSE");
                                break;
                            }

                            else
                            {
                                in.close();
                                break;
                            }
                        }
                    }

                    break;
                }

                default:
                    break;
            }
        }

    }while(ch!='z');

    return 0;
}