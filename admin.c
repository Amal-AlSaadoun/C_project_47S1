#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
//===============================================
void adminMenu(Room **rooms, Account **accounts, Booking **bookings) {
    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. View All Rooms\n");
        printf("2. Add/Edit Room\n");
        printf("3. View All Accounts\n");
        printf("4. View All Bookings\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

 if (choice == 1) {viewAllRooms(*rooms);}
 
  else if (choice == 2) {
   int c;
   do {
        printf("1. Add New Room\n");
        printf("2. Edit Existing Room\n");
        printf("3. Return to admin menu\n");
        printf("Choice: ");
        scanf("%d", &c);
        
       if(c==1){ addNewRoom(rooms);}
        else if(c==2){
            int roomID, newCap;
            float newPrice;
            
            printf("Enter Room ID : ");
            scanf("%d", &roomID);

            printf("Enter new price: ");
            scanf("%f", &newPrice);

            printf("Enter new capacity: ");
            scanf("%d", &newCap);

            editRoom(*rooms, roomID, newPrice, newCap);
        }
       else if(c==3) {printf("return to admin menu\n");}
        else {printf("Invalid choice!!!\n");}

    } while (c!=3);
  } 

    else if (choice == 3) {viewAllAccounts(*accounts);}
        
     else if (choice == 4) {viewAllBookings(*bookings, *accounts);}
        
      else if (choice == 5) {printf("Logging out -> return to main menu\n");}
      
       else { printf("Invalid choice!!!\n");}

  } while (choice != 5);
}//end adminMenu

//===============================================
void viewAllRooms(Room *rooms) {printRooms(rooms);} //end viewAllRooms
//===============================================
void addNewRoom(Room **rooms) {
    Room newRoom;
    int roomType;

    printf("Enter Room ID: ");
    scanf("%d", &newRoom.roomID);
    //prevent duplicate IDs
    if(findRoom(*rooms, newRoom.roomID) != NULL) {
        printf("Room ID already exists! Please choose another ID.\n");
        return;}
     
    printf("Enter Room Type (0=STANDARD, 1=DELUXE, 2=SUITE): ");
    scanf("%d", &roomType);
    newRoom.type = (RoomType)roomType;

    printf("Enter Capacity: ");
    scanf("%d", &newRoom.capacity);

    printf("Enter Price: ");
    scanf("%f", &newRoom.price);

    newRoom.status = 'A';

    printf("Enter number of amenities: ");
    scanf("%d", &newRoom.amenityCount);

    for (int i = 0; i < newRoom.amenityCount; i++) {
        printf("Amenity %d: ", i + 1);
        scanf("%s", newRoom.amenities[i]);
    }

    newRoom.next = NULL;

    addRoom(rooms, newRoom);
    printf("Room added successfully!\n");
} //end addNewRoom
//===============================================
void editRoom(Room *rooms, int roomID, float newPrice, int newCapacity) {
    Room *target = findRoom(rooms, roomID);

    if (target == NULL) {
        printf("Room not found\n");
        return;
    }
     else{
         target->price = newPrice;
         target->capacity = newCapacity;
         printf("Room updated successfully!\n"); 
   } 
} //end editRoom
//===============================================
void viewAllAccounts(Account *accounts) {
 Account *p = accounts;
 if (p == NULL) {
  printf("No accounts found \n");
        return; }

  printf("AccountID   Username        Age   Type\n");
    while (p != NULL) {
     printf("%-11d %-15s %-5d %s\n",p->accountID,p->username,p->age,p->isAdmin ? "Admin" : "User");
        p = p->next; }
} // end viewAllAccounts
//===============================================
void viewAllBookings(Booking *bookings, Account *accounts) {
 Booking *bookingPtr = bookings;
 
 if (bookingPtr == NULL) {
        printf("No bookings found.\n");
        return;  }
        
 printf("BookingID   RoomID   Username        Nights   TotalCost\n");
    while (bookingPtr != NULL) {

      char username[20] = "Unknown";

       Account *p = accounts;
        while (p != NULL) {
            if (p->accountID == bookingPtr->accountID) {
                strcpy(username, p->username);
                break; }
            p = p->next;
        }

 printf("%-11d %-8d %-15s %-8d %.2f\n",bookingPtr->bookingID,bookingPtr->roomID,username,bookingPtr->nights,bookingPtr->totalCost);
  bookingPtr = bookingPtr->next;
    }
} // end viewAllBookings
