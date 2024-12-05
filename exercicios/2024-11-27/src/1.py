import heapq

def solve(cables):
    cost = 0
    heap = cables.copy()

    print(cables)

    heapq.heapify(heap)

    while len(heap) > 1:
        a = heapq.heappop(heap)
        b = heapq.heappop(heap)

        cost += a + b

        heapq.heappush(heap, a + b)

    return cost

cables = list(map(int, input("Lengths: ").split()))
cost = solve(cables)

print()
print(f"Cost: {cost}")
