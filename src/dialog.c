#include "dialog.h"

int inputInt(int *n) {
  char c = ' ';
  int sf = scanf("%d%c", n, &c);
  while (c != '\n' || sf != 2) {
    if (sf == -1)
      return 0;
    sf = scanf("%*[^\n]");
    printf("Bad input, try again: ");
    sf = scanf("%d%c", n, &c);
  }
  return sf != -1;
}

int dialog() {
  printf(PROMPT);
  int n = 0;
  int sf = inputInt(&n);
  if (!sf)
    return 0;
  while (n < 0 || n > 11) {
    printf("Input from 0 to 11: ");
    sf = inputInt(&n);
    if (!sf)
      return 0;
  }
  return n;
}

int inputEdge(int *n) {
  printf("Input edge: ");
  int sf = inputInt(n);
  if (!sf)
    return 0;
  while (*n < -10 || *n > 10) {
    printf("Input from -10 to 10: ");
    sf = inputInt(n);
    if (!sf)
      return 0;
  }
  return 1;
}

int inputHandshakes(int *n) {
  printf("Input max number of handshakes: ");
  int sf = inputInt(n);
  if (!sf)
    return 0;
  while (*n < 0) {
    printf("Input positive int: ");
    sf = inputInt(n);
    if (!sf)
      return 0;
  }
  return 1;
}