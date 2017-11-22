//
//  main.c
//  Project 4
//
//  Created by Abdullah Alsayari on 11/8/17.
//  Copyright © 2017 Abdullah Alsayari. All rights reserved.
//
#include "sql-run.h"

//// Creating new relation (tuple) for the CGS
//CGSLIST* CreateNewRelation(){
//    CGSLIST* CGS_new = (CGSLIST*)malloc(sizeof(CGSLIST));
//    CGS_new->next = NULL;
//    //sets by default to 0;
//    CGS_new->Grade = "0";
//    CGS_new->Course = "0";
//    CGS_new->StudnetID = 0;
//    return CGS_new;
//}

int h(char * x)
{
    int i, sum;
    
    sum = 0;
    for (i = 0; x[i] != '\0'; i++)
        sum += x[i];
    return sum % B;
}

void bucketInsert(char *x_course, LIST *pL)
{
    if ((*pL) == NULL) {
        (*pL) = (LIST) malloc(sizeof(struct CGS_CELL));
        strcpy((*pL)->Course, x_course);
        (*pL)->next = NULL;
    }
    else if (strcmp((*pL)->Course, x_course)) /* x and element
                                         are different */
        bucketInsert(x_course, &((*pL)->next));
}

void insert(char * x, HASHTABLE H)
{
    bucketInsert(x, &(H[h(x)]));
}





//
//// insert method for CGS
//void CGSinsert(char course[5], char grade[2], int studentID,CGSHTable CSG)
//{
//    if(CSG[studentID % 1009] != NULL)
//    {
//        CGSLIST* CGSBucket = CSG[studentID % 1009];
//        while(CGSBucket != NULL)
//        {
//            if(strcmp(CGSBucket->Course, course) && strcmp(CGSBucket->Grade, grade))
//            { // if both of the attributies matches an existing one
//                printf("the tuple already exists");
//            }
//            else
//            {
//                CGSBucket = CGSBucket->next;
//            }
//        }
//        if(CGSBucket == NULL)
//        {
//            CGSBucket = CreateNewRelation();
//            strcpy(course, CSG[studentID % 1009]->Course);
//            strcpy(grade, CSG[studentID % 1009]->Grade);
//            CGSBucket->StudnetID = studentID;
//        }
//    }
//    else
//    { // if the bucket is empty
//        CSG[studentID % 1009] = CreateNewRelation();
//        strcpy(course, CSG[studentID % 1009]->Course);
//        strcpy(grade, CSG[studentID % 1009]->Grade);
//        CSG[studentID % 1009]->StudnetID = studentID;
//    }
//}

int main(int argc, const char * argv[]) {
    
//    CGSLIST *temp;
//    temp = CreateNewRelation();

    return 0;
}

/*
void *CGSLookup(char course[5], char grade[2], int studnetID, CGSHTable CSG){
    if(CSG == NULL)
    {
        printf("%s", NotFound);
        return NULL;
    }
    else
    {
        if(studnetID == CSG[studnetID%1009]->StudnetID)
        {
            if(strcmp(course, "*"))
            {
                while(CSG[studnetID%1009] != NULL)
                { // TO DO: check the condition
                    if(grade == CSG[studnetID%1009]->Grade)
                    {
                        printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
                    }
                }
            }
            else if(strcmp(grade, "*"))
            {
                while(CSG[studnetID%1009] != NULL)
                {
                    if(course == CSG[studnetID%1009]->Course)
                    {
                        printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
                    }
                }
            }
            else if(strcmp(grade, "*") && strcmp(grade, "*"))
            {
                while(CSG != NULL)
                {
                    printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
                }
            }
            else
            {
                printf("StudentID: %d |Course :%s| Grade: %s", CSG[studnetID%1009]->StudnetID, CSG[studnetID%1009]->Course, CSG[studnetID%1009]->Grade);
            }
            
        }
    }
    // NOT SURE IF WE NEED THIS
    //    else{
    //        CGSLookup(course, grade, studnetID, &CSG[studnetID%1009]->next);
    //    }
    return 0;
}
*/
