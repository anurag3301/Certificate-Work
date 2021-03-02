import sys
import csv

if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit(1)

dataf = open(sys.argv[1], "r")
seqf = open(sys.argv[2], "r")
data = csv.DictReader(dataf)
seq = seqf.read()
secdata = {"AGATC": 0, "TTTTTTCT": 0, "AATG": 0, "TCTAG": 0, "GATA": 0, "TATC": 0, "GAAA": 0, "TCTG": 0}


counter = 0
for find in secdata:
    i = 0
    count = 0
    max_count = 0
    while i < len(seq):
        if seq[i:i+len(find)] == find:
            count += 1
            max_count = max(max_count, count)
            i += len(find)
        else:
            i += 1
            count = 0
            
    secdata[find] = max_count

for i in data:
    found = True
    for j in i:
        if j == 'name':
            continue
        if int(i[j]) != secdata[j]:
            found = False
            break
            
    if found:
        print(i['name'])
        break
    
if not found:
    print("No match")

