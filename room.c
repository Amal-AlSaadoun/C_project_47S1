//============================
#include <stdio.h>
#include <string.h>
#include "room.h"
//============================
//Initializes the hotel rooms with predefined data
void initRooms(struct Room* Rooms){ 
   // Room 1
   Rooms[0].roomID = 101;
   Rooms[0].roomType = STANDARD;
   Rooms[0].capacity = 2;
   Rooms[0].price = 100.00;
   Rooms[0].status = 'A';
   strcpy(Rooms[0].amenities[0], "WiFi");
   strcpy(Rooms[0].amenities[1], "TV");
   Rooms[0].amenitiesCount = 2;
   //---------------------
   // Room 2
   Rooms[1].roomID = 201;
   Rooms[1].roomType = DELUXE;
   Rooms[1].capacity = 3;
   Rooms[1].price = 200.00;
   Rooms[1].status = 'A';
   strcpy(Rooms[1].amenities[0], "WiFi");
   strcpy(Rooms[1].amenities[1], "MiniBar");
   Rooms[1].amenitiesCount = 2;
   //---------------------
   // Room 3
   Rooms[2].roomID = 301;
   Rooms[2].roomType = SUITE;
   Rooms[2].capacity = 4;
   Rooms[2].price = 300.00;
   Rooms[2].status = 'A';
   strcpy(Rooms[2].amenities[0], "WiFi");
   strcpy(Rooms[2].amenities[1], "MiniBar");
   strcpy(Rooms[2].amenities[2], "Jacuzzi");
   Rooms[2].amenitiesCount = 3;
} // End initRooms function
//============================
//Displays all room records in a clear, tabular format.
void printRooms(struct Room* Rooms ,int roomCount) {
   printf("\n%-5s  %-9s  %-5s  %-10s  %-8s %-s \n", "ID", "Type", "Cap", "Price", "Status", "Amenities");

   for (int i = 0; i < roomCount; i++) {
    
      // Determine the type 
      if (Rooms[i].roomType == STANDARD)
         printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", Rooms[i].roomID, "STANDARD", Rooms[i].capacity, Rooms[i].price, Rooms[i].status);
      else if (Rooms[i].roomType == DELUXE)
         printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", Rooms[i].roomID, "DELUXE", Rooms[i].capacity, Rooms[i].price, Rooms[i].status);
      else if (Rooms[i].roomType == SUITE)
         printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", Rooms[i].roomID, "SUITE",  Rooms[i].capacity, Rooms[i].price, Rooms[i].status);

      for (int j = 0; j < Rooms[i].amenitiesCount; j++)
         printf("%s, ", Rooms[i].amenities[j]);
      printf("\n");
    }//end of for loop
} // End printRooms function
//============================
//Returns a pointer to the room with the given ID, or NULL if not found
struct Room* searchRoomByID(struct Room* Rooms, int roomCount, int id) {
   for (int i = 0; i < roomCount; i++) {
      if (Rooms[i].roomID == id)
         return &Rooms[i];
    }
   return NULL;//if room not found
} // End searchRoomByID function
//============================
//Prints all rooms that match the given type
void searchRoomByType(struct Room* Rooms, int roomCount, enum RoomType room_T) {

   printf("\n%-5s  %-9s  %-5s  %-10s  %-8s %-s \n", "ID", "Type", "Cap", "Price", "Status", "Amenities");
   

   for (int i = 0; i < roomCount; i++) {
      if (Rooms[i].roomType == room_T) {
         // Determine the type 
         if (Rooms[i].roomType == STANDARD)
            printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", Rooms[i].roomID,"STANDARD", Rooms[i].capacity, Rooms[i].price, Rooms[i].status);
         else if (Rooms[i].roomType == DELUXE)
            printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", Rooms[i].roomID,"DELUXE", Rooms[i].capacity, Rooms[i].price, Rooms[i].status);
         else if (Rooms[i].roomType == SUITE)
            printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", Rooms[i].roomID, "SUITE", Rooms[i].capacity, Rooms[i].price, Rooms[i].status);

         for (int j = 0; j < Rooms[i].amenitiesCount; j++)
            printf("%s, ", Rooms[i].amenities[j]);
         printf("\n");
        }//if
    }//for
} // End searchRoomByType function
//============================
//Updates a room's status (A or O) when a booking is created or canceled
void updateRoomStatus(struct Room* Rooms, int roomCount, int id, char ch) {
    struct Room* UpdatedRoom = searchRoomByID(Rooms, roomCount, id);

    if (UpdatedRoom == NULL)
        printf("Room NOT found: wrong room ID\n");
    else
        UpdatedRoom->status = ch;
} // End updateRoomStatus
