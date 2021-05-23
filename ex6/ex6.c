/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ex6
 ***************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ex6.h"
#include "Utils.h"
#include "queue.h"

#define MAX_NAME 50
#define SIZE_SPACE 3

//a function that gets a Trin_Ari pointer, and returns void
typedef void (*printCommand)(Trin_Ari*);

void freeAll(Trin_Ari* root, printCommand currentPrint);
void failedMalloc (void *current, Trin_Ari* root);
void printMenu();
Trin_Ari* addFamily(Trin_Ari* root);
void addAppointment (Trin_Ari* root);
int checkRoot (Trin_Ari* root);
Trin_Ari* addMember (Trin_Ari* father, Trin_Ari* root);
Trin_Ari* searchTree (Trin_Ari* root, int id);
void printFamTree(Trin_Ari* root);
void printPreOrder(Trin_Ari* root);
void printLeftOrder(Trin_Ari* root);
void printBfsOrder(Trin_Ari* root, printCommand currentPrint);
void printOrder(Trin_Ari* front);
void quarantine(Trin_Ari* root);
void superSpreader (Trin_Ari* root);
void printStay(Trin_Ari* front);
Trin_Ari* vaccine(Trin_Ari* root);
void printSurvive (Trin_Ari* root);

/*********************************************************************************************
 *Function Name: trinAriFamilyTree
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function manages a tree of Trin_Ari family, and enables the user to do A variety of actions,
 *                     by inserting difrrent inputs.
 *********************************************************************************************/
void trinAriFamilyTree(Trin_Ari* root){
    printMenu();
    char option;
    while (1){
        scanf(" %c", &option);
        switch (option){
            case '0' : freeAll(root, printSurvive);
                return;
            case '1' : root=addFamily(root);
                break;
            case '2' : addAppointment (root);
                break;
            case '3' : printFamTree(root);
                break;
            case '4' : quarantine(root);
                break;
            case '5' : superSpreader (root);
                break;
            case '6' : root= vaccine(root);
                break;
            case '7' : printMenu();
                break;
            default :
                printf("Error: unrecognized operation.\n");
        }
        if(option!='7'&&option!='3')
            printf("Select the next operation (insert 7 for the entire menu):\n");
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
    "\t1. Create family.\n"
    "\t2. Add family member.\n"
    "\t3. Print Family-Tree.\n"
    "\t4. Bidud.\n"
    "\t5. Superspreader.\n"
    "\t6. Vaccine.\n"
    "\t7. Print the menu.\n");
}

/*********************************************************************************************
 *Function Name: addFamily
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: Trin_Ari* (pointer to Trin_Ari type)
 * Function Operation: The function creates a new root to a Trin_Ari family tree, if the family does not existes
 *                     yet. If the family already exisets the function will print that the family already
 *                     has been created. The function will return the root of the tree.
 *********************************************************************************************/
Trin_Ari* addFamily(Trin_Ari* root) {
    if (root != NULL)
        printf("The family has already been created\n");
    else
        //the father of the root will be NULL
        root= addMember (NULL,  root);
    return root;
}

/*********************************************************************************************
 *Function Name: addMember
 * Input: Trin_Ari* father (pointer to Trin_Ari type), Trin_Ari* root (pointer to Trin_Ari type)
 * Output: Trin_Ari* (pointer to Trin_Ari type)
 * Function Operation: The function creates a new member in the Trin_Ari family tree, by getting the
 *                     father of the new member, and the root, and adding the new member to the
 *                     tree. If the new member is the root, then the father will be NULL.
 *********************************************************************************************/
Trin_Ari* addMember (Trin_Ari* father, Trin_Ari* root){
    //getting name, and checking if malloc worked
    char* newName =(char *) malloc(MAX_NAME* sizeof(char));
    failedMalloc (newName, root);
    //creating new member, checking if malloc worked
    Trin_Ari* newMember=(Trin_Ari *) malloc(sizeof(Trin_Ari));
    if(newMember==NULL){
        free(newName);
        failedMalloc (newMember, root);
        return NULL;
    }
    newMember->father=father;
    newMember->left=NULL;
    newMember->middle=NULL;
    newMember->right=NULL;
    while (1) {
        printf("enter name\n");
        scanf(" %[^\n]", newName);
        printf("enter ID\n");
        int getId;
        scanf("%d", &getId);
        Trin_Ari * check = searchTree(root, getId);
        //if id belongs to someone
        if (check != NULL) {
            printf("ID %d belongs to %s\n", check->id, check->name);
            continue;
        }
        newMember->name=newName;
        newMember->id=getId;
        printf("Hello %s, ID: %d\n", newMember->name, newMember->id);
        return newMember;
    }
}

/*********************************************************************************************
 *Function Name: addAppointment
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will add a conection between a sertion member to a new one.
 *                     The function will do so by getting the root, asking with who the appointment is
 *                     ment for, checking if the id existses, and if so adding a new member to
 *                     an appointment with the member, by sending the wanted id and root to addMember.
 *                     If there is no room for a nother appointment - the function will print so.
 *********************************************************************************************/
void addAppointment (Trin_Ari* root){
    if (!checkRoot(root))
        return;
    printf("Enter the ID of the person who wants to make an appointment?\n");
    int getId;
    scanf("%d", &getId);
    //wanted will be the wanted member
    Trin_Ari *wanted = searchTree(root, getId);
    if (wanted==NULL){
        printf("There is no ID %d\n",getId);
        return;
    }
     if (wanted->left==NULL) {
         wanted->left=addMember(wanted, root);
         return;
     }
     if (wanted->middle==NULL) {
         wanted->middle=addMember(wanted, root);
         return;
     }
     if (wanted->right==NULL) {
         wanted->right=addMember(wanted, root);
         return;
     }
     printf("%s ID: %d can't meet more than 3 members!\n",wanted->name,wanted->id);
}

/*********************************************************************************************
 *Function Name: searchTree
 * Input: Trin_Ari* root (pointer to Trin_Ari type), int id (valid values int)
 * Output: Trin_Ari* (pointer to Trin_Ari type)
 * Function Operation: The function is a recrusive function that will get the root of the tree
 *                     and the id of a member that is wanted, and will check if the member exists.
 *                     If he does the function will return a pointer to the member. If he does not,
 *                     the functon will return NULL.
 *********************************************************************************************/
Trin_Ari* searchTree (Trin_Ari* root, int id){
    if (root==NULL)
        return NULL;
    if (root->id==id)
        return root;
    Trin_Ari *next=searchTree(root->left, id);
    if (next!=NULL)
        return next;
    next=searchTree(root->middle, id);
    if (next!=NULL)
        return next;
    next=searchTree(root->right, id);
    if (next!=NULL)
        return next;
    return NULL;
}

/*********************************************************************************************
 *Function Name: printFamTree
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function enables the user to do A variety of actions of printing the tree,
 *                     by inserting difrrent inputs.
 *********************************************************************************************/
void printFamTree(Trin_Ari* root){
    char option;
    do {
        printf("Please select an operation:\n"
           "\t0. Return to the main menu.\n"
           "\t1. Print Trin-Ari family.\n"
           "\t2. Print Pre-order.\n"
           "\t3. Print Left-order.\n"
           "\t4. Print BFS.\n");
        scanf(" %c", &option);
        switch (option) {
            case '0' :
                break;
            case '1' :
                print2DUtil(root, SIZE_SPACE);
                break;
            case '2' :
                printPreOrder(root);
                break;
            case '3' :
                printLeftOrder(root);
                break;
            case '4' :
                printBfsOrder(root, printOrder);
                break;
            default :
                printf("Error: unrecognized operation.\n");
        }
    }while (option<'0'||option>'4');
    printMenu();
}

/*********************************************************************************************
 *Function Name: printPreOrder
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will print the tree in pre order.
 *********************************************************************************************/
void printPreOrder(Trin_Ari* root){
    if (root==NULL)
        return;
    printf("%s ID: %d\n",root->name,root->id);
    printPreOrder(root->left);
    printPreOrder(root->middle);
    printPreOrder(root->right);
}

/*********************************************************************************************
 *Function Name: printLeftOrder
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will print the tree in left order.
 *********************************************************************************************/
void printLeftOrder(Trin_Ari* root){
    if (root==NULL)
        return;
    printLeftOrder(root->left);
    printf("%s ID: %d\n",root->name,root->id);
    printLeftOrder(root->middle);
    printLeftOrder(root->right);
}

/*********************************************************************************************
 *Function Name: printBfsOrder
 * Input: Trin_Ari* root (pointer to Trin_Ari type),
 *        printCommand currentPrint (pointer to a function that gets a Trin_Ari type, and returns void)
 * Output: void
 * Function Operation: The function will print the tree starting from the root that is given in BFS order.
 *                     The function will use a queue to do this, while it will add the tree starting from
 *                     the given root to the queue, and will print the tree, and then destroy the queue.
 *********************************************************************************************/
void printBfsOrder(Trin_Ari* root, printCommand currentPrint){
    if (root == NULL)
        return;
    //useing queue
    Queue* q =createQueue();
    failedMalloc(q, root);
    if(enQueue(q, root)==0)
        failedMalloc(NULL,root);
    if (enQueue(q, root->left)==0)
        failedMalloc(NULL,root);
    if (enQueue(q, root->middle)==0)
        failedMalloc(NULL,root);
    if (enQueue(q, root->right)==0)
        failedMalloc(NULL,root);
    while (!isEmpty(q)) {
        currentPrint(q->front->key);
        deQueue(q);
        if (isEmpty(q))
            break;
        Trin_Ari* currentFront= q->front->key;
        if (enQueue(q, currentFront->left)==0)
            failedMalloc(NULL,root);
        if (enQueue(q, currentFront->middle)==0)
            failedMalloc(NULL,root);
        if (enQueue(q,currentFront->right)==0)
            failedMalloc(NULL,root);
    }
    destroyQueue(q);
}

/*********************************************************************************************
 *Function Name: printOrder
 * Input: Trin_Ari* front (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will print current Trin_Ari types name and id.
 *********************************************************************************************/
void printOrder(Trin_Ari* front){
    printf("%s %d\n",front->name,front->id);
}

/*********************************************************************************************
 *Function Name: quarantine
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will get the id of a suspected member who got the desise.
 *                     The function will then print to all the relavent peaple that they
 *                     should stay home.
 *********************************************************************************************/
void quarantine(Trin_Ari* root) {
    if (!checkRoot(root))
        return;
    printf("Enter the ID of the suspected member\n");
    int getId;
    scanf("%d", &getId);
    Trin_Ari *wanted = searchTree(root, getId);
    if (wanted==NULL){
        printf("ID %d does not exist\n",getId);
        return;
    }
    //printing the people that should stay home
    if (wanted->father != NULL)
        printStay(wanted->father);
    printStay(wanted);
    if (wanted->left != NULL)
        printStay(wanted->left);
    if (wanted->middle != NULL)
        printStay(wanted->middle);
    if (wanted->right != NULL)
        printStay(wanted->right);
}

/*********************************************************************************************
 *Function Name: superSpreader
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will get the id of a suspected Superspreader.
 *                     The function will then print to all the relavent peaple that they
 *                     should stay home, in BFS order, by sending to printBfsOrder function the
 *                     suspected Superspreader, and the printStay function.
 *********************************************************************************************/
void superSpreader (Trin_Ari* root){
    if (!checkRoot(root))
        return;
    printf("Enter the ID of the suspected Superspreader\n");
    int getId;
    scanf("%d", &getId);
    Trin_Ari *wanted = searchTree(root, getId);
    if (wanted==NULL){
        printf("ID %d does not exist\n",getId);
        return;
    }
    //printing father, then people that need to stay
    if (wanted->father!=NULL)
        printStay(wanted->father);
    printBfsOrder(wanted, printStay);
}

/*********************************************************************************************
 *Function Name: printStay
 * Input: Trin_Ari* front (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will print #StayHome! and the current Trin_Ari types name and id.
 *********************************************************************************************/
void printStay(Trin_Ari* front){
    printf("#StayHome! %s %d\n",front->name,front->id);
}

/*********************************************************************************************
 *Function Name: vaccine
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: Trin_Ari* (pointer to Trin_Ari type)
 * Function Operation: The function will ask who got vaccinated, and if the id existst, will
 *                     send the vaccinated person and printSurvive to freeAll function, and then
 *                     will return the root.
 *********************************************************************************************/
Trin_Ari* vaccine(Trin_Ari* root){
    if (!checkRoot(root))
        return root;
    printf("Who got vaccinated (ID)?\n");
    int getId;
    scanf("%d", &getId);
    Trin_Ari *wanted = searchTree(root, getId);
    if (wanted==NULL){
        printf("There is no ID %d\n",getId);
        return root;
    }
    if (root==wanted)
        root=NULL;
    freeAll(wanted, printSurvive);
    return root;
}

/*********************************************************************************************
 *Function Name: checkRoot
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: int (values between 1-0)
 * Function Operation: The function will check if root is NULL. If it is, it will print to
 *                     create a family first and return 0. Else it will return 1.
 *********************************************************************************************/
int checkRoot (Trin_Ari* root) {
    if (root == NULL) {
        printf("Please create the family first\n");
        return 0;
    }
    return 1;
}

/*********************************************************************************************
 *Function Name: freeAll
 * Input: Trin_Ari* root (pointer to Trin_Ari type),
 *        printCommand currentPrint (pointer to a function that gets a Trin_Ari type, and returns void)
 * Output: void
 * Function Operation: The function is a recurse function that will free starting from the root that
 *                     is sent, the Trin_Ari tree, and will print according to the function sent.
 *********************************************************************************************/
void freeAll(Trin_Ari* root, printCommand currentPrint){
    if (root==NULL)
        return;
    freeAll(root->left, currentPrint);
    freeAll(root->middle, currentPrint);
    freeAll(root->right, currentPrint);
    if (currentPrint!=NULL)
        currentPrint(root);
    if (root->father==NULL){
        free(root->name);
        free(root);
        return;
    }
    if(root->father->left!=NULL&&root->father->left->id==root->id)
        root->father->left=NULL;
    if(root->father->middle!=NULL&&root->father->middle->id==root->id)
        root->father->middle=NULL;
    if(root->father->right!=NULL&&root->father->right->id==root->id)
        root->father->right=NULL;
    free(root->name);
    free(root);
}

/*********************************************************************************************
 *Function Name: printSurvive
 * Input: Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: The function will print that the current Trin_Ari types name and id Survived.
 *********************************************************************************************/
void printSurvive (Trin_Ari* root){
    printf("%s ID: %d Survived!\n",root->name,root->id);
}

/*********************************************************************************************
 *Function Name: failedMalloc
 * Input: void *current (a pointer to any type), Trin_Ari* root (pointer to Trin_Ari type)
 * Output: void
 * Function Operation: In case of a failed malloc, the function will print Malloc Failed, and will
 *                     get to the root of the tree that was sent to it, and will sent the root to freeAll
 *                     function, with a pointer to NULL so that freeAll will not print anything.
 *                     The function will the exit the program to show there is a problem with the malloc.
 *********************************************************************************************/
void failedMalloc (void *current, Trin_Ari* root){
    if (current!=NULL)
        return;
    printf("Malloc Failed!\n");
    while (root!=NULL&&root->father!=NULL)
        root=root->father;
    freeAll(root, NULL);
    exit(1);
}
