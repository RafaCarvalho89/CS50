#include <cs50.h>
#include <stdio.h>

int somat(long numcartao);

int main(void)
{
    long numcartao;
    int soma = 0;
    long num = 0;
    //Solicita o número do cartão até que seja inserido um número válido
    do{
        numcartao = get_long("Informe o número do cartão: ");
        if (numcartao > 10000000000000000 || numcartao < 1000000000000)
        {
            printf("INVALID\n");
        }
    }
    while (numcartao > 10000000000000000 || numcartao < 1000000000000);
    //Chama a função que vai fazer a soma dos digitos para o teste de validade
    soma = somat(numcartao);
    num = numcartao;
    //Faz o teste de validade com resultado da função
    if (soma % 10 == 0)
    {
        do
        {
            num = num / 10;
        }
        while (num > 100);
    }
    else
    {
        printf("INVALID\n");

    }
    //Sendo validado pelo teste indentifica a marca do cartao
    if (num == 34 || num == 37)
    {
        printf("AMEX\n");
    }
    else if (num > 50 && num < 56)
    {
        printf("MASTERCARD\n");
    }
    else if (num >39 && num < 50)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int somat(long numcartao)
{
    long temp;
    int soma2x = 0;
    int soma2xtemp;
    int somaoutros = 0;
    int somaoutrostemp;
    int somatotal;
    temp = numcartao;
    //Faz a soma alternada dos digitos multiplicados por 2 e soma com os outros não utilizados para dar a soma total
    do
    {
        somaoutrostemp = temp % 10;
        temp = temp / 10;
        soma2xtemp = temp % 10;
        temp = temp / 10;
        somaoutros = somaoutros + somaoutrostemp;
        soma2xtemp = soma2xtemp * 2;
        if (soma2xtemp / 10 > 0)
        {
            soma2xtemp = (soma2xtemp % 10) + (soma2xtemp) / 10;
        }
        soma2x = soma2x + soma2xtemp;

    }
    while (temp > 0);
    somatotal = soma2x + somaoutros;
    return somatotal;
}
