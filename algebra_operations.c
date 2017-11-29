//
//  main.c
//  Part 3
//
//  Created by Abdullah Alsayari on 11/26/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FileName "File.txt"
#define B 5
int NumLines = 0;
char *word;
int size = 6000;

//void WriteInFile(){
//   FILE *FilePointer = fopen(FileName, "w");
//    int i ;
//    for (i = 0; i<100; i++){
////        printf("loop: %d", i);
////        word = (char *)malloc(6);
////        word = strcat("line",i);
//        fputs("line \n", FilePointer);
////        free(word);
//    }
//    fclose(FilePointer);
//}
//
//int ReadInFile(){
//    FILE *FilePointer = fopen(FileName, "r");
//    if(FilePointer != 0){
//        char ch ;
//        while( (ch = getc(FilePointer)) != EOF ){
//            if(ch == '\n'){
//                NumLines++;
//            }
//        }
//    }
//    else{
//        printf("the file can't be opened or doesn't exist\n");
//    }
//    fclose(FilePointer);
//    return NumLines;
//}



typedef char ETYPE[32];

typedef struct CELL *LIST;
struct CELL {
    ETYPE element;
    ETYPE element1;
    ETYPE element2;
    LIST next;
};

typedef LIST HASHTABLE[B*6];

// Another list to use in Join operation example.
typedef struct CELL2 *LIST2;
struct CELL2 {
    ETYPE element3;
    ETYPE element4;
    ETYPE element1;
    ETYPE element6;
    LIST2 next;
};

typedef LIST2 HASHTABLE2[B*6];



// use these two structs when creating new realations with Join operation (the second struct is the important one).

typedef struct GDB_Data* DataNode;
struct GDB_Data{
    char* Data;
    DataNode NextData;
};

typedef struct GeneralDataBase *GDB;
struct GeneralDataBase{
    ETYPE Name;
//    ETYPE *Data;
//    or could use this
    DataNode Data;
    
    // the number of attributes.
    int length;
    GDB Nextattribute;
};
//typedef GDB GDBTable;


// Hashing Function
int h(ETYPE x)
{
    int i, sum;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    return sum % B;
}

// the stupid primal selection function
// selection operation
void selection(char *attribute, char *Value, LIST *pL[size]){ // the return value should be a tupole of the relation type
    LIST* P = (LIST *)malloc(sizeof(LIST)*size);
    int i;
    
    if(strcmp(attribute, "element") == 0){
        for(i = 0; i < size; i++){
            while( (*pL[i]) != NULL){
                if( strcmp( (*pL[i])->element, Value)== 0 ){
                    strcpy( (*P)->element,  (*pL[i])->element );
                    strcpy( (*P)->element1 , (*pL[i])->element1 );
                    strcpy( (*P)->element2 , (*pL[i])->element2 );
                    // could be replaced with
                    //                    (*P) = (*pL[i])
                    (*P)->next= *(P+1);
                    P++;
                    (*pL[i]) = (*pL[i])->next;
                }
                else{
                    (*pL[i]) = (*pL[i])->next;
                }
            }
        }
    }
    else if(strcmp(attribute, (*P)->element1) == 0){
        for(i = 0; i < size; i++){
            while( (*pL[i]) != NULL){
                if( strcmp( (*pL[i])->element, Value)== 0 ){
                    strcpy( (*P)->element,  (*pL[i])->element );
                    strcpy( (*P)->element1 , (*pL[i])->element1 );
                    strcpy( (*P)->element2 , (*pL[i])->element2 );
                    // could be replaced with
                    //                    (*P) = (*pL[i])
                    (*P)->next= *(P+1);
                    P++;
                    (*pL[i]) = (*pL[i])->next;
                }
                else{
                    (*pL[i]) = (*pL[i])->next;
                }
            }
        }
    }
    else if(strcmp (attribute, (*P)->element2) == 0){
        for(i = 0; i < size; i++){
            while( (*pL[i]) != NULL){
                if( strcmp( (*pL[i])->element, Value)== 0 ){
                    strcpy( (*P)->element,  (*pL[i])->element );
                    strcpy( (*P)->element1 , (*pL[i])->element1 );
                    strcpy( (*P)->element2 , (*pL[i])->element2 );
                    // could be replaced with
                    //                    (*P) = (*pL[i])
                    (*P)->next= *(P+1);
                    P++;
                    (*pL[i]) = (*pL[i])->next;
                }
                else{
                    (*pL[i]) = (*pL[i])->next;
                }
            }
        }
    }
    
}

// Projection operation
void projection(char *Column, HASHTABLE pL){
    HASHTABLE* P = (HASHTABLE *)malloc(sizeof(HASHTABLE)*size);
    int i ;
    if(strcmp(Column, "element") == 0){
        for(i = 0; i < sizeof(HASHTABLE); i++){
            while(pL[i] != NULL){
                printf("%s \n", pL[i]->element);
                pL[i]=pL[i]->next;
            }
        }
    }
    
    else if(strcmp(Column, "element1") == 0){
    }
    
    else if(strcmp(Column, "element2") == 0){
    }
    
}

GDB CreateNewList(LIST tuple1, LIST2 tuple2){
    GDB temp = (GDB)malloc(sizeof(GDB));
    temp->length;// what to do now!!!
    temp->Nextattribute;
    temp->Data;
    temp->Name;
}

// join operation
void Join(HASHTABLE relation1, HASHTABLE2 relation2, char* attribute){
//    not sure if we need a table for join, but I think we do
//    GDBTable joinTable;
    GDB GeneralList = (GDB)malloc(sizeof(GDB));
    
    if(strcmp(attribute, "element1") == 0){
        int i, j;
        for(i = 0; i< sizeof(relation1); i++){
            for(j = 0; j< sizeof(relation2); j++ ){
                if(strcmp(relation1[i]->element1, relation2[j]->element1) == 0){ // if the two tuple equal
                    
                    
                }
            }
        }
    }
    
}

int SumOfString(char* string){
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

int main(int argc, const char * argv[]) {
    
    //    WriteInFile();
    //    printf("%d \n", ReadInFile());
    
    
    char* name;
    name = "1234";
    char* name1;
    name1 = "4321";
    //    char* name2;
    //    name2 = "Islom";
    
    //    printf("%d \n",*name);
    //    printf("%d \n",*name1);
    int  nameint = SumOfString(name);
    int  name1int = SumOfString(name1);
    
    // test for sumofstring function
    
    if(nameint > name1int){
        printf("name is bigger than name1\n");
        printf("the value of the nameint is %d\n", nameint);
        printf("the value of the nameint1 is %d\n", name1int);
        
    }
    else if (nameint < name1int){
        printf("name1 is bigger than name\n");
        printf("the value of the nameint is %d\n", nameint);
        printf("the value of the nameint1 is %d\n", name1int);
    }
    else{
        printf("they are equal \n");
    }
    
    return 0;
}
