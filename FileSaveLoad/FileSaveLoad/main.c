//
//  main.c
//  FileSaveLoad
//
//  Created by Abdullah Alsayari on 11/23/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//

#include <stdio.h>

typedef char ETYPE[32];
char word1[100];
//char word2[100];
//char word3[100];

typedef struct CELL *LIST;
struct CELL {
    ETYPE element;
    ETYPE element1;
    ETYPE element2;
    LIST next;
};
char ch;

LIST list;

void LoadFile(char FileName[40]){
    FILE *FilePointer = fopen(FileName, "r");
    
    while ((ch = getc(FilePointer)) != EOF){
        int wordCounter = 0;
        int i;
        
        while(ch != '\n'){
            for(i = 0; ch != ' ' ; i++){
                word1[i] = ch;
            }
            if(wordCounter == 0){
                strcpy(list->element, word1);
                strcpy(word1, "");
                wordCounter++;
                continue;
            }
            else if(wordCounter == 1){
                strcpy(list->element1, word1);
                strcpy(word1, "");
                wordCounter++;
                continue;
            }
            else if(wordCounter == 2){
                strcpy(list->element2, word1);
                strcpy(word1, "");
                wordCounter++;
                continue;
            }
        }
        // need to insert the words in the relation
        
    }
    
}

int main(){
    FILE *filePointer;
    char filename[100];
    char ch;
    int linecount, wordcount, charcount;
    
    // Initialize counter variables
    linecount = 0;
    wordcount = 0;
    charcount = 0;
    
    // Prompt user to enter filename
    printf("Enter a filename :");
    gets(filename);
    
    // Open file in read-only mode
    filePointer = fopen(filename,"r");
    
    // If file opened successfully, then write the string to file
    if (filePointer != 0){
        //Repeat until End Of File character is reached.
        while ( (ch = getc(filePointer)) != EOF) {
            // Increment character count if NOT new line or space
//            if (ch != ' ' && ch != '\n') {
//                ++charcount;
//            }
//
//            // Increment word count if new line or space character
//            if (ch == ' ' || ch == '\n') {
//                ++wordcount;
//            }
            
            // Increment line count if new line character
            if (ch == '\n') {
                ++linecount;
            }
            
        }
        
        if (charcount > 0) {
            ++linecount;
            ++wordcount;
        }
    }
    else{
        printf("Failed to open the file\n");
    }
    
    printf("Lines : %d \n", linecount);
    printf("Words : %d \n", wordcount);
    printf("Characters : %d \n", charcount);
    
    getchar();
    return(0);
}
