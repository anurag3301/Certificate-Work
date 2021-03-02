while True:
    dollars = input("Change owed: ")
    try:
        dollars = float(dollars)
        if dollars > 0.0:
            break
    except:
        pass
    
cents = round(dollars * 100)
val25 = cents // 25
cents -= val25 * 25

val10 = cents // 10
cents -= val10 * 10

val5 = cents // 5
cents -= val5 * 5

val1 = cents // 1
cents -= val1 * 1

print(val25 + val10 + val5 + val1)