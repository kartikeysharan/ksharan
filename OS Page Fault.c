//
//  pagefaults.c
//  pagefault
//
//  Created by Susanth Kakarla on 4/10/20.
//  Copyright © 2020 Susanth Kakarla. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 1024

int main( int argc, char * argv[] )
{
  char * line = NULL;
  size_t line_length = MAX_LINE;
  char * filename;

  FILE * file;

  if( argc < 2 )
  {
    printf("Error: You must provide a datafile as an argument.\n");
    printf("Example: ./fp datafile.txt\n");
    exit( EXIT_FAILURE );
  }

  filename = ( char * ) malloc( strlen( argv[1] ) + 1 );
  line     = ( char * ) malloc( MAX_LINE );

  memset( filename, 0, strlen( argv[1] + 1 ) );
  strncpy( filename, argv[1], strlen( argv[1] ) );

  printf("Opening file %s\n", filename );
  file = fopen( filename , "r");

    
  int count = -1;
  int page_string [100];
  if ( file )
  {
    while (fgets( line, line_length, file ) )
    {
        count = 0 ;
        char * token;
        token = strtok( line, " ");
        int set_size = atoi( token );
        
        while( token != NULL )
        {
         
            token = strtok( NULL, " " );
            if( token != NULL )
            {
                count++;
                page_string[count] = atoi(token);
            }
        }
//---------------------------------FIFO--------------------------------
        int current[set_size];
        bool b_empty = true, end = false, cont =  true,go = true;
        int empty_count = 1;
        int i=0,x = 0,y=0,z=0,a=0, fifo_page_faults = 0,lru_page_faults=0,index = 1;
        for(i = 1; b_empty; i++ )
        {
            //Getting the initial sets
            if (empty_count<=set_size)
            {
                for(x = 1; x <= empty_count; x++)
                {
                    if (current[x] == page_string[i])
                        end = true;
                    }
                    if(end == false)
                    {
                        current[empty_count] = page_string[i];
                        fifo_page_faults +=1;
                        empty_count +=1;
                    }
                    end = false;
                }
                else
                {
                    b_empty = false;
                }
        }
        for(i = set_size; i<= count; i++)
        {
            for (x = 1; x<= set_size; x++)
            {
                if (current[x] == page_string[i])
                    cont = false;
            }
        
            if(cont)
            {
                current[index] = page_string[i];
                if (index == set_size)
                    index = 1;
                else
                    index +=1;
                fifo_page_faults +=1;
            }
            cont = true;
        }
            printf("Page faults of FIFO:  %d \n", fifo_page_faults);
    
//---------------------------------LRU--------------------------------
        for(i = 0; i<= set_size; i++) //resetting current
            current[i] =-1;
        int max = 0, max_change =0,empty =1;
        
        cont = true;
        int checker[10];
        for(i = 1; i<= count; i++)
        {
            for(x = 1; x<= empty; x++)
            {
                if(current[x] == page_string[i])
                {
                    cont = false;
                    checker[page_string[i]] = 1;
                    for(y = 1; y<= 9; y++)
                    {
                        if(checker[y]>0 && y!=i)
                            checker[y]+=1;
                    }
                }
            }
        if (cont &&  go)
        {
            current[empty] = page_string[i];
            checker[page_string[i]] =+1;
            lru_page_faults+=1;
            for(a = 1; a<= 9; a++)
            {
                if(checker[a]>0 && a != i)
                    checker[a]+=1;
            }
        }
        else if (cont)
        {
            checker[page_string[i]] +=1;
            for(z = 1; z<= 9; z++)
            {
                if(checker[z] >0 && z != i)
                    checker[z] +=1;
                if(checker[z] >= max)
                {
                    max = checker[z];
                    max_change = z;
                }
            }
            for(y = 1; y<=set_size; y++)
            {
                if(current[y] == max_change)
                {
                    checker[max_change] = 0;
                    current[y]= page_string[i];
                    lru_page_faults+=1;
                }
            }
        }
        if(empty <set_size) //allows the last element of the set size to be filled
            empty+=1;
        else
            go = false;
        cont = true;
        max = checker[1];
    }
        printf("Page faults of LRU:  %d \n", lru_page_faults);
//---------------------------------MRU--------------------------------
        for(i = 1; i<= set_size; i++) //resetting current
            current[i] =0;
        cont = true;
        go = true;
        empty = 1;
        int recent = 0, mfu_page_faults=0;
        for( i = 1; i <= count;i++)
        {
            for(x = 1; x<= empty; x++)
                {
                    if(current[x] == page_string[i])
                    {
                        recent = x;
                        cont = false;
                    }
                }
                if(cont && empty <=set_size && go) //only used to fill the set_size of elements
                {
                    current[empty] = page_string[i];
                    recent = empty;
                    mfu_page_faults+=1;
                }
                else if(cont)// used after the initial set size is full
                {
                    current[recent] = page_string[i];
                    mfu_page_faults +=1;
                }
                if(empty <set_size) //allows the last element of the set size to be filled
                    empty+=1;
                else
                    go = false;
                
                cont = true;
            }
            printf("Page faults of MRU:  %d \n", mfu_page_faults);
//------------------------------Optimal--------------------------------
        for(i = 1; i<= set_size; i++) //resetting current
            current[i] =0;
        b_empty = true;
        end = false;
        cont = true;
        go = true;
        empty = 1;
        max = -1;
        int O_page_faults = 0;
        for(i = 1; b_empty; i++ )
        {
            
            //Getting the initial sets
            if (empty<=set_size)
            {
                for(x = 1; x <= empty; x++)
                {
                    if (current[x] == page_string[i])
                        end = true;
                }
                if(end == false)
                {
                    current[empty] = page_string[i];
                    O_page_faults +=1;
                    empty +=1;
                }
                end = false;
            }
            else
            {
                b_empty = false;
            }
        }
        for( i = set_size; i<=count; i++)
        {
            for(x = 1; x<= set_size; x++)
            {
                if(current[x] == page_string[i])
                    cont = false;
            }
            if (cont)
            {
                for(y = 1; y<= set_size; y++)
                {
                    for(z = i; z<= count; z++)
                    {
                        if (current[y] == page_string[z])
                        {
                            go = false;
                            if(z > max)
                                max = z;
                        }
                    }
                }
                
                if(go)
                {
                    current[1] = page_string[i];
                    O_page_faults+=1;
                }
                else
                {
                    for(a = 1; a<= set_size; a++)
                    {
                        if(current[a] == page_string[max])
                        {
                            current[a] = page_string[i];
                            O_page_faults+=1;
                        }
                            
                    }
                }
            }
            cont = true;
            go = true;
            max = -1;
        }
        printf("Page Faults of Optimal: %d \n", O_page_faults);
        printf("------------------------------------------------------------\n");
        }
      
    }
    free( line );
    fclose(file);
    

  return 0;
}
