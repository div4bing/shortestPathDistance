#include <stdio.h>

#define NUMBER_OF_CITY 6
#define INFI 9999

int printMatirx(int matrix[NUMBER_OF_CITY][NUMBER_OF_CITY]);
void printPathfromPtable(int P[NUMBER_OF_CITY][NUMBER_OF_CITY], int q, int r);

int printMatirx(int matrix[NUMBER_OF_CITY][NUMBER_OF_CITY])
{
  for (int i=0; i < NUMBER_OF_CITY; i++)
  {
    for (int j=0; j < NUMBER_OF_CITY; j++)
    {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void printPathfromPtable(int P[NUMBER_OF_CITY][NUMBER_OF_CITY], int q, int r)
{
  if (P[q][r] != 0)
  {
    printPathfromPtable(P, q, (P[q][r] - 1));
    printf("v%d ", P[q][r]);
    printPathfromPtable(P, (P[q][r] - 1), r);
    return;
  }
	else
  {
    return;
  }
}

int main (int argc, char *argv[])
{
  // int cityPath[NUMBER_OF_CITY][NUMBER_OF_CITY] = {{0, 140, INFI, INFI, INFI, 180, 100, 70, INFI, INFI, INFI}, \
  //                                                 {140, 0, 130, INFI, 100, INFI, INFI, INFI, INFI, INFI, INFI}, \
  //                                                 {INFI, 130, 0, 160, INFI, INFI, INFI, INFI, INFI, INFI, INFI}, \
  //                                                 {INFI, INFI, 160, 0, 65, INFI, INFI, INFI, INFI, INFI, 180}, \
  //                                                 {INFI, 100, INFI, 65, 0, 70, INFI, INFI, 70, INFI, INFI}, \
  //                                                 {180, INFI, INFI, INFI, 70, 0, 60, INFI, INFI, INFI, INFI}, \
  //                                                 {100, INFI, INFI, INFI, INFI, 60, 0, INFI, INFI, INFI, INFI}, \
  //                                                 {70, INFI, INFI, INFI, INFI, INFI, 65, 0, INFI, INFI, INFI}, \
  //                                                 {INFI, INFI, INFI, INFI, 70, INFI, INFI, INFI, 0, 60, INFI}, \
  //                                                 {INFI, INFI, INFI, INFI, INFI, INFI, INFI, INFI, 60, 0, 100}, \
  //                                                 {INFI, INFI, INFI, 180, INFI, INFI, INFI, INFI, INFI, 100, 0} \
  //                                               };
  int cityPath[NUMBER_OF_CITY][NUMBER_OF_CITY] = {{0, 5, INFI, 7, 3, 1}, \
                                                  {5, 0, 4, INFI, INFI, 1}, \
                                                  {INFI, 4, 0, 2, INFI, 1}, \
                                                  {7, INFI, 2, 0, 3, 50}, \
                                                  {3, INFI, INFI, 3, 0, INFI}, \
                                                  {1, 1, 1, 50, INFI, 0} \
                                                  };
  int pTable[NUMBER_OF_CITY][NUMBER_OF_CITY];
  int i, j, k;
  int q, r;

  printf("Original Matrix\n");
  printMatirx(cityPath);

  for (i=0; i < NUMBER_OF_CITY; i++)
  {
    for (j = 0; j < NUMBER_OF_CITY; j++)
    {
      pTable[i][j] = 0;
    }
  }

  printf("Original P-Table\n");
  printMatirx(pTable);

  for (k = 0; k < NUMBER_OF_CITY; k++)
  {
    for (i = 0; i < NUMBER_OF_CITY; i++)
    {
      for (j = 0; j < NUMBER_OF_CITY; j++)
      {
        if (cityPath[i][j] > (cityPath[i][k] + cityPath[k][j]))
        {
          cityPath[i][j] = (cityPath[i][k] + cityPath[k][j]);
          pTable[i][j] = (k+1); // So that we have node number starting from 1
        }
      }
    }
  }

  printf("FINAL Matrix\n");
  printMatirx(cityPath);

  printf("\nFINAL P-Table\n");
  printMatirx(pTable);

  q = 1;
  r = 4;

  printf("Path between q=%d and r=%d is: \n", q-1, r-1);
  printf("v%d ", q);
  printPathfromPtable(pTable, (q-1), (r-1));
  printf("v%d\n", r);

  return 0;
}
