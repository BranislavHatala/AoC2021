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

#define MAX 25
#define MAXLINECOUNT 600
#define MAXPOINTCOUNT 600000 //max points of everlap
#define BITS 12 //bit width of each entry

//strucure holding data of vulcanic vents line
struct Line{
    int x1;
    int y1;
    int x2;
    int y2;
    char orient;//orientation, v - vertical, h - horizontal
};

struct OverLapPoint{
    int x;
    int y;
    int order; //how many vent lines overlap in this point
};

//Checks if the line is diagonal, returns 1 if it is
int LineCheckDiag(struct Line *line);

int findOverlaps(struct Line la, struct Line lb, struct OverLapPoint *pts, int *pCount);

void LineOrderPoints(struct Line *line);

int addPoint(int x, int y, struct OverLapPoint *pts, int *pCount);

int main()
{
    FILE *fp;
    char buff[MAX];
    int lineCount = 0;// number of lines
    int pointCount = 0;
    struct Line lines[MAXLINECOUNT];
    //struct OverLapPoint points[MAXPOINTCOUNT];
    struct OverLapPoint *points;
    points = calloc(MAXPOINTCOUNT,sizeof(struct OverLapPoint));
    fp = fopen("input.txt", "r");


    while(fgets(buff, MAX, (FILE*)fp)) //read file adding lines array
    {
        //read and test line
        struct Line temp;
        sscanf(buff, "%d,%d -> %d,%d\n", &temp.x1, &temp.y1, &temp.x2, &temp.y2);//read buff into Line struct
        if(LineCheckDiag(&temp)) //skip diagonal lines
        {
            continue;
        }
        LineOrderPoints(&temp);
        lines[lineCount] = temp; //shallow copy is fine
        lineCount++;
    }

    //now check for overlaps
    for(int i = 0 ; i < (lineCount) ; i++)//check each line
    {
        if(lines[i].orient == 'h')
        {
            for(int j = lines[i].x1 ; j <= lines[i].x2 ; j++ )
            {
                if(addPoint(j,lines[i].y1, points, &pointCount) == -1)
                {
                    printf("Points array ran out of space");
                }
            }
        }
        if(lines[i].orient == 'v')
        {
            for(int j = lines[i].y1 ; j <= lines[i].y2 ; j++ )
            {
                if(addPoint(lines[i].x1, j, points, &pointCount) == -1)
                {
                    printf("Points array ran out of space");
                }
            }
        }
    }

    // count dangerous points
    int dangerCount = 0;
    for(int i = 0 ; i < pointCount ; i++)
    {
        if(points[i].order >= 2)
        {
            dangerCount++;
        }
    }
    free(points);
    points = 0;
    printf("value: %d \n", dangerCount);
    return 0;
}

int addPoint(int x, int y, struct OverLapPoint *pts, int *pCount)
{
    int retval = 0;
    //check if point already exists
    for(int i = 0 ; i < *pCount ; i++)
    {
        if((pts[i].x == x) && (pts[i].y == y))
        {
            pts[i].order++;
            retval = 1;
        }
    }
    if(retval == 0)//point was not found, it has to be made
    {
        if(*pCount <= MAXPOINTCOUNT)
        {
            pts[*pCount].x = x;
            pts[*pCount].y = y;
            pts[*pCount].order = 1;
            (*pCount)++;
        }
        else
        {
            retval = -1;
        }
    }
    return retval;
}
/*
int findOverlaps(struct Line la, struct Line lb, struct OverLapPoint *pts, int *pCount)
{
    int ovrlpStrt;//point overlap starts
    int ovrlpEnd;//point overlap ends

    if(la.orient == lb.orient)//paralell lines
    {
        if(la.orient == 'h')
        {
            if(la.x1 > lb.x1)//swap lines so a is the one on the left
            {
                struct Line swap = lb;
                lb = la;
                la = swap;
            }

            if(la.x2 >= lb.x1)//is there a overlap, if yes then we know it starts lb.x1
            {
                ovrlpStrt = lb.x1;
                if(lb.x2 < la.x2)
                {
                    ovrlpEnd = lb.x2;
                }
                else
                {
                    ovrlpEnd = la.x2;
                }


            }

            //now to create points

        }
    }
}
*/
int LineCheckDiag(struct Line *line)
{
    int retval = 1;
    if((line->x1 == line->x2))
    {
        retval = 0;
        line->orient = 'v';
    }
    if((line->y1 == line->y2))
    {
        retval = 0;
        line->orient = 'h';
    }

    return retval;
}

void LineOrderPoints(struct Line *line)
{
    if(line->orient == 'h')
    {
        if(line->x1 > line->x2) //swap so line goes from left to right
        {
            int swap = line->x2;
            line->x2 = line->x1;
            line->x1 = swap;
        }
    }
    if(line->orient == 'v')
    {
        if(line->y1 > line->y2) //swap so line goes from left to right
        {
            int swap = line->y2;
            line->y2 = line->y1;
            line->y1 = swap;
        }
    }
}
