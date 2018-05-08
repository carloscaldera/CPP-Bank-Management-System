#ifndef HASH_H
#define HASH_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class hash
{
    private:
        // CONSTANTS
        static const int tableSize = 19;

        // STRUCTURE TO ENCAPSULATE COMMON ACCOUNT FIELDS (i.e. name, account type, etc)
        // ALLOWS FOR EFFICIENT POINTING RATHER THAN MAKING
        // ALL INDIVIDUAL MEMBERS AND POINTING INDIVIDUALLY
        struct item
        {
            string name; // FUll NAME (i.e. Carlos Caldera)
            string accountnumber; // ACCOUNT NUMBER CHOSEN BY USER
            char type; // ACCOUNT TYPE (CHECKING/SAVINGS)
            double amount; // AMOUNT OF CURRENCY
            item* next;
        };

        // ARRAY OF STRUCTURES
        item* HashTable[tableSize];

    public:
        hash();
        int Hash(string key);
        void AddItem();
        int NumberOfItemsInIndex(int index);
        void PrintTable();
        void PrintItemsInIndex(int index);
        void FindAccount(string name);
        void RemoveItem(string name);
        void BalanceInquiry(string name, string accountnumber);
        string deposit_account(string name,string accountnumber);
        string withdraw_account(string name, string accountnumber);

        void deposit_transfer(string name, string accountnumber , string name2, string accountnumber2, float deposit);
        float withdraw_trasfer(string name, string accountnumber , string name2, string accountnumber2);
        bool verify(string name,string accountnumber);

};

#endif // HASH_H
