//
//  HashTable.c
//  Project 4
//
//  Created by Abdullah Alsayari on 11/21/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include "HashTable.h"

typedef struct HashBucket {
    int key;
    int Element;
    struct HashBucket *next;
}HashTabel;

//bucket hashtable[10];

void insert(int size, HashTabel H){
    
}

void search(int element, HashTabel H){
    
}

void showElements(HashTabel H[], int size){
    printf("the table: \n");
    int i;
    for(i = 0; i<size; i++){
        printf("Element: %d \t Key: %d\n", H[i].Element, H[i].key);
    }
}

int main(int argc, const char * argv[]) {
    
    int size = 0;
    printf("insert the size of the hashtable \n");
    scanf("%d",size);
    HashTabel hashtable[size];

    
    printf("print the elements in the hashtabel ");
    int i;
    for(i = 0; i < size; i++){
        int temp = 0;
        scanf("%d", temp);
        hashtable[temp%size].Element = temp;
        hashtable[temp%size].key = temp%size;
    }
    
    showElements(hashtable, size);
    
    return 0;
}
