//============================================================================
// Name        : option.h
// Author      : TA's
// Date        :
// Copyright   : 
// Description : Command line processing for the sort program
//============================================================================

#ifndef OPTION_H_
#define OPTION_H_

#include <stdexcept>

class Option {
public:
   // user defined exception class
   struct InvalidArgument:public std::invalid_argument {
      InvalidArgument():std::invalid_argument(
           "Usage: ./sort [-a ALGORITHM] [-f INPUTFILE] [-o OUTPUTFILE] "
           "[-h] [-d] [-t] [-c]\n"
           "Try `./sort -h' for more information.") {}
   };
  
private:
   /// variables representing command line options provided by the user
   char        alg;         /// Algorithm selected
   const char* input_file;  /// Name of the input file if provided
   const char* output_file; /// Name of the output file if provided
   bool        show_help;   /// Whether to show help or not
   bool        show_input;  /// Whether to display unsorted input sequence
   bool        show_time;   /// Whether to display running time
   bool        show_num_cmps;/// Whether to display number of
                             /// element comparisons
   bool        show_output;  /// Whether to display sorted input sequence

public:  
   Option() : alg(0), input_file(NULL), output_file(NULL),
              show_help(false), show_input(false), show_time(false),
              show_num_cmps(false), show_output(false) {}
  
   /* initialize options according to command line */
   void init(int argc, char** argv)
      throw (InvalidArgument);
  
   /* accessor functions */
   char getAlg() const { return alg; } 
   const char* getInputFile() const { return input_file; }
   const char* getOutputFile() const { return output_file; }
  
   /* query functions */
   bool showHelp() const { return show_help; }
   bool showInput() const { return show_input; }
   bool showTime() const { return show_time; }
   bool showNumCmps() const { return show_num_cmps; }
   bool showOutput() const { return show_output; }
  
   /* print help message */
   void printUsage() const;
};

#endif // OPTION_H_
