#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int n;

    do
    {
        // pede o número de andares que terá a pirâmide
        n = get_int("Height (between 1 and 8): \n");

    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        //imprime primeiro os espaços em seguida os blocos
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        // imprime o espaço entre as 2 pirâmides e em seguida a segunda pirâmide
        printf(" ");
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
