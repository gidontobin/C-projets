/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ass4
 ***************/
#include <stdio.h>
#include <string.h>
#include "ass4.h"
#define SPACE ' '
#define BACKSLASH '/'
#define ENDARRAY '\0'
#define ZERO '0'
#define COMMA ','
#define FIRSTLETTER 'a'
#define MAXCOMMAND 10

int checkStr(char str[]);
void replaceAll(char board[][SIZE * SIZE], char move[],int index);
void changeAddDelete(char board[][SIZE * SIZE], char move[],char command[],int index);
int isNotGoodSize(int size);
int isNotChar(char first,char second);
int isChar(char first,char second);
int isGoodSize(int size);
int isNotValidChar(char board);
int isNotGoodOnBoard(char board[][SIZE * SIZE],int row, int column);
void putInNum(char board[][SIZE * SIZE],int row, int column);


/*********************************************************************************************
 *Function Name: createBoard
 * Input:  char board[][SIZE * SIZE] (array not booted), char str[] (valid values chars)
 * Output: void
 * Function Operation: The function gets a non booted 2D array, and a 1D array, and adds the values
 *                     from the array str to board accordingly, after sending the array str to checkStr
 *                     to check if it is valid. if the array str is not valid, the function will
 *                     do nothing to the board.
 *********************************************************************************************/
void createBoard(char board[][SIZE * SIZE], char str[])
{
    //checking if the array str is valid
    if (checkStr(str))
        return;
    int row=0, column=0;
    //this loop will put every char of str to the board
    for(int i=0;str[i]!=ENDARRAY;i++)
    {
        if(str[i]==BACKSLASH)
        {
            //add spaces untill the end of row
            for(;column<(SIZE*SIZE);column++)
                board[row][column]=SPACE;
            row++;
            column=0;
        }
        //if the current char is a letter that indicates to put spaces
        else if(str[i]>=FIRSTLETTER&&str[i]<FIRSTLETTER+(SIZE*SIZE))
            //add the amount of spaces needed
            for (int j=0; j<(str[i]-(FIRSTLETTER-1)); j++,column++)
                board[row][column]=SPACE;
        //if the current char is not a letter, add the current char to the board
        else
        {
            board[row][column]=str[i];
            column++;
        }
    }
    //adding spaces if needed in last row
    for (;column <SIZE*SIZE ; column++)
    {
        board[row][column]=SPACE;
    }
}

/*********************************************************************************************
 *Function Name: checkStr
 * Input: char str[] (valid values chars)
 * Output: int (values between 0-1)
 * Function Operation: The function get an array, checks if it is valid, to put on a board.
 *                     if the array str is not valid, the function will print "Error",
 *                     and send back 1. If it is valid, it will send back 0.
 *********************************************************************************************/
int checkStr(char str[])
{
    int row = 0, column = 0;
    //this loop will check str
    for (int i = 0; str[i] != ENDARRAY; i++)
    {
        //a new row
        if (str[i] == BACKSLASH)
        {
            //move to next row
            row++;
            column = 0;
        }
        //if the char is to indacate spaces
        else if (str[i] >= FIRSTLETTER && str[i] < FIRSTLETTER + (SIZE * SIZE))
            //seek the amount of spaces needed
            for (int j = 0; j < (str[i] - (FIRSTLETTER-1)); j++)
                column++;
        //if the char is ',' it is not valid
        else if (isChar(str[i], COMMA))
            return 1;
        else
            //go to next column in the row
            column++;
        //if there are to many chars in a row or to many rows
        if (column > (SIZE*SIZE) || row == (SIZE*SIZE))
        {
            printf("Error\n");
            return 1;
        }
    }
    //checking if there are not enough rows submited
    if (row != (SIZE*SIZE)-1)
    {
        printf("Error\n");
        return 1;
    }
    //if str is good
    return 0;
}
/*********************************************************************************************
 *Function Name: makeMove
 * Input:  char board[][SIZE * SIZE] (array booted), char move[] (valid values chars)
 * Output: void
 * Function Operation: The function receives a two-dimensional array of characters booted by
 *                     the function createBoard, and an array move, that Describes a move.
 *                     The function will check if the command is valid. If it is, the function
 *                     will change the board accordingly, by sending it to replaceAll,
 *                     or changeAddDelete. If an illegal move has been submitted the board
 *                     will not be changed at all, and the message Error will be printed.
 *********************************************************************************************/
void makeMove(char board[][SIZE * SIZE], char move[])
{
    //this array will recieve the command that is in move
    char command[MAXCOMMAND+1]="";
    int index = 0;
    //putting the command in checks
    for (; move[index] != COMMA; index++)
    {
        //checking if command is to long
        if (index>MAXCOMMAND)
        {
            printf("Error\n");
            return;
        }
        command[index] = move[index];
    }
    //going to the char after the first comma
    index++;
    if (strcmp(command, "replaceAll") == 0)
        replaceAll(board, move, index);
    else if (strcmp(command, "change") == 0)
        changeAddDelete(board, move,command,index);
    else if (strcmp(command, "add") == 0)
        changeAddDelete(board, move,command,index);
    else if (strcmp(command, "delete") == 0)
        changeAddDelete(board, move,command,index);
    else
        printf("Error\n");
}

/*********************************************************************************************
 *Function Name: replaceAll
 * Input:  char board[][SIZE * SIZE] (booted array), char move[] (valid values chars),
 *         int index (valid values 0 - SIZE * SIZE)
 * Output: void
 * Function Operation: The function receives a two-dimensional array of characters from the function
 *                     makeMove, and the array move, and the current index.
 *                     The function first checks if the move is valid, and if it is - it will change
 *                     the first char on the whole board that is mention in move, to the second char
 *                     mention in move. If it does not change any char - move is no valid.
 *                     If a non valid move has been submitted the board will not be changed at all,
 *                     and the message Error will be printed.
 *********************************************************************************************/
void replaceAll(char board[][SIZE * SIZE], char move[],int index)
{
    int row = 0, column = 0, flag = 0;
    //these vars will get the char that will be switched, and the char it will be switched to
    char fromChar, toChar;
    //incase the char is a non valid char
    if(isChar(move[index], SPACE)||isChar(move[index], BACKSLASH)||
       isChar(move[index], COMMA)||isGoodSize(move[index]-FIRSTLETTER))
        return;
    fromChar=move[index];
    index++;
    if (isNotChar(move[index], COMMA))
        return;
    index++;
    if(isChar(move[index], SPACE)||isChar(move[index], BACKSLASH)||
       isChar(move[index], COMMA)||isGoodSize(move[index]-FIRSTLETTER))
        return;
    toChar=move[index];
    index++;
    if (isNotChar(move[index], ENDARRAY))
        return;
    //the array move is good, the loop will switch every char
    while (row<SIZE * SIZE)
    {
        if (board[row][column] == fromChar)
        {
            board[row][column] = toChar;
            flag=1;
        }
        column++;
        //incase end of row
        if (column==SIZE*SIZE)
        {
            row++;
            column=0;
        }
    }
    //if there were no chars to change
    if (flag==0)
        printf("Error\n");
}

/*********************************************************************************************
 *Function Name: changeAddDelete
 * Input:  char board[][SIZE * SIZE] (booted array), char move[] (valid values chars),
 *         int index (valid values 0 - SIZE * SIZE)
 * Output: void
 * Function Operation: The function receives a two-dimensional array of characters from the function
 *                     makeMove, and the array move, and the current index.
 *                     The function first checks if the move is valid, and if it is - it will do
 *                     the move that is mention.
 *                     If a non valid move has been submitted the board will not be changed at all,
 *                     and the message Error will be printed.
 *********************************************************************************************/
void changeAddDelete(char board[][SIZE * SIZE], char move[],char command[],int index)
{
    int row,column;
    //sigh is the var that will be add or changed
    char sigh;
    row = move[index]-ZERO;
    if (isNotGoodSize(row))
        return;
    index++;
    if(isNotChar(move[index], COMMA))
        return;
    index++;
    column = move [index]-ZERO;
    if (isNotGoodSize(column))
        return;
    index++;
    //incase the command is not delete
    if (strcmp(command, "delete")!=0)
    {
        if (isNotChar(move[index], COMMA))
            return;
        index++;
        sigh = move[index];
        //if sigh is not valid
        if (isChar(sigh, SPACE)||isChar(sigh, BACKSLASH)||isChar(sigh, COMMA))
            return;
        if (isGoodSize(sigh-FIRSTLETTER))
            return;
        index++;
    }
    if (isNotChar(move[index], ENDARRAY))
        return;
    //making sure it does not add to something that is not a space
    if (strcmp(command, "add")==0)
    {
        if (isNotChar(board[row][column], SPACE))
            return;
    }
    //making sure it does not switch or delete with a space
    else if (isChar (board[row][column], SPACE))
        return;
    //if the command was delete
    if (strcmp(command, "delete")==0)
        board[row][column]=SPACE;
    //if the command was change or add
    else
        board[row][column] = sigh;
}

/*********************************************************************************************
 *Function Name: isNotGoodSize
 * Input:  int size (valid values int)
 * Output: void
 * Function Operation: The function receives an int, and checks if it is bigger that 0
 *                     and smaller that SIZE*SIZE. If it is not - the function will print "Error"
 *                     and return 1. If it is - the function will return 0.
 *********************************************************************************************/
int isNotGoodSize(int size)
{
    //if the size is to big or to small
    if (size<0 || size >= SIZE * SIZE)
    {
        printf("Error\n");
        return 1;
    }
    //the size is good
    return 0;
}

/*********************************************************************************************
 *Function Name: isGoodSize
 * Input:  int size (valid values int)
 * Output: void
 * Function Operation: The function receives an int, and checks if it is bigger that 0
 *                     and smaller that SIZE*SIZE. If it is not - the function will return 0.
 *                     If it is - the function will print "Error" and return 1.
 *********************************************************************************************/
int isGoodSize(int size)
{
    //if the size is the good size
    if (size>=0 && size<SIZE * SIZE)
    {
        printf("Error\n");
        return 1;
    }
    //not the good size
    return 0;
}

/*********************************************************************************************
 *Function Name: isNotChar
 * Input: char first (valid values char),char second (valid values char)
 * Output: void
 * Function Operation: The function receives 2 chars. If they are the same - the function will
 *                     return 0. If they are not - the function will print "Error"
 *                     and return 1.
 *********************************************************************************************/
int isNotChar(char first,char second)
{
    if (first != second)
    {
        printf("Error\n");
        return 1;
    }
    //if it is the same
    return 0;
}

/*********************************************************************************************
 *Function Name: isChar
 * Input: char first (valid values char),char second (valid values char)
 * Output: void
 * Function Operation: The function receives 2 chars. If they are not the same - the function will
 *                     return 0. If they are - the function will print "Error"
 *                     and return 1.
 *********************************************************************************************/
int isChar(char first,char second)
{
    if (first == second)
    {
        printf("Error\n");
        return 1;
    }
    //if it is not the same
    return 0;
}

/*********************************************************************************************
 *Function Name: printBoard
 * Input:  char board[][SIZE * SIZE] (array booted)
 * Output: void
 * Function Operation: The function receives a two-dimensional array of characters booted by
 *                     the function createBoard, and prints the array accordingly.
 *********************************************************************************************/
void printBoard(char board[][SIZE * SIZE])
{
    int row=0, column=0, blockRow = 0, blockColumn = 0;
    while (row<SIZE*SIZE)
    {
        //incase the column finedshed the certion block
        if (blockColumn==SIZE)
        {
            //if it is at the end of the row
            if (column == SIZE * SIZE)
            {
                printf("\n");
                //go to the first column of next row
                column = 0;
                row++;
                //indacates every block of rows
                blockRow++;
                //if the row is the end of the block
                if (blockRow == SIZE)
                {
                    printf("\n");
                    blockRow = 0;
                    //if it is the end of the board
                    if (row==SIZE*SIZE)
                        break;
                }
            }
            //the middle of the row
            else
                printf(" | ");
            blockColumn=0;
        }
        //print the current char
        printf("%c", board[row][column]);
        //next column of the row
        column++;
        blockColumn++;
    }
}

/*********************************************************************************************
 *Function Name: testBoard
 * Input:  char board1[][SIZE * SIZE] (array booted)
 * Output: int (values between 0-1)
 * Function Operation: The function receives a two-dimensional array of characters booted by
 *                     the function createBoard, checks if it is valid. If it is -
 *                     the function wil return 1, if not - it will return 0.
 *********************************************************************************************/
int testBoard(char board[][SIZE * SIZE])
{
    //check every row
    for (int row = 0; row < SIZE * SIZE; row++)
    {
        //check every column
        for (int column = 0; column < SIZE * SIZE; column++)
        {
            //if the current char is space - move on to next char
            if (board[row][column] == SPACE)
                continue;
            //checking the char is a valid char
            if (isNotValidChar(board[row][column]))
                return 0;
            //check if the char is in the right place on the board
            if(isNotGoodOnBoard(board, row, column))
                return 0;
        }
    }
    //if the board is good
    return 1;
}

/*********************************************************************************************
 *Function Name: isNotValidChar
 * Input:  char board (valid values char)
 * Output: int (values between 0-1)
 * Function Operation: The function receives a char and checks if it is valid. If it is not -
 *                     the function wil return 1, if it is - it will return 0.
 *********************************************************************************************/
int isNotValidChar(char board)
{
    //checking the char is valid
    if (board - ZERO < 1 || board - ZERO > SIZE * SIZE)
        //if it is not a number, checking if it is a space
        if (board !=SPACE)
            return 1;
    return 0;
}
/*********************************************************************************************
 *Function Name: isNotGoodOnBoard
 * Input: char board[][SIZE * SIZE] (array booted),int row (valid values 0-SIZE*SIZE),
 *        int column (valid values 0-SIZE*SIZE)
 * Output: int (values between 0-1)
 * Function Operation: The function receives a two-dimensional array of characters booted by
 *                     the function createBoard, the current row and column that it needs to check,
 *                     and checks if the char is good on the board. If it is not -
 *                     the function wil return 1, if it is - it will return 0.
 *********************************************************************************************/

int isNotGoodOnBoard(char board[][SIZE * SIZE],int row, int column)
{
    //check every char in the row
    for (int checkColumn = 0; checkColumn < SIZE * SIZE; checkColumn++)
    {
        if (column == checkColumn)
            continue;
        //if the current number is in the same row
        if (board[row][column] == board[row][checkColumn])
            return 1;
    }
    //check every char in the column
    for (int checkRow = 0; checkRow < SIZE * SIZE; checkRow++)
    {
        if (row == checkRow)
            continue;
        //if the current number is in the same column
        if (board[row][column] == board[checkRow][column])
            return 1;
    }
    //checking the box, boxRow will indacate end of box row, boxColumn will indacte end of box column
    int boxRow=row%SIZE,boxColumn=column%SIZE;
    //checking the row right of the current in box
    for (int c = 1; c+boxColumn <SIZE ; c++)
    {
        //checking the entire column in box under the current
        for (int r = 1; boxRow < SIZE - 1 ; r++)
        {
            if (board[row][column] == board[row+r][column+c])
                return 1;
            boxRow++;
        }
        boxRow = row % SIZE;
    }
    boxRow = row % SIZE;
    //checking left and down diagonal in box
    for (int c = 1; boxColumn-c >=0 ; c++)
    {
        for (int r = 1; boxRow < SIZE - 1; r++)
        {
            if (board[row][column] == board[row+r][column-c])
                return 1;
            boxRow++;
        }
        boxRow = row % SIZE;
    }
    return 0;
}

/*********************************************************************************************
 *Function Name: isSameBoard
 * Input:  char board1[][SIZE * SIZE] (array booted), char board1[][SIZE * SIZE] (array booted)
 * Output: int (values between 0-1)
 * Function Operation: The function receives 2 two-dimensional array of characters booted by
 *                     the function createBoard, checks if they are the same. If they are -
 *                     the function wil return 1, if they are not - the function will print
 *                     the first char that is not the same, and return 0.
 *********************************************************************************************/
int isSameBoard(char board1[][SIZE * SIZE], char board2[][SIZE * SIZE])
{
    //check every row
    for (int row = 0; row < SIZE * SIZE; row++)
    {
        //check every column
        for (int column = 0; column < SIZE * SIZE; column++)
            if (board1[row][column]!=board2[row][column])
            {
                printf("Found inequality on row %d col %d.\n",row,column);
                return 0;
            }
    }
    return 1;
}

/*********************************************************************************************
 *Function Name: completeBoard
 * Input:  char board[][SIZE * SIZE] (array booted)
 * Output: void
 * Function Operation: The function receives a two-dimensional array of characters booted by
 *                     the function createBoard, and will complete it by sending it to the function
 *                     putInNum, after checking it is valid. if it is not valid - the function
 *                     will print Error.
 *********************************************************************************************/
void completeBoard(char board[][SIZE * SIZE])
{
    //check every row
    for (int row = 0; row < SIZE * SIZE; row++)
    {
        //check every column
        for (int column = 0; column < SIZE * SIZE; column++)
        {
            //checking the char is valid
            if (isNotValidChar(board[row][column]))
            {
                printf("Error\n");
                return;
            }
            //check every char in the column
            if(isNotGoodOnBoard(board, row, column))
            {
                printf("Error\n");
                return;
            }
        }
    }
    //check every row
    for (int row = 0; row < SIZE * SIZE; row++)
    {
        //check every column
        for (int column = 0; column < SIZE * SIZE; column++)
        {
            if (board[row][column] == SPACE)
                //complete the space
                putInNum(board, row, column);
        }
    }
    return;
}

/*********************************************************************************************
 *Function Name: putInNum
 * Input: char board[][SIZE * SIZE] (array booted),int row (valid values 0-SIZE*SIZE),
 *        int column (valid values 0-SIZE*SIZE)
 * Output: void
 * Function Operation: The function receives a two-dimensional array of characters booted by
 *                     the function createBoard, the row and column that is currently a SPACE
 *                     and will complete it by checking every row to see witch number is missing,
 *                     and adding that number to the current space.
 *********************************************************************************************/
void putInNum(char board[][SIZE * SIZE],int row, int column)
{
    //this is the number that we are looking for
    for (int num = 1; num <=SIZE*SIZE ; num++)
    {
        int flag=0;
        //go over the intire row, to see if num is in row
        for (int i = 0; i < SIZE *SIZE; i++)
        {
            if (i==column)
                continue;
            //if the number is in the column move to next number
            if (board[row][i]==num+ZERO)
            {
                flag=1;
                break;
            }
        }
        //num is not in column
        if (flag==0)
        {
            //put num in the place
            board[row][column]=num+ZERO;
            return;
        }
    }
}