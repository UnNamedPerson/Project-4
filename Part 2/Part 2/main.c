//
//  main.c
//  Part 2
//
//  Created by Abdullah Alsayari on 11/23/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <stdio.h>

// the tree definition for Secondary index structure

typedef struct tupleCGS {
    char Course[5];
    char Grade[2];
    int StudnetID;
    struct tupleCGS *next;
}CGSLIST;

typedef struct Node *SITree;
struct Node {
    char Name[30]; // or depending on the what is decided as the 2nd index
    CGSLIST PointertoCGS;
    SITree Lc;
    SITree Rc;
};

void insertTree(SITree SecondIndex, char name[30], CGSLIST p){
    if(SecondIndex == NULL){
        
    }
    else{
        if(SecondIndex->Name > name){
            
        }
        else{
            
        }
    }
}

// updating the secondary index
void update(){
    
}

int main(int argc, const char * argv[]) {

    return 0;
}

