#include <iostream>
#include <string>
#include <cstdlib>
#include "hash.h"
#include <ctime>

using namespace std;

int main()
{
    hash Bd;
    char choice;
    string name;
    string name2;
    string status;
    string accountnumber;
    string accountnumber2;
    bool exist = false;
    float money = 0;
    do
    {

        cout << "\n\n\n\tMain Menu";
        cout << "\n\n\n\t0. Create Account";
        cout << "\n\n\n\t1. Deposit  Account";
        cout << "\n\n\n\t2. Withdraw Account";
        cout << "\n\n\n\t3. Transfer from Account to Account";
        cout << "\n\n\n\t4. Balance Inquiry"; // Still need this
        cout << "\n\n\n\t5. All Account Holder List";
        cout << "\n\n\n\t6. Close an Account";
        cout << "\n\n\n\t7. Find Account";
        cout << "\n\n\n\t8. Exit";
        cout << "\n\n\n\tEnter a number Hoss!";
        cout << endl << "\t";
        cin >> choice;
        cout << endl << endl;

        system("Cls");
        switch(choice)
        {
        // Create Account
        case '0':

            Bd.AddItem();
            break;
        // Deposit Account
        case '1':
            while((name != "exit") && (status != "exit")){
				cout << "What's the name on the account? " << endl;
				cin.sync();
				getline(cin, name);
				if (name != "exit")
				{
                    cout << "What is the account number? " << endl;
                    getline(cin, accountnumber);
                    if(accountnumber != "exit")
                    {
                      status = Bd.deposit_account(name,accountnumber);
                    }
				}
            }
            status = "more";
			break;
        // Withdraw Account
        case '2':
            while((name != "exit") && (status != "exit")){
				cout << "What's the name on the account? " << endl;
				cin.sync();
				getline(cin, name);
				if (name != "exit")
				{
                    cout << "What is the account number? " << endl;
                    getline(cin, accountnumber);
                    if(accountnumber != "exit")
                    {
                     status = Bd.withdraw_account(name,accountnumber);

                    }
				}
            }
            status = "more";
			break;
        case '3': // Transfer from Account to Account
            do{
                cout <<"Type exit to cancel transfer process."<< endl;
                cout << "What's the name on the account of transferor? " << endl;
				cin.sync();
				getline(cin, name);
				cout << "What is the account number? " << endl;
				cin.sync();
                getline(cin, accountnumber);

                exist = Bd.verify(name, accountnumber);
                }while ((exist != true )&& ( name!= "exit") && (accountnumber != "exit"));


				if ((name != "exit") && (accountnumber != "exit") )
				{
				    do{
				    cout << "What's the name on the account of transferee? " << endl;
                    cin.sync();
                    getline(cin, name2);
                    cout << "What is the account number? " << endl;
                    cin.sync();
                    getline(cin, accountnumber2);
                    exist =Bd.verify(name2, accountnumber2);
                    }while ((exist != true )&& ( name2!= "exit") && (accountnumber2 != "exit"));

                    if((accountnumber != "exit") && (name2 != "exit") )
                    {
                     money = Bd.withdraw_trasfer(name,accountnumber,name2,accountnumber2);
                     Bd.deposit_transfer(name2,accountnumber2,name,accountnumber, money);
                    }
				}
            break;
        case '4': // Balance Inquiry

            cout << "What's the name on the account? " << endl;
            cin.sync();
            getline(cin, name);

            cout << "What is the account number? " << endl;
            cin.sync();
            getline(cin, accountnumber);

            Bd.BalanceInquiry(name, accountnumber);
            break;

        case '5': // All Account Holder List
            Bd.PrintTable();
            break;

        case '6': // Close an Account
            cin.sync();
            getline(cin, name);
            Bd.RemoveItem(name);
            break;

        case '7': // Find Account
            cin.sync();
            getline(cin, name);
            Bd.FindAccount(name);
            break;
        case '8': // Exit
            break;
        }
        // For pausing purposes...
        cin.ignore();
        cin.get();
        }while(choice != '8');
    return 0;
}

