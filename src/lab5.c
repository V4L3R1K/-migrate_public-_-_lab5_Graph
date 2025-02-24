#include "lab5.h"

int addVertexFunc(Graph **g) {
  char *v = NULL;

  v = readline("Input name: ");
  if (!v)
    return 0;

  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++)
      if (!strcmp((*g)->vertices[i], v)) {
        printf("Can't add, vertex \"%s\" already exists\n", v);
        free(v);
        return 1;
      }

  *g = addVertex(*g, v);

  return 1;
}

int addEdgeFunc(Graph **g) {
  char *v1 = NULL, *v2 = NULL;
  int edge = NO_EDGE;
  int v1exists = 0, v2exists = 0;

  v1 = readline("Input first vertex name: ");
  if (!v1)
    return 0;
  v2 = readline("Input second vertex name: ");
  if (!v2) {
    free(v1);
    return 0;
  }
  if (!strcmp(v1, v2)) {
    free(v1);
    free(v2);
    printf("Can't add edge between vertex itself\n");
    return 1;
  }
  if (!inputEdge(&edge)) {
    free(v1);
    free(v2);
    return 0;
  }
  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++) {
      if (!strcmp((*g)->vertices[i], v1))
        v1exists = 1;
      if (!strcmp((*g)->vertices[i], v2))
        v2exists = 1;
    }
  if (!v1exists) {
    printf("Can't add edge, vertex \"%s\" does not exist\n", v1);
    free(v1);
    free(v2);
    return 1;
  }
  if (!v2exists) {
    printf("Can't add edge, vertex \"%s\" does not exist\n", v2);
    free(v1);
    free(v2);
    return 1;
  }

  *g = addEdge(*g, edge, v1, v2);

  free(v1);
  free(v2);
  return 1;
}

int delVertexFunc(Graph **g) {
  char *v = NULL;
  int vExists = 0;

  v = readline("Input vertex name: ");
  if (!v)
    return 0;

  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++)
      if (!strcmp((*g)->vertices[i], v))
        vExists = 1;

  if (!vExists) {
    printf("Can't delete vertex \"%s\", it does not exist\n", v);
    free(v);
    return 1;
  }

  *g = delVertex(*g, v);

  free(v);
  return 1;
}

int delEdgeFunc(Graph **g) {
  char *v1 = NULL, *v2 = NULL;
  int v1exists = 0, v2exists = 0;

  v1 = readline("Input first vertex name: ");
  if (!v1)
    return 0;
  v2 = readline("Input second vertex name: ");
  if (!v2) {
    free(v1);
    return 0;
  }
  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++) {
      if (!strcmp((*g)->vertices[i], v1))
        v1exists = 1;
      if (!strcmp((*g)->vertices[i], v2))
        v2exists = 1;
    }
  if (!v1exists) {
    printf("Can't delete edge, vertex \"%s\" does not exist\n", v1);
    free(v1);
    free(v2);
    return 1;
  }
  if (!v2exists) {
    printf("Can't delete edge, vertex \"%s\" does not exist\n", v2);
    free(v1);
    free(v2);
    return 1;
  }

  *g = delEdge(*g, v1, v2);

  free(v1);
  free(v2);
  return 1;
}

int changeVertexFunc(Graph **g) {
  char *vOld = NULL, *vNew;
  int vExists = 0;

  vOld = readline("Input vertex name: ");
  if (!vOld)
    return 0;
  vNew = readline("Input new vertex name: ");
  if (!vNew) {
    free(vOld);
    return 0;
  }

  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++)
      if (!strcmp((*g)->vertices[i], vOld))
        vExists = 1;

  if (!vExists) {
    printf("Vertex \"%s\", it does not exist\n", vOld);
    free(vOld);
    free(vNew);
    return 1;
  }

  *g = changeVertex(*g, vOld, vNew);

  free(vOld);
  return 1;
}

int changeEdgeFunc(Graph **g) {
  char *v1 = NULL, *v2 = NULL;
  int edge = NO_EDGE;
  int v1exists = 0, v2exists = 0;

  v1 = readline("Input first vertex name: ");
  if (!v1)
    return 0;
  v2 = readline("Input second vertex name: ");
  if (!v2) {
    free(v1);
    return 0;
  }
  if (!inputEdge(&edge)) {
    free(v1);
    free(v2);
    return 0;
  }
  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++) {
      if (!strcmp((*g)->vertices[i], v1))
        v1exists = 1;
      if (!strcmp((*g)->vertices[i], v2))
        v2exists = 1;
    }
  if (!v1exists) {
    printf("Vertex \"%s\" does not exist\n", v1);
    free(v1);
    free(v2);
    return 1;
  }
  if (!v2exists) {
    printf("Vertex \"%s\" does not exist\n", v2);
    free(v1);
    free(v2);
    return 1;
  }

  *g = changeEdge(*g, v1, v2, edge);

  free(v1);
  free(v2);
  return 1;
}

int printGraphFunc(Graph **g) {
  if (*g) {
    printf("\n\t");
    for (int v = 0; v < (*g)->nVertices; v++)
      printf("%s\t", (*g)->vertices[v]);
    for (int from = 0; from < (*g)->nVertices; from++) {
      printf("\n\n%s\t", (*g)->vertices[from]);
      for (int to = 0; to < (*g)->nVertices; to++)
        if ((*g)->matrix[from][to] != NO_EDGE)
          printf("%d\t", (*g)->matrix[from][to]);
        else
          printf("-\t", (*g)->matrix[from][to]);
    }
    printf("\n\n");
  } else
    printf("Graph is empty, nothing to print\n");
  return 1;
}

int exportGraphvizFunc(Graph **g) {
  if (*g)
    exportGraphviz(*g);
  else
    printf("Graph is empty, nothing to export\n");
  return 1;
}

int handshakeDFSFunc(Graph **g) {
  int nVertices = 0, nHandshakes = 0;
  char *v = NULL;

  v = readline("Input vertex name: ");
  if (!v)
    return 0;
  if (!inputHandshakes(&nHandshakes)) {
    free(v);
    return 0;
  }

  char **vertices = handshakeDFS(*g, v, nHandshakes, &nVertices);

  printf("\n");
  for (int i = 0; i < nVertices; i++)
    printf("%s\n", vertices[i]);
  printf("\n");

  free(v);
  free(vertices);
  return 1;
}

int shortestPathDijkstraFunc(Graph **g) {
  char *v1 = NULL, *v2 = NULL;
  int v1exists = 0, v2exists = 0;
  v1 = readline("Input first vertex name: ");
  if (!v1)
    return 0;
  v2 = readline("Input second vertex name: ");
  if (!v2) {
    free(v1);
    return 0;
  }
  if (*g)
    for (int i = 0; i < (*g)->nVertices; i++) {
      if (!strcmp((*g)->vertices[i], v1))
        v1exists = 1;
      if (!strcmp((*g)->vertices[i], v2))
        v2exists = 1;
    }
  if (!v1exists) {
    printf("Vertex \"%s\" does not exist\n", v1);
    free(v1);
    free(v2);
    return 1;
  }
  if (!v2exists) {
    printf("Vertex \"%s\" does not exist\n", v2);
    free(v1);
    free(v2);
    return 1;
  }

  Vertex *res = shortestPathDijkstra(*g, v1, v2);

  if (!res) {
    printf("Path from \"%s\" to \"%s\" does not exists\n", v1, v2);
    free(v1);
    free(v2);
    return 1;
  }

  printf("\n");
  int i = 0;
  for (;; i++) {
    if (strcmp(res[i], v2))
      printf("%s -> ", res[i]);
    else
      break;
  }
  printf("%s\n\n", res[i]);

  free(v1);
  free(v2);
  free(res);
  return 1;
}

int separateFriendsFunc(Graph **g) {
  if (*g)
    *g = separateFriends(*g);
  else
    printf("Graph is empty\n");
  return 1;
}