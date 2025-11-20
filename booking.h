//============================
//Prevents multiple inclusion of this header file
#ifndef _BOOKING_H 
#define _BOOKING_H 
//-----------------
#include "account.h" 
#include "room.h"
//============================
//Booking structure definition
typedef struct Booking { 
int bookingID; 
int roomID; 
int accountID; 
int nights; 
float totalCost; 
struct Booking *next; 
} Booking;
//============================
//Function prototypes
Booking* loadBookings(const char *filename);
//
void saveBookings(Booking *head, const char *filename); 
Booking* createBooking(Booking *head, Room *rooms, int accountID, int roomID, 
int nights); 
//
Booking* cancelBooking(Booking *head, int bookingID, Room *rooms); 
//
void printUserBookings(Booking *head, int accountID); 
//
float calculateTotalCost(float pricePerNight, int nights);
// 
void freeBookings(Booking *head); 
//============================
#endif 