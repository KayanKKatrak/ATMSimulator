#include<iostream>
#include<cstdlib>
#include<string>
#include<stdio.h>
#include<iomanip>
#include<conio.h>
#include<ctime>

using namespace std;

void Datetime();

class account
{
    char name[20];
    string accno;
    void accno_generator();
    protected:
    float savings_balance;
    float checkings_balance;
    public:
    account();
    void transfer_funds();
    void create_account();
    void display_account();
    void update_savings(float x);
    void update_checkings(float y);
    float get_checkings();
    float get_savings();
    void balance_enquiry_slip();
};
account::account()
{
    accno_generator();
    savings_balance=0;
    checkings_balance=0;
}

void account::transfer_funds()
{
    int op,flag=0;
    float amt;
    again:
    cout<<"\n1)Checkings-->Savings\n2)Savings-->Checkings\n";
    cin>>op;
    switch(op)
    {
        case 1:cout<<"\nEnter the amount: ";
               cin>>amt;
               if(amt<=checkings_balance)
                {
                    checkings_balance-=amt;
                    savings_balance+=amt;
                    cout<<"\nDONE!";
                    break;
                }
                else
                {
                    cout<<"\nNot enough money to transfer ";
                    break;
                }
        case 2:cout<<"\nEnter the amount: ";
               cin>>amt;
               if(amt<=(savings_balance-1000))
               {
                    checkings_balance+=amt;
                    savings_balance-=amt;
                    cout<<"\nDONE!";
                    break;
               }
               else
                {
                    cout<<"\nNot enough money to transfer ";
                    break;
                }
        default:flag=1;
    }
    if(flag)
        goto again;
}
void account::accno_generator()
{
    string str;
    for (int j=0;j<3;j++)
    {
        int i = 10000 + rand()%90000;
        string str1 = to_string(i);
        if(j<2)
            str = str+str1+" ";
        else
            str = str+str1;
    }
    accno = str;
}

void account::create_account()
{
    cout<<"\nEnter the account holder's name : ";
    cin>>name;
    do
    {
        cout<<"how much money will the account hold (minimum of 10000) : ";
        cin>>savings_balance;
    }while(savings_balance<10000);
    //function call to generate an account number here
    accno_generator();
}

void account::display_account()
{
    cout<<"NAME: "<<name<<"\nACCOUNT NO: "<<accno<<"\nCHECKINGS BALANCE: ";
    cout<<fixed;
    cout<<setprecision(2)<<checkings_balance;
    cout<<"\nSAVINGS BALANCE: ";
    cout<<fixed;
    cout<<setprecision(2)<<savings_balance;
}

void account::update_checkings(float x)
{
    checkings_balance=x;
}

void account::update_savings(float y)
{
    savings_balance=y;
}

float account::get_checkings()
{
    return checkings_balance;
}

float account::get_savings()
{
    return savings_balance;
}

void account::balance_enquiry_slip()
{
    cout<<"\n\t\tBALANCE ENQUIRY\n";
    Datetime();
    cout<<"\nNAME: "<<name<<endl;
    cout<<"ACC: XXXXX XXXXX X"<<accno[13]<<accno[14]<<accno[15]<<accno[16]<<endl;
    cout<<"CHECKINGS BALANCE: "<<checkings_balance<<endl;
    cout<<"SAVINGS BALANCE: "<<savings_balance<<endl;
}

class card:public account
{
    string cardno;
    string cardpin;
    void cardno_generator();
    void cardpin_generator();
    public:
    void change_cardpin();
    void create_card();
    void display_card();
    int check_num(string);
    string get_pswd();
    string get_cardno();
};

string card::get_cardno()
{
    return cardno;
}

int card::check_num(string num)
{
    if (num==cardno)
        return 1;
    return 0;
}

string card::get_pswd()
{
    return cardpin;
}
void card::cardno_generator()
{
    string str;
    for(int i=0;i<4;i++)
    {
        int j = 1000 + rand()%9000;
        string str1 = to_string(j);
        if(i<3)
            str = str+str1+" ";
        else
            str = str+str1;
    }
    cardno = str;
}

void card::cardpin_generator()
{
    string str;
    int i = 1000 + (rand()%8999+1);
    str = to_string(i);
    cardpin = str;
}


void card::change_cardpin()
{
    string str,str1;
    char ch[19],ch1[4];
    int i=0;
    do
    {
        fflush(stdin);
        cout<<"\nEnter card number: ";
        gets(ch);
        fflush(stdin);
        str=string(ch);
        i++;
    }while(str!=cardno&&i<3);
    if(str!=cardno)
    {
        cout<<"\nREQUEST DECLINED\n";
        return;
    }
    i=0;
    do
    {
        fflush(stdin);
        cout<<"\nEnter the old pin: ";
        fflush(stdin);
        gets(ch1);
        //cout<<endl<<ch1<<sizeof(string(ch1));
        //cout<<endl<<sizeof(cardpin);
        //cout<<"1";
        str1=string(ch1);
        //cout<<"1";
        i++;

        //cout<<"1";
    }while(str1!=cardpin&&i<3);
    if(cardpin!=str1)
    {
        cout<<"\nREQUEST DECLINED\n";
        return;
    }
    //cout<<"1";
    string newpin;
    cout<<"\nenter the new pin: ";
    cin>>cardpin;
    //getline(cin,newpin);
    //cardpin=newpin;
    cout<<"\nPin has been changed to  "<<cardpin;
}

void card::create_card()
{
    cardno_generator();
    cardpin_generator();
}

void card::display_card()
{
    cout<<"\nCARD NO: "<<cardno<<"\nPIN: "<<cardpin;
}

class login:public card
{
    float dynamic_balance_savings;
    float dynamic_balance_checkings;
    public:
    float withdraw();
    float deposit();
    float transfer();
    int log();
};

int login::log()
{
    string pass;
    char ch;
    fflush(stdin);
    cout<<"Enter password"<<endl;
    ch=_getch();
    while(ch!=13){
        if (ch==8){
            if (pass.length()>0){
                cout<<"\b \b";
                pass.erase(pass.length()-1);
            }
        }
        else{
            pass.push_back(ch);
            cout<<'*';
        }
        ch=_getch();
    }
    string pswd=get_pswd();
    if (pass==pswd)
        return 1;
    return 0;
}

float login::withdraw()
{
    cout<<"\nPlease select account to withdraw from:\n1. Savings\n2.Checkings"<<endl;
    int type;
    cin>>type;
    int amount;
    cout<<"Enter amount to be withdrawn:"<<endl;
    cin>>amount;
    string ch;
    cout<<"Are you sure you want to withdraw "<<amount<<" from account?(yes/no)"<<endl;
    fflush(stdin);
    cin>>ch;
    fflush(stdin);
    string quitch;
    if (ch=="no" || ch=="No")
        return -1;
    switch(type)
    {
        case 1:dynamic_balance_savings=account::get_savings();
            while((dynamic_balance_savings-amount)<10000)
            {
                cout<<"Not enough money in account"<<endl<<"Continue?(yes/no)"<<endl;
                fflush(stdin);
                cin>>quitch;
                fflush(stdin);
                if (quitch=="no" || quitch=="No")
                    return -1;
                cout<<"Enter amount to be withdrawn:"<<endl;
                cin>>amount;
            }
            dynamic_balance_savings=dynamic_balance_savings-amount;
            update_savings(dynamic_balance_savings);
            return dynamic_balance_savings;
            break;
        case 2:dynamic_balance_checkings=account::get_checkings();
            while((dynamic_balance_checkings-amount)<0)
            {
                cout<<"Not enough money in account"<<endl<<"Continue?(yes/no)"<<endl;
                fflush(stdin);
                cin>>quitch;
                fflush(stdin);
                if (quitch=="no" || quitch=="No")
                    return -1;
                cout<<"Enter amount to be withdrawn:"<<endl;
                cin>>amount;
            }
            dynamic_balance_checkings=dynamic_balance_checkings-amount;
            update_checkings(dynamic_balance_checkings);
            return dynamic_balance_checkings;
            break;
        default: cout<<"Invalid entry"<<endl;
        return -1;
    }
}

float login::deposit()
{
    float amount;
    int ch;
    cout<<"\nPlease specify account to deposit in:\n1. Savings\n2. Checkings"<<endl;
    cin>>ch;
    cout<<"Enter amount to be deposited: "<<endl;
    cin>>amount;
    switch(ch)
    {
        case 1:dynamic_balance_savings=get_savings();
        dynamic_balance_savings+=amount;
        update_savings(dynamic_balance_savings);
        return dynamic_balance_savings;
        break;
        case 2:dynamic_balance_checkings=get_checkings();
        dynamic_balance_checkings+=amount;
        update_checkings(dynamic_balance_checkings);
        return dynamic_balance_checkings;
        break;
        default: cout<<"Invalid entry."<<endl;
        return -1;
    }
}

int search(string num,login a[],int n)
{
    int i=0;
    while (num!=a[i].get_cardno() && i<n)
        {
            ++i;
        }
    if (i!=n)
    {
        return i;
    }
    cout<<"Card does not exist"<<endl;
    return -1;
}

void Datetime()
{
    // current date/time based on current system
   time_t now = time(0);

   // convert now to string form
   char* dt = ctime(&now);

   cout << endl << dt << endl;

   // convert now to tm struct for UTC
   //tm *gmtm = gmtime(&now);
   //dt = asctime(gmtm);
   //cout << "The UTC date and time is:"<< dt << endl;
}

void menu()
{
    login p[5];
    static int account_count = 0;
    int choice,a;
    char q,ch[19];
    string cardnum,ans;
    start:
    cout<<"\n------MOOLA BANK------\n";
    cout<<"\t1)Create Account\n\t2)Deposit\n\t3)Withdraw\n\t4)Fund Transfer\n\t5)Account Details\n\t6)Card Details\n";
    cout<<"What would you like to do? ";
    fflush(stdin);
    cin>>choice;
    switch(choice)
    {
        case 1:{
                int i = account_count;
                account_count++;
                p[i].create_account();
                cout<<"\nYour Account: "<<endl;
                p[i].display_account();
                cout<<"\nA card has been generated for you: "<<endl;
                p[i].create_card();
                p[i].display_card();
                cout<<"\nplease set your own personal PIN number"<<endl;
                p[i].change_cardpin();
               }
               break;
        case 2:{
                cout<<endl<<"\nEnter your card number ";
                fflush(stdin);
                gets(ch);
                fflush(stdin);
                cardnum = string(ch);
                a = search(cardnum,p,account_count);
                if(a==-1)
                   break;
                if(!p[a].log())
                {
                    cout<<"INVALID PASSWORD";
                    break;
                }
                p[a].deposit();
                cout<<"Would you like a receipt with that? (yes/no)";
                cin>>ans;
                if(ans=="yes")
                {
                    p[a].balance_enquiry_slip();
                }
               }
               break;
        case 3:{
                cout<<endl<<"\nEnter your card number ";
                fflush(stdin);
                gets(ch);
                fflush(stdin);
                cardnum = string(ch);
                a = search(cardnum,p,account_count);
                if(a==-1)
                   break;
                if(!p[a].log())
                {
                    cout<<"INVALID PASSWORD";
                    break;
                }
                p[a].withdraw();
                cout<<"Would you like a receipt with that? (yes/no)";
                cin>>ans;
                if(ans=="yes")
                {
                    p[a].balance_enquiry_slip();
                }
                }
               break;
        case 4:{
                cout<<endl<<"\nEnter your card number ";
                fflush(stdin);
                gets(ch);
                fflush(stdin);
                cardnum = string(ch);
                a = search(cardnum,p,account_count);
                if(a==-1)
                   break;
                if(!p[a].log())
                {
                    cout<<"INVALID PASSWORD";
                    break;
                }
                p[a].transfer_funds();
                cout<<"Would you like a receipt with that? (yes/no)";
                cin>>ans;
                if(ans=="yes")
                {
                    p[a].balance_enquiry_slip();
                }
               }
               break;
        case 5:{
                cout<<endl<<"\nEnter your card number ";
                fflush(stdin);
                gets(ch);
                fflush(stdin);
                cardnum = string(ch);
                a = search(cardnum,p,account_count);
                if(a==-1)
                   break;
                if(!p[a].log())
                {
                    cout<<"INVALID PASSWORD";
                    break;
                }
                p[a].display_account();
               }
               break;
        case 6:{
                cout<<endl<<"\nEnter your card number ";
                fflush(stdin);
                gets(ch);
                fflush(stdin);
                cardnum = string(ch);
                a = search(cardnum,p,account_count);
                if(a==-1)
                   break;
                if(!p[a].log())
                {
                    cout<<"INVALID PASSWORD";
                    break;
                }
                p[a].display_card();
               }
               break;
        default:break;
    }
    cout<<"\nPress q to signout ";
    cin>>q;
    if(q!='q'&&q!='Q')
        goto start;
}

int main()
{
    srand(time(0));
    menu();
    return 0;
}
