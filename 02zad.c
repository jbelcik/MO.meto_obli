#include <stdio.h>
#include <math.h>


#define E 2.71828183


int main()
{
  printf("\n   Dla  równania  f(x) = 0,  gdzie  f(x) = 3x + 2 - e^x,  wczytac  a, b  nalezace\n");
  printf("   do zbioru liczb rzeczywistych takie, by a < b oraz f(a) * f(b) < 0. Nastepnie,\n");
  printf("   dopoki  \"uzytownik sie nie znudzi\",  wczytywac  wartosci  0 < E < 1  i  metoda\n");
  printf("   polowienia  na  [a, b]  przyblizyc z dokladnoscia E rozwiazanie tego rownania.\n");
  printf("   Rozwiazanie to przyblizyc rowniez metoda Newtona  z  x_0 = a,  przy czym,  x_k\n");
  printf("   bedzie  dobrym   przyblizeniem,  gdy  |x_k - x_(k - 1)| <= E.  Porownac  ilosc\n");
  printf("   krokow wykonanych metoda polowienia i metoda Newtona.\n\n");

  double a, b;

  printf("   Podaj 'a' należące do zbioru liczb rzeczywistych:\n   a = ");
  scanf("%lf", &a);

  b = a;

  while(a >= b && (3 * a + 2 - pow(E, a)) * (3 * a + 2 - pow(E, a)) >= 0)
  {
    printf("   Podaj 'b' należące do zbioru liczb rzeczywistych,\n   takie by b > a oraz f(b) * f(a) < 0:\n   b = ");
    scanf("%lf", &b);
  }

  return 0;
}
