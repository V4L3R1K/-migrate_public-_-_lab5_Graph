#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/src/graph.h"
#include "dialog.h"

int addVertexFunc(Graph **g);
int addEdgeFunc(Graph **g);
int delVertexFunc(Graph **g);
int delEdgeFunc(Graph **g);
int changeVertexFunc(Graph **g);
int changeEdgeFunc(Graph **g);
int printGraphFunc(Graph **g);
int exportGraphvizFunc(Graph **g);
int handshakeDFSFunc(Graph **g);
int shortestPathDijkstraFunc(Graph **g);
int separateFriendsFunc(Graph **g);