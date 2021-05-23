/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ex5
 ***************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ex5.h"
#define MAX_CLASS 5
#define MAX_INPUT 200
#define MAX_CLASS_NAME 30
#define MAX_STUDENT_NAME 20
#define MAX_GRADE 3
#define HIGHEST_GRADE 100

struct Student{
    char* name;
    int grade;
};
typedef struct Student Student;

struct StudentList{
    Student* data;
    struct StudentList* next;
};
typedef struct StudentList StudentList;

typedef struct{
    char* numClass;
    char* nameClass;
    StudentList* firstStudent;
}Class;

typedef int (*check)(Class* theClass, char* name);
typedef int (*calculate)(StudentList* theClass);

void freeAll(Class* listClass[]);
void freeClass(StudentList* current);
void printMenu();
void addChangeClass(Class* listClass[]);
int numOfClass(Class* newClass, char classNumName[],Class* listClass[]);
int nameOfClass (Class* newClass, char classNumName[], int index, Class* listClass[]);
int changeClassName(Class* newClass, Class* listClass[]);
void addNewClass(Class* newClass, Class* listClass[]);
int nameStudent(char grades[], char *name);
void checkAddChangeStudent(Class* listClass[]);
int goodCourseNum(int index, char grades[],Class* listClass[]);
int isCourseExsisting(int index, Class* listClass[], char *course);
int goodGrade(int index, char grades[]);
int checkCourse (char grades [], Class* listClass[], int index);
void addChangeGrade(char courseNum[],Class* listClass[], char* name, int theScore);
void getStudentGrade(char grades[], int index, Class* listClass[], char* name);
StudentList* newStudent(Class* theClass, Class* listClass[], char* name, int theScore);
void checkEraseStudent (Class* listClass[]);
int isGoodCourses (int index, char classDelete[],Class* listClass[], char* name,check checker);
int isInCourse (Class* theClass, char* name);
int isInOther(int index, char classDelete[],Class* listClass[], char* name);
int eraseTheStudent (Class* theClass, char* name);
void printCourse (Class* listClass[]);
void printHasStudents (char course[], Class* listClass[]);
StudentList* sortClassNames(StudentList* theClass);
void calculatedClass (Class* listClass[]);
void printCalculatedClass(Class* listClass[],calculate function);
int averageGrade(StudentList* theClass);
int getSum(StudentList* theClass);
int getNumOfStudents(StudentList* theClass);
int getMax(StudentList* theClass);
int getMin(StudentList* theClass);

/*********************************************************************************************
 *Function Name: freeAll
 * Input:  Class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets an array of pointers to class type, and frees the memory,
 *                     by sending evey class to the function free class, and the frees the number
 *                     of the class and the name pf the class.
 *********************************************************************************************/
void freeAll(Class* listClass[]){
    for (int count= 0; count < MAX_CLASS; count++) {
        if (listClass[count]==NULL)
            continue;
        if (listClass[count]->firstStudent!=NULL)
            freeClass(listClass[count]->firstStudent);
        free(listClass[count]->numClass);
        free(listClass[count]->nameClass);
        free(listClass[count]);
    }
}

/*********************************************************************************************
 *Function Name: freeClass
 * Input:  StudentList* current (a pointer to StudentList type)
 * Output: void
 * Function Operation: The function gets a pointer to StudentList type, and frees the memory,
 *                     within the class useing recrision.
 *********************************************************************************************/
void freeClass(StudentList* current){
    if (current->next!=NULL)
        freeClass(current->next);
    free(current->data->name);
    free(current->data);
    free(current);
}

/*********************************************************************************************
 *Function Name: CourseManagementSystem
 * Input:
 * Output: void
 * Function Operation: The function manages course, and enables the user to do A variety of actions,
 *                     by inserting difrrent inputs.
 *********************************************************************************************/
void CourseManagementSystem(){
    char option;
    //an array of pointers to class type
    Class* listClass[MAX_CLASS];
    //boot evry pointer to NULL
    for (int count = 0; count < MAX_CLASS; count++)
        listClass[count]=NULL;
    printMenu();
    while (1){
        scanf(" %c", &option);
        switch (option){
            case '0' : freeAll(listClass);
                return;
            case '1' : addChangeClass(listClass);
                break;
            case '2' : checkAddChangeStudent(listClass);
                break;
            case '3' : checkEraseStudent(listClass);
                break;
            case '4' : printCourse(listClass);
                break;
            case '5' : calculatedClass (listClass);
                break;
            case '6' : printMenu();
                break;
            default :
                printf("Error: unrecognized operation.\n");
        }
        if(option!='6')
            printf("Select the next operation (insert 6 for the entire menu):\n");
    }
}

/*********************************************************************************************
 *Function Name: printMenu
 * Input:
 * Output: void
 * Function Operation: The function prints the menu.
 *********************************************************************************************/
void printMenu(){
    printf("Please select an operation:\n"
           "\t0. Exit.\n"
           "\t1. Insert or update a class.\n"
           "\t2. Insert or update a student.\n"
           "\t3. Remove a student from classes.\n"
           "\t4. Print a class.\n"
           "\t5. Print all classes with their computed scores.\n"
           "\t6. Print the menu.\n");
}

/*********************************************************************************************
 *Function Name: addChangeClass
 * Input: class* listClass[] (array of pointers to class type)
 * Output: void
 * Function Operation: The function adds a class if the class does not yet exisest,
 *                     or changes the name of an exisesting class.
 *********************************************************************************************/
void addChangeClass(Class* listClass[]) {
    //making a new class
    Class *newClass = (Class *) malloc(sizeof(Class));
    if (newClass == NULL) {
        freeAll(listClass);
        exit(1);
    }
    //classNumName will get the users input
    char classNumName[MAX_INPUT]="";
    scanf(" %[^\n]", classNumName);
    //checking if input is valid
    int index= numOfClass(newClass, classNumName,listClass);
    if(index==0) {
        printf("Error: invalid class number or name.\n");
        return;
    }
    if (nameOfClass (newClass, classNumName, index,listClass)==0) {
        printf("Error: invalid class number or name.\n");
        return;
    }
    //checking if class already exists
    if (changeClassName(newClass,listClass))
        return;
    //adding class if new class
    addNewClass( newClass,listClass);
}

/*********************************************************************************************
 *Function Name: numOfClass
 * Input: class* newClass (pointer to Class type), char classNumName[] (array of chars),
 *        class* listClass[] (array of pointers to class type)
 * Output: int (values between MAXCLASS-0)
 * Function Operation: The function gets a pointer to a class type, the input of the user,
 *                     and an array of pointers to class types an checks if the number of class
 *                     that the user submited is valid. If it is, the function will add the number
 *                     of the class to newClass and return the current index.
 *                     If not - it will free the newClass and return 0.
 *********************************************************************************************/
int numOfClass(Class* newClass, char classNumName[],Class* listClass[]) {
    //add number class
    newClass->numClass = (char *) malloc(MAX_CLASS+1 * sizeof(char));
    if (newClass->numClass == NULL) {
            freeAll(listClass);
            exit(1);
    }
    int index=0, flag=0,count=0;
    //skips spaces
    for (;classNumName[index]==' '; index++);
    //gets the number until spaces
    for (;classNumName[index]!=' '; count++, index++) {
        //if class num is good
        if (isdigit(classNumName[index])&&count<MAX_CLASS)
            *(newClass->numClass + count) = classNumName[index];
        else{
            flag=1;
            break;
        }
    }
    if (flag == 1||count!=MAX_CLASS){
        free(newClass->numClass);
        free(newClass);
        return 0;
    }
    *(newClass->numClass + count) = '\0';
    return index;
}

/*********************************************************************************************
 *Function Name: nameOfClass
 * Input: class* newClass (pointer to Class type), char classNumName[] (array of chars),
 *        int index(valid value int), class* listClass[] (array of pointers to Class type)
 * Output: int (values between 1-0)
 * Function Operation: The function gets a pointer to a class type, the input of the user,
 *                     the current index, and an array of pointers to class types an checks if the
 *                     name of class that the user submited is valid. If it is, the function will
 *                     add the name of the class to newClass and return 1.
 *                     If not - it will free the newClass and return 0.
 *********************************************************************************************/
int nameOfClass (Class* newClass, char classNumName[], int index,Class* listClass[]) {
    //add name of class
    newClass->nameClass = (char *) malloc(MAX_CLASS_NAME+1 * sizeof(char));
    if (newClass->nameClass == NULL) {
            freeAll(listClass);
            exit(1);
    }
    int count=0, flag=0;
    for (;classNumName[index]==' '; index++);
    for (;classNumName[index]!='\0'; count++, index++){
        if((isdigit(classNumName[index])||isalpha(classNumName[index])||classNumName[index]==' ')&&count<MAX_CLASS_NAME)
            *(newClass->nameClass + count) = classNumName[index];
        else{
            flag=1;
            break;
        }
    }
    if (flag == 1||count==0){
        free(newClass->numClass);
        free(newClass->nameClass);
        free(newClass);
        return 0;
    }
    *(newClass->nameClass + count) = '\0';
    return 1;
}

/*********************************************************************************************
 *Function Name: changeClassName
 * Input: class* newClass (pointer to Class type), class* listClass[] (array of pointers to Class type)
 * Output: int (values between 1-0)
 * Function Operation: The function gets a pointer to a class type and an array of pointers to class types
 *                     an checks if the number of the class already exists in list class.
 *                     If the name already exists - it will change the class name to the new one,
 *                     free the new class,prints that the name was updated, and return one.
 *                     If the name dose not exsist, it will return 0.
 *********************************************************************************************/
int changeClassName(Class* newClass, Class* listClass[]) {
    for (int count = 0; count < MAX_CLASS; count++) {
        if (listClass[count] == NULL)
            continue;
        if (strcmp(newClass->numClass, listClass[count]->numClass) == 0) {
            char *temp = listClass[count]->nameClass;
            listClass[count]->nameClass = newClass->nameClass;
            free(temp);
            free(newClass->numClass);
            free(newClass);
            printf("Class \"%s %s\" updated.\n", listClass[count]->numClass, listClass[count]->nameClass);
            return 1;
        }
    }
    return 0;
}

/*********************************************************************************************
 *Function Name: addNewClass
 * Input: class* newClass (pointer to Class type), class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets a pointer to a class type and an array of pointers to class types
 *                     and checks if there is room in listClass for a new class. If there is - the function
 *                     will add the new class to list class and print that it was added. If there is no more
 *                     room - the function will print that there is no more room, and free newClass.
 *********************************************************************************************/
void addNewClass(Class* newClass, Class* listClass[]){
    for (int count = 0; count < MAX_CLASS; count++){
        if (listClass[count] == NULL){
            newClass->firstStudent=NULL;
            listClass[count] = newClass;
            printf("Class \"%s %s\" added.\n",newClass->numClass,newClass->nameClass);
            return;
        }
    }
    //incase no room for a new class
    printf("Unfortunately, there is no room for more classes.\n");
    free(newClass->nameClass);
    free(newClass->numClass);
    free(newClass);
}

/*********************************************************************************************
 *Function Name: checkAddChangeStudent
 * Input: class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets an array of pointers to class types and gets an
 *                     input from the user. The function will first check the input is
 *                     valid, by checkin the name, class and grade, and if it is - will
 *                     send the input and the name pf the student to getStudentGrade function.
 *********************************************************************************************/
void checkAddChangeStudent(Class* listClass[]){
    //gets input
    char grades[MAX_INPUT]="";
    scanf(" %[^\n]", grades);
    //makes a new name
    char *name = (char *) malloc(MAX_STUDENT_NAME+1 * sizeof(char));
    if (name == NULL) {
        freeAll(listClass);
        exit(1);
    }
    *name ='\0';
    int index=nameStudent(grades, name);
    if (index==0){
        printf("Error: invalid name, class number or grade.\n");
        return;
    }
    if (checkCourse (grades, listClass, index)==0){
        printf("Error: invalid name, class number or grade.\n");
        free (name);
        return;
    }
    getStudentGrade(grades,index, listClass, name);
    free(name);
}

/*********************************************************************************************
 *Function Name: nameStudent
 * Input: char grades[] (array of chars), char *name (pointer to array of chars)
 * Output: int (values between MAX_STUDENT_NAME-0)
 * Function Operation: The function gets an array of chars and a pointer to a non booted array,
 *                     and adds the name of the student, if valid to the non booted array name.
 *                     if name is valid - the function will return the current index of grades,
 *                     if it is not valid - the function will free name, and return 0.
 *********************************************************************************************/
int nameStudent(char grades[], char *name){
    int index=0, flag=0,count=0 ;
    for (;grades[index]==' '; index++);
    for (;grades[index]!=':'&&grades[index]!='\0'; count++, index++){
        if ((isalpha(grades[index]) || grades[index] == ' ') && count < MAX_STUDENT_NAME)
            *(name+count) = grades[index];
        else{
            flag= 1;
            break;
        }
    }
    if (flag == 1||count==0||grades[index]=='\0'){
        free(name);
        return 0;
    }
    *(name+count) = '\0';
    return index+1;
}

/*********************************************************************************************
 *Function Name: checkCourse
 * Input: char grades[] (array of chars), class* listClass[] (array of pointers to Class type),
 *        int index (values int)
 * Output: int (values between 1-0)
 * Function Operation: The function gets an array of chars, an array of pointers to class types,
 *                     a pointer to a non booted array, and the current index of grades, and checks
 *                     if the number of classes and grade submited are valid, by useing the functions
 *                     goodCourseNum and goodGrade. if the they are valid - the function will return 1,
 *                     if not it will return 0.
 *********************************************************************************************/
int checkCourse (char grades [],Class* listClass[], int index){
    while (index!=0&&grades[index]!='\0') {
        index = goodCourseNum(index, grades, listClass);
        if (index==0||grades[index]=='\0')
            return 0;
        index=goodGrade(index,grades);
        for (; grades[index] == ' '; index++);
    }
        if (index==0)
            return 0;
    return 1;
}

/*********************************************************************************************
 *Function Name: goodCourseNum
 * Input: int index (values int), char grades[] (array of chars),
 *        class* listClass[] (array of pointers to Class type),
 * Output: int (values between MAX_INPUT-0)
 * Function Operation: The function gets an array of chars, an array of pointers to class types
 *                     and the current index of grades, and checks if the number of class is valid.
 *                     If it is, it will send index listClass and grades to the function isCourseExsisting,
 *                     and return the value that is returned from there. If the course number is not valid
 *                     the function will return 0.
 *********************************************************************************************/
int goodCourseNum(int index, char grades[],Class* listClass[]) {
    int flag = 0, count = 0;
    char course[MAX_CLASS+1] = "";
    for (; grades[index] == ' '; index++);
    for (; grades[index] != ',' && grades[index] != '\0'; count++, index++) {
        if (isdigit(grades[index]) && count < MAX_CLASS)
            course[count] = grades[index];
        else{
            flag = 1;
            break;
        }
    }
    if (flag == 1 || count < MAX_CLASS || grades[index] != ',')
        return 0;
    return isCourseExsisting(index, listClass, course);
}

/*********************************************************************************************
 *Function Name: isCourseExsisting
 * Input: int index (values int), char grades[] (array of chars),
 *        class* listClass[] (array of pointers to Class type)
 * Output: int (values between MAX_INPUT-0)
 * Function Operation: The function gets an array of chars, an array of pointers to class types
 *                     and the current index of grades, and checks if the number of class exsists.
 *                     If it does, it will return the current index. If it does not
 *                     the function will return 0.
 *********************************************************************************************/
int isCourseExsisting(int index, Class* listClass[], char *course) {
    int flag=0;
    for (int count = 0; count < MAX_CLASS; count++){
        if (listClass[count]==NULL)
            continue;
        if (strcmp(course, listClass[count]->numClass) == 0) {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        return 0;
    index++;
    return index;
}

/*********************************************************************************************
 *Function Name: goodGrade
 * Input: int index (values int), char grades[] (array of chars)
 * Output: int (values between MAX_INPUT-0)
 * Function Operation: The function gets an array of chars, and the current index of grades,
 *                     and checks if the the grade submited by the user is valid. If it is,
 *                     it will return the current index. If it is not - the function will return 0.
 *********************************************************************************************/
int goodGrade(int index, char grades[]) {
    for (; grades[index] == ' '; index++);
    char number[MAX_GRADE+1] = "";
    int count = 0;
    for (; grades[index] != ';' && count < MAX_GRADE+1; count++, index++) {
        if (isdigit(grades[index]) && count < MAX_GRADE)
            number[count] = grades[index];
        else
            return 0;
    }
    int theNum = atoi(number);
    if (theNum < 0 || theNum > HIGHEST_GRADE || count == 0||grades[index]!=';')
        return 0;
    return index+1;
}

/*********************************************************************************************
 *Function Name: getStudentGrade
 * Input: char grades[] (array of chars), int index (values int),
 *        class* listClass[] (array of pointers to Class type), char *name (pointer to array of chars)
 * Output: void
 * Function Operation: The function gets an array of chars, and the current index of grades,
 *                     an array of pointers to class types and a pointer to an array of chars name,
 *                     and after already checked validity gets the class number and the grade of the
 *                     student in the class, and sends them to addChangeGrade function. If it has
 *                     not reached the end of the array grades, it will make a recursion, and get
 *                     more class numbers and grades until the end of the array grades.
 *********************************************************************************************/
void getStudentGrade(char grades[], int index, Class* listClass[], char* name){
    char course[MAX_CLASS+1]="";
    //get course number
    for (; grades[index] == ' '; index++);
    for (int count = 0; grades[index] != ','; count++, index++)
        course[count] = grades[index];
    index++;
    //get grade in course
    for (; grades[index] == ' '; index++);
    char score[MAX_GRADE+1]="";
    for (int count=0; grades[index] !=';' ; count++, index++)
        score[count]=grades[index];
    index++;
    int theScore= atoi(score);
    addChangeGrade( course, listClass, name, theScore);
    for (; grades[index] == ' '; index++);
    if (grades[index]!='\0')
        getStudentGrade(grades,index,listClass,name);
}

/*********************************************************************************************
 *Function Name: addChangeGrade
 * Input: char course[] (array of chars), Class* listClass[] (array of pointers to Class type),
 *        char *name (pointer to array of chars), int theScore (valid values 0-100)
 * Output: void
 * Function Operation: The function gets an array of chars, an array of pointers to class types,
 *                     a pointer to an array of chars name, and a number between 0-100, and
 *                     checks if the student already exsists in the course. If he does - the function
 *                     will change his grade in that class. If he does not the function will add
 *                     the student to the class with his grade by sending the class, listClass, name
 *                     and theScore to newStudent function, that will be added to the last place in
 *                     the class.
 *********************************************************************************************/
void addChangeGrade(char course[],Class* listClass[], char* name, int theScore){
    int count=0;
    //checking witch class to add student
    for (; count < MAX_CLASS; count++) {
        if (listClass[count]==NULL)
            continue;
        if (strcmp(course, listClass[count]->numClass) == 0)
            break;
    }
    //if no students in class - add student
    if (listClass[count]->firstStudent==NULL){
        listClass[count]->firstStudent=newStudent(listClass[count],listClass,name,theScore);
        return;
    }
    StudentList *next = listClass[count]->firstStudent;
    while (next!= NULL){
        //if student exsist - change his grade
        if (strcmp(name, (next->data->name)) == 0){
            (next->data->grade) = theScore;
            printf("Student \"%s\" updated on class \"%s %s\" with grade %d.\n",
                   name, course,listClass[count]->nameClass, theScore);
            return;
        }
        if (next->next!=NULL)
            next = next->next;
        else
            break;
    }
    //adding new student
    next->next= newStudent(listClass[count],listClass,name,theScore);
}

/*********************************************************************************************
 *Function Name: addChangeGrade
 * Input: Class* theClass (pointers to Class type), Class* listClass[] (array of pointers to Class type),
 *        char *name (pointer to array of chars), int theScore (valid values 0-100)
 * Output: StudentList* (a pointer to StudentList type)
 * Function Operation: The function gets the current class, an array of pointers to class types,
 *                     a pointer to an array of chars name, and a number between 0-100, and will
 *                     make a new student and add in the new student the name and score, and will
 *                     then return a pointer to that studentList.
 *********************************************************************************************/
StudentList* newStudent(Class* theClass, Class* listClass[], char* name, int theScore){
    StudentList* currentStudent;
    currentStudent = (StudentList *) malloc(sizeof(StudentList));
    if (currentStudent==NULL) {
        freeAll(listClass);
        free(name);
        exit(1);
    }
    currentStudent->data = (Student *) malloc(sizeof(Student));
    if (currentStudent->data==NULL) {
        freeAll(listClass);
        free(name);
        exit(1);
    }
    currentStudent->next=NULL;
    char *addName = (char *) malloc(MAX_STUDENT_NAME+1 * sizeof(char));
    if (addName == NULL) {
        freeAll(listClass);
        free(name);
        exit(1);
    }
    strcpy(addName,name);
    currentStudent->data->name = addName;
    currentStudent->data->grade = theScore;
    printf("Student \"%s\" added to class \"%s %s\" with grade %d.\n",
           addName,theClass->numClass,theClass->nameClass,theScore);
    return currentStudent;
}

/*********************************************************************************************
 *Function Name: checkEraseStudent
 * Input: Class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets an array of pointers to Class types and gets an
 *                     input from the user. The function will first check the input is
 *                     valid, by checkin the name and classes, and if it is - will
 *                     send the input and the name of the student to isGoodCourses function,
 *                     with a pointer to eraseTheStudent function, wich will earase the student
 *                     from the classes mentioned.
 *********************************************************************************************/
void checkEraseStudent (Class *listClass[]){
    //getting input
    char classDelete[MAX_INPUT]="";
    scanf(" %[^\n]", classDelete);
    char *name = (char *) malloc(MAX_STUDENT_NAME * sizeof(char));
    if (name==NULL) {
        freeAll(listClass);
        exit(1);
    }
    *name='\0';
    //check if valid name
    int index=nameStudent(classDelete, name);
    if (index==0){
        printf("Error: invalid name or class number.\n");
        return;
    }
    //check if course is valid
    int copyIndex=index;
    while (classDelete[copyIndex]!='\0') {
        copyIndex = goodCourseNum(copyIndex, classDelete, listClass);
        if (copyIndex == 0) {
            printf("Error: invalid name or class number.\n");
            free(name);
            return;
        }
    }
    //checking if student is in courses, and in others
    if (isInOther( index, classDelete, listClass, name)==0){
        free(name);
        return;
    }
    //earasing student from courses
    isGoodCourses(index, classDelete, listClass, name, eraseTheStudent);
    free(name);
}

/*********************************************************************************************
 *Function Name: isGoodCourses
 * Input: int index (valid values>0), char classDelete[](array of chars),
 *        Class* listClass[] (array of pointers to Class type),char *name (pointer to array of chars),
 *        check checker (pointer to a function)
 * Output: int (values between 0-1)
 * Function Operation: The function gets and index, an array of chars, an array of pointers to class types,
 *                     a pointer to an array of chars name, and function that returns an int, and will
 *                     check the whole array classDelete by getting every course number and sending the
 *                     class to the function that was sent, untill the char at the index of classDelete
 *                     is the end of the array. if the function that was sent returns 0 - the function
 *                     will return 0, else it will return 1.
 *********************************************************************************************/
int isGoodCourses (int index, char classDelete[],Class* listClass[], char* name,check checker){
    while (classDelete[index]!='\0'){
        char course[MAX_CLASS+1] = "";
        for (; classDelete[index] == ' '; index++);
        for (int count = 0; classDelete[index] != ','; count++, index++)
            course[count] = classDelete[index];
        index++;
        int count = 0;
        for (; count < MAX_CLASS; count++) {
            if (listClass[count] == NULL)
                continue;
            if (strcmp(course, listClass[count]->numClass) == 0)
                break;
        }
        if (checker(listClass[count], name)==0)
            return 0;
    }
    return 1;
}

/*********************************************************************************************
 *Function Name: isInCourse
 * Input: Class* theClass (pointer to Class type),char *name (pointer to array of chars)
 * Output: int (values between 0-1)
 * Function Operation: The function gets a pointer to a Class and a pointer to an array of chars name
 *                     and will check if the student is in the cores that was given. If he is not, the
 *                     function will print that he is not a member of the course, and will return 0.
 *                     If he is - the function will return 1.
 *********************************************************************************************/
int isInCourse (Class* theClass, char* name){
    //checking if student is in the course
    if (theClass->firstStudent!=NULL){
        StudentList *next = (theClass->firstStudent);
        while (next != NULL){
            if (strcmp(name, (next->data->name)) == 0)
                return 1;
            if (next->next!=NULL)
                next = next->next;
            else
                break;
        }
    }
    printf("Error: student is not a member of class \"%s %s\".\n", theClass->numClass, theClass->nameClass);
    return 0;
}

/*********************************************************************************************
 *Function Name: isInOther
 * Input: int index (valid values>0), char classDelete[](array of chars),
 *        Class* listClass[] (array of pointers to Class type),char *name (pointer to array of chars)
 * Output: int (values between 0-1)
 * Function Operation: The function gets and index, an array of chars, an array of pointers to class types
 *                     and a pointer to an array of chars name and will check if the student is in other
 *                     classes then the classes that the user submited. The function will do this by
 *                     counting the amount of class the student is in, counting the amount of classes
 *                     the user wants to earese the student from, and comparing them. The function
 *                     after checking the student exsists, will send isGoodCourses, as well as the
 *                     other paramators, a pointer to isInCourse function, and after checking that
 *                     the student is in the courses the user submited to delete, will check if
 *                     the student is in other courses. If he is not, the function will print that
 *                     it cant remove the student from all courses, and will return 0. If he is
 *                     the function will return 1.
 *********************************************************************************************/
int isInOther(int index, char classDelete[],Class* listClass[], char* name){
    //compA will be compared with compB, and will indacate if student can be deleted
    int compA=0, compB=0, copyIndex=index;
    while (classDelete[index] != '\0'){
        compA++;
        char course[MAX_CLASS] = "";
        for (; classDelete[index] == ' '; index++);
        //getting class num
        for (int count = 0; classDelete[index] != ','; count++, index++)
            course[count] = classDelete[index];
        index++;
        //checking if the student is in more classes
        for (int count = 0; count<MAX_CLASS; count++){
            if (listClass[count]==NULL)
                continue;
            StudentList *next = (listClass[count]->firstStudent);
            while (next != NULL){
                if (strcmp(name, (next->data->name)) == 0)
                    compB++;
                next = next->next;
            }
        }
    }
    //if student is in no classes
    if (compB==0){
        printf("Error: invalid name or class number.\n");
        return 0;
    }
    //if student is not in the classes mention
    if (isGoodCourses(copyIndex, classDelete, listClass, name, isInCourse)==0)
        return 0;
    //student is in other classes
    if ((compA*compA)<compB)
        return 1;
    //user submited to earase studnt from all classes
    printf("Error: student cannot be removed from all classes.\n");
    return 0;
}

/*********************************************************************************************
 *Function Name: eraseTheStudent
 * Input: Class* theClass (pointer to Class type),char *name (pointer to array of chars)
 * Output: int (values between 0-1)
 * Function Operation: The function gets a pointer to a Class and a pointer to an array of chars name
 *                     and will earase the student from the course that was sent. If the function earased
 *                     the student it will return 1, if not it will return 0.
 *********************************************************************************************/
int eraseTheStudent (Class* theClass, char* name) {
    if (theClass->firstStudent==NULL)
        return 0;
    if (strcmp(name,(theClass->firstStudent->data->name)) == 0){
        printf("Student \"%s\" removed from class \"%s %s\".\n",
               (theClass->firstStudent->data->name),theClass->numClass,theClass->nameClass);
        StudentList *temp=theClass->firstStudent;
        theClass->firstStudent=theClass->firstStudent->next;
        free(temp->data->name);
        free(temp->data);
        free(temp);
        return 1;
    }
    StudentList *next = (theClass->firstStudent);
    while (next->next != NULL) {
        if (strcmp(name, (next->next->data->name)) == 0){
            printf("Student \"%s\" removed from class \"%s %s\".\n",
                   (next->next->data->name),theClass->numClass,theClass->nameClass);
            StudentList *temp = next->next;
            next->next = next->next->next;
            free(temp->data->name);
            free(temp->data);
            free(temp);
            return 1;
        }
        next = next->next;
    }
    return 0;
}

/*********************************************************************************************
 *Function Name: printCourse
 * Input: Class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets an array of pointers to Class types and gets an
 *                     input from the user. The function will first check the input is
 *                     valid, by checking the number of class, and if it is - will
 *                     send the class number and listClass to printHasStudents function, witch
 *                     will print the students in the class.
 *********************************************************************************************/
void printCourse (Class* listClass[]) {
    char input[MAX_INPUT] = "";
    scanf(" %[^\n]", input);
    char course[MAX_CLASS + 1] = "";
    int index = 0;
    //getting class number
    for (; input[index] == ' '; index++);
    for (int count = 0; input[index] != '\0'; count++, index++) {
        if (isdigit(input[index]) && count < MAX_CLASS)
            course[count] = input[index];
        else {
            printf("Error: invalid class number.\n");
            return;
        }
    }
    //checking if class exists
    if (isCourseExsisting(0, listClass, course)==0){
        printf("Error: invalid class number.\n");
        return;
    }
    //printing students
    printHasStudents (course,listClass);
}

/*********************************************************************************************
 *Function Name: printHasStudents
 * Input: char course[] (array of chars), Class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets an array of chars with the number of class and an array
 *                     of pointers to Class types and checks if the course number has student.
 *                     If it does not, the function will print that it has no student. If it does,
 *                     the function will print the students of the class after sending the students
 *                     of the class to the function sortClassNames, that will sort the, in an alfabetical
 *                     order.
 *********************************************************************************************/
void printHasStudents (char course[], Class* listClass[]) {
    int count = 0;
    //getting course
    for (; count < MAX_CLASS; count++) {
        if (listClass[count] != NULL && (strcmp(listClass[count]->numClass, course) == 0))
            break;
    }
    //checking if class is empty
    if (listClass[count]->firstStudent == NULL) {
        printf("Class \"%s %s\" has no students.\n", listClass[count]->numClass, listClass[count]->nameClass);
        return;
    }
    //printing students in class
    printf("Class \"%s %s\" students:\n", listClass[count]->numClass, listClass[count]->nameClass);
    StudentList *next = (listClass[count]->firstStudent);
    while (next->next!=NULL){
        next=sortClassNames(next);
        printf("%s, %d\n",next->data->name,next->data->grade);
        next=next->next;
    }
    printf("%s, %d\n",next->data->name,next->data->grade);
}

/*********************************************************************************************
 *Function Name: sortClassNames
 * Input: StudentList* theClass (pointer to StudentList type)
 * Output: StudentList* (pointer to StudentList type)
 *                     of pointers to Class types and checks if the course number has student.
 * Function Operation: The function gets a pointer to StudentList, and by recrucion goes to the
 *                     end of the list of students, and compares the name of each student with
 *                     the student before him. If the student after the current student is in
 *                     a higher place alphabeticly, the function will switch the two students places
 *                     and will return the higher place student.
 *********************************************************************************************/
StudentList* sortClassNames(StudentList* theClass){
    StudentList *name;
    if (theClass->next!=NULL)
        name=sortClassNames(theClass->next);
    else
        return theClass;
    int compare = strcmp(theClass->data->name,name->data->name);
    if (compare>0){
        Student *temp= theClass->data;
        theClass->data=name->data;
        name->data=temp;
    }
    return theClass;
}

/*********************************************************************************************
 *Function Name: calculatedClass
 * Input: Class* listClass[] (array of pointers to Class type)
 * Output: void
 * Function Operation: The function gets an array of pointers to Class types and then checks if
 *                     there are classes that have been submited. If not, the function will print
 *                     that there are no classes. If there are classes, the function will print a
 *                     menu, with diffrent options to calculate scores or students in class, that
 *                     the user can chose from. The function will then send to printCalculatedClass
 *                     function the function that the users input was ment for.
 *********************************************************************************************/
void calculatedClass (Class* listClass[]){
    int flag=0;
    //checking if there are classes
    for (int count = 0; count < MAX_CLASS; count++) {
        if (listClass[count] != NULL)
            flag = 1;
    }
    if (flag==0){
        printf("Error: there are no classes.\n");
        return;
    }
    //getting option from user
    char option;
    printf("Please select the aggregation method:\n"
           "\ta. Average Grade.\n"
           "\tb. Maximal Grade.\n"
           "\tc. Minimal Grade.\n"
           "\td. Sum.\n"
           "\te. Count.\n"
           "\t0. Return to the main menu.\n");
    scanf(" %c", &option);
    switch (option){
        case '0' :
            return;
        case 'a' : printCalculatedClass(listClass,averageGrade);
            break;
        case 'b' : printCalculatedClass(listClass,getMax);
            break;
        case 'c' : printCalculatedClass(listClass,getMin);
            break;
        case 'd' : printCalculatedClass(listClass,getSum);
            break;
        case 'e' : printCalculatedClass(listClass,getNumOfStudents);
            break;
        default :
            return;
    }
}

/*********************************************************************************************
 *Function Name: printCalculatedClass
 * Input: Class* listClass[] (array of pointers to Class type), calculate function (pointer to a function)
 * Output: void
 * Function Operation: The function gets an array of pointers to Class types and a pointer to a function
 *                     and check evrey class to see if it has students. If it does not, it will print
 *                     that there are no students in the class. If it does, it will print the calculated
 *                     class, acording to the function sent.
 *********************************************************************************************/
void printCalculatedClass(Class* listClass[],calculate function){
    for (int count = 0; count < MAX_CLASS; count++){
        if(listClass[count]==NULL)
            continue;
        //incase there are no students
        if (listClass[count]->firstStudent==NULL){
            printf("Class \"%s %s\" has no students.\n",listClass[count]->numClass,listClass[count]->nameClass);
            continue;
        }
        //printing according to function
        int calculated=function(listClass[count]->firstStudent);
        printf("%s %s, %d\n",listClass[count]->numClass,listClass[count]->nameClass, calculated);
    }
}

/*********************************************************************************************
 *Function Name: averageGrade
 * Input: StudentList* theClass (a pointer to StudentList type)
 * Output: int (values > 0)
 * Function Operation: The function gets a pointer to a list of students, and sends the list
 *                     to getSum function witch get the sum, and devides it by getNumOfStudents
 *                     function witch returns the number of students in the class, and then
 *                     returns the average grade in the class.
 *********************************************************************************************/
int averageGrade(StudentList* theClass){
    return getSum(theClass)/getNumOfStudents(theClass);
}

/*********************************************************************************************
 *Function Name: getSum
 * Input: StudentList* theClass (a pointer to StudentList type)
 * Output: int (values > 0)
 * Function Operation: The function gets a pointer to a list of students, and calculates the sum
 *                     of all grades of students by useing recrocion, and then returns the sum.
 *********************************************************************************************/
int getSum(StudentList* theClass){
    if (theClass->next!=NULL)
        return theClass->data->grade+getSum(theClass->next);
    return theClass->data->grade;
}

/*********************************************************************************************
 *Function Name: getNumOfStudents
 * Input: StudentList* theClass (a pointer to StudentList type)
 * Output: int (values > 0)
 * Function Operation: The function gets a pointer to a list of students, and calculates the amount
 *                     of students by useing recrocion, and then returns the amount.
 *********************************************************************************************/
int getNumOfStudents(StudentList* theClass){
    if (theClass->next!=NULL)
        return 1+getNumOfStudents(theClass->next);
    return 1;
}

/*********************************************************************************************
 *Function Name: getMax
 * Input: StudentList* theClass (a pointer to StudentList type)
 * Output: int (values > 0)
 * Function Operation: The function gets a pointer to a list of students, and calculates the max
 *                     grade of all students by useing recrocion, and then returns the max grade.
 *********************************************************************************************/
int getMax(StudentList* theClass){
    if (theClass->next!=NULL)
        return (getMax(theClass->next) > theClass->data->grade) ?getMax(theClass->next) : theClass->data->grade;
    return theClass->data->grade;
}

/*********************************************************************************************
 *Function Name: getMin
 * Input: StudentList* theClass (a pointer to StudentList type)
 * Output: int (values > 0)
 * Function Operation: The function gets a pointer to a list of students, and calculates the minimum
 *                     grade of all students by useing recrocion, and then returns the minimum grade.
 *********************************************************************************************/
int getMin(StudentList* theClass) {
    if (theClass->next != NULL)
        return (getMin(theClass->next) < theClass->data->grade) ? getMin(theClass->next) : theClass->data->grade;
    return theClass->data->grade;
}