while True:
    try:
        change = float(input("Change owed: "))
        if change > 0:
            break
    except ValueError:
        pass
cents = round(change * 100)
coins = 0
coins += cents // 25
cents %= 25
coins += cents // 10
cents %= 10
coins += cents // 5
cents %= 5
coins += cents // 1
cents %= 1
print(coins)
