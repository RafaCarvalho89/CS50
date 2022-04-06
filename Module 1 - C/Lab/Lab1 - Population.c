#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start;
    int end;
    int years = 0;
    int temp;
      // TODO: Solicite o valor inicial ao usuário
      do
      {
          start = get_int("Insira o número inicial de lhamas (no mínimo 9): ");
      }
      while (start < 9);

     // TODO: Solicite o valor final ao usuário
     do
     {
         end = get_int("Insira o número final de lhamas desejado (no mínimo igual ao valor inicial): ");
     }
     while (end < start);
     temp = start;


     // TODO: Calcule o número de anos até o limite
     do
     {
         temp = temp + (temp / 3) - (temp / 4);
         years++;
     }
     while (temp < end);

     // TODO: Imprima o número de anos
     printf("Leva %i anos para atingir o número desejado\n", years);

}
