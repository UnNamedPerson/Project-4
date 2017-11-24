//
//  main.c
//  test proj 4
//
//  Created by Zhan Dov on 11/22/17.
//  Copyright © 2017 accolade. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define B 5

typedef char ETYPE[32];

typedef struct CELL *LIST;
struct CELL {
    ETYPE element;
    ETYPE element1;
    ETYPE element2;
    LIST next;
};

typedef LIST HASHTABLE[B*6];

// Hashing Function
int h(ETYPE x)
{
    int i, sum;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    return sum % B;
}

// Display Function

void displayRelations(HASHTABLE temp){
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> {|\"%s\"|}\n", i,temp[i]->element);
        } else {
            printf("HASH[%d]\t", i);
            while (p!=NULL) {
                printf("\t-> {|\"%s\"| |\"%s\"| |\"%s\"|}", p->element,p->element1,p->element2);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Insert Functions
void bucketInsert(ETYPE x, ETYPE y, ETYPE z,LIST *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST) malloc(sizeof(struct CELL));
        strcpy((*pL)->element, x);
        strcpy((*pL)->element1, y);
        strcpy((*pL)->element2, z);
        (*pL)->next = NULL;
    } else if (strcmp((*pL)->element, x))
        bucketInsert(x,y,z,&((*pL)->next));
    
}
void insert(ETYPE x, ETYPE y, ETYPE z,HASHTABLE H)
{
    bucketInsert(x,y,z,&(H[h(x)]));
}

// Delete Functions

void bucketDelete(ETYPE x, ETYPE y, ETYPE z,LIST *pL)
{
    if ((*pL) != NULL) {
        if(strcmp((*pL)->element, x)==0 || strcmp((*pL)->element1, y)==0 ||strcmp((*pL)->element2, z)==0){
            (*pL)=(*pL)->next;
        } else {
            bucketDelete(x, y, z, &((*pL)->next));
        }
    }
}
void delete(ETYPE x, ETYPE y, ETYPE z,HASHTABLE S)
{
    bucketDelete(x,y,z,&(S[h(x)]));
}

//Lookup functions
void bucketLookup(ETYPE x, ETYPE y, ETYPE z, LIST *pL){
    if(strcmp((*pL)->element, x)==0)// if the Studnetid is found
    {
        if(strcmp(y, "*")==0 && strcmp(z, "*")==0){
            while((*pL) != NULL){
                printf("StudentID: %s |Course :%s| Grade: %s\n", (*pL)->element, (*pL)->element1, (*pL)->element2);
                (*pL)=(*pL)->next;
            }
        } else if(strcmp(y, "*")==0){
            while( (*pL) != NULL){ // TO DO: check the condition
                if(strcmp((*pL)->element2, z)==0){
                    printf("StudentID: %s |Course :%s| Grade: %s\n",  (*pL)->element,  (*pL)->element1, (*pL)->element2);
                }
                (*pL)=(*pL)->next;
            }
        } else if(strcmp(z, "*")==0){
            while((*pL) != NULL){
                if(strcmp((*pL)->element1, y)==0){
                    printf("StudentID: %s |Course :%s| Grade: %s\n", (*pL)->element, (*pL)->element1, (*pL)->element2);
                }
                (*pL)=(*pL)->next;
            }
        } else {
            printf("StudentID: %s |Course :%s| Grade: %s\n", (*pL)->element, (*pL)->element1, (*pL)->element2);
        }
        
    } else {
        bucketLookup(x, y, z, &((*pL)->next));
    }
}

void lookup(ETYPE x, ETYPE y, ETYPE z,HASHTABLE L){
    bucketLookup(x,y,z,&(L[h(x)]));

}

void saveDatabase(HASHTABLE temp){
// create a FILE typed pointer
    FILE *file_pointer;

// open/create the file "test.sql" for writing
    file_pointer = fopen("check_data.txt","a+");

// write to the file
    LIST p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        while (p!=NULL) {
            fprintf(file_pointer,"%s\t%s\t%s\n",p->element,p->element1,p->element2);
            p=p->next;
        }
    }
// Close the file
    fclose(file_pointer);
}

int main(int argc, const char * argv[]) {
    HASHTABLE temp;
    
    printf("\n\tInserting Database\n");

    insert("1234",  "anyd", "one",  temp);
    insert("5678",  "live", "edw",  temp);
    insert("2135",  "icid", "dar",  temp);
    insert("1232",  "sala", "omq",  temp);
    insert("8784",  "chfd", "roy",  temp);
    insert("3421",  "insa", "ofa",  temp);
    insert("4322",  "iyer", "mon",  temp);
    
    displayRelations(temp);
    
    saveDatabase(temp);
    
    printf("\n\tDeleting Some Tuples\n");

    delete("3421",  "insa", "ofa",  temp);
    delete("4322",  "iyer", "mon",  temp);

    displayRelations(temp);
    
    lookup("8784",  "*", "*",  temp);
    lookup("2135",  "icid", "*",  temp);
    lookup("1232",  "*", "omq",  temp);
    
    return 0;
}
