// The MIT License (MIT)
//
// Copyright (c) 2020 Trevor Bakker
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024

int array[MAX_LINE/2];
int page_faults = 0;

void initialize_check(int working_set_size)
{
  page_faults = 0;
  int j = 0;
  for(j = 0; j < working_set_size; j++)
  {
    array[j] = -1;
  }
}

int check_present(int check, int working_set_size)
{
  int present = 0;
  int k  = 0;
  while(k < working_set_size)
  {
    if(array[k] != check){}
    else
    {
      present = 1;
      break;
    }
    k++;
  }
  return present;
}

int get_check_index(int check, int working_set_size)
{
  int check_index;
  int i = 0;
  while(i < working_set_size)
  {
    if(array[i] != check){}
    else
    {
      check_index = i;
      break;
    }
    i++;
  }
  return check_index;
}

int FIFO_pagefault(int pages[], int working_set_size, int length)
{
  initialize_check(working_set_size);
  int i,j = 0;
  for(i = 0; i < length; i++)
  { 
    if(check_present(pages[i],working_set_size) == 0)
    {
      for(j = 0; j < working_set_size-1 ;j++)
      {
        array[j]=array[j+1];
      }
      array[j]=pages[i];
      page_faults = page_faults + 1;
    }
  }
  return page_faults;
}

//int optimal_pagefault(int pages[], int working_)

int main( int argc, char * argv[] ) 
{
  int pages[MAX_LINE];
  int working_set_size = 0;
  int length = 0;
  char * line = NULL;
  size_t line_length = MAX_LINE;
  char * filename;

  FILE * file;

  if( argc < 2 )
  {
    printf("Error: You must provide a checkfile as an argument.\n");
    printf("Example: ./fp checkfile.txt\n");
    exit( EXIT_FAILURE );
  }

  filename = ( char * ) malloc( strlen( argv[1] ) + 1 );
  line     = ( char * ) malloc( MAX_LINE );

  memset( filename, 0, strlen( argv[1] + 1 ) );
  strncpy( filename, argv[1], strlen( argv[1] ) );

  printf("Opening file %s\n", filename );
  file = fopen( filename , "r");

  if ( file ) 
  {
    while ( fgets( line, line_length, file ) )
    {
      char * token;

      token = strtok( line, " ");
      working_set_size = atoi( token );

      //printf("\nWorking set size: %d\n", working_set_size );
 
      while( token != NULL )
      {
        token = strtok( NULL, " " );
        
        if( token != NULL )
        {
          pages[length] = atoi(token);
          //printf("Request: %d\n", pages[length]); 
          length++;
        }
      }
      //printf("\n");
      
    }

    //printf("%d\n",length);
    printf("%d\n",FIFO_pagefault(pages,working_set_size,length));
    free( line );
    fclose(file);
  }

  return 0;
}

