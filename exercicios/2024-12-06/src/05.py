def coin_change(coins, total):
    dp = [float('inf')] * (total + 1)
    dp[0] = 0

    for t in range(1, total + 1):
        for coin in coins:
            if t - coin >= 0:
                dp[t] = min(dp[t], dp[t - coin] + 1)

    return dp[total] if dp[total] != float('inf') else -1

coins = [1, 2, 5]
total = 11
result = coin_change(coins, total)

print(f"The minimum number of coins needed: {result}")
