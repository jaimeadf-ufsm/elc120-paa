def solve(price, coins):

    count = 0
    coins = sorted(coins)

    coins.reverse()

    for coin in coins:
        while price >= coin:
            count += 1
            price -= coin
    
    if price != 0:
        return -1
    
    return count

price = int(input("Price: "))
coins = list(map(int, input("Coins: ").split()))

count = solve(price, coins)

print()
print(f"Count: {count}")