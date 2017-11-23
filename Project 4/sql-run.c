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

// Display Functions and other methods that're needed for display functions
int countNodes(LIST start){
    int i = 0;
    if (start == NULL){
        return i; //As nodes are 0, the list is empty
    } else {
        LIST p; p=start;
        while (p!=NULL){
            i++;
            p=p->next;
        }
        return i;
    }
}

void displayCells(LIST start, int numnodes){
   
    LIST p; p=start;
    for (int i = 0; i<(numnodes-1); i++){
        p=p->next;
        printf("\t-> {|\"%s\"| |\"%s\"| |\"%s\"|}", p->element,p->element1,p->element2);
    }
}

void displayRelations(HASHTABLE temp){
    int numnodes=0;
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> |\"%s\"|", i,temp[i]->element);
        } else {
            printf("HASH[%d]\t\t-> {|\"%s\"| |\"%s\"| |\"%s\"|}", i,p->element,p->element1,p->element2);
        }
        numnodes=countNodes(p);
        displayCells(p, numnodes);
        printf("\n");
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
    //it works also without else if statement -> in this way:
    // else {bucketInsert(x,y,z,&((*pL)->next));}
    //but book chose the first way
    
}
void insert(ETYPE x, ETYPE y, ETYPE z,HASHTABLE H)
{
    bucketInsert(x,y,z,&(H[h(x)]));
}

// Delete Functions

//if((*pL)->element!=x || (*pL)->element1!=y ||(*pL)->element2!=z){
//still didn't get it that why  above code works it should be '==' and not '!='
//as if it's '!=' doesn't make sense as if it's equal to x,y,or z then we should perform that remove operation
//but if we put '==' it doesn't work, why???

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
    
    printf("\n\tDeleting Some Tuples\n");
    
    delete("1232",  "sala", "omq",  temp);
    delete("3421",  "insa", "ofa",  temp);
    delete("2135",  "icid", "dar",  temp);

    displayRelations(temp);
    
    return 0;
}
