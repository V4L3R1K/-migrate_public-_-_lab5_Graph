#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRAPHVIZ_FILENAME "out.out"

#define NO_EDGE -11

typedef signed char Edge;
typedef char *Vertex;

typedef struct Graph {
  unsigned nVertices;
  Vertex *vertices;
  Edge **matrix;
} Graph;

Graph *addVertex(Graph *g, Vertex v);
Graph *addEdge(Graph *g, Edge e, Vertex from, Vertex to);
Graph *delVertex(Graph *g, Vertex v);
Graph *delEdge(Graph *g, Vertex from, Vertex to);
Graph *changeVertex(Graph *g, Vertex vOld, Vertex vNew);
Graph *changeEdge(Graph *g, Vertex from, Vertex to, Edge eNew);

void freeGraph(Graph *g);

void exportGraphviz(Graph *g);

Vertex *handshakeDFS(Graph *g, Vertex v, unsigned nHandshakes,
                     unsigned *nVertices);
Vertex *shortestPathDijkstra(Graph *g, Vertex from, Vertex to);
Graph *separateFriends(Graph *g);