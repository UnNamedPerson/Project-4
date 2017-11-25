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

// open/create the txt file for saving the database
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

//char ch;
//char word1[32];
//char word2[32];
//char word3[32];
//
//void loadDatabase(HASHTABLE temp){
//    // create a FILE typed pointer
//    FILE *file_pointer;
//
//    // open/create the txt file for reading/loading the database
//    file_pointer = fopen("check_data.txt","r");
//
//    while ((ch = getc(file_pointer)) != EOF){
//        int wordCounter = 0;
//        while(ch != '\n'){
//            char word_loop[32];        //islam \t 123412 \t 234123
//            for(int i = 0; ch != '\t' ; i++){
//                word_loop[i] = ch;
//            }
//            if(wordCounter == 0){
//                strcpy(word1, word_loop);
//                wordCounter++;
//                ++ch;
//            }
//            if(wordCounter == 1){
//                strcpy(word2, word_loop);
//                wordCounter++;
//                ++ch;
//            }
//            if(wordCounter == 2){
//                strcpy(word3, word_loop);
//                insert(word1, word2, word3, temp);
//            }
//        }
//    }
//}



//void loadDatabase(HASHTABLE temp){
//    // create a FILE typed pointer
//    FILE *file_pointer;
//
//    // open/create the txt file for reading/loading the database
//    file_pointer = fopen("check_data.txt","r");
//
//    while ((ch = getc(file_pointer)) != EOF){
//            char word_loop[32];
//            char *x[4];
//            //word_loop = 3321 \t asds \t asw\n
//            for(int i = 0; ch != '\n' ; i++){
//                word_loop[i] = ch;
//            }
//            if (ch=='\n') {
//                char *p;
//                p = strtok(word_loop,"\t");
//                int i = 0;
//                x[0] = p;
//
//                while (strcmp(p,"\n")!=0) {
//                    p = strtok(word_loop,"\t");
//                    i++;
//                    x[i]=p;
//                    insert(x[1], x[2], x[3], temp);
//                }
//
//             }
//        ch++;
//    }
//}


//void loadDatabase(HASHTABLE temp){
//    // create a FILE typed pointer
//    FILE *file_pointer;
//
//    // open/create the txt file for reading/loading the database
//    file_pointer = fopen("check_data.txt","r");
//    char ch;
//    while ((ch = getc(file_pointer)) != EOF){
//
//
//        char str[] = "this, is the string - I want to parse";
//        char delim[] = " ,-";
//        char* token;
//
//        for (token = strtok(str, delim); token; token = strtok(NULL, delim))
//        {
//            printf("token=%s\n", token);
//        }
//
//        char word_loop[32];
//        char *x[4];
//        //word_loop = 3321 \t asds \t asw\n
//        for(int i = 0; ch != '\n' ; i++){
//            word_loop[i] = ch;
//        }
//        if (ch=='\n') {
//            char *p;
//            p = strtok(word_loop,"\t");
//            int i = 0;
//            x[0] = p;
//
//            while (strcmp(p,"\n")!=0) {
//                p = strtok(word_loop,"\t");
//                i++;
//                x[i]=p;
//                insert(x[1], x[2], x[3], temp);
//            }
//
//        }
//        ch++;
//    }
//}

//
//void printData(){
//    char * buffer = 0;
//    long length;
//    FILE * f = fopen ("check_data.txt", "rb");
//
//    if (f)
//    {
//        fseek (f, 0, SEEK_END);
//        length = ftell (f);
//        fseek (f, 0, SEEK_SET);
//        buffer = malloc (length);
//
//        if (buffer)
//        {
//            fread (buffer, 1, length, f);
//        }
//        fclose (f);
//    }
//
//    if (buffer)
//    {
//        printf("%s", buffer);
//    }
//}
void loadDatabase(char *filename, HASHTABLE temp)
{
    // loads the database
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return;
    
    while(!feof(fp))
    {
        char x[32],y[32],z[32];
        fscanf(fp, "%s\t%s\t%s\n", x,y,z);
        insert(x, y, z, temp);
    }
    fclose(fp);
    return;
}

//void parseToTokens(char str[], char delim[]){
//    char* token;
//    int i = 0;
//    printf("The number of lines are %d\n", countlines("check_data.txt"));
//    char *arr[countlines(str)];
//
//    for (token = strtok(str, delim); token; token = strtok(NULL, delim))
//    {
//        arr[i]=token;
//        printf("token %d  is %s\n", i, token);
//        i++;
//    }
//
////    for (int i=0; i<countlines(str); i++) {
////        printf("asdfasfsaf");
//        printf("The array %d is %s\n", i, arr[1]);
////}
//}
////void justTokens(char str[], char delim[]){
////    char * pch;
////    pch = strtok (str,delim);
////    while (pch != NULL)
////    {
////        parseToTokens(pch, "\t");
////        printf ("sente %s\n",pch);
////        pch = strtok (NULL, delim);
////    }
////
////}


//
//void printData(){
//    char * buffer = 0;
//    long length;
//    FILE * f = fopen ("check_data.txt", "rb");
//
//    if (f){
//        fseek (f, 0, SEEK_END);
//        length = ftell (f);
//        fseek (f, 0, SEEK_SET);
//        buffer = malloc (length);
//
//        if (buffer) {
//            fread (buffer, 1, length, f);
//        }
//        fclose (f);
//
//    }
//    if (buffer){
//        printf("TEXT in BUFFER\n");
//        printf("%s", buffer);
//        printf("\n\n");
//        parseToTokens(buffer, "\t\n");
//    }
//}



int main(int argc, const char * argv[]) {
      HASHTABLE temp;
//
//    printf("\n\tInserting Database\n");

//    insert("1234",  "anyd", "one",  temp);
//    insert("5678",  "live", "edw",  temp);
//    insert("2135",  "icid", "dar",  temp);
//    insert("1232",  "sala", "omq",  temp);
//    insert("8784",  "chfd", "roy",  temp);
//    insert("3421",  "insa", "ofa",  temp);
//    insert("4322",  "iyer", "mon",  temp);
    
      loadDatabase("check_data.txt", temp);
      displayRelations(temp);
    
//    loadDatabase(temp);
//
//    displayRelations(temp);
//
//    saveDatabase(temp);
//
//    printf("\n\tDeleting Some Tuples\n");
//
//    delete("3421",  "insa", "ofa",  temp);
//    delete("4322",  "iyer", "mon",  temp);
//
//    displayRelations(temp);
//
//    lookup("8784",  "*", "*",  temp);
//    lookup("2135",  "icid", "*",  temp);
//    lookup("1232",  "*", "omq",  temp);
    
    return 0;
}
