//
//  main.c
//  Part 2
//
//  Created by Abdullah Alsayari on 11/23/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <stdio.h>

// the tree definition for Secondary index structure

typedef char ETYPE[32];
#define B 5

typedef struct tupleCGS {
    char Course[5];
    char Grade[2];
    int StudnetID;
    struct tupleCGS *next;
}CGSLIST;

typedef struct CELL *LIST;
struct CELL {
    ETYPE element;
    ETYPE element1;
    ETYPE element2;
    LIST next;
};

typedef LIST HASHTABLE[30];

// Hashing Function
int h(ETYPE x)
{
    int i, sum;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    return sum % B;
}

int SumOfChars(char* string){
    int Sum = 0;
    int i=0;
    //    int size = strlen(string);
    //    printf("the size of %s is %d\n", string, strlen(string));
    while(string[i] != '\0'){
        Sum = Sum + string[i];
        //        string++;
        i++;
    }
    return Sum;
}


typedef struct Node *SITree;
struct Node {
    char* Name; // or depending on the what is decided as the 2nd index
    LIST PointertoList;
    SITree Next;
    SITree Lc;
    SITree Rc;
};
typedef SITree SINodeList[100];


SITree newSINode(char* name, LIST PointertoList){
    SITree temp =  (SITree )malloc(sizeof(struct Node));
    temp->Name = name;
    temp->Lc = temp->Rc = NULL;
    temp->PointertoList = PointertoList;
    return temp;
}

void bucketLookup(ETYPE x, ETYPE y, ETYPE z, LIST *pL){
    HASHTABLE* pLTable; // the return variable table.
    
    if(strcmp((*pL)->element, x)==0)// if the Studnetid is found
    {
        if(strcmp(y, "*")==0 && strcmp(z, "*")==0){
            while((*pL) != NULL){
                printf("StudentID: %s |Course :%s| Grade: %s\n", (*pL)->element, (*pL)->element1, (*pL)->element2);
//                pLTable[0]->element = (*pL)->element;
//                pLTable[0]->element1 = (*pL)->element1;
//                pLTable[0]->element2 = (*pL)->element2;
                
                //                pLTable[0]->
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

SITree SIinsert(SITree node, char* name, LIST PointertoList){
    // If the SItree is empty, return a new SInode
    if (node == NULL){
        return newSINode(name, PointertoList);
    }
    // Otherwise, recur down the SItree
    else{
        if (SumOfChars(name) < SumOfChars(node->Name)){
            node->Lc  = SIinsert(node->Lc, name, PointertoList);
        }
        // This is a special case for when two or more students have the same name
        else if(SumOfChars(node->Name) == SumOfChars(name)){
            node->Next = newSINode(name, PointertoList);
        }
        else if (SumOfChars(name) > SumOfChars(node->Name)){
            node->Rc = SIinsert(node->Rc, name, PointertoList);
        }
    }
    
    return node;
}


SITree search(SITree root, char* name){
//    SINodeList tempList;

    if (root == NULL || strcmp(root->Name, name) == 0)
        return root;
    
    // name characters values are greater than root's Name
    if ( SumOfChars(root->Name)  < SumOfChars(name) ){
        return search(root->Rc, name);
    }
    
    // name characters values are smaller than root's Name
    else{
    return search(root->Lc, name);
    }
}

//void insertTree(SITree SecondIndex, char name[30], CGSLIST p){
//    if(SecondIndex == NULL){
//
//    }
//    else{
//        if(SecondIndex->Name > name){
//
//        }
//        else{
//
//        }
//    }
//}



void bucketInsert(ETYPE x, ETYPE y, ETYPE z,LIST *pL, SITree Root)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST) malloc(sizeof(struct CELL));
        strcpy((*pL)->element, x);
        strcpy((*pL)->element1, y);
        strcpy((*pL)->element2, z);
        (*pL)->next = NULL;
        SIinsert(Root, (*pL)->element1, pL);
    } else if (strcmp((*pL)->element, x))
        bucketInsert(x,y,z,&((*pL)->next),Root);
    
}
void insert(ETYPE x, ETYPE y, ETYPE z,HASHTABLE H, SITree Root)
{
    bucketInsert(x,y,z,&(H[h(x)]), Root);
}

void StudentGradeQuery(char* element1, char* course, SITree Root){
    LIST P = (LIST)malloc(sizeof(LIST));
    strcpy(P->element, "*");
    strcpy(P->element1, element1);
    strcpy(P->element2,"*");

    SITree temp;
    
    temp = search(Root, element1);
    
    bucketLookup(P->element, temp->Name,P->element2 , &P) ;
    
}

// updating the secondary index
//void update(){
//
//}

int main(int argc, const char * argv[]) {
    
    SITree Root;
    HASHTABLE H;
    
    insert("Islom", "0121313", "element1", H, Root);
    insert("Islam", "1990021", "hobb", H, Root);
    insert("Ahmad", "8141232", "herk", H, Root);
    insert("Abdullah", "3999183", "wow", H, Root);
    insert("Sayari", "38951993", "y", H, Root);

    
    StudentGradeQuery("Islam", "Jerk", Root);

    return 0;
}

