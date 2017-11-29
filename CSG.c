// WORKS CSG
//  notepad_1.c
//  Project 4
//
//  Created by Zhan Dov on 11/28/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_CSG 5

typedef char ETYPE[32];

typedef struct CELL_CSG *LIST_CSG;

struct CELL_CSG {
    ETYPE studentID;
    ETYPE course;
    ETYPE grade;
    LIST_CSG next;
};

typedef LIST_CSG HASHTABLE_CSG[SIZE_CSG*6];

int h_CSG(ETYPE x);
void displayRelations_CSG(HASHTABLE_CSG temp);
void bucketInsert_CSG(ETYPE x, ETYPE y, ETYPE z,LIST_CSG *pL);
void insert_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG H);
void bucketDelete_CSG(ETYPE x, ETYPE y, ETYPE z,LIST_CSG *pL);
void delete_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG S);
void bucketLookup_CSG(ETYPE x, ETYPE y, ETYPE z, LIST_CSG *pL);
void lookup_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG L);
void saveDatabase_CSG(HASHTABLE_CSG temp, char *new_name);
void loadDatabase_CSG(char *filename, HASHTABLE_CSG temp);

int main(int argc, const char * argv[]) {
    HASHTABLE_CSG temp;
    char *name_of_database = "database_CGS.txt";

    //inserts into the database
    printf("Inserting Database\n\n");
    insert_CSG("12345",  "CS101", "A",  temp);
    insert_CSG("67890",  "CS101", "B",  temp);
    insert_CSG("12345",  "EE200", "C",  temp);
    insert_CSG("22222",  "EE200", "B+",  temp);
    insert_CSG("33333",  "CS101", "A-",  temp);
    insert_CSG("67890",  "PH100", "C+",  temp);

    
    //saves the database
    saveDatabase_CSG(temp,name_of_database);

    /*** Before Testing Make Sure To Comment Out saveDatabase_CSG(temp,name_of_database) & insert functions ***/
    /*** As while loading it will duplicate the database ***/
    /*** Try to comment out saveDatabase_CSG() & insert functions and test loadDatabase(). Thanks. ***/
    //loads the database
    //loadDatabase_CSG(name_of_database, temp);
    displayRelations_CSG(temp);
    //deletes some tuples
    printf("Deleting Tuples\n\n");
    delete_CSG("33333",  "CS101", "A-",  temp);
    delete_CSG("67890",  "PH100", "C+",  temp);

    displayRelations_CSG(temp);

    //lookups some tuples
    
    lookup_CSG("12345",  "*", "A",  temp);
    lookup_CSG("67890",  "CS101", "*",  temp);
    lookup_CSG("12345",  "*", "*",  temp);

    return 0;
}

int h_CSG(ETYPE x)
{
    int i, sum, result=0;

    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    result = sum % SIZE_CSG;
//    printf("sum is %d mode %d is %d\n", sum, SIZE_CSG, result);
    return result;
}

// Insert Functions
void bucketInsert_CSG(ETYPE x, ETYPE y, ETYPE z,LIST_CSG *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST_CSG)malloc(sizeof(struct CELL_CSG));
        strcpy((*pL)->studentID, x);
        strcpy((*pL)->course, y);
        strcpy((*pL)->grade, z);
        (*pL)->next = NULL;
    } else
        bucketInsert_CSG(x,y,z,&((*pL)->next));

}
void insert_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG H)
{
    bucketInsert_CSG(x,y,z,&(H[h_CSG(x)]));
}

// Delete Functions

void bucketDelete_CSG(ETYPE x, ETYPE y, ETYPE z,LIST_CSG *pL)
{
    if ((*pL) != NULL) {
        if(strcmp((*pL)->studentID, x)==0 && strcmp((*pL)->course, y)==0 && strcmp((*pL)->grade, z)==0){
            (*pL)=(*pL)->next;
        } else {
            bucketDelete_CSG(x, y, z, &((*pL)->next));
        }
    }
}
void delete_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG S)
{
    bucketDelete_CSG(x,y,z,&(S[h_CSG(x)]));
}

//Lookup functions
void bucketLookup_CSG(ETYPE x, ETYPE y, ETYPE z, LIST_CSG *pL){
    if ((*pL)==NULL) {
        return;
    }
    else if(strcmp((*pL)->studentID, x)==0)// if x is found
    {
        if(strcmp(y, "*")==0 && strcmp(z, "*")==0){

            if(strcmp((*pL)->studentID, x)==0){
                printf("StudentID: %s |Course: %s| Grade: %s\n", (*pL)->studentID, (*pL)->course, (*pL)->grade);
                bucketLookup_CSG(x, y, z, &((*pL)->next));
            }
        }
        else if(strcmp(y, "*")==0 && strcmp(z, "*")!=0){
            LIST_CSG temp = (*pL);
            while( temp != NULL){
                if(strcmp(temp->grade, z)==0 && strcmp((*pL)->studentID, x)==0 && strcmp(y, "*")==0){
                    printf("StudentID: %s |Course: %s| Grade: %s\n", temp->studentID, temp->course, temp->grade);
                }
                temp=temp->next;
            }
        }
        else if(strcmp(z, "*")==0 && strcmp(y, "*")!=0){
            LIST_CSG temp = (*pL);
            while( temp != NULL){
                if(strcmp(temp->course, y)==0 && strcmp((*pL)->studentID, x)==0 && strcmp(z, "*")==0){
                    printf("StudentID: %s |Course: %s| Grade: %s\n", temp->studentID, temp->course, temp->grade);
                }
                temp=temp->next;
            }
        }
    }
    else {
        bucketLookup_CSG(x, y, z, &((*pL)->next));
    }
}


void lookup_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG L){
    bucketLookup_CSG(x,y,z,&(L[h_CSG(x)]));

}

void saveDatabase_CSG(HASHTABLE_CSG temp, char *new_name){
    // create a FILE typed pointer
    FILE *file_pointer;

    // open/create the txt file for saving the database
    file_pointer = fopen(new_name,"w+");

    // write to the file
    LIST_CSG p;
    for (int i = 0; i<SIZE_CSG; i++) {
        p=temp[i];
        while (p!=NULL) {
            fprintf(file_pointer,"%s\t%s\t%s\n",p->studentID,p->course,p->grade);
            p=p->next;
        }
    }
    // Close the file
    fclose(file_pointer);
    printf("Database is saved\n\n");
}

void loadDatabase_CSG(char *filename, HASHTABLE_CSG temp)
{
    // loads the database
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return;

    while(!feof(fp))
    {
        char x[32],y[32],z[32];
        fscanf(fp, "%s\t%s\t%s\n", x,y,z);
        insert_CSG(x, y, z, temp);
    }
    fclose(fp);
    printf("Database is loaded\n\n");
    return;
}
void displayRelations_CSG(HASHTABLE_CSG temp){
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST_CSG p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> {|\"%s\"|}\n", i,temp[i]->studentID);
        } else {
            printf("HASH[%d]\t", i);
            while (p!=NULL) {
                printf("\t-> {|\"%s\"| |\"%s\"| |\"%s\"|}", p->studentID,p->course,p->grade);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}






