#include <stdio.h>


int n = -1;


void polynomialUnion (float *poly1, float *poly2)
{
  
}


void polynomialIntersection (float *poly1, float *poly2)
{
  
}


void polynomialIntersectionByConstans (float *poly, float con)
{
  int i;

  for (i = 0; i <= n; i++) poly[i] *= con;
}


int main()
{
  printf("\nUstalić naturalną n_max. Wczytać n  z zakresu '0 - n_max'  oraz różne\n");
  printf("węzły x[0], x[1], ..., x[n] i dowolne wartości f[0], f[1], ..., f[n].\n");
  printf("Wielomian  interpolacyjny  w  postaci  Lagrange'a  L = L(x)  taki, że\n");
  printf("L(x[i]) = f[i] dla i = 0, 1, ..., n,  przedstawić w postaci  ogólnej.\n");
  printf("Następnie,   \"dopóki  użytkownik  się  nie  znudzi\",   wczytywać  'j'\n");
  printf("z zakresu '0 - n' oraz 't'  należace  do zbioru  liczb  rzeczywistych\n");
  printf("i obliczać pochodne dla L(t) stopnia 'j'.\n\n");

  int nMax = 100, i, j;
  
  while (n < 0 || n > nMax)
  {
    printf("Podaj n z zakresu '0 - %i'\n", nMax);
    printf("n = ");
    scanf("%i", &n);
    printf("\n");
  }

  float x[n + 1],
        f[n + 1],
        divisor[n + 1],
        H[n + 1][2],
        L[n + 1][n + 1],
        W[n + 1];

  for (i = 0; i <= n; i++)
  {
    printf("(x[%i], f[%i]) = \n", i, i);
    scanf("%f", &x[i]);
    scanf("%f", &f[i]);
  }

  for (i = 0; i <= n; i++)
  {
    for (j = 0; j <= n; j++)
    {
      if (j > 1) H[i][j] = 0;
      L[i][j] = 0;
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
      //printf("H[%i][%i] = %f\n", i, j, H[i][j]);
      //printf("L[%i][%i] = %f\n\n", i, j, L[i][j]);
      if (j != i)
      {
        divisor[i] *= 1 / (x[i] - x[j]);
        polynomialIntersection(L[i], H[j]);
      }
    }

    //printf("\ndivisor[%i] = %f\n", i, divisor[i]);
    //printf("W[%i] = %f\n\n\n", i, W[i]);
    polynomialIntersectionByConstans(L[i], divisor[i] * f[i]);
    polynomialUnion(W, L[i]);
  }

  printf("W = ");
  for (i = n; i > 0; i--)
  {
    if (W[i] != 0) printf("%fx^%i ", W[i], i);
  }
  
  if (W[0] != 0) printf("%f", W[0]);
  printf("\n");

  return 0;
}
