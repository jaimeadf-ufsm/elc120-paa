n, x = map(int, input().split())

weights = list(map(int, input().split()))
values = list(map(int, input().split()))

def knapsack():
    dp = [0 for _ in range(x + 1)]

    for i in range(n):
        for j in range(x, weights[i] - 1, -1):
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i])

    return dp[x]

print(knapsack())

