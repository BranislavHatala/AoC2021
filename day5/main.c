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
    char orient;//orientation, v - vertical, h - horizontal, d - down( diagonal left to right descends downwards), u - up (diagonal from left to right rises upwards.)
};

struct OverLapPoint{
    int x;
    int y;
    int order; //how many vent lines overlap in this point
};



int findOverlaps(struct Line la, struct Line lb, struct OverLapPoint *pts, int *pCount);

//orders points and assing orientation to line struct
void LineOrderPoints(struct Line *line);

//swap points of line
void LineSwapPoints(struct Line *line);

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
        LineOrderPoints(&temp);
        lines[lineCount] = temp; //shallow copy is fine
        lineCount++;
    }

    //now check for overlaps
    for(int i = 0 ; i < (lineCount) ; i++)//iterate lines creating points
    {
        if(i%50 == 0)
        {
            printf("value: %d \n", i);
        }

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
        if(lines[i].orient == 'u')
        {
            for(int j = 0 ; j <= (lines[i].x2 - lines[i].x1) ; j++ )//j is now number of point in line
            {
                if(addPoint(lines[i].x1 + j , lines[i].y1 - j , points , &pointCount) == -1)
                {
                    printf("Points array ran out of space");
                }
            }
        }
        if(lines[i].orient == 'd')
        {
            for(int j = 0 ; j <= (lines[i].x2 - lines[i].x1) ; j++ )//j is now number of point on the line
            {
                if(addPoint(lines[i].x1 + j , lines[i].y1 + j , points , &pointCount) == -1)
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


void LineOrderPoints(struct Line *line)
{
    //first we deal with horizontal and vertical
    line->orient = 0;
    if((line->x1 == line->x2))
    {
        line->orient = 'v';
    }
    if((line->y1 == line->y2))
    {
        line->orient = 'h';
    }

    if(line->orient == 'h')
    {
        if(line->x1 > line->x2) //swap so line goes from left to right
        {
            LineSwapPoints(line);
        }
    }
    if(line->orient == 'v')
    {
        if(line->y1 > line->y2) //swap so line goes from left to right
        {
            LineSwapPoints(line);
        }
    }

    //now we deal with diagonal
    if(line->orient == 0)// line was not vertial or horizontal
    {
        //order points so starting point is the leftmost one
        if(line->x1 > line->x2)
        {
            LineSwapPoints(line);
        }
        //determine orientation
        if(line->y1 < line->y2)//down
        {
            line->orient = 'd';
        }
        else//up
        {
            line->orient = 'u';
        }
    }

}

void LineSwapPoints(struct Line *line)
{
    int swap = line->x2;
    line->x2 = line->x1;
    line->x1 = swap;

    swap = line->y2;
    line->y2 = line->y1;
    line->y1 = swap;
}
