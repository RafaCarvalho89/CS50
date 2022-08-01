#include <cs50.h>
#include <stdio.h>
#include <math.h>

int checkDigits(long num);
int sumAlternate(long num);
int sumAlternateOther(long num);
int sum(long cardNumber);
int printBrand(int digits, int sum, long cardNumber);
//int somat(long numcartao);

int main(void)
{
    long cardNumber;
    int digits;
    int sum1;
    int sum2;
    int totalSum;

    // Get the credit card number (pega o número do cartão de crédito)
    cardNumber = get_long("Credit card number: ");
    // Return the number of digits of the credit card (retorna o número de dígitos do cartão de crédito)
    digits = checkDigits(cardNumber);
    // Calls the function that make the sum using the Luhn's Algorithm (chama a função que faz a soma usando o Algoritmo de Luhn)
    totalSum = sum(cardNumber);
    // If valid print the brand of the card, else print invalid (se válido imprime a marca do cartãp, se não imorime inválido )
    printBrand(digits, totalSum, cardNumber);
}

// Return the number of digits of the credit card (retorna o número de dígitos do cartão de crédito)
int checkDigits(long num)
{
    int count = 0;
    do
    {
        num = num / 10;
        count++;
    }
    while (num > 0);

    return count;
}

// Sum every alternate digit multiplying each one by 2, starting from second-last digit
// soma todo dígito alternado multiplicando cada dígito por 2, começando pelo penúltimo dígito
int sumAlternate(long num)
{
    bool isAlternate = false;
    int sumAlt = 0;
    int rest;
    do
    {
        rest = 0;
        if (isAlternate)
        {
            rest = num % 10;
            rest *= 2;
            if (rest > 9)
            {
                rest = (rest / 10) + (rest % 10);
            }
        }

        sumAlt += rest;
        num /= 10;
        isAlternate = !(isAlternate);
    }
    while(num > 0);

    return sumAlt;
}

//Sum every alternate digit, starting from last digit (soma todo dígito alternado, começando pelo último)
int sumAlternateOther(long num)
{
    bool isAlternate = true;
    int sumAltOt = 0;
    int rest;
    do
    {
        rest = 0;
        if (isAlternate)
        {
            rest = num % 10;
        }

        sumAltOt += rest;
        num /= 10;
        isAlternate = !(isAlternate);
    }
    while(num > 0);

    return sumAltOt;
}

// Get the results from alternates sums and sum they two (pega os resultados das somas alternadas e as soma)
int sum(long cardNumber)
{
    int sum1 = sumAlternate(cardNumber);
    int sum2 = sumAlternateOther(cardNumber);

    int sum = sum1 + sum2;

    return sum;
}

// If valid print the brand of the card, else print invalid (se válido imprime a marca do cartãp, se não imorime inválido )
int printBrand(int digits, int sum, long cardNumber)
{
    // Check if has a valid amount of digits (checa se tem uma quantidade válida de dígitos)
    if (digits > 16 || digits < 13)
    {
        printf("INVALID\n");
        return 1;
    }
    if (sum % 10 == 0)
    {
        int num = cardNumber / pow(10, (digits - 2));
        if (num > 39 && num < 50)
        {
            printf("VISA\n");
            return 0;
        }

        if (digits == 15 && (num == 34 || num == 37))
        {
            printf("AMEX\n");
            return 0;
        }

        if (digits == 16 && (num > 50 && num < 56))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 1;
        }
    }
    else
    {
        printf("INVALID\n");
        return 1;
    }
}