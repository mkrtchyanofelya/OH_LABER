#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double tri_area(double a, double b, double c);

int main(int argc, char** argv) {
  if (argc != 4) {
    printf("Wrong amount of arguments:\n");
    return 1;
  }

  double area = tri_area(atof(argv[1]), atof(argv[2]), atof(argv[3]));

  if (area == -1) {
    return -1;
  }

  printf("The area of triangle = %f\n", area);

  return 0;
}

double tri_area(double a, double b, double c) {
  if (a <= 0 || b <= 0 || c <= 0) {
    printf("One of the sides is negative:\n");
    return -1;
  }

  if (a + b <= c || a + c <= b || b + c <= c) {
    printf("Can't be triangle with this sides:\n");
    return -1;
  }
	
  double p = (a + b + c) / 2;

  return sqrt(p * (p - a) * (p - b) * (p - c));
}
