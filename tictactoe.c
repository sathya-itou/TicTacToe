#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LEN 3
#define COL_LEN 3
#define STRING_INPUT_LEN 30

//✅TODO : get players name and announce who won at the end
//✅TODO : check and print if tie_flag                 
//✅TODO : check and warn if the position is already taken
//✅TODO : get only valid input [0 or 1 or 2 ] ie., within the bound range of table 


//safe string input with limit
int limit_input(char s[], int maxlen) {
    char ch;
    int i;
    int chars_remain;
    i = 0;
    chars_remain = 1;
    while (chars_remain) {
        ch = getchar();
        if ((ch == '\n') || (ch == EOF) ) {
            chars_remain = 0;
        } else if (i < maxlen - 1) {
            s[i] = ch;
            i++;
        }
    }
    s[i] = '\0';
    return i;
}

//input flush
void flush()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

//prints table
void table_print(int row, int col, char array[row][col])
{
    printf("  0   1   2\n");
    for (int i = 0; i < ROW_LEN; ++i)
    {
        printf("%d ", i);
        for (int j = 0; j < COL_LEN; ++j)
        {
            printf("%c", array[i][j]);
            if (j < 2) printf(" | ");
        }
        printf("\n");
    }
}

/* validate whether input is inside the bound or 
   given place is preocupied */
bool validate_input(int i, int j, int row, int col, char array[row][col])
{
    int flag = 0;
    for (int num = 0; num < 3; ++num)
    {
        if (i == num) flag++;
        if (j == num) flag++;
    }
    if (flag == 2 && array[i][j] == ' ')
    {
        flag++;
    }
    return ((flag==3)?1:0);
}

//col checking function
bool checkcol(int row, int col, char array[row][col],char c)
{
    int val = 0;
    for (int i = 0; i < row; ++i)
    {
        int flag = 0;
        for (int j = 0; j < col; ++j)
        {
            if (array[i][j] == c) {flag++;} 
        }
        if (flag == 3) {val++; break;}
    }
    return ((val==1)?1:0);  
}

//row checking function
bool checkrow(int row, int col, char array[row][col],char c)
{
    int val = 0;
    for (int j = 0; j < row; ++j)
    {
        int flag = 0;
        for (int i = 0; i < col; ++i)
        {
            if (array[i][j] == c) {flag++;} 
        }
        if (flag == 3) {val++; break;}
    }
    return ((val == 1)?1:0);   
}

// forward slash cross checking function [00, 11, 02]
bool forward_slash(int row, int col, char array[row][col], char c)
{
    int flag = 0;   
    for (int i = 0; i < ROW_LEN; ++i)
    {
        if (array[i][i] == c) flag++;
    }
    return ((flag==3)?1:0);
}

// back slash cross checking function [02, 11, 20]
bool back_slash(int row, int col, char array[row][col], char c)
{
    int flag = 0;
    for (int i = 0, j = 2; i < 3; ++i, --j)
    {
        if (array[i][j] == c) flag++; 
    }
    return ((flag==3)?1:0);
}

/************************************************************** || MAIN  || *******************************************************************/

int main(int argc, char const *argv[])
{
    char table[ROW_LEN][COL_LEN];
    int turns = 10;
    // table clean
    for (int i = 0; i < ROW_LEN; ++i)
    {
        for (int j = 0; j < COL_LEN; ++j)
        {
            table[i][j] = ' ';
        }
    }

    system("cls");

    //ask player's name
    char player_1[STRING_INPUT_LEN];
    char player_2[STRING_INPUT_LEN];
    printf("----Note enter name within 30 characters!---\n");
    printf("Enter the name if u choose x: ");
    limit_input(player_1, STRING_INPUT_LEN);
    printf("Enter the name if u choose o: ");
    limit_input(player_2, STRING_INPUT_LEN);

    system("cls");

    //print table before loop begins
    table_print(ROW_LEN, COL_LEN, table);

    // tie check
    int tie_flag = 0;

    while (turns > 1)
    {
        //input and input validation
        int i, j;
        while (true) 
        {
            printf("Enter the position: ");
            scanf("%1d%1d", &i, &j);
            flush();
            //input validation
            bool a = validate_input(i, j, ROW_LEN, COL_LEN, table);
            if (a == 1)
            {
                //turn record and printing turns
                turns--;
                printf("round: %d\n", turns);
                break; 
            }

            else
            {
                system("cls");
                table_print(ROW_LEN, COL_LEN, table);
                printf("round: %d\n", turns); 
                printf("either the input valid is outside the bound"
                       "\n\tor\nthe given place is preoccupied\n");
                continue;
            }
        }

        //place allocation based on turns
        table[i][j] = ((turns%2)==0)?'o':'x'; 

        //update screen
        system("cls");

        //print table after loop begins
        table_print(ROW_LEN, COL_LEN, table);

        //check if x wins
        bool row_x = checkcol(ROW_LEN, COL_LEN, table, 'x');
        bool col_x = checkrow(ROW_LEN, COL_LEN, table, 'x');
        bool forward_x = forward_slash(ROW_LEN, COL_LEN, table, 'x');
        bool back_x = back_slash(ROW_LEN, COL_LEN, table, 'x');

        //check if y wins
        bool row_o = checkcol(ROW_LEN, COL_LEN, table, 'o');
        bool col_o = checkrow(ROW_LEN, COL_LEN, table, 'o');
        bool forward_o = forward_slash(ROW_LEN, COL_LEN, table, 'o');
        bool back_o = back_slash(ROW_LEN, COL_LEN, table, 'o');

        if (row_x || col_x || forward_x || back_x == 1)
        {
            printf("x won\n");
            printf("%s\n", player_1);
            tie_flag++;
            break;
        }
        else if (row_o || col_o || forward_o || back_o == 1) 
        {
            printf("o won\n");
            printf("%s\n", player_2);
            tie_flag++;
            break;
        }
    }
    if (tie_flag == 0) printf("Tie\n");
    else NULL;
    printf("GAME OVER!\n");
    system("pause");
    
    return 0;
}