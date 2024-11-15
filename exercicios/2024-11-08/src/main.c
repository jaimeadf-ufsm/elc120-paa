#include <stdio.h>
#include <stdbool.h>
 
typedef struct graph Graph;
 
#define MAX_VERTICES 100
#define MAX_DEGREE 50
 
struct graph
{
    int n_vertices;
    int n_edges;
    int edges[MAX_VERTICES][MAX_DEGREE];
    int degrees[MAX_VERTICES];
};
 
bool visited[MAX_VERTICES];
 
Graph graph_create(int n_vertices, int n_edges)
{
    Graph graph;
 
    graph.n_vertices = n_vertices;
    graph.n_edges = n_edges;
 
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        graph.degrees[i] = 0;
    }
 
    return graph;
}
 
void graph_connect(Graph *graph, int x, int y)
{
    graph->edges[x][graph->degrees[x]++] = y;
    graph->edges[y][graph->degrees[y]++] = x;
}
 
Graph graph_prompt()
{
    int n_vertices;
    int n_edges;
 
    printf("Digite o número de vértices: ");
    scanf("%d", &n_vertices);
 
    printf("Digite o número de arestas: ");
    scanf("%d", &n_edges);
 
    Graph graph = graph_create(n_vertices, n_edges);
 
    printf("Digite %d arestas:\n", n_edges);
    for (int i = 0; i < n_edges; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
 
        graph_connect(&graph, x, y);
    }
 
    return graph;
}
 
int graph_degree(Graph *graph, int x)
{
    return graph->degrees[x];
}
 
int graph_max_degree(Graph *graph)
{
    int max_degree = 0;
 
    for (int i = 0; i < graph->n_vertices; i++)
    {
        if (graph_degree(graph, i) > max_degree)
        {
            max_degree = graph_degree(graph, i);
        }
    }
 
    return max_degree; 
}
 
void process_vertex(int x)
{
  printf("Vertice Processado: %d\n", x);
}
 
void process_edge(int x, int y)
{
   printf("Arco Processado: (%d, %d)\n", x, y);
}
 
void dfs(Graph *graph, int v)
{
    visited[v] = true;
 
    process_vertex(v);
 
    for (int i = 0; i < graph->degrees[v]; i++)
    {
        process_edge(v, graph->edges[v][i]);

        if (!visited[graph->edges[v][i]])
        {
            dfs(graph, graph->edges[v][i]);
        }
    }
}
 
int main()
{
    Graph graph = graph_prompt();

    printf("- Grau Máximo: %d\n", graph_max_degree(&graph));
 
    printf("- DFS:\n");
    dfs(&graph, 1);
}