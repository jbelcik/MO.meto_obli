#include <stdio.h>


int n = -1;


void polynomialUnion (double *poly1, double *poly2)
{
  int i;

  for (i = 0; i <= n; i++) poly1[i] += poly2[i];
}


void polynomialIntersection (double *poly1, double *poly2)
{
  int i;
  double polyH[2][n + 1];

  for (i = 0; i <= n; i++)
  {
    polyH[0][i] = poly2[0] * poly1[i];
    polyH[1][i + 1] = poly2[1] * poly1[i];
  }

  polynomialUnion(polyH[0], polyH[1]);

  for (i = 0; i <= n; i++)
  {
    poly1[i] = polyH[0][i];
  }
}


void polynomialIntersectionByConstans (double *poly, double con)
{
  int i;

  for (i = 0; i <= n; i++) poly[i] *= con;
}


void polynomialDerivative (double *poly1, double *poly2)
{
  int i;

  for (i = 1; i <= n; i++) poly1[i - 1] = poly2[i] * i;
}


float polynomialResult (double *poly, double value)
{
  int i;

  double result = poly[n];

  for (i = n - 1; i >= 0; i--)
  {
    result = value * result + poly[i];
  }

  return result;
}


void polynomialPrint (double *poly)
{
  int i, guard = 1;

  for (i = n; i >= 0; i--)
  {
    if (poly[i] != 0)
    {
      guard = 0;

      if (poly[i] > 0 && i + 1 <= n && poly[i + 1] != 0) printf("+");
      if (i == 0) printf("%lf ", poly[i]);
      else if (i == 1)
      {
        if (poly[i] == 1) printf("x ");
        else if (poly[i] == -1) printf("-x ");
        else printf("%lfx ", poly[i]);
      }
      else
      {
        if (poly[i] == 1) printf("x^%i ", i);
        else if (poly[i] == -1) printf("-x^%i ", i);
        else printf("%lfx^%i ", poly[i], i);
      }
    }
  }

  if (guard == 1) printf("0");
}


int main()
{
  printf("\n   Ustalić naturalną n_max. Wczytać n  z zakresu '0 - n_max'  oraz różne\n");
  printf("   węzły x[0], x[1], ..., x[n] i dowolne wartości A[0], A[1], ..., A[n].\n");
  printf("   Wielomian  interpolacyjny  w  postaci  Lagrange'a  L = L(x)  taki, że\n");
  printf("   L(x[i]) = f[i] dla i = 0, 1, ..., n,  przedstawić w postaci  ogólnej.\n");
  printf("   Następnie,   \"dopóki  użytkownik  się  nie  znudzi\",   wczytywać  'j'\n");
  printf("   z zakresu '0 - n' oraz 't'  należace  do zbioru  liczb  rzeczywistych\n");
  printf("   i obliczać pochodne dla W(t) stopnia 'j'.\n\n");

  int nMax = 100, i, j, guard;
  
  while (n < 0 || n > nMax)
  {
    printf("   Podaj 'n' z zakresu '0 - %i':\n", nMax);
    printf("   n = ");
    scanf("%i", &n);
    printf("\n");
  }

  double x[n + 1],
         A[n + 1],
         divisor[n + 1],
         H[n + 1][2],
         L[n + 1][n + 1],
         polyH[n + 1],
         W[n + 1];

  printf("   Podaj dane (każda wartość dla 'x' musi być różna od siebie):\n");

  for (i = 0; i <= n; i++)
  {
    guard = 1;

    while (guard == 1)
    {
      printf("   x[%i] = ", i);
      scanf("%lf", &x[i]);

      if (i > 0)
      {
        for (j = 0; j < i; j++)
        {
          if (x[i] == x[j])
          {
            printf("   Wartość %lf dla 'x' została już wprowadzona (w x[%i]). Wprowadź inną wartość.\n\n", x[i], j);
            guard = 1;
            break;
          }
          else guard = 0;
        }
      }
      else guard = 0;
    }

    printf("   A[%i] = ", i);
    scanf("%lf", &A[i]);
    printf("\n");
  }

  for (i = 0; i <= n; i++)
  {
    for (j = 0; j <= n; j++)
    {
      if (j == 0) L[i][j] = 1;
      else L[i][j] = 0;
    }
    
    H[i][0] = x[i] * -1;
    H[i][1] = 1;
    polyH[i] = 0;
    W[i] = 0;
  }

  for (i = 0; i <= n; i++)
  {
    divisor[i] = 1;

    for (j = 0; j <= n; j++)
    {
      if (j != i)
      {
        divisor[i] *= 1 / (x[i] - x[j]);
        polynomialIntersection(L[i], H[j]);
      }
    }

    polynomialIntersectionByConstans(L[i], divisor[i] * A[i]);
    polynomialUnion(W, L[i]);
  }

  printf("   Postać ogólna wyliczonego wielomianu:\n   W(x) = ");
  polynomialPrint(W);

  printf("\n");

  int choice, s;
  double t, result;

  while (1)
  {
    printf("\n   1 - Oblicz pochodną dla W(t) stopnia 'j'\n");
    printf("   2 - Zakończ program\n");
    printf("   Twój wybór: ");
    scanf("%i", &choice);

    switch (choice)
    {
      case 1:
        s = -1;

        while(s < 0 || s > n)
        {
          printf("\n   Podaj 'j' z zakresu '0 - %i':\n   j = ", n);
          scanf("%i", &s);
        }

        printf("   Podaj 't' należące do zbioru liczb rzeczywistych:\n   t = ");
        scanf("%lf", &t);

        for (i = 0; i < s; i++)
        {
          if (i == 0) polynomialDerivative(polyH, W);
          else polynomialDerivative(polyH, polyH);
        }
        
        printf("\n   Pochodna dla W(x) stopnia '%i' wynosi:\n   ", i);
        
        if (s == 0)
        {
          polynomialPrint(W);
          result = polynomialResult(W, t);
        }
        else
        {
          polynomialPrint(polyH);
          result = polynomialResult(polyH, t);
        }
        
        printf("\n\n   Pochodna dla W(%lf) stopnia '%i' wynosi:\n   %lf\n", t, s, result);

        break;

      case 2:
        printf("\n");
        return 0;
    }
  }
}
