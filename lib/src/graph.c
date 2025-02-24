#include "graph.h"

Graph *addVertex(Graph *g, Vertex v) { /* O(V) */
  if (!g) {
    g = malloc(sizeof(Graph));
    g->vertices = malloc(1 * sizeof(Vertex));
    g->matrix = malloc(1 * sizeof(Edge *));
    g->matrix[0] = malloc(1 * sizeof(Edge));

    g->nVertices = 1;
    g->vertices[0] = v;
    g->matrix[0][0] = NO_EDGE;

    return g;
  }

  for (int i = 0; i < (g->nVertices); i++)
    if (!strcmp(g->vertices[i], v))
      return g;

  g->vertices = realloc(g->vertices, (g->nVertices + 1) * sizeof(Vertex));
  g->matrix = realloc(g->matrix, (g->nVertices + 1) * sizeof(Edge *));
  for (int i = 0; i < (g->nVertices); i++)
    g->matrix[i] = realloc(g->matrix[i], (g->nVertices + 1) * sizeof(Edge));
  g->matrix[g->nVertices] = malloc((g->nVertices + 1) * sizeof(Edge));

  g->vertices[g->nVertices] = v;
  for (int i = 0; i < (g->nVertices + 1); i++) {
    g->matrix[i][g->nVertices] = NO_EDGE;
    g->matrix[g->nVertices][i] = NO_EDGE;
  }
  g->nVertices++;

  return g;
}

Graph *addEdge(Graph *g, Edge e, Vertex from, Vertex to) { /* O(V) */
  if (g) {
    unsigned vFrom = g->nVertices + 1, vTo = g->nVertices + 1;
    for (int i = 0; i < (g->nVertices); i++) {
      if (!strcmp(g->vertices[i], from))
        vFrom = i;
      if (!strcmp(g->vertices[i], to))
        vTo = i;
    }

    if (vFrom == g->nVertices + 1 || vTo == g->nVertices + 1)
      return g;

    if (g->matrix[vFrom][vTo] == NO_EDGE)
      g->matrix[vFrom][vTo] = e;
  }

  return g;
}

Graph *delVertex(Graph *g, Vertex v) { /* O(V^2) */
  if (!g || g->nVertices == 1) {
    freeGraph(g);
    return NULL;
  }

  unsigned nV = g->nVertices + 1;
  for (int i = 0; i < (g->nVertices); i++) {
    if (!strcmp(g->vertices[i], v))
      nV = i;
  }

  if (nV == g->nVertices + 1)
    return g;

  free(g->vertices[nV]);

  for (int i = 0; i < (g->nVertices); i++) {
    for (int j = 0; j < (g->nVertices); j++)
      if (j > nV)
        g->matrix[i][j - 1] = g->matrix[i][j];
    if (i != nV)
      g->matrix[i] = realloc(g->matrix[i], (g->nVertices - 1) * sizeof(Edge));
    else
      free(g->matrix[i]);
    if (i > nV) {
      g->vertices[i - 1] = g->vertices[i];
      g->matrix[i - 1] = g->matrix[i];
    }
  }

  g->matrix = realloc(g->matrix, (g->nVertices - 1) * sizeof(Edge *));
  g->vertices = realloc(g->vertices, (g->nVertices - 1) * sizeof(Vertex));
  g->nVertices--;

  return g;
}

Graph *delEdge(Graph *g, Vertex from, Vertex to) { /* O(V) */
  if (g) {
    unsigned vFrom = g->nVertices + 1, vTo = g->nVertices + 1;
    for (int i = 0; i < (g->nVertices); i++) {
      if (!strcmp(g->vertices[i], from))
        vFrom = i;
      if (!strcmp(g->vertices[i], to))
        vTo = i;
    }

    if (vFrom == g->nVertices + 1 || vTo == g->nVertices + 1)
      return g;

    g->matrix[vFrom][vTo] = NO_EDGE;
  }

  return g;
}

Graph *changeVertex(Graph *g, Vertex vOld, Vertex vNew) { /* O(V) */
  if (g) {
    unsigned nV = g->nVertices + 1;
    for (int i = 0; i < (g->nVertices); i++)
      if (!strcmp(g->vertices[i], vOld))
        nV = i;

    if (nV == g->nVertices + 1)
      return g;

    free(g->vertices[nV]);
    g->vertices[nV] = vNew;
  }

  return g;
}

Graph *changeEdge(Graph *g, Vertex from, Vertex to, Edge eNew) { /* O(V) */
  if (g) {
    unsigned vFrom = g->nVertices + 1, vTo = g->nVertices + 1;
    for (int i = 0; i < (g->nVertices); i++) {
      if (!strcmp(g->vertices[i], from))
        vFrom = i;
      if (!strcmp(g->vertices[i], to))
        vTo = i;
    }

    if (vFrom == g->nVertices + 1 || vTo == g->nVertices + 1 ||
        g->matrix[vFrom][vTo] == NO_EDGE)
      return g;

    g->matrix[vFrom][vTo] = eNew;
  }

  return g;
}

void freeGraph(Graph *g) { /* O(V) */
  if (g) {
    for (int i = 0; i < (g->nVertices); i++) {
      free(g->vertices[i]);
      free(g->matrix[i]);
    }
    free(g->vertices);
    free(g->matrix);
    free(g);
  }
}

void exportGraphviz(Graph *g) { /* O(V^2) */
  if (!g)
    return;

  FILE *f = fopen(GRAPHVIZ_FILENAME, "wt");
  fprintf(f, "digraph G{\nnode[shape=circle];\n");

  for (int i = 0; i < (g->nVertices); i++)
    fprintf(f, "%s\n", g->vertices[i]);

  for (int i = 0; i < (g->nVertices); i++)
    for (int j = 0; j < (g->nVertices); j++)
      if (g->matrix[i][j] != NO_EDGE && g->matrix[i][j] > 0)
        fprintf(f, "%s -> %s [label=%d, color=green]\n", g->vertices[i],
                g->vertices[j], g->matrix[i][j]);
      else if (g->matrix[i][j] != NO_EDGE)
        fprintf(f, "%s -> %s [label=%d, color=red]\n", g->vertices[i],
                g->vertices[j], g->matrix[i][j]);

  fprintf(f, "}\n");
  fclose(f);
  return;
}

void DFS(Graph *g, int v, int maxDepth, int *visited) { /* O(V+E) */
  visited[v] = 1;

  if (maxDepth == 0)
    return;

  for (int i = 0; i < (g->nVertices); i++) {
    if (g->matrix[v][i] != NO_EDGE)
      DFS(g, i, maxDepth - 1, visited);
  }
}

Vertex *handshakeDFS(Graph *g, Vertex v, unsigned nHandshakes,
                     unsigned *nVertices) {
  *nVertices = 0;

  if (!g)
    return NULL;

  int nV = g->nVertices + 1;
  int *visited = malloc(g->nVertices * sizeof(int));
  for (int i = 0; i < g->nVertices; i++) {
    visited[i] = 0;
    if (!strcmp(g->vertices[i], v))
      nV = i;
  }

  if (nV == g->nVertices + 1) {
    free(visited);
    return NULL;
  }

  DFS(g, nV, nHandshakes, visited);

  Vertex *vertices = malloc(g->nVertices * sizeof(Vertex));
  for (int i = 0; i < g->nVertices; i++)
    if (visited[i]) {
      vertices[*nVertices] = g->vertices[i];
      (*nVertices)++;
    }

  free(visited);
  return vertices;
}

Vertex *shortestPathDijkstra(Graph *g, Vertex from, Vertex to) { /* O(V^2) */
  if (!g)
    return NULL;

  unsigned vFrom = g->nVertices + 1, vTo = g->nVertices + 1;
  for (int i = 0; i < (g->nVertices); i++) {
    if (!strcmp(g->vertices[i], from))
      vFrom = i;
    if (!strcmp(g->vertices[i], to))
      vTo = i;
  }
  if (vFrom == g->nVertices + 1 || vTo == g->nVertices + 1)
    return NULL;

  int *paths = malloc(g->nVertices * sizeof(Vertex));
  int *visited = malloc(g->nVertices * sizeof(int));
  for (int i = 0; i < g->nVertices; i++) {
    paths[i] = g->nVertices + 1;
    visited[i] = 0;
  }
  paths[vFrom] = 0;

  for (;;) {
    int v = g->nVertices + 1;
    int vPath = g->nVertices + 1;
    for (int i = 0; i < g->nVertices; i++) {
      if (!visited[i] && paths[i] < vPath) {
        v = i;
        vPath = paths[v];
      }
    }

    if (vPath == g->nVertices + 1)
      break;

    visited[v] = 1;

    for (int i = 0; i < g->nVertices; i++) {
      if (g->matrix[v][i] != NO_EDGE && g->matrix[v][i] > 0 && !visited[i] &&
          paths[i] > paths[v] + 1)
        paths[i] = paths[v] + 1;
    }
  }

  if (paths[vTo] > g->nVertices) {
    free(paths);
    free(visited);
    return NULL;
  }

  Vertex *path = malloc(g->nVertices * sizeof(Vertex));
  int v = vTo;
  while (v != vFrom) {
    path[paths[v]] = g->vertices[v];
    for (int i = 0; i < g->nVertices; i++) {
      if (g->matrix[i][v] != NO_EDGE && g->matrix[i][v] > 0 &&
          paths[i] == paths[v] - 1)
        v = i;
    }
  }
  path[0] = g->vertices[vFrom];

  free(paths);
  free(visited);
  return path;
}

Graph *separateFriends(Graph *g) { /* O(V^2) */
  if (!g)
    return NULL;

  int *visited = malloc(g->nVertices * sizeof(int));
  int *comps = malloc(g->nVertices * sizeof(int));

  for (int i = 0; i < g->nVertices; i++) {
    visited[i] = 0;
    comps[i] = i;
  }

  for (int i = 0; i < g->nVertices; i++)
    if (!visited[i]) {
      visited[i] = 1;
      for (int j = 0; j < g->nVertices; j++) {
        Vertex *path1 = shortestPathDijkstra(g, g->vertices[i], g->vertices[j]);
        Vertex *path2 = shortestPathDijkstra(g, g->vertices[j], g->vertices[i]);
        if (!visited[j] && path1 && path2) {
          visited[j] = 1;
          comps[j] = comps[i];
        }
        free(path1);
        free(path2);
      }
    }

  for (int i = 0; i < g->nVertices; i++) {
    for (int j = 0; j < g->nVertices; j++) {
      if (g->matrix[i][j] < 0 || comps[i] != comps[j])
        g->matrix[i][j] = NO_EDGE;
    }
  }

  free(visited);
  free(comps);
  return g;
}