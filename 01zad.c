#include <stdio.h>


int n = -1;


void polynomialUnion (float *poly1, float *poly2)
{
  int i;

  for (i = 0; i <= n; i++) poly1[i] += poly2[i];
}


void polynomialIntersection (float *poly1, float *poly2)
{
  int i;
  float polyH[2][n + 1];

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


void polynomialIntersectionByConstans (float *poly, float con)
{
  int i;

  for (i = 0; i <= n; i++) poly[i] *= con;
}


void polynomialDerivative (float *poly)
{
  int i;

  for (i = 1; i <= n; i++) poly[i - 1] = poly[i] * i;

  poly[i - 1] = 0;
}


float polynomialResult (float *poly, float value)
{
  int i;

  float result = poly[n];

  for (i = n - 1; i >= 0; i--)
  {
    result = value * result + poly[i];
  }

  return result;
}


void polynomialPrint (float *poly)
{
  int i, guard = 1;

  for (i = n; i >= 0; i--)
  {
    if (poly[i] != 0)
    {
      guard = 0;

      if (poly[i] > 0 && i + 1 <= n && poly[i + 1] != 0) printf("+");
      if (i == 0) printf("%f ", poly[i]);
      else if (i == 1)
      {
        if (poly[i] == 1) printf("x ");
        else if (poly[i] == -1) printf("-x ");
        else printf("%fx ", poly[i]);
      }
      else
      {
        if (poly[i] == 1) printf("x^%i ", i);
        else if (poly[i] == -1) printf("-x^%i ", i);
        else printf("%fx^%i ", poly[i], i);
      }
    }
  }

  if (guard == 1) printf("0");
}


int main()
{
  printf("\n   Ustalić naturalną n_max. Wczytać n  z zakresu '0 - n_max'  oraz różne\n");
  printf("   węzły x[0], x[1], ..., x[n] i dowolne wartości f[0], f[1], ..., f[n].\n");
  printf("   Wielomian  interpolacyjny  w  postaci  Lagrange'a  L = L(x)  taki, że\n");
  printf("   L(x[i]) = f[i] dla i = 0, 1, ..., n,  przedstawić w postaci  ogólnej.\n");
  printf("   Następnie,   \"dopóki  użytkownik  się  nie  znudzi\",   wczytywać  's'\n");
  printf("   z zakresu '0 - n' oraz 't'  należace  do zbioru  liczb  rzeczywistych\n");
  printf("   i obliczać pochodne dla W(t) stopnia 's'.\n\n");

  int nMax = 100, i, j, guard;
  
  while (n < 0 || n > nMax)
  {
    printf("   Podaj 'n' z zakresu '0 - %i':\n", nMax);
    printf("   n = ");
    scanf("%i", &n);
    printf("\n");
  }

  float x[n + 1],
        f[n + 1],
        divisor[n + 1],
        H[n + 1][2],
        L[n + 1][n + 1],
        W[n + 1];

  printf("   Podaj dane (każda wartość dla 'x' musi być różna od siebie):\n");

  for (i = 0; i <= n; i++)
  {
    guard = 1;

    while (guard == 1)
    {
      printf("   x[%i] = ", i);
      scanf("%f", &x[i]);

      if (i > 0)
      {
        for (j = 0; j < i; j++)
        {
          if (x[i] == x[j])
          {
            printf("   Wartość %f dla 'x' została już wprowadzona (w x[%i]). Wprowadź inną wartość.\n\n", x[i], j);
            guard = 1;
            break;
          }
          else guard = 0;
        }
      }
      else guard = 0;
    }

    printf("   f[%i] = ", i);
    scanf("%f", &f[i]);
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

    polynomialIntersectionByConstans(L[i], divisor[i] * f[i]);
    polynomialUnion(W, L[i]);
  }

  printf("   Postać ogólna wyliczonego wielomianu:\n   W = ");
  polynomialPrint(W);

  printf("\n");

  int choice, s;
  float t, result;

  while (1)
  {
    printf("\n   1 - Oblicz pochodną dla W(t) stopnia 's'\n");
    printf("   2 - Zakończ program\n");
    printf("   Twój wybór: ");
    scanf("%i", &choice);

    switch (choice)
    {
      case 1:
        s = -1;

        while(s < 0 || s > n)
        {
          printf("\n   Podaj 's' z zakresu '0 - %i':\n   s = ", n);
          scanf("%i", &s);
        }

        printf("   Podaj 't' należące do zbioru liczb rzeczywistych:\n   t = ");
        scanf("%f", &t);

        for (i = 0; i < s; i++) polynomialDerivative(W);
        
        printf("\n   Pochodna dla W(x) stopnia '%i' wynosi:\n   ", i);
        polynomialPrint(W);
        printf("\n");
        result = polynomialResult(W, t);
        
        printf("\n   Pochodna dla W(%f) stopnia '%i' wynosi:\n   %f\n", t, s, result);

        break;

      case 2:
        printf("\n");
        return 0;
    }
  }
}
