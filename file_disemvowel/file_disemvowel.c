#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZE 1024

bool is_vowel(char c) { 

  char letter = tolower(c);
  
  if (letter == 'a' || letter == 'e' || letter == 'u' || letter == 'i' || letter== 'o') {
    return true;
  }
  
  return false;
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {

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

    disemvowel(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0; 
}
