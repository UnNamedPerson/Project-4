// WORKS SNAP
//  notepad_1.c
//  Project 4
//
//  Created by Zhan Dov on 11/28/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_SNAP 5

typedef char ETYPE[32];

typedef struct CELL_SNAP *LIST_SNAP;

struct CELL_SNAP {
    ETYPE studentID;
    ETYPE name;
    ETYPE address;
    ETYPE phone;
    LIST_SNAP next;
};

typedef LIST_SNAP HASHTABLE_SNAP[SIZE_SNAP*6];

int h_SNAP(ETYPE x);
void displayRelations_SNAP(HASHTABLE_SNAP temp);
void bucketInsert_SNAP(ETYPE x, ETYPE y, ETYPE z, ETYPE k,LIST_SNAP *pL);
void insert_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k, HASHTABLE_SNAP H);
void bucketDelete_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,LIST_SNAP *pL);
void delete_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,HASHTABLE_SNAP S);
void bucketLookup_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,LIST_SNAP *pL);
void lookup_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,HASHTABLE_SNAP L);
void saveDatabase_SNAP(HASHTABLE_SNAP temp, char *new_name);
void loadDatabase_SNAP(char *filename, HASHTABLE_SNAP temp);

int main(int argc, const char * argv[]) {
    HASHTABLE_SNAP temp;
    char *name_of_database = "database_SNAP.txt";
    
    //inserts into the database
    printf("Inserting Database\n\n");
    insert_SNAP("12345",  "C.Brown",    "12AppleSt.",    "555-1234",  temp);
    insert_SNAP("67890",  "L.VanPelt",  "34PearAve.",    "555-5678",  temp);
    insert_SNAP("22222",  "P.Patty",    "56GrapeBlvd.",  "555-9999",  temp);


    //saves the database
    saveDatabase_SNAP(temp,name_of_database);
    
    /*** Before Testing Make Sure To Comment Out saveDatabase_CSG(temp,name_of_database) & insert functions ***/
    /*** As while loading it will duplicate the database ***/
    /*** Try to comment out saveDatabase_CSG() & insert functions and test loadDatabase(). Thanks. ***/
    //loads the database
    //loadDatabase_SNAP(name_of_database, temp);

    //deletes some tuples
    printf("Deleting Tuples\n\n");
    delete_SNAP("67890",  "L.VanPelt",  "34PearAve.",    "555-5678",  temp);
    
    //lookups some tuples
    
    lookup_SNAP("12345",  "C.Brown",    "*",    "555-1234",  temp);
    lookup_SNAP("22222",  "*",          "*",    "*",         temp);
    
    return 0;
}

int h_SNAP(ETYPE x)
{
    int i, sum, result=0;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    result = sum % SIZE_SNAP;
    //    printf("sum is %d mode %d is %d\n", sum, SIZE_CSG, result);
    return result;
}

// Insert Functions
void bucketInsert_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,LIST_SNAP *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST_SNAP)malloc(sizeof(struct CELL_SNAP));
        strcpy((*pL)->studentID, x);
        strcpy((*pL)->name, y);
        strcpy((*pL)->address, z);
        strcpy((*pL)->phone, k);
        (*pL)->next = NULL;
    } else
        bucketInsert_SNAP(x,y,z,k,&((*pL)->next));
    
}
void insert_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,HASHTABLE_SNAP H)
{
    bucketInsert_SNAP(x,y,z,k,&(H[h_SNAP(x)]));
}

// Delete Functions

void bucketDelete_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,LIST_SNAP *pL)
{
    if ((*pL) != NULL) {
        if(strcmp((*pL)->studentID, x)==0 && strcmp((*pL)->name, y)==0 && strcmp((*pL)->address, z)==0 && strcmp((*pL)->phone, k)==0){
            (*pL)=(*pL)->next;
        } else {
            bucketDelete_SNAP(x, y, z, k,&((*pL)->next));
        }
    }
}
void delete_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,HASHTABLE_SNAP S)
{
    bucketDelete_SNAP(x,y,z,k,&(S[h_SNAP(x)]));
}

//Lookup functions
void bucketLookup_SNAP(ETYPE x, ETYPE y, ETYPE z, ETYPE k,LIST_SNAP *pL){
    if ((*pL)==NULL) {
        return;
    }
    else if(strcmp((*pL)->studentID, x)==0)// if x is found
    {
        if(strcmp(y, "*")==0 && strcmp(z, "*")==0 && strcmp(k, "*")==0){
            
            if(strcmp((*pL)->studentID, x)==0){
                printf("StudentID: %s | Name: %s| Address: %s | Phone: %s\n", (*pL)->studentID, (*pL)->name, (*pL)->address, (*pL)->phone);
                bucketLookup_SNAP(x, y, z,k, &((*pL)->next));
            }
        }
        else if(strcmp(y, "*")==0 && strcmp(z, "*")!=0 && strcmp(k, "*")!=0){
            LIST_SNAP temp = (*pL);
            while (temp!=NULL) {
                if(strcmp(temp->address, z)==0 && strcmp((*pL)->studentID, x)==0 && strcmp(y, "*")==0 && strcmp(temp->phone, k)==0){
                    printf("StudentID: %s | Name: %s| Address: %s | Phone: %s\n", temp->studentID, temp->name, temp->address, temp->phone);
                }
                temp=temp->next;
            }
        }
        else if(strcmp(z, "*")==0 && strcmp(y, "*")!=0 && strcmp(k, "*")!=0 ){
            LIST_SNAP temp = (*pL);
            while (temp!=NULL) {
                if(strcmp((*pL)->name, y)==0 && strcmp((*pL)->studentID, x)==0 && strcmp(z, "*")==0 && strcmp((*pL)->phone, k)==0){
                    printf("StudentID: %s | Name: %s| Address: %s | Phone: %s\n", temp->studentID, temp->name, temp->address, temp->phone);
                }
            temp=temp->next;
        }
        }
        else if(strcmp(k, "*")==0 && strcmp(y, "*")!=0 && strcmp(z, "*")!=0 ){
            LIST_SNAP temp = (*pL);
            while (temp!=NULL) {
                if(strcmp(temp->name, y)==0 && strcmp((*pL)->studentID, x)==0 && strcmp(temp->address, z)==0 && strcmp(k, "*")==0){
                    printf("StudentID: %s | Name: %s| Address: %s | Phone: %s\n", temp->studentID, temp->name, temp->address, temp->phone);
                }
                temp=temp->next;
            }
           
        }
    }
}


void lookup_SNAP(ETYPE x, ETYPE y, ETYPE z,ETYPE k,HASHTABLE_SNAP L){
    bucketLookup_SNAP(x,y,z,k,&(L[h_SNAP(x)]));
    
}

void saveDatabase_SNAP(HASHTABLE_SNAP temp, char *new_name){
    // create a FILE typed pointer
    FILE *file_pointer;
    
    // open/create the txt file for saving the database
    file_pointer = fopen(new_name,"w+");
    
    // write to the file
    LIST_SNAP p;
    for (int i = 0; i<SIZE_SNAP; i++) {
        p=temp[i];
        while (p!=NULL) {
            fprintf(file_pointer,"%s\t%s\t%s\t%s\n",p->studentID,p->name,p->address, p->phone);
            p=p->next;
        }
    }
    // Close the file
    fclose(file_pointer);
    printf("Database is saved\n\n");
}

void loadDatabase_SNAP(char *filename, HASHTABLE_SNAP temp)
{
    // loads the database
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) return;
    
    while(!feof(fp))
    {
        char x[32],y[32],z[32],k[32];
        fscanf(fp, "%s\t%s\t%s\t%s\n", x,y,z,k);
        insert_SNAP(x, y, z, k,temp);
    }
    fclose(fp);
    printf("Database is loaded\n\n");
    return;
}

void displayRelations_SNAP(HASHTABLE_SNAP temp){
    printf("\n");
    printf("Hash Table\t\tLists\n");
    LIST_SNAP p;
    for (int i = 0; i<5; i++) {
        p=temp[i];
        if (p==NULL) {
            printf("HASH[%d]\t\t-> {|\"%s\"|}\n", i,temp[i]->studentID);
        } else {
            printf("HASH[%d]\t", i);
            while (p!=NULL) {
                printf("\t-> {|\"%s\"| |\"%s\"| |\"%s\"||\"%s\"|}", p->studentID,p->name,p->address,p->phone);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

