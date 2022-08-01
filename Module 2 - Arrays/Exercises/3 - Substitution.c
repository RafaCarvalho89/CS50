#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //test if the number of arguments is correct (testa se o número de argumentos está correto)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //declare key to be the argument in argv[1] (declara key como sendo o argumento em argv[1])
    string key = argv[1];
    //declare keyLength to be the lenght of the string key (declara keyLength como sendo o comprimento da string key)
    int keyLength = strlen(key);
    //
    char cipherChar;
    //test if keyLength corresponds to the correct amount of letters that key string must have (testa se keyLenght corresponde a quantidade correta de letras que a string key deve ter)
    if (keyLength != 26)
    {
        printf("key must contain 26 characters.\n");
        return 1;
    }
    //test if there is digit in the key string (testa se tem algum número na string key)
    for (int i = 0; i < keyLength; i++)
    {
        if (isdigit(key[i]))
        {
            printf("Key must only contain alphebetic characters.\n");
            return 1;
        }
    }
    //test if the key string has repeated letters (testa se a string key tem letras repetidas)
    for (int i = 0; i < keyLength; i++)
    {
        for (int j = i + 1; j < keyLength; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    //get the text that will be ciphered (pega o texto que será criptografado)
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    //cipher char by char, analysing if the char is lowercase or uppercase to cipher correct and if it's a number or symbol kepping it the same (cifra caractere por caractere, analisando se o caractere está minúsculo ou maiúsculo para cifrar corretamente e se é um número ou símbolo para mantê-lo igual)
    for (int i = 0, t = strlen(text), x = 0; i < t; i++)
    {
        if (islower(text[i]))
        {
            x = (text[i] - 'a');
            cipherChar = key[x];
            printf("%c", tolower(cipherChar));
        }
        else if (isupper(text[i]))
        {
            x = (text[i] - 'A');
            cipherChar = key[x];
            printf("%c", toupper(cipherChar));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}