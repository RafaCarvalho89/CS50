import sys
import csv

if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")

dataInput = sys.argv[1]
dnaInput = sys.argv[2]

with open(dataInput, "r") as csvfile:
    reader = csv.DictReader(csvfile)
    dataList = list(reader)

with open(dnaInput, "r") as file:
    dna = file.read()

maxCount = []

for i in range(1, len(reader.fieldnames)):
    STR = reader.fieldnames[i]
    maxCount.append(0)

    for j in range(len(dna)):
        STRCount = 0

        if dna[j:(j + len(STR))] == STR:
            x = 0
            while dna[(j + x):(j + x + len(STR))] == STR:
                STRCount += 1
                x += len(STR)
            if STRCount > maxCount[i - 1]:
                maxCount[i - 1] = STRCount

for i in range(len(dataList)):
    matches = 0
    for j in range(1, len(reader.fieldnames)):
        if int(maxCount[j - 1]) == int(dataList[i][reader.fieldnames[j]]):
            matches += 1
        if matches == (len(reader.fieldnames) - 1):
            print(dataList[i]['name'])
            sys.exit(0)

print("No match")

