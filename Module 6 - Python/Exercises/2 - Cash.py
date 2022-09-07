import cs50

while True:
    cash = cs50.get_float("Cash owed: ")
    if (cash > 0):
        break

cash *= 100
cash = round(cash)
coin = 0

while True:
    if cash >= 25:
        cash -= 25
        coin += 1
    elif cash < 25:
        break
while True:
    if cash >= 10:
        cash -= 10
        coin += 1
    elif cash < 10:
        break
while True:
    if cash >= 5:
        cash -= 5
        coin += 1
    elif cash < 5:
        break
while True:
    if cash >= 1:
        cash -= 1
        coin += 1
    elif cash == 0:
        break
print(str(coin) + "coins")