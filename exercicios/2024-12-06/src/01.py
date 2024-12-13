def subset_sum(S, T):
    n = len(S)
    dp = [[False for _ in range(T + 1)] for _ in range(n + 1)]
    
    for i in range(n + 1):
        dp[i][0] = True
    
    for i in range(1, n + 1):
        for j in range(1, T + 1):
            if S[i-1] > j:
                dp[i][j] = dp[i-1][j]
            else:
                dp[i][j] = dp[i-1][j] or dp[i-1][j-S[i-1]]
    
    return dp[n][T]

S = [3, 34, 4, 12, 5, 2]
T = 9

print(f"Is there a subset: {subset_sum(S, T)}")