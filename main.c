/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Diego Arturo Contreras Gonzalez LOGIN 1: diego.contreras@udc.es
 * AUTHOR 2: Kris Santiso Sampedro LOGIN 2: kris.santiso@udc.es
 * GROUP: 6
 * DATE: 19 / 3 / 24
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

//function for adding a new user
void addNewUser(char *param1, char *param2, tList *L){

    //it creates the new item it will add
    tItemL itemN;
    strcpy (itemN.userName, param1);
    itemN.numPlay = 0;
    //as it can't access the userCategory directly it compares the category introduced with the string basic
    if ( strcmp( param2, "basic" ) == 0){
        //if it's the same it assigns basic to the item to add
        itemN.userCategory = basic;
    } else{
        //if it's not it assigns pro to the item to add
        itemN.userCategory = pro;
    }

    //if the list is empty it tries to add the item directly
    if ( isEmptyList(*L) ){
        bool inserted = insertItem(itemN, LNULL, L);
        //        //if the insertion works it adds the item and prints the command
        if (inserted == true) {
            printf("* New: user %s category %s\n", param1, param2);
        //if the insertion fails it cant add the item, so it prints an error
        } else {
            printf("+ Error: New not possible\n");
        }
    } else {
        //if it's not empty we need to check if there's already an item with the same name
        if (findItem(param1, *L) == LNULL) {
            //if there's not any item with the same name it tries to add the item
            bool inserted = insertItem(itemN, LNULL, L);
            //if the insertion works it adds the item and prints the command
            if (inserted == true) {
                printf("* New: user %s category %s\n", param1, param2);
            //if the insertion fails it cant add the item, so it prints an error
            } else {
                printf("+ Error: New not possible\n");
            }
        //if there's already an item with the same name it cant add the new item, so it prints an error
        } else {
            printf("+ Error: New not possible\n");
        }
    }
}

//function for deleting a user
void deleteUser(char *param1, tList *L){
    //if the list is empty there's not user to delete, so it prints an error
    if ( isEmptyList(*L) ) {
        printf("+ Error: Delete not possible\n");
    } else {
        //if the list isn't empty it searches for the user it wants to delete
        tPosL posD = findItem( param1, *L);
        if (  posD != LNULL ){
            //it gets the item it will delete, so it can access its category and numplays
            tItemL itemD;
            itemD = getItem(posD, *L);
            deleteAtPosition(posD, L);

            //as it can't print the category directly it creates a string category and assigns basic or pro depending on the category
            char categoryD[6];
            if ( itemD.userCategory == basic ){
                strcpy(categoryD, "basic");
            } else{
                strcpy(categoryD, "pro");
            }

            printf("* Delete: user %s category %s numplays %d\n", param1, categoryD, itemD.numPlay);
        //if it doesn't find the item it wants to delete it prints an error
        } else {
            printf("+ Error: Delete not possible\n");
        }
    }
}

//function for upgrading a user category from basic to pro
void upgradeUserCategory(char *param1, tList *L){
    //if the list is empty there's no item to upgrade
    if ( isEmptyList(*L) ) {
        printf("+ Error: Upgrade not possible\n");
    } else {
        //if the list isn't empty it searches for the user it wants to upgrade
        tPosL posU = findItem( param1, *L);
        if ( posU != LNULL ){
            //it gets the item it will upgrade, so it can check its category
            tItemL itemU = getItem(posU, *L);
            if ( itemU.userCategory == basic) {
                //if the item's category is basic it changes it to pro
                itemU.userCategory = pro;
                //as it can't print the category directly it creates a string category with value pro
                char categoryU[6] = "pro";
                //it updates the item to the new item
                updateItem(itemU, posU, L);
                printf("* Upgrade: user %s category %s\n", itemU.userName, categoryU);
            //if the item's category is pro it cant upgrade its category, so it prints an error
            } else {
                printf("+ Error: Upgrade not possible\n");
            }
        //if it doesn't find the item it wants to delete it prints an error
        } else {
            printf("+ Error: Upgrade not possible\n");
        }
    }
}

//function that increments the amount of plays a user has by 1
void playSong(char *param1, char *param2, tList *L){
    //if the list is empty we print an error message
    if ( isEmptyList(*L) == true ) {
        printf("+ Error: Play not possible\n");
    } else {
        //we assign to the variable posP the item that has the same username as imputed
        tPosL posP = findItem( param1, *L);
        //we check whether the position is null
        if ( posP != LNULL ){
            //we use get item on the position stored in posP
            tItemL itemP = getItem(posP, *L);
            //we increase the number of songs played by 1
            itemP.numPlay++;
            //we update the item at position posP so that it now has the updated number of plays
            updateItem(itemP, posP, L);
            printf("* Play: user %s plays song %s numplays %d\n", itemP.userName, param2, itemP.numPlay);
        } else {
            //if the position is null we print an error message
            printf("+ Error: Play not possible\n");
        }
    }
}

//function for showing the current list of users as well as some of their stats
void showStats(tList *L){
    //if the list is empty we can't show its stats (because it has none) no we print an error
    if ( isEmptyList(*L) == true ) {
        printf("+ Error: Stats not possible\n");
        //if the list is not empty we go position by position printing and storing the elements that we want
    } else {
        //variable that stores the position we want to check (when first declared stores the first position in the list)
        tPosL posCount = first(*L);
        //multiple variables that count various things we will print later
        tNumPlay basicPlayCount = 0, proPlayCount = 0;
        int basicUserCount = 0, proUserCount = 0;
        //two variables that we will use later to store averages in them
        float basicAveragePlay, proAveragePlay;
        while ( posCount != LNULL ) {
            //we use get item to get the information stored in the position of the current iteration of the loop and store it in itemS
            tItemL itemS = getItem(posCount, *L);
            //we use a string to store the category of the user in the current position
            char categoryS[6];
            //we add one to the basic or pro counting variables depending on the category the user has
            if ( itemS.userCategory == basic ){
                strcpy(categoryS, "basic");
                basicUserCount++;
                basicPlayCount += itemS.numPlay;
            } else{
                strcpy(categoryS, "pro");
                proUserCount++;
                proPlayCount += itemS.numPlay;
            }
            //we print a message with the username, category and number of plays of the user in the current position
            printf("User %s category %s numplays %d\n", itemS.userName, categoryS, itemS.numPlay);
            //we make it so that posCount is now the position following it
            posCount = next(posCount, *L);
        }
        //if the number of users of category basic is 0, we make it so the average is also 0, as to not make an operation where we divide by 0
        if (basicUserCount == 0) {
            basicAveragePlay=0;
        } else {
            //we calculate the average number of plays
            basicAveragePlay = (float) basicPlayCount / (float) basicUserCount;
        }
        //same as with basicUserCount, but now with users of pro category
        if (proUserCount == 0) {
            proAveragePlay=0;
        } else {
            proAveragePlay = (float) proPlayCount / (float) proUserCount;
        }
        //finally, we print a table with the number of users with each category as well as their total number of plays and the average ammount of users with each category
        printf("Category  Users  Plays  Average\n");
        printf("Basic     %5d %6d %8.2f\n", basicUserCount, basicPlayCount, basicAveragePlay);
        printf("Pro       %5d %6d %8.2f\n", proUserCount, proPlayCount, proAveragePlay);
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, tList *L) {
    switch (command) {
        //for each case we print a series of asterisks followed by a message detailing the number of the command, the type of command and what the parameters represent
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);
            //addNewUser only needs the user to add, its category and the list it'll be added to
            addNewUser(param1, param2, L);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);
            //deleteUser only needs the user to delete and the list it'll be deleted from
            deleteUser(param1, L);
            break;
        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);
            //upgradeUser only needs the user to upgrade and the list it'll be upgraded from
            upgradeUserCategory(param1, L);
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);
            //playSong only needs the user that plays the song, the name of the song and the list the user is from
            playSong(param1, param2, L);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c:\n", commandNumber, command);
            //showStats only needs the list the stats will be shown from
            showStats(L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        tList L;
        createEmptyList(&L);

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, &L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}