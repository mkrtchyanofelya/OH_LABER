#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double rec_area(double a, double b);

int main(int argc, char** argv) {
  if (argc != 6) {
    printf("Wrong arguments count:\n");
    return 1;
  }

  double area = rec_area(atof(argv[1]), atof(argv[2]));

  if (area == -1) {
    return 1;
  }

  printf("Rectangle area = %f\n", area);

  int ret = execl("./triangle", "triangle", argv[3], argv[4], argv[5], (char*)NULL);
  
  if (ret) {
    printf("exec command issue:\n");
    return 1;
  }
}

double rec_area(double a, double b) {
  if (a <= 0 || b <= 0) {
    printf("One of the sides is negative:\n");
    return -1;
  }

  return a * b;
}
