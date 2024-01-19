#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {

  // Open the filename given as the first command line argument for reading
  FILE* fp = fopen(argv[1], "r");
  if (!fp) {
    perror("fopen failed");
    return EXIT_FAILURE;
  }

  char buf[256];

  char* string = fgets(buf, 256, fp);
  int x = atoi(string);

  char* string2 = fgets(buf, 256, fp);
  int y = atoi(string2);

  typedef enum { F, T } boolean;
  boolean bool1;
  bool1 = T;

  if(bool1){
    double var0 = sqrt((x*x)+(y*y));
    int temp = (int) var0;
    if(var0/temp == 1){
      printf( "%d\n", temp );
      bool1 = F;
    }
  }
  if((x*x)>(y*y) && bool1 == T){
    double var1 = sqrt((x*x)-(y*y));
    int temp = (int) var1;
    if(var1/temp == 1){
      printf( "%d\n", temp );
    }
    else {
      printf( "%d\n", -1);
    }
  }

  if((x*x)<(y*y) && bool1 == T){
    double var2 = sqrt((y*y)-(x*x));
    int temp = (int) var2;
    if (var2/temp == 1){
      printf("%d\n", temp);
    }
    else{
      printf( "%d\n", -1 );
    }
  }
  // Printing in C.
  // %d is the format specifier for integer numbers.
  // \n is the newline character
  //printf( "%d\n", x );
  return EXIT_SUCCESS;

}
