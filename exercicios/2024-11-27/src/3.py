def solve(vertices, edges):
    uncovored_edges = set(edges)
    answer_vertices = set()

    while uncovored_edges:
        vertex_degrees = {vertex: 0 for vertex in vertices}

        for u, v in uncovored_edges:
            vertex_degrees[u] += 1
            vertex_degrees[v] += 1
        
        best_vertex = max(vertex_degrees, key=vertex_degrees.get)

        answer_vertices.add(best_vertex)

        uncovored_edges = {edge for edge in uncovored_edges if best_vertex not in edge}

    return list(answer_vertices)

n_vertices = int(input("Number of vertices: "))
n_edges = int(input("Number of edges: "))

vertices = list(range(1, n_vertices + 1))
edges = []

print("Edges:")
for _ in range(n_edges):
    a, b = map(int, input().split())
    edges.append((a, b))

answer = solve(vertices, edges)

print()
print(f"Vertices: {answer}")

