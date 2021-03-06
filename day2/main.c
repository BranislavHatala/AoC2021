/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int main()
{
    FILE *fp;
    int comm; //command
    char buff[MAX];
    int num;
    fp = fopen("input.txt", "r");
    int depth = 0;
    int pos = 0;
    int aim = 0;

    for(;;) //read command, we use the fact that commands have distinct initial char
    {
        comm = fgetc((FILE*)fp);
        if(comm == EOF)//check if end of file reached
        {
            break;
        }
        while(fgetc((FILE*)fp) != ' ')//advance iterator to get to num in next read
        {
            //NOP
        }

        if(fgets(buff, MAX, (FILE*)fp) )// read value for command
        {
            num = atoi(buff);
        }
        else
        {
            printf("ERROR: failed to read value for command");
        }

        switch(comm)//execute command
        {
            case 'u': //up
                aim-=num;
                if(depth<0)
                {
                    printf("ERROR: your submarine lacks technical equipment to soar the sky");
                }
                break;
            case 'd': //down
                aim+=num;
                break;
            case 'f': //forward
                pos+=num;
                depth += aim*num;
                break;
            default:
                printf("ERROR: uknown command");
                break;
        }

    }
    printf("result: %d \n", depth*pos);
    return 0;
}
