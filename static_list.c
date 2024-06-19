/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: --- LOGIN 1: ---
 * AUTHOR 2: --- LOGIN 2: ---
 * GROUP: -
 * DATE: - / - / -
 */

#include "static_list.h"
#include "string.h"

/* Write your code here... */

//GENERATORS

//function for creating a new empty list
void createEmptyList(tList* L){
    //initializes a list by giving a value to its last position
    L->lastPos = LNULL;
}

//function for inserting an item into a list
bool insertItem(tItemL item, tPosL pos, tList* L){
    //if the list is full it cant add more elements, so it returns false
    if ( L->lastPos == (MAX-1) ){
        return false;
    //if the given position is null it adds the given item to the last position
    } else if (pos == LNULL){
        L->lastPos+=1;
        L->data[L->lastPos]=item;
        return true;
    //if the given position is any other valid position it adds the item there and "moves the other items to  the right"
    } else{
        int i=L->lastPos;
        L->lastPos+=1;
        while (i>=pos){
            L->data[i+1]=L->data[i];
            i--;
        }
        L->data[pos]=item;
        return true;
    }
}

//MODIFIERS

//function for changing the value of an item of a list given its position
void updateItem(tItemL item, tPosL pos, tList* L){
    //changes the value of the data in the given position with the given item
    L->data[pos]=item;
}

//DESTRUCTORS

//function for deleting an item of a list given its position
void deleteAtPosition(tPosL pos, tList* L){
    int i=pos;
    L->lastPos--;
    //deletes the item in the given position and "moves the other items to  the left"
    while (i <= L->lastPos){
        L->data[i]=L->data[i+1];
        i++;
    }
}

//OBSERVERS

//function for checking if the list is empty
bool isEmptyList(tList L){
    //initialized lists are empty when their last position is null
    return (L.lastPos == LNULL);
}

//function that returns the first position of a given list
tPosL first(tList L){
    //if the list is not empty its first position is always 0
    return 0;
}

//function that returns the last position of a given list
tPosL last(tList L){
    //we always store the last position of a list into the lastPos variable
    return L.lastPos;
}

//function that returns the next position of a given position
tPosL next(tPosL pos, tList L){
    //if the given position is the last position it doesn't have a next position
    if (pos == L.lastPos){
        return LNULL;
    //if its any other position it returns the next one
    }else{
        return (pos+1);
    }
}

//function that returns the previous position of a given position
tPosL previous(tPosL pos, tList L){
    //if the given position is the first position it doesn't have a previous position
    if (pos == 0){
        return LNULL;
        //if its any other position it returns the previous one
    }else{
        return (pos-1);
    }
}

//function that returns the data of a list in a given position
tItemL getItem(tPosL pos, tList L){
    //it returns the data of the list in the given position
    return L.data[pos];
}

//function that returns the first position of a given item
tPosL findItem(tUserName user, tList L){
    int i;
    //it searches through the list until a username coincides with the given one
    for (i=0; i <= L.lastPos; i++){
        if ( strcmp(user,L.data[i].userName) == 0 ){
            return i;
        }
    }
    return LNULL;
}
