#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //test if argv[1] is NULL (testa se argv[1] é nulo)
    if (argv[1] == NULL)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //declare key to be the argument argv[1] (declara key como sendo o argumento argv[1])
    string key = argv[1];

    //declare k to be the conversion of string key to an integer (declara k como a conversão da string key para um número inteiro)
    int k = atoi(key);
    string text;

    //declare a variable to be the result of the cipher formula (declara a variável que vai ser o resultado da fórmula de cifragem)
    int cipher = 0;

    //declare variables to be used in the "if" tests (declara as variáveis que serão usadas nos testes de "if")
    int f1 = 0;
    int f2 = 0;
    int f3 = 0;

    //test if it has the correct amount of arguments in the command line (testa se tem a quantidade correta de argumentos na linha de comando)
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        //if the number of arguments are correct test if the argument is a digit (se o número de argumentos estiver correto testa se o argumento é um número)
        for (int i = 0, n = strlen(key); i < n; i++)
        {
            if (isdigit(key[i]) == 0)
            {
                f1++;
            }
            else
            {
                f2++;
            }
        }
        //if there is a letter instead of a digit print a message to user (se há uma letra em vez de um número imprime uma mensagem ao usuário)
        if (f1 > 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        //if everything is correct with arguments get the plaintext (se estiver tudo correto com os argumentos pega o texto a ser cifrado)
        else if (f1 == 0 && f2 > 0)
        {
            text = get_string("Plaintext: ");
            printf("Ciphertext: ");
            //f3++;
        }
        // cipher the letters and print the ciphertext (cifra as letras e as imprime)
        for (int j = 0, t = strlen(text); j < t; j++)
        {
            if (text[j] >= 'a' && text[j] <= 'z')
            {
                cipher = (((text[j] - 'a') + k) % 26) + 'a';
                printf("%c", cipher);
            }
            else if (text[j] >= 'A' && text[j] <= 'Z')
            {
                cipher = (((text[j] - 'A') + k) % 26) + 'A';
                printf("%c", cipher);
            }
            else
            {
                printf("%c", text[j]);
            }
        }

        printf("\n");
    }
}