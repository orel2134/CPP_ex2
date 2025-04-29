#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "my_mat.h"

int shortestDist[N][N];
int nextNode[N][N];
int updateNeeded = TRUE; // Use int to match header file

void initializeMatrices(int mat[N][N])
{
    // Initialize shortestDist and nextNode matrices
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i == j){
                shortestDist[i][j] = 0;
                nextNode[i][j] = -1;
                continue;
            }
            shortestDist[i][j] = mat[i][j];
            if (mat[i][j] != 0) // Update nextNode matrix only if there is a path
                nextNode[i][j] = j;
            else
                nextNode[i][j] = -1; // No path initially
        }
    }
}

void floydWarshall(int mat[N][N])
{
    initializeMatrices(mat);

    for (int k = 0; k < N; ++k)
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (i == j)
                    continue;

                if (shortestDist[i][k] == 0 || shortestDist[k][j] == 0)
                {
                    // There is no path from i to k or from k to j
                    continue;
                }

                // If there is no path from i to j or if the path from i to k and k to j is shorter than the current path
                if (shortestDist[i][j] == 0 || shortestDist[i][k] + shortestDist[k][j] < shortestDist[i][j])
                {
                    shortestDist[i][j] = shortestDist[i][k] + shortestDist[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }
}

int isPathExists(int mat[N][N], int start, int end, int need_update)
{
    if (need_update == TRUE)
    {
        floydWarshall(mat);
    }
    return shortestDist[start][end] != 0 ? TRUE : FALSE;
}

void printShortestPath(int mat[N][N], int start, int end, int need_update)
{
    if (need_update == TRUE)
    {
        floydWarshall(mat);
    }

    // No path
    if (isPathExists(mat, start, end, FALSE) == FALSE || (start == end && mat[start][end] == 0))
    {
        puts("-1");
        return;
    }

    printf("%d\n", shortestDist[start][end]);
}

//