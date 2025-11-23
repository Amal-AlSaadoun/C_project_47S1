#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "room.h"
#include "account.h"
#include "booking.h"
#include "admin.h"

void showAvailableOnly(Room *allRooms);
int main() {

   Room *roomList= loadRooms("rooms.txt");
   Account *userList= loadAccounts("accounts.txt");
   Booking *bookList= loadBookings("bookings.txt");
   Account *loggedIn = NULL;

   int option = 0;
   char name[21], password[21];
   int userAge;
    
   while(option != 3) {
      printf("\nMain Menu:\n");
      printf("1. Register\n");
      printf("2. Login\n");
      printf("3. Exit\n");
      printf("Enter your choice: ");
      scanf("%d", &option);
   //===============================================================
   //REGISTER
   //===============================================================
      if(option == 1) {
         printf("Enter your username: ");
         scanf(" %[^\n]", name);
         // keep asking if username too long
         while (strlen(name) > 20) {
            printf("Username is too long! (max 20 characters)\n");
            printf("Enter a shorter username: ");
            scanf(" %[^\n]", name);
         }
         printf("Enter your age: ");
         scanf("%d", &userAge);
         
         printf("Create password: ");
         scanf("%s", password); 
         //check password length
         while (strlen(password) > 20) {
            printf("Password is too long! Maximum length is 20 characters.\n");
            printf("Enter a shorter password: ");
            scanf("%s", password);
        }
         userList = registerAccount(userList, name, userAge, password);  }

   //===============================================================
   //LOGIN
   //===============================================================
      else if (option == 2) {
         printf("Username: ");
         scanf("%s", name);
         printf("Password: ");
         scanf("%s", password);
         loggedIn = login(userList, name, password);
         if (loggedIn == NULL) {
                printf("Login unsuccessful. Please try again.\n"); }
         else {
      //=======================================================
      //ADMIN MENU
      //=======================================================
            if(loggedIn->isAdmin == 1) {adminMenu(&roomList, &userList, &bookList);}
      //=======================================================
      //USER MENU
      //=======================================================
            else {
               int userOption = 0;
               while(userOption != 5) {
                  printf("\nUser Menu:\n");
                  printf("1.View Available Rooms\n");
                  printf("2.Book a Room\n");
                  printf("3.Cancel a Booking\n");
                  printf("4.View My Bookings\n");
                  printf("5.Logout\n");
                  printf("Choose an option: ");
                  scanf("%d", &userOption);
                  //View Available Rooms    
                  if(userOption == 1) {showAvailableOnly(roomList);}
                  //Book a Room
                  else if(userOption == 2) {
                     int rID, nights;
                     printf("Enter Room ID to reserve: ");
                     scanf("%d", &rID);
                     printf("How many nights: ");
                     scanf("%d", &nights);
                     bookList = createBooking(bookList,roomList,loggedIn->accountID,rID,nights);}
                  //Cancel a Booking
                  else if(userOption == 3) {
                     int cancelID;
                     printf("Enter Booking ID to cancel: ");
                     scanf("%d", &cancelID);
                     // verify booking belongs to this user BEFORE cancellation
                    Booking *temp = bookList;
                    int allowed = 0;
                    
                    while (temp != NULL) {
                        if (temp->bookingID == cancelID) {
                            if (temp->accountID == loggedIn->accountID) {
                                allowed = 1;
                            }
                            break; //stop searching
                        }
                        temp = temp->next;
                    }
                    
                    if (!allowed) {
                        printf("You cannot cancel this booking! It does not belong to your account\n");
                    } else {
                        bookList = cancelBooking(bookList, cancelID, roomList);
                    }
                     
                     
                      }
                  //View My Bookings
                  else if (userOption == 4) {printUserBookings(bookList, loggedIn->accountID);}
                  //Logout
                  else if (userOption == 5) {printf("You have logged out\n"); }
                  else {printf("Invalid option selected\n");}
               }//end while user menu
            } //end else "if it is a user"
         } //end login success
      }//end option 2
   //===============================================================
   // EXIT
   //===============================================================
      else if (option == 3) {
         printf("Saving all data... Goodbye!\n");
         saveRooms(roomList, "rooms.txt");
         saveAccounts(userList, "accounts.txt");
         saveBookings(bookList, "bookings.txt");
         freeRooms(roomList);
         freeAccounts(userList);
         freeBookings(bookList); }
      else {printf("Invalid choice.\n"); }
   } // end menu
   return 0;
} //end main

//====================================================================
void showAvailableOnly(Room *allRooms) {

 printf("Rooms Currently Available:\n");
 printf("--------------------------------------------\n");

 Room *p = allRooms;
 int found = 0; 
  while (p != NULL) {
   if (p->status == 'A') {
     found = 1;   
     char type[20];
     if (p->type == STANDARD) strcpy(type, "Standard");
     else if (p->type == DELUXE) strcpy(type, "Deluxe");
     else strcpy(type, "Suite");

      printf("\nRoom ID       : %d\n", p->roomID);
      printf("Room Type     : %s\n", type);
      printf("Capacity      : %d guests\n", p->capacity);
      printf("Price per night: %.2f SAR\n", p->price);

      printf("Amenities : ");
      for (int i = 0; i < p->amenityCount; i++) {
       printf("%s", p->amenities[i]);
       if (i < p->amenityCount - 1) printf(", "); }

    printf("\n--------------------------------------------\n"); }

  p = p->next;  }

 if (!found) {printf("No available rooms at the moment.\n");}
} //end showAvailableOnly
