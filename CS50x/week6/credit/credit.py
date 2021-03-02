num = int(input("Number: "))
if num > 1000000000000:
    arr = [0] * 16
    i, j, r = 0, 0, 0
  
    while num != 0: 
        r = num % 10
        arr[i] = r
        i += 1
        num = num // 10
    
    dino = 0
    for k in range(15, 10, -1):
        if arr[k] > 0:
            dino = k
            break
    
    val1 = 0
    add = 0
    for k in range(1, 16, 2):
        val1 = arr[k] * 2
        if val1 > 9:
            add += val1 % 10
            add += val1 // 10
        else:
            add += val1
    
    for l in range(0, 16, 2):
        add += arr[l]
    
    if add % 10 == 0:
        if arr[dino] == 3 and (arr[dino - 1] == 4 or arr[dino - 1] == 7):
            print("AMEX")
            
        elif arr[dino] == 5 and (arr[dino - 1] == 1 or arr[dino - 1] == 2 or arr[dino - 1] == 3 
                                 or arr[dino - 1] == 4 or arr[dino - 1] == 5):
            print("MASTERCARD")
        
        elif arr[dino] == 4:
            print("VISA")
        
        else:
            print("INVALID")
    
    else:
        print("INVALID")
    
else:
    print("INVALID")