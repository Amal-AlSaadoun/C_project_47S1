//============================
//Prevents multiple inclusion of this header file
#ifndef _ACCOUNT_H
#define _ACCOUNT_H
//============================
//Account structure definition
typedef struct Account {
   int accountID;
   char username[20];
   int age;
   char password[20];
   int isAdmin;
   struct Account *next;
}Account;
//============================
//Function prototypes
Account* loadAccounts(const char *filename);
void saveAccounts(Account *head, const char *filename);
Account* registerAccount(Account *head, char *username, int age, char *password);
Account* login (Account *head, char *username, char *password);
void encryptPassword(char *password);
void decryptPassword(char *password); 
void freeAccounts(Account *head);
/*
int registerAccount(struct Account accounts[], int *totalAccounts, int capacity);
int login(struct Account accounts[], int totalAccounts, char *username, char *password);
*/
//============================
#endif 