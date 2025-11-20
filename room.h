//============================
//Prevents multiple inclusion of this header file
#ifndef _ROOM_H
#define _ROOM_H
//============================
//Room structure definition
struct Room{
   int roomID;
   enum RoomType{STANDARD ,DELUXE ,SUITE } roomType;
   int capacity;
   float price;
   char status;
   char amenities[3][20];
   int amenitiesCount;
};
//============================
//Function Prototypes
void initRooms( struct Room* Rooms);
void printRooms( struct Room* Rooms, int roomCount);
struct Room* searchRoomByID( struct Room* Rooms, int roomCount, int id);
void searchRoomByType (struct Room* Rooms , int roomCount, enum RoomType room_T);
void updateRoomStatus( struct Room* Rooms , int roomCount, int id , char ch);
//============================
#endif


