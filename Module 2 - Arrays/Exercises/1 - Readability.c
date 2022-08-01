#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    //get the text to make the analysis (pega o texto para fazer a análise)
    string t = get_string("Enter text here: ");

    int words = 0;

    int sentences = 0;

    int letters = 0;

    // Loop through the tex and sum the number pf letters, words and sentences
    // percorre o texto e soma o número de letras, palavras e sentenças
    for (int i = 0, total = strlen(t); i < total; i++)
    {
        if (isalnum(t[i]))
        {
            letters++;
        }
        else if (isspace(t[i]))
        {
            words++;
        }
        else if (t[i] == '.' || t[i] == '!' || t[i] == '?')
        {
            sentences++;
        }
    }

    //calculate the average number of letters per 100 words in the text (calcula o número médio de letras por 100 palavras no texto)
    float L = (float) letters / (words + 1) * 100;

    //calculate the average number of sentences per 100 words in the text (calcula o número médio de senteças por 100 palavras no texto)
    float S = (float) sentences / (words + 1) * 100;

    //calculate the index of Coleman-Liau to show the necessary school level (USA) to understand the text (calcula o index the Coleman-Liau para mostrar o nível escolar necessário para entender o texto)
    float index = (0.0588 * L) - (0.296 * S) - 15.8;

    //print the grade result in cases: from 1 to 16, less than 1 and greater than 16 (imprime o resultado nos casos: de 1 até 16, menor que 1 e maior que 16)
    if  (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(index));
    }
}