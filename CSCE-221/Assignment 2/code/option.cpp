//============================================================================
// Name        : option.cpp
// Author      : TA's
// Date        :
// Copyright   : 
// Description : Command line processing for the sort program
//============================================================================

#include <iostream>
#include "option.h"

/* initialize options according to command line */
void Option::init(int argc, char** argv)
   throw (InvalidArgument)
{
   // loop through all the arguments except for the program name itself
   for (int i = 1; i < argc; i++)
      {
         char* p = argv[i];

         // if option does not start from dash, report an error
         if (*p != '-') throw InvalidArgument(); 

         switch (p[1]) // switch on whatever comes after dash
            {
            case 'a': if (i+1 < argc) alg = argv[++i][0]; break;
            case 'f': if (i+1 < argc) input_file  = argv[++i]; break;
            case 'o': if (i+1 < argc) output_file = argv[++i]; break;
            case 'h': show_help   = true; break;
            case 'd': show_input  = true; break;
            case 't': show_time   = true; break;
            case 'c': show_num_cmps = true; break;
            case 'p': show_output = true;  break;
            default : throw InvalidArgument();
            }
      }

   if (!show_help && alg!='S' && alg!='B' &&
       alg!='I' && alg!='H' && alg!= 'R')
      throw InvalidArgument();          
}


void Option::printUsage() const {
   std::cout <<
      "Usage: ./sort [-a ALGORITHM] [-f INPUTFILE] [-o OUTPUTFILE] [-h] "
      "[-d] [-p] [-t] [-c]\n"
      "Read an integer sequence and display the sorted sequence, "
      "a program written by\n"
      "Raymond Zhu, Wesley Ng\n"
      "Example: ./sort -a S -f input.txt -o output.txt -t -c -p\n"
      "         ./sort -h\n"
      "Options:\n"
      "  -a ALGORITHM    Use ALGORITHM to sort.\n"
      "     ALGORITHM is a single character representing an algorithm:\n"
      "     S   (selection sort)\n"
      "     B   (bubble sort)\n"
      "     I   (insertion sort)\n"
      "     H   (shell sort)\n"
      "     R   (radix sort)\n" 
      "  -f INPUTFILE    Obtain integers from INPUTFILE instead of STDIN\n"
      "  -o OUTPUTFILE   Place output message into OUTPUTFILE "
      "instead of STDOUT\n"
      "  -h  Display this help and exit\n"
      "  -d  Display input: unsorted integer sequence\n"
      "  -p  Display output: sorted integer sequence\n"
      "  -t  Display running time of the chosen algorithm in milliseconds\n"
      "  -c  Display number of element comparisons (excluding radix sort)\n";
}

