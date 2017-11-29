// WORKS CDH
//  notepad_1.c
//  Project 4
//
//  Created by Zhan Dov on 11/28/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_CDH 5

typedef char ETYPE[32];

typedef struct CELL_CDH *LIST_CDH;

struct CELL_CDH {
    ETYPE course;
    ETYPE day;
    ETYPE hour;
    LIST_CDH next;
};

typedef LIST_CDH HASHTABLE_CDH[SIZE_CDH*6];

int h_CDH(ETYPE x);
void displayRelations_CDH(HASHTABLE_CDH temp);
void bucketInsert_CDH(ETYPE x, ETYPE y, ETYPE z,LIST_CDH *pL);
void insert_CDH(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CDH H);
void bucketDelete_CDH(ETYPE x, ETYPE y, ETYPE z,LIST_CDH *pL);
void delete_CDH(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CDH S);
void bucketLookup_CDH(ETYPE x, ETYPE y, ETYPE z, LIST_CDH *pL);
void lookup_CDH(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CDH L);
void saveDatabase_CDH(HASHTABLE_CDH temp, char *new_name);
void loadDatabase_CDH(char *filename, HASHTABLE_CDH temp);

int main(int argc, const char * argv[]) {
    HASHTABLE_CDH temp;
    char *name_of_database = "database_CDH.txt";
    
    //inserts into the database
    printf("Inserting Database\n\n");
    insert_CDH("CS101",  "M", "9AM",  temp);
    insert_CDH("CS101",  "W", "9AM",  temp);
    insert_CDH("CS101",  "F", "9AM",  temp);
    insert_CDH("EE200",  "Tu", "10AM",  temp);
    insert_CDH("EE200",  "W", "1PM",  temp);
    insert_CDH("EE200",  "Th", "10AM",  temp);


    //saves the database
    saveDatabase_CDH(temp,name_of_database);

    /*** Before Testing Make Sure To Comment Out saveDatabase_CSG(temp,name_of_database) & insert functions ***/
    /*** As while loading it will duplicate the database ***/
    /*** Try to comment out saveDatabase_CSG() & insert functions and test loadDatabase(). Thanks. ***/
    //loads the database
    //loadDatabase_CDH(name_of_database, temp);
    displayRelations_CDH(temp);
    //deletes some tuples
    printf("Deleting Tuples\n\n");
    delete_CDH("CS101",  "M", "9AM",  temp);
    delete_CDH("CS101",  "W", "9AM",  temp);
    
    displayRelations_CDH(temp);
    
    //lookups some tuples
    
    lookup_CDH("CS101",  "*", "*",  temp);
    lookup_CDH("EE200",  "Tu", "*",  temp);
    lookup_CDH("EE200",  "*", "1PM",  temp);
    
    return 0;
}

int h_CDH(ETYPE x)
{
    int i, sum, result=0;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    result = sum % SIZE_CDH;
    //    printf("sum is %d mode %d is %d\n", sum, SIZE_CSG, result);
    return result;
}

// Insert Functions
void bucketInsert_CDH(ETYPE x, ETYPE y, ETYPE z,LIST_CDH *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST_CDH)malloc(sizeof(struct CELL_CDH));
        strcpy((*pL)->course, x);
        strcpy((*pL)->day, y);
        strcpy((*pL)->hour, z);
        (*pL)->next = NULL;
    } else
        bucketInsert_CDH(x,y,z,&((*pL)->next));
    
}
void insert_CDH(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CDH H)
{
    bucketInsert_CDH(x,y,z,&(H[h_CDH(x)]));
}

// Delete Functions

void bucketDelete_CDH(ETYPE x, ETYPE y, ETYPE z,LIST_CDH *pL)
{
    if ((*pL) != NULL) {
        if(strcmp((*pL)->course, x)==0 && strcmp((*pL)->day, y)==0 && strcmp((*pL)->hour, z)==0){
            (*pL)=(*pL)->next;
        } else {
            bucketDelete_CDH(x, y, z, &((*pL)->next));
        }
    }
}
void delete_CDH(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CDH S)
{
    bucketDelete_CDH(x,y,z,&(S[h_CDH(x)]));
}

//Lookup functions
void bucketLookup_CDH(ETYPE x, ETYPE y, ETYPE z, LIST_CDH *pL){
    if ((*pL)==NULL) {
        return;
    }
    else if(strcmp((*pL)->course, x)==0)// if x is found
    {
        if(strcmp(y, "*")==0 && strcmp(z, "*")==0){
            
            if(strcmp((*pL)->course, x)==0){
                printf("Course: %s | Day: %s| Hour: %s\n", (*pL)->course, (*pL)->day, (*pL)->hour);
                bucketLookup_CDH(x, y, z, &((*pL)->next));
            }
        }
        else if(strcmp(y, "*")==0 && strcmp(z, "*")!=0){
            LIST_CDH temp = (*pL);
            while( temp != NULL){
                if(strcmp(temp->hour, z)==0 && strcmp((*pL)->course, x)==0 && strcmp(y, "*")==0){
                    printf("Course: %s | Day: %s| Hour: %s\n", temp->course, temp->day, temp->hour);
                }
                temp=temp->next;
            }
        }
        else if(strcmp(z, "*")==0 && strcmp(y, "*")!=0){
            LIST_CDH temp = (*pL);
            while( temp != NULL){
                if(strcmp(temp->day, y)==0 && strcmp((*pL)->course, x)==0 && strcmp(z, "*")==0){
                    printf("Course: %s | Day: %s| Hour: %s\n", temp->course, temp->day, temp->hour);
                }
                temp=temp->next;
            }
        }
    }
    else {
        bucketLookup_CDH(x, y, z, &((*pL)->next));
    }
}


void lookup_CDH(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CDH L){
    bucketLookup_CDH(x,y,z,&(L[h_CDH(x)]));
    
}

void saveDatabase_CDH(HASHTABLE_CDH temp, char *new_name){
    // create a FILE typed pointer
    FILE *file_pointer;
    
    // open/create the txt file for saving the database
    file_pointer = fopen(new_name,"w+");
    
    // write to the file
    LIST_CDH p;
    for (int i = 0; i<SIZE_CDH; i++) {
        p=temp[i];
        while (p!=NULL) {
            fprintf(file_pointer,"%s\t%s\t%s\n",p->course,p->day,p->hour);
            p=p->next;
        }
    }
    // Close the file
    fclose(file_pointer);
    printf("Database is saved\n\n");
}

void loadDatabase_CDH(char *filename, HASHTABLE_CDH temp)
{
    // loads the database
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return;
    
    while(!feof(fp))
    {
        char x[32],y[32],z[32];
        fscanf(fp, "%s\t%s\t%s\n", x,y,z);
        insert_CDH(x, y, z, temp);
    }
    fclose(fp);
    printf("Database is loaded\n\n");
    return;
}
void displayRelations_CDH(HASHTABLE_CDH temp){
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST_CDH p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> {|\"%s\"|}\n", i,temp[i]->course);
        } else {
            printf("HASH[%d]\t", i);
            while (p!=NULL) {
                printf("\t-> {|\"%s\"| |\"%s\"| |\"%s\"|}", p->course,p->day,p->hour);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}


