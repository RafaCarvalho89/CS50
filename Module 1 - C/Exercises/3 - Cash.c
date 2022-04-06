#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    int coin = 0;
    float cash;
    do
    {
    cash = get_float("Cash owed: ");
    }
    while (cash < 0);
    cash = cash * 100;
    cash = round (cash);
    int money = (int)cash;
    do
    {
        if (money >= 25){
            do{
                money = money - 25;
                coin++;
            }
            while (money >= 25);
        }
        if (money >= 10){
            do{
                money = money - 10;
                coin++;
            }
            while (money >= 10);
        }
        if (money >= 5){
            do{
                money = money - 5;
                coin++;
            }
            while (money >= 5);
        }
        if (money >= 1){
            do{
                money = money - 1;
                coin++;
            }
            while (money >= 1);
        }
    }
    while (money > 0);
    printf("You'll need %i coins\n", coin);
}
