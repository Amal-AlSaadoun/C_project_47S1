#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booking.h"
#include "room.c"


/*Booking* loadBookings(const char *filename);

void saveBookings(Booking *head, const char *filename); 
Booking* createBooking(Booking *head, Room *rooms, int accountID, int roomID, 
int nights);*/

Booking* cancelBooking(Booking *head, int bookingID, Room *rooms) {
    
 Booking *p = head , q=NULL;
  
// Search for booking
  while (p != NULL && p->bookingID != bookingID) {
        q = p;
        p = p->next; }

  if (p == NULL) {
        printf("Booking not found!\n");
        return head; }

// Update room status
  updateRoomStatus(rooms, p->roomID, 'A');

// delete the node
    if (q == NULL) { head = p->next;}
     else {q->next = p->next; }

    free(p);

    printf("Booking cancelled successfully\n");
    return head; } //end cancelBooking
//=====================================================
void printUserBookings(Booking *head, int accountID) {

  Booking *p = head;
  int found = 0;

  printf("\nYour Bookings:\n");
  printf("----------------------------------------\n");

  while (p!= NULL) {
    if (p->accountID == accountID) {
     printf("\n----------------------------\n");
     printf("Booking ID : %d\n", p->bookingID);
     printf("Room ID    : %d\n", p->roomID);
     printf("Nights     : %d\n", p->nights);
     printf("TotalCost  : %.2f\n", p->totalCost);
     printf("----------------------------\n");
     found = 1;   }

       p = p->next; }
       
    if (!found) {
        printf("No bookings found.\n");
    }
} //end printUserBookings
//=====================================================
float calculateTotalCost(float pricePerNight, int nights){
return pricePerNight*nights;} //end calculateTotalCost
//=====================================================
void freeBookings(Booking *head){
Booking *temp;
while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
   }
} //end freeBookings
//=====================================================
