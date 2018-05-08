#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "hash.h"
using namespace std;



// INITIALIZES AND SETS ALL DEFAULT VALUES OF ALL INDEXES OF TABLE ARRAY
hash::hash()
{
    for(int i = 0; i < tableSize; i++)
    {

        HashTable[i] = new item;
        HashTable[i]->name = "empty";
        HashTable[i]->accountnumber = "empty";
        HashTable[i]->type = 'n';
        HashTable[i]->amount = 0;
        HashTable[i]->next = NULL;
    }
}

// EACH INDEX OF OUR ARRAY WILL HOLD 1 >= ITEMS
// THIS FUNCTION IS A HELPER FUNCTION
int hash::NumberOfItemsInIndex(int index)
{
    int count = 0;

    if(HashTable[index]->name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        item* Ptr = HashTable[index];
        while(Ptr->next != NULL) // as long as our next item isn't null... increment count
        {
            count++;
            Ptr = Ptr->next; // Keep moving pointer down the list
        }
    }
    return count;
}


// RUNS THROUGH TABLE AND PRINTS OUT ALL CONTENTS OF OUR ITEMS/USER
void hash::PrintTable()
{
    int number;
    for(int i = 0; i < tableSize; i++)
    {
        if(!(HashTable[i]->name == "empty"))
        {
        PrintItemsInIndex(i);
        }
    }
}


// HELPER FUNCTION FOR PRINT TABLE
// PURPOSE: SWEEPS THROUGH SPECIFIED ARRAY INDEX
// AND PRINTS ANY/ALL CHAINED ITEMS
void hash::PrintItemsInIndex(int index)
{
    item* Ptr = HashTable[index];
    if(Ptr->name == "empty")
    {
        cout << "Index : " << index << " is empty" << endl;
    }
    else
    {
        //
        while(Ptr != NULL) // RUNS THROUGH AND CHECKS FOR ITEMS, PRINTS CONTENTS
        {
            cout << "-------------\n";
            cout << "Account name: " << Ptr->name << endl;
            cout << "Account number: " << Ptr->accountnumber << endl;
            cout << "Account type: " << Ptr->type << endl;
            cout << "Amount: " << Ptr->amount << endl;
            cout << "-------------\n";
            Ptr = Ptr->next; // MOVES TO NEXT ITEM
        }
    }

}

// FINDS ACCOUNT BY MEANS OF NAME
// USES HASH ALGORITHM TO LOCATE
// AND CHECK IF VALID SEARCH
void hash::FindAccount(string name)
{

    int index = Hash(name);
    bool foundName = false;
    string accountnumber;

    item* Ptr = HashTable[index];

    while(Ptr != NULL)
    {

        if(Ptr->name == name)
        {
            foundName = true;
            name = Ptr->name;
        }
        Ptr = Ptr->next;
    }
    if(foundName == true)
    {
        cout << "Your account number is : " << HashTable[index]->accountnumber;
    }
    else
    {
        cout << name << "'s info was not found in the hash table\n";
    }
}


// REMOVS ITEM WHILE CHECKING IF THERE IS A CURRENT ITEM,
// ALSO IMPLEMENTS SCRATCH POINTERS INCASE OF REMOVAL
// IN THE MIDDLE OF A LIST
void hash::RemoveItem(string name)
{
    int index = Hash(name);

    item* delPtr;
    item* P1;
    item* P2;

    string BankAccount = name;
    std::ofstream ofs;
    time_t ctt = time(0);
    BankAccount += ".txt";

    if(HashTable[index]->name == "empty")
    {
        cout << name << " was not found in the banking system\n";
        ctt=time(0);
        ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
        ofs << "**********************************************************************************************************************" << endl;
        ofs << "Account Closed On:    " << asctime(localtime(&ctt));
        ofs << "Account Holders Name: " << name << endl;
        ofs << "Final Balance:        " << "$" << HashTable[index]->amount << endl;
        ofs.close();
    }
    else if(HashTable[index]->name == name && HashTable[index]->next == NULL)
    {
        HashTable[index]->name = "empty";
        HashTable[index]->accountnumber = "empty";
        HashTable[index]->type = 'n';
        HashTable[index]->amount = 0;

        cout << name << " was removed from the banking system\n";

        ctt=time(0);
        ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
        ofs << "**********************************************************************************************************************" << endl;
        ofs << "Account Closed On:    " << asctime(localtime(&ctt));
        ofs << "Account Holders Name: " << name << endl;
        ofs << "Final Balance:        " << "$" << HashTable[index]->amount << endl;
        ofs.close();
    }
    else if(HashTable[index]->name == name)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;

        cout << name << " was removed from the banking system\n";
    }
    else
    {
        P1 = HashTable[index]->next;
        P2 = HashTable[index];

        while(P1 != NULL && P1->name != name)
        {
            P2 = P1;
            P1 = P1->next;
        }
        if(P1 == NULL)
        {
            cout << name << " was not removed from the banking system \n";
        }
        else
        {
            delPtr = P1;
            P1 = P1->next;
            P2->next = P1;

            delete delPtr;
            cout << name << " was removed from the hash table\n";
        }
    }
}



// HASH KEY ALGORITHM, SIMPLY TAKES
// A NAME (KEY) AND USES
// TYPE CASTING AND MODULOUS BY TABLE SIZE -- HELPS WITH LOCATING ITEMS INSTANTLY (IF THEY EXSIST)
int hash::Hash(string key)
{
    int hash = 0;
    int index;
    index = key.length();

    for(int i = 0; i < key.length(); i++)
    {
        hash = hash + (int)key[i];
    }
    index = (hash % tableSize);
    return index;
}

// ADDS AN ACCOUNT TO OUR HASH TABLE
// BY MEANS OF INSERTING AT AN EMPTPY INDEX
// OR BY CHAINING TO AN EXSISTING ITEM
void hash::AddItem()
{

    string a; // account number
    char t; // type
    double amt; // amount
    string nn; // name
    string BankAccount;
    std::ofstream ofs;
    time_t ctt = time(0);

    cout << "Enter your name: " << endl;
    cin.sync();
    getline(cin, nn);

    BankAccount = nn;
    BankAccount += ".txt";

    cout << "Enter your account type: " << endl;
    cin.sync();
    cin >> t;


    cout << "Enter your account number: " << endl;
    cin.sync();
    getline(cin, a);

    cout << "Initial amount: ";
    cin >> amt;
    while(amt <= 0){
        cout << "Enter Amount Greater than zero: " << endl;
        cin >> amt;

        cout << "Account created. \n";


    }
    ofstream newfile;
    newfile.open(BankAccount.c_str(), ios::app);
    ctt=time(0);

    ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
    ofs << "                                 **********ALAMO CITY BANK********** " << endl;

    ofs << "Account Created On:   " << asctime(localtime(&ctt));
    ofs << "Account Holders Name: " << nn << endl;
    ofs << "Account Type:         " << t << endl;
    ofs << "Account Number:       " << a << endl;
    ofs << "Account Balance:      " << "$" << amt << endl;
    ofs.close();

    cout << endl;

    int index = Hash(nn);
    if(HashTable[index]->name == "empty")
    {
        HashTable[index]->name = nn;
        HashTable[index]->accountnumber = a;
        HashTable[index]->type = t;
        HashTable[index]->amount = amt;
    }
    else
    {
        // N DENOTES NEW ACCOUNT

        item* Ptr = HashTable[index];
        item* n = new item;
        n->name = nn;
        n->accountnumber = a;
        n->type = t;
        n->amount = amt;
        n->next = NULL;
        while(Ptr->next != NULL)
        {
            Ptr = Ptr->next;
        }
        cout << "Account created. \n";
        Ptr->next = n;
    }
}


string hash::withdraw_account(string name, string accountnumber)
{
	float b;
	int index = Hash(name);
	item* Ptr = HashTable[index];
	string status;
	string BankAccount = name;
    std::ofstream ofs;
    time_t ctt = time(0);

    BankAccount += ".txt";

	if (HashTable[index]->name == name && HashTable[index]->accountnumber == accountnumber)
	{

		cout << "Account number: " << HashTable[index]->accountnumber << endl;
		cout << "Your total Amount is: " << HashTable[index]->amount << endl;

		cout << "How much would you like to take out?: " << endl;
		cin >> b;
		if (HashTable[index]->amount < b)
		{
			cout << "Insufficient funds" << endl;
		}
		else
		{
			HashTable[index]->amount -= b;
		}
		cout << "You new total is: " << HashTable[index]->amount << endl;
        ctt=time(0);
        ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
        ofs << "**********************************************************************************************************************" << endl;
        ofs << "Account Updated On:                           " << asctime(localtime(&ctt));
        ofs << "Account Holders Name:                         " << name << endl;
        ofs << "Account Number Number:                        " << accountnumber << endl;
        ofs << "Account Type:                                 " << HashTable[index]->type << endl;
        ofs << "Amount of Withdrawal:                         " << b <<endl;
        ofs << "Account Balance:                              " << "$" << HashTable[index]->amount << endl;
        ofs.close();
        status = "exit";
        return status;
	}
	else
	{
		cout << "Could not find account: " << endl;
		status = "retry";
		return status;
	}
}


string hash::deposit_account(string name,string accountnumber)
{
	float a;
	int index = Hash(name);
	item* Ptr = HashTable[index];
	string status;
    string BankAccount = name;
    std::ofstream ofs;
    time_t ctt = time(0);
    BankAccount += ".txt";

	if (HashTable[index]->name == name && HashTable[index]->accountnumber == accountnumber)
	{

		cout << "Account number: " << HashTable[index]->accountnumber << endl;
		cout << "Your total Amount is: " << HashTable[index]->amount << endl;

		cout << "How much would you like to put in?: " << endl;
		cin.sync();
		cin >> a;

		HashTable[index]->amount += a;
        cout << "You new total is: " << HashTable[index]->amount << endl;
        ctt=time(0);
        ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
        ofs << "**********************************************************************************************************************" << endl;
        ofs << "Account Updated On:                           " << asctime(localtime(&ctt));
        ofs << "Account Holders Name:                         " << name << endl;
        ofs << "Account Number Number:                        " << accountnumber << endl;
        ofs << "Account Type:                                 " << HashTable[index]->type << endl;
        ofs << "Amount of Deposit:                            " << a <<endl;
        ofs << "Account Balance:                              " << "$" << HashTable[index]->amount << endl;
        ofs.close();
        status = "exit";
        return status;

	}
	else
	{
		cout << "Could not find account: " << endl;
	}
}

void hash::BalanceInquiry(string name, string accountnumber)
{
    int index = Hash(name);
    item* Ptr = HashTable[index];
    if(HashTable[index]->name == name && HashTable[index]->accountnumber == accountnumber)
	{
        cout << "Name : " << HashTable[index]->name << endl;
		cout << "Account number: " << HashTable[index]->accountnumber << endl;
		cout << "Type of Account: " << HashTable[index]->type << endl;
		cout << "Total Amount: " << HashTable[index]->amount << endl;
	}
	else
	{
		cout << "Could not find account: " << endl;
	}

}



bool hash::verify(string name, string accountnumber)
{
	float b;
	int index = Hash(name);
	item* Ptr = HashTable[index];
	bool answer;

	if (HashTable[index]->name == name && HashTable[index]->accountnumber == accountnumber)
	{

		cout << "Account Verified"<< endl;
		answer = true;
		return answer;

	}
	else
	{
		cout << "Could not find account: " << endl;
		answer = false;
		return answer;
	}
}


float hash::withdraw_trasfer(string name, string accountnumber , string name2, string accountnumber2)
{
	float b;
	int index = Hash(name);
	item* Ptr = HashTable[index];
	string status;
	string BankAccount = name;
    std::ofstream ofs;
    time_t ctt = time(0);

    BankAccount += ".txt";//UPDATE CODE

		cout << "Account number: " << HashTable[index]->accountnumber << endl;
		cout << "Your total Amount is: " << HashTable[index]->amount << endl;
		cout << "How much would you like to transfer out?: " << endl;
		cin >> b;
		if (HashTable[index]->amount < b)
		{
			cout << "Insufficient funds" << endl;
		}
		else
		{
			HashTable[index]->amount -= b;
		}
		cout << "Your new total is: " << HashTable[index]->amount << endl;

		  // UPDATE CODE
        ctt=time(0);
        ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
        ofs << "**********************************************************************************************************************" << endl;
        ofs << "Account Updated On:                           " << asctime(localtime(&ctt));
        ofs << "Account Holders Name:                         " << name << endl;
        ofs << "Account Type:                                 " << HashTable[index]->type << endl;
        ofs << "---Money Transfer Information Information-----" << endl;
        ofs << "Account Holders Name (Transferee) :           " << name2 << endl;
        ofs << "Account Number Number (Transferee):           " <<  accountnumber2 << endl;
        ofs << "Amount of transfer  :                         " << b <<endl;
        ofs << "\nNew Account Balance:                        " << "$" << HashTable[index]->amount << endl;
        ofs.close();

        return b;

}


void hash::deposit_transfer(string name, string accountnumber , string name2, string accountnumber2, float deposit)
{
	int index = Hash(name);
	item* Ptr = HashTable[index];
	string status;
    string BankAccount = name;
    std::ofstream ofs;
    time_t ctt = time(0);

    BankAccount += ".txt";//UPDATE CODE


		HashTable[index]->amount += deposit;


        // UPDATE CODE
        ctt=time(0);
        ofs.open (BankAccount.c_str(), std::ofstream::out | std::ofstream::app);
        ofs << "**********************************************************************************************************************" << endl;
        ofs << "Account Updated On:                           " << asctime(localtime(&ctt));
        ofs << "Account Holders Name:                         " << name << endl;
        ofs << "Account Number Number:                        " << accountnumber << endl;
        ofs << "Account Type:                                 " << HashTable[index]->type << endl;
        ofs << "---Money Transfer Information Information-----" << endl;
        ofs << "Account Holders Name (Transferor) :           " << name2 << endl;
        ofs << "Account Number Number (Transferor):           " <<  accountnumber2 << endl;
        ofs << "Amount of Deposit   :                         " << deposit <<endl;
        ofs << "\nNew Account Balance:                       " << "$" << HashTable[index]->amount << endl;
        ofs.close();

}
