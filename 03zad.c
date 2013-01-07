// gcc -Wall 03zad.c -o 03zad.o -lm


#include <stdio.h>
#include <math.h>


double differential(double x, double y)
{
  return 2.0 * sqrt(y - 2.0 * x) + 2.0;
}


double exact(double x)
{
  return x * x + 2.0 * x; 
}


int main()
{
  printf("\n   Zagadnienie różniczkowe:"); 
  printf("\n                y' = 2 * sqrt(y - 2x) + 2, y(1) = 3,");
  printf("\n   rozwiązać na przedziale [1, 3] metodą Eulera oraz udoskonaloną");
  printf("\n   metodą Eulera, zwaną metodą Heuna.");
  printf("\n   Wyniki  porównać  z  rozwiązaniem  dokładnym  y(x) = x^2 + 2x.\n");

  double h;

  do
  {
    printf("\n   Podaj krok całkowania z przedziału (0, 1):\n   h = ");
    scanf("%lf", &h);
  }
  while (h <= 0.0 || h >= 1.0);

  printf("\n        x      |  dokladne  |   Eulera   |    błąd    |   Heuna    |    błąd    ");
  printf("\n   ------------+------------+------------+------------+------------+------------");

  double x = 1,
         euler = 3.0,
         heun = 3.0;

  int i, guard;

  if ((3.0 - 1.0) / h > 30.0) guard = (int)(((3.0 - 1.0) / h) / 30.0);
  else guard = 1;

  for (i = 0; x <= 3.0 - h; i++)
  {
    euler = euler + differential(x, euler) * h;
    heun = heun + (differential(x, heun) + differential(x + h, heun + differential(x, heun) * h)) * h / 2;
    x += h;

    if (i % guard == 0)
    {
      printf("\n    %.8lf | %10.7lf | %10.7lf | %.8lf | %10.7lf | %.8lf ", x, exact(x), euler, fabs(euler - exact(x)), heun, fabs(heun - exact(x)));
    }  
  }

  printf("\n\n");

  return 0;
}
