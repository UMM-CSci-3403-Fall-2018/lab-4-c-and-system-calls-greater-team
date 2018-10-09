#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 1024

bool is_vowel(char c) { 
    /* 
     * Returns true if c is a vowel (upper or lower case), and 
     * false otherwise. 
     */
  char letter = tolower(c);
  if (letter == 'a' || letter == 'e' || letter == 'u' || letter == 'i' || letter== 'o') {
  return true;
  }  
  return false;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf. 
     * num_chars indicates how many characters are in in_buf, 
     * and this function should return the number of non-vowels that
     * that were copied over.
     */
  int num_not_vowels = 0;
  int j = 0;
  for (int i = 0; i < num_chars; i++) {
    if (!is_vowel(in_buf[i])){
      out_buf[j] = in_buf[i];
      num_not_vowels++;
      j++;
    }
  }
  return num_not_vowels;
}

void disemvowel(FILE* inputFile, FILE* outputFile) { 
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out. 
     */
  
  /*
   * int num_read = fread(--);
   * while(num_read>0) {
   *   fread a buffer full from inputFile
   *   use copy_non_vowels to remove vowels from that
   *   fwrite that vowel-free buffer to outputFile
   *   num_read = fread(--);
   * }
   */

   char* in_buf = (char*) calloc(BUF_SIZE, sizeof(char));
   char* out_buf = (char*) calloc(BUF_SIZE, sizeof(char));

   int num_read = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);

   while(num_read > 0) {
     int constonants = copy_non_vowels(strlen(in_buf), in_buf, out_buf);
     fwrite(out_buf, sizeof(char), constonants, outputFile);
     num_read = fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
   }
  

}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;
    
    if (argc == 1) {
      inputFile = stdin;
      outputFile = stdout;
    }
      
    if (argc == 2 && argv[1] == 0) {
        inputFile = stdin;
	outputFile = fopen(argv[2], "w");
    }

    if (argc == 2 && argv[2] == 0 ) {
        outputFile = stdout;
        inputFile = fopen(argv[1], "r");
    }
    
    if (argc == 3) {
        inputFile = fopen(argv[1], "r");
        outputFile = fopen(argv[2], "w");
    }

    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.

    disemvowel(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0; 
}
