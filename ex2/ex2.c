/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ex2
 ***************/
#include <stdio.h>
int main() {

    //optionUser will be the varuble of the option
    char optionUser;
    //this loop is to show again if a wrong number is written, it will ony stop if 0 is entered
    while (1){

        printf("Choose an option:\n");
        printf("1. Rhombus\n");
        printf("2. Base 20 to Decimal\n");
        printf("3. Base to Decimal\n");
        printf("4. Pow2\n");
        printf("5. Different bits\n");
        printf("6. Add\n");
        printf("7. Multiply\n");
        printf("0. Exit\n");

        //geting the optin from the user
        scanf(" %c", &optionUser);
        //understanding if the character submited is good, by converting the character into an integer
        int checkOption=0,i=0;
        //this loop is incase the user submits more then one character
        while (optionUser!='\n'){
            checkOption = checkOption + optionUser-'0';
            scanf("%c", &optionUser);
            i++;
        }

        //checking if the option is to exit
        if (checkOption == 0)
            return 0;
        //checking if a wrong number or character was ishude
        if (checkOption > 7 || checkOption < 1||i>1)
            printf("Wrong option!\n");

        //in case the option is good
        else {

            //in case the option was 1
            if (checkOption == 1) {

                //leangthRhombus will be used as the length varuble
                int leangthRhombus;

                printf("Enter the sides length:\n");
                scanf("%d", &leangthRhombus);

                //this loop is to draw the top of Rhombus
                for (int i = 0; i < leangthRhombus; i++) {

                    //this loop is to print the amount of spaces needid on the right side
                    for (int j = 0; j < leangthRhombus - 1 - i; j++)
                        printf(" ");

                    //after printing the spaces on the right, the program will print a /
                    printf("/");

                    //this is to print the spaces after the first /
                    for (int x = 0; x < i; x++)
                        printf(" ");

                    //to print in the middle of Rhombus
                    printf("*");

                    //this is to print the spaces after the *
                    for (int x = 0; x < i; x++)
                        printf(" ");

                    //this is the end pf the line
                    printf("\\\n");
                }

                //this is to draw the middle of the row of the Rhombus
                printf("|");

                //the amount of spaces on the right
                for (int i = 0; i < leangthRhombus - 1; i++)
                    printf(" ");

                //the middle of the Rhombus
                printf("+");

                //spaces after the middle of the Rhombus
                for (int i = 0; i < leangthRhombus - 1; i++)
                    printf(" ");

                //the end of the middle row
                printf("|\n");

                //this loop is to draw the botom part of Rhombus
                for (int i = leangthRhombus; i > 0; i--) {

                    //this is to print the amount of spaces needid on the right side
                    for (int j = 0; j < leangthRhombus - i; j++)
                        printf(" ");

                    //the first tab of the row
                    printf("\\");

                    //this is to print the spaces after the first /
                    for (int x = 0; x < i-1; x++)
                        printf(" ");

                    //to print in the middle of Rhombus
                    printf("*");

                    //this is to print the spaces after the *
                    for (int x = 0; x < i-1; x++)
                        printf(" ");

                    //the end pf the row
                    printf("/\n");
                }
            }

            // in case the option was 2
            if(checkOption==2){

                //this is going to be the varuble the user enters
                char numTwenty;
                /*
                the decemle num is a varuble to add up with, and it repelsents the num in dec
                the indecator is to show if the user enter a wrong letter
                */
                int decNum=0, indecator=0;
                printf("Enter a reversed number in base 20:\n");
                scanf(" %c", &numTwenty);

                //this loop is to add all of the number submitid together
                for (int i = 0; numTwenty != '\n'; i++) {
                    //twentyTimes is the varuble that defines how many times 20 we need to multiply the number
                    int twentyTimes = 20;
                    //this loop gives us the amount of time we need twenty multiplide by
                    for (int j = 1; j < i; j++)
                        twentyTimes = twentyTimes * 20;
                    //numTwenty1 is the varuble that is used to seek the number submeted from the user
                    int numTwenty1;
                    //incase the leeter submited is upper case
                    if (numTwenty > ('A'-1) && numTwenty < 'K')
                        numTwenty1 = numTwenty - '7';
                    //incase the leeter submited is lower case
                    else if (numTwenty > ('a'-1) && numTwenty < 'k')
                        numTwenty1 = numTwenty - 'W';
                    //incase a number is submeted
                    else if (numTwenty > ('0'-1) && numTwenty < ('9'+1))
                        numTwenty1 = numTwenty - '0';
                    //if a wrong number was submited
                    else {
                        printf("Error! %c is not a valid digit in base 20\n", numTwenty);
                        indecator=1;
                    }

                    //multuplie the number by the amout of twenty times needed
                    if (i != 0)
                        numTwenty1 = numTwenty1 * twentyTimes;
                    //add numder to the total decemal number
                    decNum = decNum + numTwenty1;
                    //scan a nother number from the buffer
                    scanf("%c", &numTwenty);
                }
                //checking to see if no wrong numbers were submitid, and then printing answer
                if(indecator==0)
                    printf("%d\n",decNum);
            }

            if(checkOption==3){
                /*
                 base wiil be used as the base
                 decNum - is the final number in decemal
                 limetdNum will multuply the specific by the base acording to its place
                 indecator will make sure there were no wrong numbers
                 */
                int base,decNum=0,limetedNum,indecator3=0;
                //this is the actual number the user will submit
                char numOfBase;
                printf("Enter a base (2-10):\n");
                scanf("%d",&base);
                printf("Enter a reversed number in base %d:\n",base);
                scanf(" %c", &numOfBase);
                /*
                this loop is to add all of the number submitid together,
                and once the users hits enter, the loop will stop
                */
                for (int i = 0; numOfBase != '\n'; i++) {

                    //oneNum will turn the number from a char to an int
                    int oneNum = numOfBase-'0';
                    //to check if the number is not valid, and inform the indecator
                    if (oneNum>base-1||oneNum<0) {
                        indecator3 = 1;
                        printf("Error! %c is not a valid digit in base %d\n",numOfBase,base);
                    }

                    //timesBase will multiply the base by itself the ampunt of times needed
                    int timesBase=base;
                    for (int j=1;j<i; j++)
                        timesBase=timesBase*base;

                    //for evrey number after the first number, we multeply it by the timesBase
                    if (i>0){
                        limetedNum=timesBase*oneNum;
                        decNum=decNum+limetedNum;
                    }
                        //for the first number, we will add it as is to the decemal number
                    else
                        decNum=decNum+oneNum;
                    //this scanf is to allow scaning blank symble, to make the loop stop once the user hits enter
                    scanf("%c", &numOfBase);
                }
                //there will only be a print if the number is valid
                if(indecator3==0)
                    printf("%d\n",decNum);
            }

            //the program will oporate in case the user picks 4
            if(checkOption==4){
                printf("Enter a number:\n");
                int num;
                scanf("%d",&num);
                //numCheck if it is worth 0 will indecate that the number is a power of 2
                int numCheck=num&(num-1);
                if (numCheck==0)
                    printf("%d is a power of 2\n", num);
                else
                    printf("%d is not a power of 2\n",num);
            }

            //in case user picks 5
            if(checkOption==5){
                //getting 2 numbers from user
                int firstNum,secondNum,theDif=0;
                printf("Enter two numbers:\n");
                scanf("%d",&firstNum);
                scanf("%d",&secondNum);
                //checkBit is the number that will simble the amount of bits that are difrent
                int checkBit= firstNum^secondNum;
                /*
                 this loop will go untill we know how many 1 bits there are in checkBit,
                while theDif is the indacotor to how many 1 bits are in checkBit
                */
                for(int i=0;i<(sizeof(i)*8);i++){
                    if((checkBit&1)==1)
                        theDif++;
                    checkBit=checkBit>>1;
                }

                printf("There are %d different bits\n", theDif);
            }

            //incase user picks 6
            if(checkOption==6){
                //getting 2 numbers from user as unsigned numbers
                unsigned firstNum,secondNum;
                //varlibules to change bits, and add to finale number
                int num=0,a,b,c=0,xorAb,x;
                printf("Enter two numbers:\n");
                scanf("%u",&firstNum);
                scanf("%u",&secondNum);
                //this loop is as long as an int, so there will be no overflow problem
                for(int i=0;i<(sizeof(i)*8);i++) {
                    //a is the corrent bit of firstNum
                    a = (firstNum & 1);
                    //b is the corrent bit of secondNum
                    b = (secondNum & 1);
                    //xorAb is to know what to add to final number
                    xorAb=a^b;
                    //x checks if there is a carry to consedir
                    x=c^xorAb;
                    //c is the carry
                    c=(xorAb&c)^(a&b);
                    //nums is our final number
                    num=num^(x<<i);
                    //checking if both nubers are 0
                    if((firstNum==0)&&(secondNum==0))
                        break;
                    //moving on to the next bit
                    firstNum=firstNum>>1;
                    secondNum=secondNum>>1;
                }

                printf("%d\n",num);
            }

            if(checkOption==7){
                //getting 2 numbers from user as unsigned numbers
                int firstNum,secondNum,times,add=0;
                printf("Enter two numbers:\n");
                scanf("%d",&firstNum);
                scanf("%d",&secondNum);
                //checking if the second number is negative
                if(secondNum<0)
                    //id it is negative - turn it into positive
                    times=(~secondNum)+1;
                else
                    times=secondNum;
                //adding the first number second number times
                for(int i=0;i<times;i++)
                    add=add+firstNum;
                //incase the second number was negative
                if(secondNum<0)
                    add=~add+1;
                printf("%d\n",add);
            }
        }
    }
}