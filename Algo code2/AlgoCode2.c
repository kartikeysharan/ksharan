//
//
//  AlgoCode2
//
//  Name: Kartikey Sharan on 03/10/19.
// student ID 1001659433
//command: gcc AlgoCode2.c
//

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int washing_time;
    int drying_time;
    int number;
}load;
int comparator(const void *p, const void *q)
{
    load const *l = (load const *)p;
    load const *r = (load const *)q;
    int num1;
    int num2;
    if(l->drying_time >= l->washing_time)
        num1= l->washing_time;
    else
        num1= l->drying_time;
    if(r->drying_time >= r->washing_time)
        num2=r->washing_time;
    else
        num2=r->drying_time;
    return (num1-num2);
        
}
int main()
{
    int numloads=3;
    int counter =0;
    load *loads = malloc(numloads * sizeof(load));
    scanf("%d",&numloads);
    for(counter = 0; counter < numloads ; counter++)
    {
        
        scanf("%d %d",&loads[counter].washing_time,&loads[counter].drying_time);
        loads[counter].number = counter;
        
    }
    qsort(loads,numloads , sizeof(load),comparator);
    int *timetask = (int *)malloc(numloads * sizeof(int));
    int first=0;
    int last=counter-1;
    for(counter = 0; counter< numloads; counter++)
    {
        if(loads[counter].drying_time >= loads[counter].washing_time)
        {
            timetask[first] = counter;
            first++;
        }
        else
        {
            timetask[last] = counter;
            last--;
        }
    }
    
    int washing = 0;
    int drying = loads[timetask[0]].washing_time;;
    for(counter = 0;counter < numloads; counter++)
    {
       if((washing + loads[timetask[counter]].washing_time) > drying)
       {
           printf("\ngap from %d to ",drying);
           drying += ((washing + loads[timetask[counter]].washing_time) - drying);
           printf("%d",drying);
       }
       printf("\n%d %d %d %d ",loads[timetask[counter]].number,loads[timetask[counter]].washing_time,loads[timetask[counter]].drying_time,washing);
       washing += loads[timetask[counter]].washing_time;
       
       printf("%d",drying);
       drying += loads[timetask[counter]].drying_time;
    }
    printf("\nmakespan is %d",drying);
    
    
    
    return 0;
                         
}
