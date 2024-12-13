def rod_cutting(prices, n):
    dp = [0] * (n + 1)

    for length in range(1, n + 1):
        max_value = float('-inf')
        for cut in range(1, length + 1):
            max_value = max(max_value, prices[cut - 1] + dp[length - cut])
        dp[length] = max_value

    return dp[n]

prices = [1, 5, 8, 9, 10, 17, 17, 20]
n = 8
result = rod_cutting(prices, n)

print(f"Maximum revenue obtainable: {result}")