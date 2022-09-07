import cs50
import math
import numpy as np

def main():
    cardNumber = cs50.get_int ("Credit card number: ")
    digits = checkDigits(cardNumber)
    totalSum = sum(cardNumber)
    printBrand(digits, totalSum, cardNumber)

def checkDigits(num):
    count = 0
    while True:
        num /= 10
        num = math.floor(num)
        count += 1
        if num == 0:
            break

    return count

def sumAlternate(num):
    isAlternate = False
    sumAlt = 0

    while True:
        rest = 0
        if isAlternate:
            rest = num % 10
            rest *= 2
            if rest > 9:
                rest = math.floor(rest / 10) + (rest % 10)
        sumAlt += rest
        num /= 10
        num = math.floor(num)
        isAlternate = np.bitwise_not(isAlternate)
        if num == 0:
            break

    return sumAlt

def sumAlternateOther(num):
    isAlternate = True
    sumAltOt = 0

    while True:
        rest = 0
        if isAlternate:
            rest = num % 10
        sumAltOt += rest
        num /= 10
        num = math.floor(num)
        isAlternate = np.bitwise_not(isAlternate)
        if num == 0:
            break

    return sumAltOt

def sum(cardNumber):
    sum1 = sumAlternate(cardNumber)
    sum2 = sumAlternateOther(cardNumber)

    sum = sum1 + sum2

    return sum

def printBrand(digits, sum, cardNumber):
    if digits > 16 or digits < 13:
        print("INVALID")
        return 1

    if sum % 10 == 0:
        num = cardNumber / math.pow(10, (digits - 2))
        num = math.floor(num)

        if num > 39 and num < 50:
            print("VISA")
            return 0

        elif digits == 15 and (num == 34 or num == 37):
            print("AMEX")
            return 0

        elif digits == 16 and num > 50 and num < 56:
            print("MASTERCARD")
            return 0

        else:
            print("INVALID")
            return 1
    else:
        print("INVALID")
        return 1

main()