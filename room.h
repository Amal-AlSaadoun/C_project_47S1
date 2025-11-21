//============================
//Prevents multiple inclusion of this header file
#ifndef _ROOM_H
#define _ROOM_H
//============================
//Room structure definition
typedef enum {
STANDARD,
DELUXE,
SUITE
} RoomType;

typedef struct Room {
int roomID;
RoomType type;
int capacity;
float price;
char status; char amenities[5][20];
int amenityCount;
struct Room *next; } Room;
//=========================
//Function Prototypes
Room* loadRooms(const char *filename);
void saveRooms(Room *head, const char *filename);
void printRooms(Room *head);
Room* findRoom(Room *head, int roomID);
void updateRoomStatus(Room *head, int roomID, char newStatus);
void addRoom(Room **head, Room newRoom);
void freeRooms(Room *head);
//============================
#endif


