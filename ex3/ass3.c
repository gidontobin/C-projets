/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ass3
 ***************/
#include <stdio.h>
#include "ass3.h"
#define FIRSTINDEX 0
#define QUESTION_MARK '?'
#define ZERO '0'
#define TWO '2'
#define BONUS

int indexNum(int bigNum,int smallNum, char str[]);
void printACombination(char pattern[],int len,int index);
void changeVar(char pattern[],char var,int len,int index);
float powerOf(float firsrtNum, long int secondNum);
int checkThree(long long n, int isThree);
long int getGcd(long int n1, long int n2);
void checkNegative(long int num);
int theCount(long long n, int d);

/*
This global varuble is used to count the number of Combination that are printed in
printAllCombinations function. The use of the global varuble is because it is the
most eficiet way to calculate the number of combinations printed.
*/
int numOf=0;

/*********************************************************************************************
 *Function Name: towerOfHanoi
 * Input: int numDisks (valid values numDisks>0),
 *        char fromRod (valid values fromRod any char),
 *        char toRod (valid values toRod any char),
 *        char auxRod (valid values auxRod any char)
 * Output: void
 * Function Operation: The function is a recursion function that gets the number of disks
 *                     and the names of the rods, and by recursion prints where the user
 *                     should move each disk, by sending the function itself the new destination
 *                     for the coming disk.
 *********************************************************************************************/
void towerOfHanoi(int numDisks, char fromRod, char toRod, char auxRod)
{
    //incase the function has finished, or the numDisks is a wrong value
    if (numDisks<=0)
        return;
    //incase numDisks is valid and bigger then 1
    if (numDisks>1)
    {
        //the function will recurse by sending numDisk-1, and switching auxRod and toRod
        towerOfHanoi(numDisks-1, fromRod,auxRod,toRod);
        //the function will print the current task
        printf("Move disk %d from rod %c to rod %c.\n",numDisks,fromRod,toRod);
        //the function will recurse by sending numDisk-1, and the order of the rods
        towerOfHanoi(numDisks-1,auxRod,toRod, fromRod);
    }
    //incase numDisks is 1
    else
        printf("Move disk %d from rod %c to rod %c.\n",numDisks,fromRod,toRod);
}

/*********************************************************************************************
 *Function Name: isPalindrome
 * Input: char str[](valid values str[] an array of any chars),int len (valid values len>0)
 * Output: void
 * Function Operation: The function checks if an array is a palindrome by sending it to indexNum function.
 *                     If it is, it will print : The reverse of the "array" is also the "array".
 *                     If it is not, it will print : The reverse of the "array" is not the "array".
 *********************************************************************************************/
void isPalindrome(char str[],int len)
{
    printf("The reverse of ");
    printf(str);
    //checking the array is a palindrome
    if (indexNum(len-1,FIRSTINDEX, str)==0)
        printf(" is also ");
    else
        printf(" is not ");
    printf(str);
    printf(".\n");
}

/*********************************************************************************************
 *Function Name: indexNum
 * Input: int bigNum (valid values bigNum>0),int smallNum (valid values smallNum>0),
 *        char str[](valid values str[] an array of any chars)
 * Output: int (values between 0-1)
 * Function Operation: The function is a recursion function that gets from
 *                     isPalindrome the first and last index of the array str[] and checks every char
 *                     to see if it the same as the palindrome one.
 *                     If it is, the function will return 0 to isPalindrome function,
 *                     to indicate the word is a palindrome.
 *                     If it is not, the function will return 1 to isPalindrome function,
 *                     to indicate the word is not a palindrome.
 *********************************************************************************************/
int indexNum(int bigNum,int smallNum, char str[])
{
    //flag will indacate if the array is a palindrome
    int flag=0;
    //checking to see if the function has checked all chars of the array
    if(bigNum<=smallNum)
        return flag;
    //if at one point a certion char is not the same as the other
    if (str[bigNum]!=str[smallNum])
        return flag+1;
    //if the char are similar, move on to the next pair of chars
    return indexNum(bigNum-1,smallNum+1,str);
}

/*********************************************************************************************
 *Function Name: printAllCombinations
 * Input: char pattern[](valid values pattern[] an array of chars '0','1','2','?'),
 *        int len (valid values len>0)
 * Output: void
 * Function Operation: The function sends the array 'pattern', the length of the array,
 *                     and the first index, to printACombination function,
 *                     that prints all the Combinations of numbers, from smallest to biggest,
 *                     that can be made by switching the char '?' to '1','2','0'.
 *                     The function also prints the number of Combinations,
 *                     by printing the global int numOf, the counts the amount of Combinations
 *                     that have been printed in printACombination.
 *********************************************************************************************/
void printAllCombinations(char pattern[],int len)
{
    //before every use of the function, make the value of the global in numOf to be 0
    numOf=0;
    //sending the array, the length of the array and the first index of the array to printACombination
    printACombination(pattern,len,FIRSTINDEX);
    //printing number of combinations
    printf("Number of combinations is: %d\n", numOf);
}

/*********************************************************************************************
 *Function Name: printACombination
 * Input: char pattern[](valid values pattern[] an array of chars '0','1','2','?'),
 *        int len (valid values len>0), int index(valid values len>=0)
 * Output: void
 * Function Operation: The function is a recursion function that prints all the Combinations of numbers,
 *                     from smallest to biggest, that can be made by switching the char '?' to 1,2,0.
 *                     It does this by checking every index in the array to see if it is '?',
 *                     and if it is - sending pattern,'0'',len and index to changeVar.
 *                     Once the function gets to the end of the array, it prints the array,
 *                     and adds 1 to the global int numOf.
 *********************************************************************************************/
void printACombination(char pattern[],int len,int index)
{
    //if the index is the last index of the array
    if(index==len)
    {
        printf(pattern);
        printf("\n");
        numOf++;
        return;
    }
    //checking the current index, sending to changeVar if the char in the array is '?'
    if (pattern[index]==QUESTION_MARK)
        changeVar(pattern,ZERO,len,index);
    //recursing to the next index, if it is not '?'
    else
        printACombination(pattern,len,index+1);
}

/*********************************************************************************************
 *Function Name: changeVar
 * Input: char pattern[](valid values pattern[] an array of chars '0','1','2','?'),
 *        char var (valid values chars '0','1','2','?'),int len (valid values len>0),
 *        int index(valid values len>=0)
 * Output: void
 * Function Operation: The function is a recursion function that
 *                     switches the char of pattern at the current index to var,
 *                     sends printACombination function pattern,len and index+1,
 *                     and then recurses with var+1, and all the other similar values.
 *                     If var is '2', after sending to printACombination
 *                     changeVar will change pattern[index] to be '?', and then end the function.
 *********************************************************************************************/
void changeVar(char pattern[],char var,int len,int index)
{
    //changing the current char
    pattern[index]=var;
    printACombination(pattern,len,index+1);
    //if var has reached its limmit
    if(var==TWO)
    {
        pattern[index]=QUESTION_MARK;
        return;
    }
    changeVar(pattern,var+1,len,index);
}

/*********************************************************************************************
 *Function Name: powRec
 * Input: long int firsrtNum (valid values any long int) , long int secondNum (valid values any long int)
 * Output: void
 * Function Operation: The function prints "The result is " firsrtNum in the power of secondNum.
 *                     if secondNum is negative, and firstNum is 0, it will print "The result is nan"
 *********************************************************************************************/
void powRec (long int firsrtNum, long int secondNum)
{
    printf("The result is ");
    //if secondNum is negative, and firstNum is 0
    if((firsrtNum==0)&&secondNum<0)
        printf("nan.\n");
    else
        //sending to powerOf, and casting firstNum into a float
        printf("%f.\n",powerOf((float)firsrtNum,secondNum));
}

/*********************************************************************************************
 *Function Name: powerOf
 * Input: float firsrtNum (valid values float) , long int secondNum (valid values long int)
 * Output: float (value of a float number)
 * Function Operation: The function is a recursion function that sends
 *                     the firstNum in the power of secondNum as a float.
 *********************************************************************************************/
float powerOf(float firsrtNum, long int secondNum)
{
    //if the power secondNum is 0, power 0 is 1
    if (secondNum==0)
        return 1;
    //if secondNum is negative, then power is 1/the possitive number
    if (secondNum<0) {
        secondNum = (~secondNum) + 1;
        firsrtNum = 1/firsrtNum;
    }
    //recruses the next power number*firstNum
    return firsrtNum*powerOf(firsrtNum, secondNum-1);
}

/*********************************************************************************************
 *Function Name: isDivisibleBy3
 * Input: long long n (valid values long long)
 * Output: void
 * Function Operation: The function prints if the number is divisible by 3 or not.
 *                     It does so by sending the number and the number 0 to
 *                     the function checkThree.
 *********************************************************************************************/
void isDivisibleBy3(long long n)
{
    printf("The number %lld is",n);
    //if checkThree sent back that a number diffret from 0 - n is not divisible by 3
    if (checkThree(n,FIRSTINDEX)!=0)
        printf(" not divisible by 3.\n");
    //if checkThree sent back 0 - n is divisible by 3
    else
        printf(" divisible by 3.\n");
}

/*********************************************************************************************
 *Function Name: checkThree
 * Input: long long n (valid values long long), int isThree (valid value int)
 * Output: int (value between 0-2)
 * Function Operation: The function is a recursion function that gets a long long number
 *                     and the number 0, that is saved as isThree.
 *                     The function checks if the long long number%10
 *                     is 1 or 2, and then changes the int number accordingly, and then
 *                     sends back to the same function the long long number/10,
 *                     and isThree that was changed.
 *                     The function will then send back a value between 0-2,
 *                     while if it sends back 0, the number is divisible by 3.
 *********************************************************************************************/
int checkThree(long long n, int isThree)
{
    //the end of the recruseion, after checking every number of n
    if(n==0)
        return isThree;
    //if the current number of n is 2
    if (n%10==2)
    {
        //isThree will change by 2, in moodolo 3
        if (isThree==0)
            isThree=2;
        else if (isThree==2)
            isThree=1;
        else
            isThree=0;
    }
    //if the current number of n is 1
    if (n%10==1)
    {
        //isThree will change by 1, in moodolo 3
        if (isThree==2)
            isThree=0;
        else if(isThree==1)
            isThree=2;
        else
            isThree=1;
    }
    return checkThree(n/10,isThree);
}

/*********************************************************************************************
 *Function Name: gcd
 * Input: long int n1 (valid values long int), long int n2 (valid values long int)
 * Output: void
 * Function Operation: The function sends to the function checkNegative the function getGcd,
 *                     while sending the two numbers ni and n2 to the function getGcd,
 *                     that returns the gcd of the two numbers if they are both different then 0.
 *                     If the one of the numbers is 0 - it send the other one to checkNegative.
 *********************************************************************************************/
void gcd(long int n1, long int n2)
{
    //if n1 is zero, it will print the possitive n2
    if(n1==0)
    {
        checkNegative(n2);
        return;
    }
    //if n2 is zero, it will print the possitive n1
    if(n2==0)
    {
        checkNegative(n1);
        return;
    }
    //if both numbers are not zero
    checkNegative(getGcd(n1,n2));
}

/*********************************************************************************************
 *Function Name: checkNegative
 * Input: long int num (valid values long int)
 * Output: void
 * Function Operation: The function get a number, and checks if it negative.
 *                     If it is - it changes the number to positive.
 *                     The function then prints GCD= the number.
 *********************************************************************************************/
void checkNegative(long int num)
{
    //if num is negative, change it to positive
    if(num<0)
        num=(~num)+1;
    printf("GCD=%d\n",num);
}

/*********************************************************************************************
 *Function Name: getGcd
 * Input: long int n1 (valid values long int), long int n2 (valid values long int)
 * Output: long int (value long int)
 * Function Operation: The function is a recursion function that gets two numbers,
 *                     returns the gcd of the two numbers, after printing the way
 *                     that it got to the gcd.
 *********************************************************************************************/
long int getGcd(long int n1, long int n2)
{
    //if the recurison comes to an end
    if (n2==0)
        return n1;
    //gets the q
    long int q = n1/n2;
    //gets the r
    long int r= n1%n2;
    printf("%d*%d+%d=%d(a=%d,b=%d)\n",n2,q,r,n1,n1,n2);
    //recruse with n2 and r
    getGcd(n2, r);
}

/*********************************************************************************************
 *Function Name: countDigit
 * Input: long long n (valid values n>0), int d (valid values d>0)
 * Output: void
 * Function Operation: The function prints the amount of times the
 *                     number d is in n, by sending the two numbers to countDigit function.
 *********************************************************************************************/
void countDigit(long long n, int d)
{
    //if both numbers are zero, then it is 1 time
    if(n==0&&d==0)
        printf("%lld has %d times %d.\n",n,1,d);
    else
        printf("%lld has %d times %d.\n",n,theCount(n,d),d);
}

/*********************************************************************************************
 *Function Name: theCount
 * Input: long long n (valid values n>0), int d (valid values d>0)
 * Output: int (value >0)
 * Function Operation: The function is a recursion function that gets two numbers,
 *                     and returns how many time d is in n.
 *********************************************************************************************/
int theCount(long long n, int d)
{
    //if the function is at its final recrusion
    if(n==0)
        return 0;
    //adding 1 to the returned number if n%10 is d
    if (n%10==d)
        return 1+theCount(n/10,d);
    return theCount(n/10,d);
}

/*********************************************************************************************
 *Function Name: isPalindromeIter
 * Input: char str[](valid values str[] an array of any chars),int len (valid values len>0)
 * Output: void
 * Function Operation: The function checks if a array is a palindrome by
 *                      checking every char to see if it the same as the palindrome one.
                        If the array is a palindrome, it will print : The reverse of the "array"
                        is also the "array".
                        If it is not, it will print : The reverse of the "array"" is not the "array".
 *********************************************************************************************/
void isPalindromeIter(char str[],int len)
{
    //the flag is to determen if the array is a palindrome
    int flag=0;
    //a loop to check every opposite chars to see if they are the same
    for(int smallNum=0;len-1>smallNum;smallNum++, len--)
        //if the chars are not the same - flag will be 1
        if (str[len - 1] != str[smallNum])
        {
            flag = 1;
            break;
        }
    printf("The reverse of ");
    printf(str);
    //if flag is zero, the array is a palindrome
    if (flag==0)
        printf(" is also ");
    else
        printf(" is not ");
    printf(str);
    printf(".\n");
}

/*********************************************************************************************
 *Function Name: IsDividedBy3Iter
 * Input: long long n (valid value long long)
 * Output: void
 * Function Operation: The function prints if the number is divisible by 3 or not.
 *                     It does so by declaring and int isThree to be 0, then checks if by using a loop if
 *                     the long long number%10 is a number that is not dividable by three,
 *                     and if so changes isThree accordingly.
 *                     If at the end of the loop isThree = 0, it will print that the numbers is divided by 3,
 *                     else it will print that the number is not divided by 3.
 *********************************************************************************************/
void IsDividedBy3Iter(long long num)
{
    //isThree indacates if the number is divadable by 3
    int isThree=0;
    printf("The number %lld is",num);
    //this loop checks every number of num, and changes isThree acorrindingly
    while (num!= 0)
    {
        //if num%10 devided by 3 is 2
        if (num%10==2||num%10==5||num%10==8)
        {
            //isThree will change by 2, in moodolo 3
            if (isThree==0)
                isThree=2;
            else if (isThree==2)
                isThree=1;
            else
                isThree=0;
        }
        //if num%10 devided by 3 is 1
        if (num%10==1||num%10==4||num%10==7)
        {
            //isThree will change by 1, in moodolo 3
            if (isThree==2)
                isThree=0;
            else
                isThree++;
        }
        num=num/10;
    }
    //incase isThree is not 0 - num is not divisible by 3
    if (isThree!=0)
        printf(" not divisible by 3.\n");
    else
        printf(" divisible by 3.\n");
}