// The MIT License (MIT)
//
// Copyright (c) 2016, 2017 Trevor Bakker
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 5     // Mav shell only supports five arguments

uint16_t BPB_BytesPerSec;
uint8_t BPB_SecPerClus;
uint16_t BPB_RsvdSecCnt;
uint8_t BPB_NumFATs;
uint16_t BPB_RootEntCnt;
uint32_t BPB_FATSz32;
struct __attribute__((__packed__)) DirectoryEntry
{
    char DIR_Name[11];
    uint8_t Dir_Attribute;
    uint16_t DIR_FstClusHI;
    uint8_t Unused[4];
    uint16_t DIR_FstClusLO;
    uint32_t DIR_FileSize;
};

struct DirectoryEntry dir[16];


int main()
{
    char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  while( 1 )
  {
    // Print out the mfs prompt
    printf ("mfs> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *arg_ptr;
                                                           
    char *working_str  = strdup( cmd_str );

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) &&
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    // Now print the tokenized input as a debug check
    // \TODO Remove this code and replace with your shell functionality
      FILE *fp;
      fp = fopen("fat32.img","r");
      
      if(!fp)
      {
          perror("Error opening file");
          exit(1);
      }
      
      int root_cluster = (BPB_NumFATs*BPB_FATSz32*BPB_BytesPerSec)+(BPB_RsvdSecCnt*BPB_BytesPerSec);
      int cd_offset = (6099-2)*BPB_BytesPerSec +(BPB_NumFATs*BPB_FATSz32*BPB_BytesPerSec)+(BPB_RsvdSecCnt*BPB_BytesPerSec);
      int FATAddress = (BPB_BytesPerSec * BPB_RsvdSecCnt) + (6099*4);
      
      fseek(fp, 11, SEEK_SET);
      fread(&BPB_BytesPerSec,1,2,fp);
      
      fseek(fp, 13, SEEK_SET);
      fread(&BPB_SecPerClus,1,1,fp);
      
      fseek(fp, 14, SEEK_SET);
      fread(&BPB_RsvdSecCnt,1,2,fp);
      
      fseek(fp, 16, SEEK_SET);
      fread(&BPB_NumFATs,1,1,fp);
      
      fseek(fp, 17, SEEK_SET);
      fread(&BPB_RootEntCnt, 1, 1, fp);
      
      fseek(fp, 36, SEEK_SET);
      fread(&BPB_FATSz32, 1, 4, fp);
      
      fseek(fp,root_cluster, SEEK_SET);
      fread(&dir[0], 16, sizeof(struct DirectoryEntry),fp);
      
      fseek(fp, cd_offset, SEEK_SET);
      fread(&dir[0], 16, sizeof(struct DirectoryEntry), fp);
      
      fseek(fp, FATAddress, SEEK_SET);
      int next;
      fread(&next, 1, 2, fp);
      
      printf("\nBPB_BytesPerSec: %d",BPB_BytesPerSec);
      printf("\nBPB_BytesPerSec: %x",BPB_BytesPerSec);
      printf("\nBPB_SecPerClus: %d",BPB_SecPerClus);
      printf("\nBPB_SecPerClus: %x",BPB_SecPerClus);
      printf("\nBPB_RsvdSecCnt: %d",BPB_RsvdSecCnt);
      printf("\nBPB_RsvdSecCnt: %x",BPB_RsvdSecCnt);
      printf("\nBPB_NumFATs: %d",BPB_NumFATs);
      printf("\nBPB_NumFATs: %x",BPB_NumFATs);
      printf("\nBPB_FATSz32: %d",BPB_FATSz32);
      printf("\nBPB_FATSz32: %x",BPB_FATSz32);
     
      printf("\nroot directory:%x",root_cluster);
      printf("\nNext cluster of directory: %d",next);
      
      int i;
      for (i=0; i<16; i++)
      {
          if(dir[i].Dir_Attribute == 0x01 || dir[i].Dir_Attribute == 0x10 || dir[i].Dir_Attribute == 0x20 || dir[i].Dir_Attribute != 0xe5)
          {
          printf("\nFile Name: %s and lower CLuster number: %d",dir[i].DIR_Name,dir[i].DIR_FstClusLO);
          }
      }
      FATAddress =(BPB_BytesPerSec * BPB_RsvdSecCnt) + (next*4);
      fseek(fp, FATAddress, SEEK_SET);
      fread(&next, 1, 2, fp);
      printf("\nNext cluster of directory: %d",next);
      fclose(fp);
      
      
      
      
    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ )
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );
    }

    free( working_root );

  }
  return 0;
}
