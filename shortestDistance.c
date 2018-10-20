#include <stdio.h>

#define NUMBER_OF_CITY 11
// #define NUMBER_OF_CITY 6
#define INFI 9999

int printMatirx(int matrix[NUMBER_OF_CITY][NUMBER_OF_CITY]);
void printPathfromPtable(int P[NUMBER_OF_CITY][NUMBER_OF_CITY], int q, int r);

int printMatirx(int matrix[NUMBER_OF_CITY][NUMBER_OF_CITY])                     // Print the Matrix
{
  int i, j;
  for (i = 0; i < NUMBER_OF_CITY; i++)
  {
    for (j = 0; j < NUMBER_OF_CITY; j++)
    {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void printPathfromPtable(int P[NUMBER_OF_CITY][NUMBER_OF_CITY], int q, int r)   // Finds intermediate nodes recursively
{
  if (P[q][r] != 0)                                                             // Check if we have intermediate nodes
  {
    printPathfromPtable(P, q, (P[q][r] - 1));                                   // Find further intermediate nodes
    printf("%d->", P[q][r]);                                                    // Print the intermediate node
    printPathfromPtable(P, (P[q][r] - 1), r);                                   // Find further intermediate nodes
  }

  return;
}

int main (int argc, char *argv[])
{
  // Load the given graph in the array for calculation
  int cityPath[NUMBER_OF_CITY][NUMBER_OF_CITY] = {{0, 140, INFI, INFI, INFI, 180, 100, 70, INFI, INFI, INFI}, \
                                                  {140, 0, 130, INFI, 100, INFI, INFI, INFI, INFI, INFI, INFI}, \
                                                  {INFI, 130, 0, 160, INFI, INFI, INFI, INFI, INFI, INFI, INFI}, \
                                                  {INFI, INFI, 160, 0, 65, INFI, INFI, INFI, INFI, INFI, 180}, \
                                                  {INFI, 100, INFI, 65, 0, 70, INFI, INFI, 70, INFI, INFI}, \
                                                  {180, INFI, INFI, INFI, 70, 0, 60, INFI, INFI, INFI, INFI}, \
                                                  {100, INFI, INFI, INFI, INFI, 60, 0, INFI, INFI, INFI, INFI}, \
                                                  {70, INFI, INFI, INFI, INFI, INFI, 65, 0, INFI, INFI, INFI}, \
                                                  {INFI, INFI, INFI, INFI, 70, INFI, INFI, INFI, 0, 60, INFI}, \
                                                  {INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, 60, 0, 100}, \
                                                  {INFI, INFI, INFI, 180, INFI, INFI, INFI, INFI, INFI, 100, 0} \
                                                };

  // int cityPath[NUMBER_OF_CITY][NUMBER_OF_CITY] = {{0, 5, INFI, 7, 3, 1}, \
  //                                                 {5, 0, 4, INFI, INFI, 1}, \
  //                                                 {INFI, 4, 0, 2, INFI, 1}, \
  //                                                 {7, INFI, 2, 0, 3, 50}, \
  //                                                 {3, INFI, INFI, 3, 0, INFI}, \
  //                                                 {1, 1, 1, 50, INFI, 0} \
  //                                                 };

  int pTable[NUMBER_OF_CITY][NUMBER_OF_CITY];                                   // P - Table to store the route for shortest distance
  int i, j, k;
  int q, r;

  printf("Original Matrix\n");
  printMatirx(cityPath);

  for (i=0; i < NUMBER_OF_CITY; i++)                                            // Initialize P-Table with all 0
  {
    for (j = 0; j < NUMBER_OF_CITY; j++)
    {
      pTable[i][j] = 0;
    }
  }

  printf("Original P-Table\n");
  printMatirx(pTable);

  for (k = 0; k < NUMBER_OF_CITY; k++)                                          // Floyd's Algorithm to calculate shortest path in-place
  {
    for (i = 0; i < NUMBER_OF_CITY; i++)
    {
      for (j = 0; j < NUMBER_OF_CITY; j++)
      {
        if (cityPath[i][j] > (cityPath[i][k] + cityPath[k][j]))
        {
          cityPath[i][j] = (cityPath[i][k] + cityPath[k][j]);
          pTable[i][j] = (k+1);                                                 // So that we have node number starting from 1
        }
      }
    }
  }

  printf("FINAL Matrix\n");
  printMatirx(cityPath);

  printf("\nFINAL P-Table\n");
  printMatirx(pTable);

  printf("\n************************ FINAL OUTPUT ************************\n\n");

  for (i = 1; i <= NUMBER_OF_CITY; i++)                                         // Print all the all the node pairs with the shortest path and path
  {
    for (j = 1; j <= NUMBER_OF_CITY; j++)
    {
      q = i;
      r = j;

      printf("%d %d %d ", q, r, cityPath[q-1][r-1]);
      printf("path:%d->", q);
      printPathfromPtable(pTable, (q-1), (r-1));                                // Find the path for given two nodes recursively
      printf("%d\n", r);
    }
  }

  return 0;
}
