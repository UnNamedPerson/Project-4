//  WORKS CR
//  notepad_1.c
//  Project 4
//
//  Created by Zhan Dov on 11/28/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_CR 5

typedef char ETYPE[32];

typedef struct CELL_CR *LIST_CR;

struct CELL_CR {
    ETYPE course;
    ETYPE room;
    LIST_CR next;
};

typedef LIST_CR HASHTABLE_CR[SIZE_CR*6];

int h_CR(ETYPE x);
void displayRelations_CR(HASHTABLE_CR temp);
void bucketInsert_CR(ETYPE x, ETYPE y, LIST_CR *pL);
void insert_CR(ETYPE x, ETYPE y, HASHTABLE_CR H);
void bucketDelete_CR(ETYPE x, ETYPE y, LIST_CR *pL);
void delete_CR(ETYPE x, ETYPE y, HASHTABLE_CR S);
void bucketLookup_CR(ETYPE x, ETYPE y, LIST_CR *pL);
void lookup_CR(ETYPE x, ETYPE y, HASHTABLE_CR L);
void saveDatabase_CR(HASHTABLE_CR temp, char *new_name);
void loadDatabase_CR(char *filename, HASHTABLE_CR temp);

int main(int argc, const char * argv[]) {
    HASHTABLE_CR temp;
    char *name_of_database = "database_CR.txt";

    //inserts into the database
    printf("Inserting Database\n\n");
    insert_CR("CS101",  "Turing Aud.",  temp);
    insert_CR("EE200",  "25 Ohm Hall",  temp);
    insert_CR("PH100",  "Newton Lab.",  temp);


    //saves the database
    saveDatabase_CR(temp,name_of_database);

    /*** Before Testing Make Sure To Comment Out saveDatabase_CSG(temp,name_of_database) & insert functions ***/
    /*** As while loading it will duplicate the database ***/
    /*** Try to comment out saveDatabase_CSG() & insert functions and test loadDatabase(). Thanks. ***/
    //loads the database
    //loadDatabase_CR(name_of_database, temp);
    displayRelations_CR(temp);
    //deletes some tuples
    printf("Deleting Tuples\n\n");
    delete_CR("PH100",  "Newton Lab.",  temp);
    displayRelations_CR(temp);

    //lookups some tuples

    lookup_CR("EE200",  "*",  temp);

    return 0;
}

int h_CR(ETYPE x)
{
    int i, sum, result=0;

    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    result = sum % SIZE_CR;
    //    printf("sum is %d mode %d is %d\n", sum, SIZE_CSG, result);
    return result;
}

// Insert Functions
void bucketInsert_CR(ETYPE x, ETYPE y, LIST_CR *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST_CR)malloc(sizeof(struct CELL_CR));
        strcpy((*pL)->course, x);
        strcpy((*pL)->room, y);
        (*pL)->next = NULL;
    } else
        bucketInsert_CR(x,y,&((*pL)->next));

}
void insert_CR(ETYPE x, ETYPE y, HASHTABLE_CR H)
{
    bucketInsert_CR(x,y,&(H[h_CR(x)]));
}

// Delete Functions

void bucketDelete_CR(ETYPE x, ETYPE y, LIST_CR *pL)
{
    if ((*pL) != NULL) {
        if(strcmp((*pL)->course, x)==0 && strcmp((*pL)->room, y)==0){
            (*pL)=(*pL)->next;
        } else {
            bucketDelete_CR(x, y, &((*pL)->next));
        }
    }
}
void delete_CR(ETYPE x, ETYPE y, HASHTABLE_CR S)
{
    bucketDelete_CR(x,y,&(S[h_CR(x)]));
}

//Lookup functions
void bucketLookup_CR(ETYPE x, ETYPE y, LIST_CR *pL){
    if ((*pL)==NULL) {
        return;
    }
    else if(strcmp((*pL)->course, x)==0)// if x is found
    {
        if(strcmp(y, "*")==0){
            if(strcmp((*pL)->course, x)==0 && strcmp(y, "*")==0){
                printf("Course: %s |Room: %s \n", (*pL)->course, (*pL)->room);
                bucketLookup_CR(x, y, &((*pL)->next));
            }
        }
    }
    else {
        bucketLookup_CR(x, y, &((*pL)->next));
    }
}


void lookup_CR(ETYPE x, ETYPE y, HASHTABLE_CR L){
    bucketLookup_CR(x,y, &(L[h_CR(x)]));
}

void saveDatabase_CR(HASHTABLE_CR temp, char *new_name){
    // create a FILE typed pointer
    FILE *file_pointer;

    // open/create the txt file for saving the database
    file_pointer = fopen(new_name,"w+");

    // write to the file
    LIST_CR p;
    for (int i = 0; i<SIZE_CR; i++) {
        p=temp[i];
        while (p!=NULL) {
            fprintf(file_pointer,"%s\n%s\n",p->course,p->room);
            p=p->next;
        }
    }
    // Close the file
    fclose(file_pointer);
    printf("Database is saved\n\n");
}

void loadDatabase_CR(char *filename, HASHTABLE_CR temp)
{
    // loads the database
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return;

    while(!feof(fp))
    {
        char x[32],y[32];
        fscanf(fp, "%s\n%s\n", x,y);
        insert_CR(x, y, temp);
    }
    fclose(fp);
    printf("Database is loaded\n\n");
    return;
}
void displayRelations_CR(HASHTABLE_CR temp){
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST_CR p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> {|\"%s\"|}\n", i,temp[i]->course);
        } else {
            printf("HASH[%d]\t", i);
            while (p!=NULL) {
                printf("\t-> {|\"%s\"| |\"%s\"|}", p->course,p->room);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}


