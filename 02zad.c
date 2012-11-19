/// gcc -Wall 02zad.c -o 02zad.o -lm


#include <stdio.h>
#include <math.h>


#define E 2.71828183


int iB = 0,
    iN = 0;


double equation(double x)
{
  return 3 * x + 2 - pow(E, x);
}


double equationDerivative(double x)
{
  return 3 - pow(E, x);
}


double bisection(double left, double right, double epsilon)
{
  double point = (left + right) / 2;

  while(fabs(left - right) > epsilon)
  {
    iB++;

    point = (left + right) / 2;

    if (equation((point) == 0)) break;

    if (equation(point) * equation(left) < 0) right = point;
    else left = point;
  }

  return point;
}


double  newton(double epsilon)
{
  iN++;

  return epsilon;
}


int main()
{
  printf("\n   Dla  równania  f(x) = 0,  gdzie  f(x) = 3x + 2 - e^x,  wczytać  a, b  należące");
  printf("\n   do zbioru liczb rzeczywistych takie, by a < b oraz f(a) * f(b) < 0. Następnie,");
  printf("\n   dopóki  \"użytownik się nie znudzi\",  wczytywać  wartości  0 < E < 1  i  metodą");
  printf("\n   połowienia  na  [a, b]  przybliżyc z dokładnością E rozwiązanie tego równania.");
  printf("\n   Rozwiązanie to przybliżyc również metodą Newtona  z  x_0 = a,  przy czym,  x_k");
  printf("\n   będzie  dobrym   przybliżeniem,  gdy  |x_k - x_(k - 1)| <= E.  Porównać  ilość");
  printf("\n   kroków wykonanych metodą połowienia i metodą Newtona.\n");

  double a, b;

  printf("\n   Podaj a należące do zbioru liczb rzeczywistych:\n   a = ");
  scanf("%lf", &a);

  b = a;

  while(a >= b || equation(a) * equation(b) >= 0)
  {
    printf("\n   Podaj b należące do zbioru liczb rzeczywistych,\n   takie by b > a oraz f(b) * f(a) < 0\n   b = ");
    scanf("%lf", &b);
  }

  double epsilon;
  int choice;

  while (1)
  {
    printf("\n   1 - Przybliż rozwiazanie dla innego E");
    printf("\n   2 - Zakoncz program");
    printf("\n   Twoj wybor: ");
    scanf("%i", &choice);

    switch (choice)
    {
      case 1:
        epsilon = 0;

        while (epsilon <= 0 || epsilon >= 1)
        {
          printf("\n   Podaj E, takie by 0 < E < 1:\n   E = ");
          scanf("%lf", &epsilon);
        }

        printf("\n   Metoda połowienia:\n   %.6lf - przybliżone rozwiązanie\n   %8i - ilość kroków\n", bisection(a, b, epsilon), iB);
        printf("\n   Metoda Newtona:\n   %.6lf - przybliżone rozwiązanie\n   %8i - ilość kroków\n", newton(epsilon), iN);

        iB = iN = 0;

        break;

      case 2:
        printf("\n");
        return 0;
    }
  }
}
