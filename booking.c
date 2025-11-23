#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booking.h"
#include "room.h"
//==========================================
Booking* loadBookings(const char *filename){
   //-------------
   //open the file
   FILE *fp=fopen(filename,"r");
   //check
   if (fp == NULL) {
      printf("Sorry, Can't open Booking file\n");
      return NULL;}
   //-------------
   Booking *head = NULL;
   Booking *current;
   int bID, rID, aID, nights;
   float cost;
   //read line by line using fscanf
   while (fscanf(fp, "%d %d %d %d %f", &bID, &rID, &aID, &nights, &cost) == 5) {
      Booking *newB = (Booking*) malloc(sizeof(Booking));
      newB->bookingID = bID;
      newB->roomID = rID;
      newB->accountID = aID;
      newB->nights = nights;
      newB->totalCost = cost;
      newB->next = NULL;
      //first node
      if (head == NULL) {
         head = current= newB;
        }
      else {
         current->next = newB;
         current= newB;}
   }//while
   //close file
   fclose(fp);
   return head;
}//end
//==========================================
void saveBookings(Booking *head, const char *filename){
   FILE *fp=fopen(filename,"w");
   //check
   if (fp == NULL) {
      printf("Sorry, Can't save the file\n");
      return;}
   
   Booking *curr = head;
   while (curr) {
      fprintf(fp, "%d %d %d %d %.2f\n", curr->bookingID, curr->roomID, curr->accountID, curr->nights, curr->totalCost);
      curr = curr->next;}
   //close the file
   fclose(fp);
}//end save
//==========================================
Booking* createBooking(Booking *head, Room *rooms, int accountID, int roomID, int nights){
   Room *room=findRoom(rooms,roomID);
   if(room==NULL){
      printf("Room not found");
      return head;}
   
   if(room->status !='A'){
      printf("room is not available");
      return head;}
      
   if(nights<=0){
      printf("invalid number of nights");
      return head;}

   Booking *curr = head;
   Booking *last = NULL;
   int count=0;
   //count + track last node
   while (curr != NULL) {
      count++;            //count existing bookings
      last = curr;        //update last node
      curr = curr->next;  //move forward
   }
   int newID=last->bookingID+1;

   //create new booking node
   Booking *newB = (Booking*) malloc(sizeof(Booking));
   newB->bookingID = newID;
   newB->roomID = roomID;
   newB->accountID = accountID;
   newB->nights = nights;
   newB->totalCost = calculateTotalCost(room->price, nights);
   newB->next = NULL;
   updateRoomStatus(rooms, roomID,'O');
   printf("Booking created successfully\n");

   //if list is empty
   if (head == NULL){
      return newB;}
   last->next = newB;
   return head;
}
//==========================================
Booking* cancelBooking(Booking *head, int bookingID, Room *rooms) {
    
 Booking *p = head , *q=NULL;
  
//search for booking
  while (p != NULL && p->bookingID != bookingID ) {
        q = p;
        p = p->next; }

  if (p == NULL) {
        printf("Booking not found!\n");
        return head; }

    //update room status
    updateRoomStatus(rooms, p->roomID, 'A');

    //delete the node
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
