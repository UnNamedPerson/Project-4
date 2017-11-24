//
//  main.c
//  Project 4
//
//  Created by Abdullah Alsayari on 11/8/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

// DECLARATIONS AND SETUPS

#include <stdio.h>
#include <string.h>

struct HashPair{
    char Key;
    int* Pointer;
};

typedef char Etype[35];
char NotFound[30] = "Not Found";
char Found[30] = "Found";

// the secondary indext structure
struct SIS{
    
};

// part 3
typedef struct GeneralDataBase{
    char Name[20];
    char* Data;
}GeneralDB;

//typedef struct tupleCGS* CGSLIST;

typedef struct tupleCGS {
    char Course[5];
    char Grade[2];
    int StudnetID;
    struct tupleCGS *next;
}CGSLIST;

typedef CGSLIST *CGSHTable[1009];



// LOOKUP function for CGS Relation (my version)

//char CGSlookup(char course[5], char grade[2], int studnetID, CGSHTable CSG){
//    if(CSG[studnetID % 1009] != NULL){
//        if(CSG[studnetID % 1009]->StudnetID == studnetID){
//            // display the values
//        }
//        else{
//           // go the next tuple in the bucket
//            while (CSG[studnetID%1009]->next != NULL) {
//                if(CSG[studnetID % 1009]->StudnetID == studnetID){
//                    // display the values
//                }
////                CGSlookup(course, grade, studnetID, &CSG[studnetID%1009]);
//            }
//
//        }
//    }
//    return NULL;
//}

// Creating new relation (tuple) for the CGS
CGSLIST* CreateNewRelation(){
    CGSLIST* newCGSRelation = (CGSLIST*)malloc(sizeof(CGSLIST));
    newCGSRelation->next = NULL;
    return newCGSRelation;
}


// insert method for CGS
void CGSinsert(char course[5], char grade[2], int studentID,CGSHTable CSG){
    
    if(CSG[studentID % 1009] != NULL){
        CGSLIST* CGSBucket = CSG[studentID % 1009];
        while(CGSBucket != NULL){
            if(strcmp(CGSBucket->Course, course) && strcmp(CGSBucket->Grade, grade)){ // if both of the attributies matches an existing one
                printf("the tuple already exists");
            }
            else{
                CGSBucket = CGSBucket->next;
            }
        }
        if(CGSBucket == NULL){
            CGSBucket = CreateNewRelation();
            strcpy(course, CSG[studentID % 1009]->Course);
            strcpy(grade, CSG[studentID % 1009]->Grade);
            CGSBucket->StudnetID = studentID;
        }
//        CGSLookup(char *course, char *grade, int studnetID, CGSLIST *CSG)
//        if(){
        
//        }
    }
    else{ // if the bucket is empty
        CSG[studentID % 1009] = CreateNewRelation();
        strcpy(course, CSG[studentID % 1009]->Course);
        strcpy(grade, CSG[studentID % 1009]->Grade);
        CSG[studentID % 1009]->StudnetID = studentID;
    }
}



void *CGSLookup(char course[5], char grade[2], int studnetID, CGSHTable CSG){ // book version of lookup (NOT FINISHED)
    if(CSG == NULL){
        printf("%s", NotFound);
        return NULL;
    }
    if(studnetID == CSG[studnetID%1009]->StudnetID){ // if the Studnetid is found

        if(strcmp(course, "*")){
            if(CSG[studnetID%1009] != NULL){ // TO DO: check the condition
                if(grade == CSG[studnetID%1009]->Grade){
                    printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
                }
                
            }
        }
        else if(strcmp(grade, "*")){
            if(CSG[studnetID%1009] != NULL){
                if(course == CSG[studnetID%1009]->Course){
                    printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
                }
            }
        }
        else if(strcmp(grade, "*") && strcmp(grade, "*")){
            if(CSG != NULL){
                printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
                
            }
        }
        else{
            printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
        }
        
        CGSLookup
    }
    

    // NOT SURE IF WE NEED THIS
//    else{
//        CGSLookup(course, grade, studnetID, &CSG[studnetID%1009]->next);
//    }

}



// delete methode for CGS
void CGSdelete(char course[5], char grade[2], int studnetID, CGSHTable CSG){
    CGSLookup(course, grade, studnetID, CSG);
    
}

typedef struct tupleCP *CPLIST;
struct tupleCP{
    char Course[5] ;
    char Prerequisite[5];
    CPLIST next;
};
typedef CPLIST CPHTable[1009];


typedef struct tupleSNAP *SNAPLIST;
struct tupleSIDNAP{
    char Name[20];
    int ID;
    char Address[40];
    int phoneNum;
    SNAPLIST next;
};
typedef SNAPLIST SIDNAPHTable[1009];


typedef struct tupleCR *CRLIST;

struct tupleCR{
    char Course[5] ;
    char room[20];
    CRLIST next;
};
typedef CRLIST CRHTable[1009];


typedef struct tupleCDH *CDHLIST;

struct tupleCDH{
    char Course[5] ;
    char Day[2];
    char Hour[4];
    CDHLIST next;
};
typedef CDHLIST CDHHTable[1009];

// part one-1


int IndexH(Etype X){
    int i;
    int sum = 0;
    for(i = 0; X[i] != '\0'; i++){
        
        sum += X[i];
    }
    return sum;
}

// part 2

// the tree definition for Secondary index structure

typedef struct Node *SITree;
struct Node {
    char Name[30]; // or depending on the what is decided as the 2nd index
    CGSLIST PointertoCGS;
    SITree Lc;
    SITree Rc;
};

// updating the secondary index
void update(){
    
}


// part 3

void join(){
    
}

// a lookup method for Select
void *CGS_SelectLookup(char course[5], char grade[2], int studnetID, CGSHTable CSG){
    if(CSG == NULL){
        printf("%s", NotFound);
        return NULL;
    }
    if(studnetID == CSG[studnetID%1009]->StudnetID){ // if the Studnetid is found
        
        
        if(){
            printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
        }
        
    }
}

void Select(char attribut[20], char condition[20],char relation[5]){
    if(strcmp(relation, "CGS")){
        // do a lookup on the CGS relation
    }
    else if(strcmp(relation, "CP")){
        
    }
    else if(strcmp(relation, "CDH")){
        
    }
    else if(strcmp(relation, "SNAP")){
        
    }
    else if(strcmp(relation, "CR")){
        
    }
}




int main(int argc, const char * argv[]) {
    printf("the value of \"NotFound\" is %s /n", NotFound);
    return 0;
}
