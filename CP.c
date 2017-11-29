//  WORKS CP
//  notepad_1.c
//  Project 4
//
//  Created by Zhan Dov on 11/28/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_CP 11

typedef char ETYPE[32];

typedef struct CELL_CP *LIST_CP;

struct CELL_CP {
    ETYPE course;
    ETYPE prerequisite;
    LIST_CP next;
};

typedef LIST_CP HASHTABLE_CP[SIZE_CP*6];

int h_CP(ETYPE x);
void displayRelations_CP(HASHTABLE_CP temp);
void bucketInsert_CP(ETYPE x, ETYPE y, LIST_CP *pL);
void insert_CP(ETYPE x, ETYPE y, HASHTABLE_CP H);
void bucketDelete_CP(ETYPE x, ETYPE y, LIST_CP *pL);
void delete_CP(ETYPE x, ETYPE y, HASHTABLE_CP S);
void bucketLookup_CP(ETYPE x, ETYPE y, LIST_CP *pL);
void lookup_CP(ETYPE x, ETYPE y, HASHTABLE_CP L);
void saveDatabase_CP(HASHTABLE_CP temp, char *new_name);
void loadDatabase_CP(char *filename, HASHTABLE_CP temp);

int main(int argc, const char * argv[]) {
    HASHTABLE_CP temp;
    char *name_of_database = "database_CP.txt";

    //inserts into the database
    printf("Inserting Database\n\n");
    insert_CP("CS101",  "CS100",  temp);
    insert_CP("EE200",  "EE005",  temp);
    insert_CP("EE200",  "CS100",  temp);
    insert_CP("CS120",  "CS101",  temp);
    insert_CP("CS121",  "CS120",  temp);
    insert_CP("CS205",  "CS101",  temp);
    insert_CP("CS206",  "CS121",  temp);
    insert_CP("CS206",  "CS205",  temp);


    //saves the database
    saveDatabase_CP(temp,name_of_database);

    /*** Before Testing Make Sure To Comment Out saveDatabase_CSG(temp,name_of_database) & insert functions ***/
    /*** As while loading it will duplicate the database ***/
    /*** Try to comment out saveDatabase_CSG() & insert functions and test loadDatabase(). Thanks. ***/
    //loads the database
    //loadDatabase_CP(name_of_database, temp);
    displayRelations_CP(temp);
    //deletes some tuples
    printf("Deleting Tuples\n\n");
    delete_CP("CS205",  "CS101",  temp);
    delete_CP("CS121",  "CS120",  temp);
    displayRelations_CP(temp);

    //lookups some tuples

    lookup_CP("EE200",  "*",  temp);

    return 0;
}

int h_CP(ETYPE x)
{
    int i, sum, result=0;

    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    result = sum % SIZE_CP;
    //printf("sum is %d mode %d is %d\n", sum, SIZE_CP, result);
    return result;
}

// Insert Functions
void bucketInsert_CP(ETYPE x, ETYPE y, LIST_CP *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST_CP)malloc(sizeof(struct CELL_CP));
        strcpy((*pL)->course, x);
        strcpy((*pL)->prerequisite, y);
        (*pL)->next = NULL;
    } else
        bucketInsert_CP(x,y,&((*pL)->next));

}
void insert_CP(ETYPE x, ETYPE y, HASHTABLE_CP H)
{
    bucketInsert_CP(x,y,&(H[h_CP(x)]));
}

// Delete Functions

void bucketDelete_CP(ETYPE x, ETYPE y, LIST_CP *pL)
{
    if ((*pL) != NULL) {
        if(strcmp((*pL)->course, x)==0 && strcmp((*pL)->prerequisite, y)==0){
            (*pL)=(*pL)->next;
        } else {
            bucketDelete_CP(x, y, &((*pL)->next));
        }
    }
}
void delete_CP(ETYPE x, ETYPE y, HASHTABLE_CP S)
{
    bucketDelete_CP(x,y,&(S[h_CP(x)]));
}

//Lookup functions
void bucketLookup_CP(ETYPE x, ETYPE y, LIST_CP *pL){
    if ((*pL)==NULL) {
        return;
    }
    else if(strcmp((*pL)->course, x)==0)// if x is found
    {
        if(strcmp(y, "*")==0){
            if(strcmp((*pL)->course, x)==0 && strcmp(y, "*")==0){
                printf("Course: %s |Prerequisite: %s \n", (*pL)->course, (*pL)->prerequisite);
                bucketLookup_CP(x, y, &((*pL)->next));
            }
        }
    }
    else {
        bucketLookup_CP(x, y, &((*pL)->next));
    }
}


void lookup_CP(ETYPE x, ETYPE y, HASHTABLE_CP L){
    bucketLookup_CP(x,y, &(L[h_CP(x)]));
}

void saveDatabase_CP(HASHTABLE_CP temp, char *new_name){
    // create a FILE typed pointer
    FILE *file_pointer;

    // open/create the txt file for saving the database
    file_pointer = fopen(new_name,"w+");

    // write to the file
    LIST_CP p;
    for (int i = 0; i<SIZE_CP; i++) {
        p=temp[i];
        while (p!=NULL) {
            fprintf(file_pointer,"%s\n%s\n",p->course,p->prerequisite);
            p=p->next;
        }
    }
    // Close the file
    fclose(file_pointer);
    printf("Database is saved\n\n");
}

void loadDatabase_CP(char *filename, HASHTABLE_CP temp)
{
    // loads the database
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return;

    while(!feof(fp))
    {
        char x[32],y[32];
        fscanf(fp, "%s\n%s\n", x,y);
        insert_CP(x, y, temp);
    }
    fclose(fp);
    printf("Database is loaded\n\n");
    return;
}
void displayRelations_CP(HASHTABLE_CP temp){
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST_CP p;
    for (int i = 0; i<SIZE_CP; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> {|\"%s\"|}\n", i,temp[i]->course);
        } else {
            printf("HASH[%d]\t", i);
            while (p!=NULL) {
                printf("\t-> {|\"%s\"| |\"%s\"|}", p->course,p->prerequisite);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}



