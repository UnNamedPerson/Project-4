//
//  sql-run.h
//  Project 4
//
//  Created by Zhan Dov on 11/21/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#ifndef sql_run_h
#define sql_run_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashPair{
    char Key;
    int* Pointer;
};

typedef char Etype[35];
char NotFound[30] = "Not Found";
char Found[30] = "Found";

typedef struct tupleCGS {
    char *Course;
    char *Grade;
    int StudnetID;
    struct tupleCGS *next;
} CGSLIST;
typedef CGSLIST *CGSHTable[1009];

//typedef struct tupleCP *CPLIST;
//struct tupleCP{
//    char Course[5] ;
//    char Prerequisite[5];
//    CPLIST next;
//};
//typedef CPLIST CPHTable[1009];
//
//
//typedef struct tupleSNAP *SNAPLIST;
//struct tupleSIDNAP{
//    char Name[20];
//    int ID;
//    char Address[40];
//    int phoneNum;
//    SNAPLIST next;
//};
//typedef SNAPLIST SIDNAPHTable[1009];
//
//
//typedef struct tupleCR *CRLIST;
//
//struct tupleCR{
//    char Course[5] ;
//    char room[20];
//    CRLIST next;
//};
//typedef CRLIST CRHTable[1009];
//
//
//typedef struct tupleCDH *CDHLIST;
//
//struct tupleCDH{
//    char Course[5] ;
//    char Day[2];
//    char Hour[4];
//    CDHLIST next;
//};
//typedef CDHLIST CDHHTable[1009];

#endif /* sql_run_h */
