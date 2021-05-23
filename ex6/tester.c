//
// Created by shira goren on 03/01/2021.
//

//**********************************************************************************************************
//     את השורות האלו יש להעתיק למיין המרכזי שלכם,למעלה לפני כל שאר המימוש שלכם,
//    כמובן שיש לשנות את הקלט הראשון שבפונקציה לpath של הקבצים במחשב שלכם
//
//    freopen("C:\\Users\\97250\\CLionProjects\\bar ilan\\ex6\\input.txt", "r", stdin);
//    freopen("C:\\Users\\97250\\CLionProjects\\bar ilan\\ex6\\output.txt", "w", stdout);
//**********************************************************************************************************

//#include "ex6.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

void compareFiles(FILE *fp1, FILE *fp2)
{
    // fetching character of two file
    // in two variable ch1 and ch2
    char ch1 = getc(fp1);
    char ch2 = getc(fp2);

    // error keeps track of number of errors
    // pos keeps track of position of errors
    // line keeps track of error line
    int error = 0, pos = 0, line = 1;

    // iterate loop till end of file
    while (ch1 != EOF && ch2 != EOF)
    {
        pos++;

        // if both variable encounters new
        // line then line variable is incremented
        // and pos variable is set to 0
        if (((ch1 == '\n')||(ch1 == '\r')))
        {
            while (((ch2 != '\n')&&(ch2 != '\r'))) {
                ch2++;
            }
            line++;
            pos = 0;
        }else if (((ch2 == '\n')||(ch2 == '\r'))){
            while (((ch1 != '\n')&&(ch1 != '\r'))){
                ch1++;
            }
            line++;
            pos = 0;
        }

        // if fetched data is not equal then
        // error is incremented
        if (ch1 != ch2)
        {
            error++;
            printf("Line Number : %d \tError"
                   " Position : %d\tExpected: %c\t Got: %c \n", line, pos, ch2, ch1);
        }

        // fetching character until end of file
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }

    printf("Total Errors : %d\t", error);
}


int main() {
    // opening both file in read only mode
    FILE *fp1 = fopen("C:\\Users\\Toshiba\\CLionProjects\\untitled\\output.txt", "r");
    FILE *fp2 = fopen("C:\\Users\\Toshiba\\CLionProjects\\untitled\\expected.txt", "r");

    if (fp1 == NULL || fp2 == NULL)
    {
        printf("Error : Files not open");
        exit(0);
    }

    compareFiles(fp1, fp2);

    // closing both file
    fclose(fp1);
    fclose(fp2);
    return 0;
}




