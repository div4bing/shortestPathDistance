#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_INPUT_PARAMETER 3
#define INFI 9999999999
#define NUMBER_OF_CITY 11                                                       // Change as per the number of City/node for input

long long getTotalLines(FILE *fp);
void printPathfromPtable(long long P[NUMBER_OF_CITY][NUMBER_OF_CITY], long long q, long long r);

long long totalLines;
FILE *inputFD;
FILE *outputFD;

// Recursive function to print intermediate shortest path
void printPathfromPtable(long long P[NUMBER_OF_CITY][NUMBER_OF_CITY], long long q, long long r)
{
  if (P[q][r] != 0)                                                             // Check if we have intermediate nodes
  {
    printPathfromPtable(P, q, (P[q][r] - 1));                                   // Find further intermediate nodes
    fprintf(outputFD, "%lld->", P[q][r]);                                       // Print the intermediate node
    printPathfromPtable(P, (P[q][r] - 1), r);                                   // Find further intermediate nodes
  }

  return;
}

// Function to fetch total lines from input
long long getTotalLines(FILE *fp)
{
  long long totalLines = 0;
  char string[100];

  while(!feof(fp)) {
    fgets(string, 100, fp);
    totalLines++;
  }

  totalLines--;

  if(fseek(fp, 0L, SEEK_SET) == EOF) {
    perror("Error while seeking to begining of file");
    exit(0);
  }

  return totalLines;
}

// Main function
int main (int argc, char *argv[])
{
  long long cityPath[NUMBER_OF_CITY][NUMBER_OF_CITY];
  long long pTable[NUMBER_OF_CITY][NUMBER_OF_CITY];
  long long i, j, k;
  long long q, r;
  char string[100];

  if (argc != 3)                                                                // Make sure the number of input is correct
  {
    printf("Error! Invalid number of Arguments. Please run program as ./submission inputFile.txt outputFile.txt\n");
    return -1;
  }

  inputFD = fopen(argv[1], "r");                                                // Open file for Reading the input
  if (inputFD == NULL)
  {
    perror("Error opening the input file");
    return -1;
  }

  totalLines = getTotalLines(inputFD) + 1;

  for (i = 0; i < NUMBER_OF_CITY; i++)                                          // Initialize cityPath array with 0 or INFI
  {
    for (j = 0; j < NUMBER_OF_CITY; j++)
    {
      pTable[i][j] = 0;                                                         // Initialize P -Table all zero

      if (i == j)
      {
        cityPath[i][j] = 0;                                                     // If self node, distance is 0
      }
      else
      {
        cityPath[i][j] = INFI;                                                  // Rest Initialize to INFI
      }
    }
  }

  long long tempNode1 = 0, tempNode2 = 0, tempDistance = 0;
  for(i=0; i < totalLines; i++)                                                 // Load given input to Array
  {
    fgets(string, 100, inputFD);
    sscanf(string, "%lld %lld %lld", &tempNode1, &tempNode2, &tempDistance);
    cityPath[tempNode1-1][tempNode2-1] = tempDistance;                          // Update values directly to cityPath from input
  }
  fclose(inputFD);                                                              // Close input file

  outputFD = fopen(argv[2], "w");                                               // Open file for Writing the output
  if (outputFD == NULL)
  {
    perror("Error opening the ouput file");
    return -1;
  }

  for (k = 0; k < NUMBER_OF_CITY; k++)                                          // Floyd's Algorithm to calculate shortest path in-place
  {
    for (i = 0; i < NUMBER_OF_CITY; i++)
    {
      for (j = 0; j < NUMBER_OF_CITY; j++)
      {
        if (cityPath[i][j] > (cityPath[i][k] + cityPath[k][j]))                 // If new distance with intermediate node is less than original load it and mark in P Table
        {
          cityPath[i][j] = (cityPath[i][k] + cityPath[k][j]);
          pTable[i][j] = (k+1);                                                 // So that we have node number starting from 1
        }
      }
    }
  }

  for (i = 1; i <= NUMBER_OF_CITY; i++)                                         // Print all the all the node pairs with the shortest path and path to output file
  {
    for (j = 1; j <= NUMBER_OF_CITY; j++)
    {
      q = i;
      r = j;

      fprintf(outputFD, "%lld %lld %lld ", q, r, cityPath[q-1][r-1]);           // Write the output to the file
      fprintf(outputFD, "path:%lld->", q);
      printPathfromPtable(pTable, (q-1), (r-1));                                // Find the path for given two nodes recursively
      fprintf(outputFD, "%lld\n", r);
    }
  }

  fclose(outputFD);                                                             // Close output file
  return 0;
}
