#include "lab5.h"

int main() {
  Graph *g = NULL;

  int (*arrFunc[])(Graph **) = {NULL,
                                addVertexFunc,
                                addEdgeFunc,
                                delVertexFunc,
                                delEdgeFunc,
                                changeVertexFunc,
                                changeEdgeFunc,
                                printGraphFunc,
                                exportGraphvizFunc,
                                handshakeDFSFunc,
                                shortestPathDijkstraFunc,
                                separateFriendsFunc};
  int rc;
  while (rc = dialog()) {
    if (!arrFunc[rc](&g))
      break;
  }

  freeGraph(g);
  return 0;
}