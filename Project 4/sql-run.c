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

int h(ETYPE x)
{
    int i, sum;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    return sum % B;
}

void bucketInsert(ETYPE x, ETYPE y, ETYPE z,LIST *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST) malloc(sizeof(struct CELL));
        strcpy((*pL)->element, x);
        strcpy((*pL)->element1, y);
        strcpy((*pL)->element2, z);
        (*pL)->next = NULL;
    }
    else
        bucketInsert(x,y,z,&((*pL)->next));
}

void insert(ETYPE x, ETYPE y, ETYPE z,HASHTABLE H)
{
    bucketInsert(x,y,z,&(H[h(x)]));
}
int countNodes(LIST start){
    
    LIST p;
    int i = 0;
    if (start == NULL){
        //printf("As nodes are 0, the list is empty\n");
        return 0;
    }
    p=start;
    while (p!=NULL){ i++; p=p->next;}
    return i;
}
void displayCells(LIST start, int numnodes){
    
    LIST p = start;
    for (int i = 0; i<(numnodes-1); i++) {
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

int main(int argc, const char * argv[]) {
    HASHTABLE temp;
    
    insert("anyone",    "any",   "one",  temp);
    insert("lived",     "live",  "ed",   temp);
    insert("in",        "icida", "dar",  temp);
    insert("a",         "sal",   "om",   temp);
    insert("pretty",    "ch",    "royli",temp);
    insert("how",       "ins",   "of",   temp);
    insert("town",      "iy",    "mon",  temp);
    
    displayRelations(temp);
    
    return 0;
}

