#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// the tree definition for Secondary index structure

// part 2.1

typedef char ETYPE[32];
#define B 5
#define SIZE_CSG 5

typedef struct tupleCGS* CGSLIST;
 struct tupleCGS {
    char Course[6];
    char Grade[2];
    char StudnetID[20];
    struct tupleCGS *next;
};

typedef CGSLIST HASHTABLE_CSG[SIZE_CSG*6];


typedef struct SNAP *LIST;
struct SNAP {
    ETYPE id;
    ETYPE name;
    ETYPE PhoneNumber;
    ETYPE Address;
    LIST next;
};

typedef LIST HASHTABLE[30];

// Hashing Functions
int h(ETYPE x)
{
    int i, sum;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    return sum % B;
}
int h_CSG(char studentID[20])
{
    int i, sum;
    
    sum = 0;
    for (i = 0; studentID[i] != '\0'; i++)
        sum += studentID[i];
    return sum % SIZE_CSG;
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

LIST bucketInsert(ETYPE x, ETYPE y, ETYPE z, ETYPE W, LIST *pL){
    if ((*pL) == NULL) {
        (*pL) = (LIST) malloc(sizeof(struct SNAP));
        strcpy((*pL)->name, x);
        strcpy((*pL)->id, y);
        strcpy((*pL)->PhoneNumber, z);
        strcpy((*pL)->Address, W);

        (*pL)->next = NULL;
        //        SIinsert(Root, (*pL)->element1, (*pL));
        
    } else if (strcmp((*pL)->id, y)){
        return bucketInsert(x,y,z,W, &((*pL)->next));
    }
    
    return (*pL);
}

typedef struct Node *SINode;
struct Node {
    char* Name; // or depending on the what is decided as the 2nd index
    LIST PointertoList;
    SINode RightNode; // for when we have similar names;
    SINode Lc;
    SINode Rc;
};
//typedef SINode SINodeList[100];


SINode newSINode(char* name, LIST PointertoList){
    SINode temp =  (SINode)malloc(sizeof(struct Node));
    temp->Name = name;
    temp->Lc = temp->Rc = NULL;
    temp->PointertoList = PointertoList;
    return temp;
}

void bucketInsert_CSG(char course[5], char grade[2], char studentid[20], CGSLIST *CSGlist)
{
    if ((*CSGlist) == NULL) {
        (*CSGlist) = (CGSLIST)malloc(sizeof(struct tupleCGS));
        strcpy(((*CSGlist))->Course, course);
        strcpy(((*CSGlist))->Grade, grade);
        strcpy(((*CSGlist))->StudnetID, studentid);
        ((*CSGlist))->next = NULL;
    } else
        bucketInsert_CSG(course,grade,studentid,&((*CSGlist)->next));
    
}
void insert_CSG(char course[5], char grade[2], char studentid[20],HASHTABLE_CSG H)
{
    bucketInsert_CSG(course,grade,studentid,&(H[h_CSG(studentid)]));
}

LIST bucketLookup(ETYPE x, ETYPE y, ETYPE z, ETYPE w, LIST *pL){
    HASHTABLE pLTable; // the return variable table.
    
    if(strcmp((*pL)->id, x)==0)// if the Studnetid is found
    {
        if(strcmp(y, "*")==0 && strcmp(z, "*")==0 && strcmp(w, "*")==0){
            while((*pL) != NULL){
                printf("StudentID: %s |name :%s| PhoneNumber:%s| Address:%s\n", (*pL)->id, (*pL)->name, (*pL)->PhoneNumber, (*pL)->Address);
                bucketInsert(y, x, z, w,&pLTable[0]);
                (*pL)=(*pL)->next;
            }
        }
        else if(strcmp(y, "*")==0 && strcmp(z, "*")==0){
            while((*pL) != NULL){
                printf("StudentID: %s |name :%s| PhoneNumber:%s| Address:%s\n", (*pL)->id, (*pL)->name, (*pL)->PhoneNumber, (*pL)->Address);
                bucketInsert(y, x, z, w,&pLTable[0]);
                (*pL)=(*pL)->next;
            }
        } else if(strcmp(y, "*")==0){
            while( (*pL) != NULL){ // TO DO: check the condition
                if(strcmp((*pL)->PhoneNumber, z)==0){
                    printf("StudentID: %s |name :%s| PhoneNumber:%s| Address:%s\n", (*pL)->id, (*pL)->name, (*pL)->PhoneNumber, (*pL)->Address);
                    bucketInsert(y, x, z, w, &pLTable[0]);
                }
                (*pL)=(*pL)->next;
            }
        } else if(strcmp(z, "*")==0){
            while((*pL) != NULL){
                if(strcmp((*pL)->name, y)==0){
                    printf("StudentID: %s |name :%s| PhoneNumber:%s| Address:%s\n", (*pL)->id, (*pL)->name, (*pL)->PhoneNumber, (*pL)->Address);
                    bucketInsert(x, y, z, w, &pLTable[0]);
                }
                (*pL)=(*pL)->next;
            }
        } else {
            printf("StudentID: %s |name :%s| PhoneNumber:%s| Address:%s\n", (*pL)->id, (*pL)->name, (*pL)->PhoneNumber, (*pL)->Address);
            bucketInsert(y, x, z, w, &pLTable[0]);
        }
        
    } else {
        return bucketLookup(x, y, z, w, &((*pL)->next));
    }
    return pLTable[0];
}

//void lookup_CSG(ETYPE x, ETYPE y, ETYPE z,HASHTABLE_CSG L){
//    bucketLookup_CSG(x,y,z,&(L[h_CSG(x)]));
//
//}

void bucketLookup2(char course[5], char grade[2], char studentID[20], CGSLIST *list){
    
    if(strcmp((*list)->StudnetID, studentID)==0) // if the Studnetid is found
    {
        if(strcmp(course, "*")==0 && strcmp(grade, "*")==0){
            while( (*list) != NULL){
                printf("StudentID: %s |Course :%s| Grade: %s\n", (*list)->StudnetID, (*list)->Course, (*list)->Grade);
                (*list)=(*list)->next;
            }
        } else if(strcmp(grade, "*")==0){
            while( (*list) != NULL){ // TO DO: check the condition
                if(strcmp((*list)->Course, course)==0){
                    printf("StudentID: %s |Course :%s| Grade: %s\n", (*list)->StudnetID, (*list)->Course, (*list)->Grade);
                }
                (*list)=(*list)->next;
            }
        } else if(strcmp(course, "*")==0){
            while((*list) != NULL){
                if(strcmp((*list)->Grade, grade)==0){
                    printf("StudentID: %s |Course :%s| Grade: %s\n", (*list)->StudnetID, (*list)->Course, (*list)->Grade);
                }
                (*list)=(*list)->next;
            }
        } else {
            printf("StudentID: %s |Course :%s| Grade: %s\n", (*list)->StudnetID, (*list)->Course, (*list)->Grade);
        }
        
    } else {
        bucketLookup2(course, grade, studentID, &((*list)->next));
    }
//    return pLTable[0];
}



LIST search(SINode root, char* name){
//    SINodeList tempList;

    if (root == NULL || strcmp(root->Name, name) == 0)
        return root->PointertoList;

    // name characters values are greater than root's Name
    if ( SumOfChars( root->Name)  < SumOfChars(name) ){
        return search(root->Rc, name);
    }

    // name characters values are smaller than root's Name
    else{
    return search(root->Lc, name);
    }
}



SINode SIinsert(SINode Root, char* name, LIST PointertoList){
    // If the SItree is empty, return a new SInode
//    SINode temp = NULL;
    if ( Root == NULL){
          return newSINode(name, PointertoList);
    }
    // Otherwise, recur down the SItree
    else{
        if (SumOfChars(name) < SumOfChars( Root->Name)){
            Root->Lc = SIinsert( Root->Lc, name, PointertoList);
        }
        // This is a special case for when two or more students have the same name
        else if(SumOfChars( Root->Name) == SumOfChars(name)){
             Root->RightNode = SIinsert( Root->RightNode, name, PointertoList);
        }
        else if (SumOfChars(name) > SumOfChars( Root->Name)){
            Root->Rc = SIinsert( Root->Rc, name, PointertoList);
        }
    }

        return Root;
}


//void bucketInsert(ETYPE x, ETYPE y, ETYPE z, LIST *pL){
//    if ((*pL) == NULL) {
//        (*pL) = (LIST) malloc(sizeof(struct CELL));
//        strcpy((*pL)->element, x);
//        strcpy((*pL)->element1, y);
//        strcpy((*pL)->element2, z);
//        (*pL)->next = NULL;
//
////        SIinsert(Root, (*pL)->element1, (*pL));
//
//    } else if (strcmp((*pL)->element, x)){
//        bucketInsert(x,y,z,&((*pL)->next));
//    }

//    return Root;
//}

LIST insert(ETYPE x, ETYPE y, ETYPE z, ETYPE w, HASHTABLE H)
{
    return bucketInsert(x,y,z,w,&(H[h(y)]));
}

void StudentGradeQuery(char* name, char* course, HASHTABLE_CSG CSG, HASHTABLE H, SINode Root){
    LIST P = (LIST)malloc(sizeof(LIST));
    strcpy(P->id, "*");
    strcpy(P->name, name);
    strcpy(P->PhoneNumber,"*");
    strcpy(P->Address, "*");
    P->next = NULL;
    
    LIST temp = search(Root, name);
    
    temp  = bucketLookup(temp->id, temp->name, temp->PhoneNumber, temp->Address ,&(H[h(temp->id)]));
    bucketLookup2(course, "*", temp->id, &(CSG[h_CSG(temp->id)]));
    
//    temp = search((*Root), element1);
//    printf("%s\n", temp->Name);

//    bucketLookup(P->element, temp->Name,P->element2 , &P) ;
    
}



int main(int argc, const char * argv[]) {
    
    SINode Root = NULL;
    HASHTABLE H;
    HASHTABLE_CSG CSG;
    
    insert_CSG("csc10", "A", "4555252", CSG);
    insert_CSG("csc11", "B", "111111", CSG);
    insert_CSG("csc11", "C", "8141232", CSG);

    
    Root = SIinsert(Root, "Islom", insert("Islom", "4555252", "0123143", "malo street", H));
    SIinsert(Root, "Islam", insert("Islam", "111111", "0132444" ,"hobb distrect", H));
    SIinsert(Root, "Ahmad",  insert("Ahmad", "8141232", "0123332","herk hotel", H));
    SIinsert(Root, "Abdullah",  insert("Abdullah", "3999183", "0123453","wow street", H));

//    insert("Sayari", "111112", "y", H);
    
    // change the name and the course for it to work
    StudentGradeQuery("Islam", "csc11", CSG, H, Root);


    return 0;
}

