#include <iostream>
#include <fstream>
#include <string>

#define MAX_SIZE 10
#define PATH_FILE "gsoc_labyrinth.txt"

using namespace std;

void PrintLabyrinth(char** labyrinth, int* rows, int* columns)
{
    for (int i = 0; i < *rows; i++)
    {
        for (int j = 0; j < *columns; j++)
        {
            cout << labyrinth[i][j];
        }
        cout << endl;
    }
}

char** NewBiDimensionalArray(int* rows, int* columns)
{
    char** array = new char* [*rows];

    for (int i = 0; i < *rows; i++)
    {
        array[i] = new char[*columns];
    }
    return array;
}

char** ReadFromFile(int* rows, int* columns)
{
    ifstream file;
    string str;
    char** labyrinth = NULL;

    file.open(PATH_FILE);

    if (file)
    {
        while (getline(file, str))
        {   
            for (int j = 0; j < str.length(); j++)
            {
                if (*rows == 0 && j == 0)
                {
                    labyrinth = new char* [MAX_SIZE];
                    for (int i = 0; i < MAX_SIZE; i++)
                    {
                        labyrinth[i] = new char[str.length()];
                    }
                }
                labyrinth[*rows][j] = str[j];
            }
            (*rows)++;
            *columns = str.length();
        }

        for (int i = *rows; i < MAX_SIZE; i++)
        {
            delete[] labyrinth[i];
        }

        file.close();
        return labyrinth;
    }
    return NULL;
}

bool IsSafe(int x, int y, int* rows, int* columns)
{
    if (x >= 0 && x < *rows && y >= 0 && y < *columns)
        return true;
    
    return false;
}

void SaveLongestRun(char** longestRun, char** labyrinth, int* rows, int* columns)
{
    for (int i = 0; i < *rows; i++)
    {
        for (int j = 0; j < *columns; j++)
        {
            longestRun[i][j] = labyrinth[i][j];
        }
    }
}

void SolveLabyrinthUtils(char** longestRun, char** labyrinth, int x, int y, int* rows, int* columns, int moveCount, int* totalMoves)
{
    if (labyrinth[x][y] == '.')
    {
        labyrinth[x][y] = (moveCount++) + '0';

        if (x == (*rows) - 1)
        {
            if (moveCount > *totalMoves)
            {
                SaveLongestRun(longestRun, labyrinth, rows, columns);
                *totalMoves = moveCount;
            }
 
            labyrinth[x][y] = '.';
            return;
        }
        if (IsSafe(x, y - 1, rows, columns) && labyrinth[x][y - 1] == '.')
        {
            SolveLabyrinthUtils(longestRun, labyrinth, x, y - 1, rows, columns, moveCount, totalMoves);
        }
        if (IsSafe(x, y + 1, rows, columns) && labyrinth[x][y + 1] == '.')
        {
            SolveLabyrinthUtils(longestRun, labyrinth, x, y + 1, rows, columns, moveCount, totalMoves);
        }
        for (int i = 1, j = -1; j < 2; j++)
        {
            if (IsSafe(x + i, y + j, rows, columns) && labyrinth[x + i][y + j] == '.')
            {
                SolveLabyrinthUtils(longestRun, labyrinth, x + i, y + j, rows, columns, moveCount, totalMoves);
            }
        }
        labyrinth[x][y] = '.';
    }
    return;
}

void SolveLabyrinth(char** longestRun, char** labyrinth, int* rows, int* columns, int* totalMoves)
{
    int moveCount = 0;
    
    for (int i = 0, j = 0; j < *columns; j++)
    {
        SolveLabyrinthUtils(longestRun, labyrinth, i, j, rows, columns, moveCount, totalMoves);
    }
    return;
}

void ReleaseMemmory(char** arr, int* rows)
{
    for (int i = 0; i < *rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    int* rows = new int(0);
    int* columns = new int(0);
    int* totalMoves = new int(-1);
    char** labyrinth = ReadFromFile(rows, columns);

    if (labyrinth == NULL)
    {
        return 1;
    }
    
    char** longestRun = NewBiDimensionalArray(rows, columns);

    SolveLabyrinth(longestRun, labyrinth, rows, columns, totalMoves);

    if (*totalMoves != -1)
        PrintLabyrinth(longestRun, rows, columns);
    else
        PrintLabyrinth(labyrinth, rows, columns);

    cout << "The longest path has " << *totalMoves << " moves" << endl;

    ReleaseMemmory(labyrinth, rows);
    ReleaseMemmory(longestRun, rows);
    delete rows;
    delete columns;
    delete totalMoves;

    return 0;
}
