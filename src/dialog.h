#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#define PROMPT                                                                 \
  "1 - add vertex\n"                                                           \
  "2 - add edge\n"                                                             \
  "3 - del vertex\n"                                                           \
  "4 - del edge\n"                                                             \
  "5 - change vertex\n"                                                        \
  "6 - change edge\n"                                                          \
  "7 - print adj matrix\n"                                                     \
  "8 - export graphviz\n"                                                      \
  "9 - handshake DFS\n"                                                        \
  "10 - shortest path Dijkstra\n"                                              \
  "11 - separate friends\n"                                                    \
  "0 - exit\n"                                                                 \
  "Input: "

int inputEdge(int *n);
int inputHandshakes(int *n);
int inputInt(int *n);
int dialog();