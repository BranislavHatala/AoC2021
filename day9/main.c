/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXPOINTS 10000

struct HMap{
    char hmap[MAXPOINTS];
    int width;
    int length;
    int height;
};

int ReadHeightMap(struct HMap *mp);

int DangerSum(struct HMap *mp);

FILE *g_fp;


int main()
{
    struct HMap hmap;
    g_fp = fopen("input.txt", "r");

    ReadHeightMap(&hmap);

    int value = DangerSum(&hmap);


    printf("value: %lld \n", value);
    return 0;
}

int DangerSum(struct HMap *mp)
{
    int retval = 0;
    for(int i = 0 ; i < mp->length ; i++)
    {
        //check multiple condition, any of these disqualify point as lowpoint
        if( i >= mp->width)//is not top edge
        {
            if(mp->hmap[i] >=  mp->hmap[i - mp->width])//check above
            {
                continue;
            }
        }
        if(((i+1)%mp->width) != 0)//is not right edge
        {
            if(mp->hmap[i] >=  mp->hmap[i + 1])//to the right
            {
                continue;
            }
        }
        if( i < (mp->length - (mp->width - 1)))//is not bottom edge
        {
            if(mp->hmap[i] >=  mp->hmap[i + mp->width])//check below
            {
                continue;
            }
        }
        if((i % mp->width) != 0)//is not left edge
        {
            if(mp->hmap[i] >=  mp->hmap[i - 1])//check to the left
            {
                continue;
            }
        }

        //after this point it is certain this point is lowpoint
        retval += 1 + mp->hmap[i];

    }
    return retval;
}


//read heightmap from input.txt returns its lenght
int ReadHeightMap(struct HMap *mp)
{
    int c = getc(g_fp);
    mp->width = 0;

    int i  = 0;
    while(c != EOF)
    {

        if(c == '\n')
        {
            if(mp->width == 0)//if width is uknown
            {
                mp->width = i;//this is the width
            }
        }
        else
        {
            mp->hmap[i] = (char)(c-48);//converts acii to num
            i++;
        }

        c = getc(g_fp);
    }
    mp->length = i;
    mp->height = mp->length / mp->width;
    return i;
}

