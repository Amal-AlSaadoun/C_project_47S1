//============================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
//============================
Room* loadRooms(const char *filename){

FILE *fpi =fopen(filename , "r");

if (fpi== NULL) {
        printf("Can't open rooms file.\n");
        return NULL; }

        Room *head = NULL;

    int RoomTypenum;
    Room NewRoom ;
    while (fscanf(fpi, "%d %d %d %f %c %d", 
                  &NewRoom.roomID, &RoomTypenum, &NewRoom.capacity, 
                  &NewRoom.price, &NewRoom.status, &NewRoom.amenityCount) == 6) { //6 is the number of 
          //determine room type  
         switch(RoomTypenum){
         case 0 : NewRoom.type = STANDARD; 
         break; 
         case 1 : NewRoom.type = DELUXE; 
         break; 
         case 2 : NewRoom.type = SUITE;
         break; 
         }
         // Read new room amenities
        for (int i = 0; i < NewRoom.amenityCount; i++) 
         fscanf(fpi, " %[^\n]", NewRoom.amenities[i]);//read 1 line
      
        NewRoom.next = NULL;
        addRoom(&head, NewRoom);

      }//End while - End loadin data

    fclose(fpi);
    return head;
}//End loadRooms comment
//============================


void saveRooms(Room *head, const char *filename){
 
   FILE *fpo = fopen(filename, "w");
    if (fpo == NULL) {
        printf("Can't save rooms in the file!\n");
        return;
    }
    Room *current = head; //start frome head

   while (current != NULL) {
         fprintf(fpo, "%d %d %d %.2f %c %d\n", 
                  current->roomID, current->type, current->capacity, 
                  current->price, current->status, current->amenityCount);
   // current amenities
        for (int i = 0; i < current->amenityCount; i++) 
            fprintf(fpo, "%s\n", current->amenities[i]);
        
        current = current->next; //move current to the next node
    }//End while
    
    fclose(fpo);
}//End saveRooms


//============================
void printRooms(Room *head){ 
   
   printf("\n%-5s  %-9s  %-5s  %-10s  %-8s %-s \n", "ID", "Type", "Cap", "Price", "Status", "Amenities");

   Room *current = head; //start frome head

   while (current != NULL) {

   if (current->type == STANDARD)
            printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", current->roomID, "STANDARD", current->capacity, current->price, current->status);
         
            else if (current->type== DELUXE)
            printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", current->roomID, "DELUXE", current->capacity, current->price, current->status);
        
            else if (current->type == SUITE)
            printf("%-5d  %-9s  %-5d  %-9.2f   %-8c ", current->roomID, "SUITE", current->capacity, current->price, current->status);


         for (int j = 0; j < current->amenityCount; j++)
            printf("%s, ", current->amenities[j]);

            printf("\n");
            current=current->next; //move current to the next node
   }//End while
} // End printRooms function

//============================
Room* findRoom(Room *head, int roomID){

   Room *current = head; //start frome head

   while (current != NULL) {
      if (current->roomID == roomID)
         return current;
            
      current=current->next; //move current to the next node   
   }//End while

   return NULL;//if room not found

}//End findRoom 


//============================

void updateRoomStatus(Room *head, int roomID, char newStatus){

   Room *current = findRoom(head, roomID);

   if (current == NULL)
        printf("Room NOT found: wrong room ID\n");
   else
        current->status = newStatus;

}//End updateRoomStatus

//============================
void addRoom(Room **head, Room newRoom){

   Room *tmp = (Room*)calloc(1,sizeof(Room));
   if(tmp==NULL){
      printf("Can't allocate memory for new room !\n");
      return;
   }
   *tmp=newRoom;
   tmp->next=NULL;

   if(*head==NULL){//empty list
      *head=tmp;
   } else {

   Room *current = *head;//start frome head
        while (current->next != NULL) 
            current = current->next;//move current to the last node   
   
        current->next = tmp;//add at the end
   }

   }//End addRoom




//============================
void freeRooms(Room *head){

   while (head != NULL) {
     Room *tmp = head;
     head = head->next;
     free(tmp);  //free each node individually (should use method saveRooms before, to not lose Rooms data)
   }
}//End freeRooms


