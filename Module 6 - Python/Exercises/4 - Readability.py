import cs50

text = cs50.get_string("Enter text here: ")
words = 0
sentences = 0
letters = 0

for i in text:
    if i.isalpha():
        letters += 1
    elif i.isspace():
        words += 1
    elif i == "." or i == "!" or i == "?":
        sentences += 1

L = letters / (words + 1) * 100

S = sentences / (words + 1) * 100

index = (0.0588 * L) - (0.296 * S) - 15.8

if round(index) < 1:
    print("Before Grade 1")
elif round(index) > 16:
    print("Grade 16+")
else:
    print("Grade " + str(round(index)))