sen = input("Text: ")
charcount = len(sen)
wordcount = 0
specialcount = 0
sentencecount = 0
for i in sen:
    if i == ' ':
        wordcount += 1

    if i == '.' or i == '!' or i == '?':
        sentencecount += 1

    if not i.isalpha() and i != " ":
        specialcount += 1

wordcount += 1
charcount = charcount - (specialcount + wordcount) + 1

L = (charcount / wordcount) * 100
S = (sentencecount / wordcount) * 100
index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

if grade < 1:
    print("Before Grade 1")
elif grade > 15:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
