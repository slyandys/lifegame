//This is a very simple C++ implementation of John Conway's Game of Life.
//This implementation uses several nested for loops as well as two-dimensional
//arrays to create a grid for the cells in the simulation to interact.
//The array that is displayed to the user is 50 x 100, but actual size
//of the array is row x column.  The reason for this is to make the 
//calculations easier for the cells on the outermost "frame" of the grid.

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 12000 //max:12000
#define column 12000 //max:12000

using namespace std;

//Copies array1 into array2.
void copy(float *array1, float *array2)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
			array2[i*column + j] = array1[i*column + j];
	}
}

//The life function is the core of this program.
//It counts the number of cells surrounding the center cell, and 
//determines whether it lives, dies, or stays the same.
void life(float *array, char choice)
{
	//Copies the main array to a temp array so changes can be entered into a grid
	//without effecting the other cells and the calculations being performed on them.
	float *temp;// [row][column];
	temp = (float*)malloc(sizeof(float)*row*column);
	copy(array, temp);

	clock_t mstart, mend;

	mstart = clock();
	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (choice == 'm')
			{
				int count = 0;

				//top left corner
				if (i == 0 && j == 0)
				{
					count = array[i*column + j] + array[i*column + j + 1] +
						array[(i + 1)*column + j] + array[(i + 1)*column + j + 1];
				}

				//top boarder
				else if (i == 0 && j != 0 && j != (column - 1))
				{
					count = array[i*column + j - 1] + array[i*column + j] + array[i*column + j + 1] +
						array[(i + 1)*column + j - 1] + array[(i + 1)*column + j] + array[(i + 1) * row + j + 1];
				}

				//top right corner
				else if (i == 0 && j == (row - 1))
				{
					count = array[i*column + j - 1] + array[i*column + j] +
						array[(i + 1)*column + j - 1] + array[(i + 1)*column + j];
				}

				//bottom left corner
				else if (i == (row - 1) && j == 0)
				{
					count = array[(i - 1)*column + j] + array[(i - 1)*column + j + 1] +
						array[i*column + j] + array[i*column + j + 1];
				}

				//bottom boarder
				else if (i == (row - 1) && j != 0 && j != (column - 1))
				{
					count = array[(i - 1)*column + j - 1] + array[(i - 1)*column + j] + array[(i - 1)*column + j + 1] +
						array[i*column + j - 1] + array[i*column + j] + array[i*column + j + 1];
				}

				//bottom right corner
				else if (i == (row - 1) && j == (column - 1))
				{
					count = array[(i - 1)*column + j - 1] + array[(i - 1)*column + j] +
						array[i*column + j - 1] + array[i*column + j];
				}

				//left boarder
				else if (j == 0 && i != 0 && i != (row - 1))
				{
					count = array[(i - 1)*column + j] + array[(i - 1)*column + j + 1] +
						array[i*column + j] + array[i*column + j + 1] +
						array[(i + 1)*column + j] + array[(i + 1)*column + j + 1];
				}
				
				//right boarder
				else if (j == (column - 1) && i != 0 && i != (row - 1))
				{
					count = array[(i - 1)*column + j - 1] + array[(i - 1)*column + j] +
						array[i*column + j - 1] + array[i*column + j] +
						array[(i + 1)*column + j - 1] + array[(i + 1)*column + j];

				}
				//This calculation is applied for cells not on boarders or corners
				//The neighborhood checks all 9 cells including itself and the surrounding neighbour in the array.
				else
				{
					count = array[(i - 1)*column + j - 1] + array[(i - 1)*column + j] + array[(i - 1)*column + j + 1] +
						array[i*column + j - 1] + array[i*column + j] + array[i*column + j + 1] +
						array[(i + 1)*column + j - 1] + array[(i + 1)*column + j] + array[(i + 1)*column + j + 1];
				}

				
				//Rules
				//The cell dies when neighbor<3 or neighbor>4.
				if (array[i*column + j] == 1 && (count < 3 || count > 4))
					temp[i*column + j] = 0;
				//The cell stays the same when neighbor=3 or =4.
				if (array[i*column + j] == 1 && (count == 3 || count == 4))
					temp[i*column + j] = 1;
				//The cell is "born" when neighbor=3 and itself is died.
				if (array[i*column + j] == 0 && count == 3)
					temp[i*column + j] = 1;
				if (array[i*column + j] == 0 && count != 3)
					temp[i*column + j] = 0;
			}
		}
	}

	mend = clock();
	printf("model start time: %d ms\n", mstart);
	printf("model end time: %d ms\n", mend);
	//Copies the completed temp array back to the main array.
	copy(temp, array);
	free(temp);
}

//Checks to see if two arrays are exactly the same. 
//This is used to end the simulation early, if it 
//becomes stable before the 100th generation. This
//occurs fairly often in the Von Neumann neighborhood,
//but almost never in the Moore neighborhood.
//bool compare(float *array1, float *array2)
//{
//	int count = 0;
//	for (int j = 0; j < row; j++)
//	{
//		for (int i = 0; i < column; i++)
//		{
//			if (array1[j*column + i] == array2[j*column + i])
//				count++;
//		}
//	}
//	//Since the count gets incremented every time the cells are exactly the same,
//	//an easy way to check if the two arrays are equal is to compare the count to 
//	//the dimensions of the array multiplied together.
//	if (count == row * column)
//	{
//		//cout << "~ they are the same" << endl;
//		return true;
//	}	
//	else
//	{
//		return false;
//	}
//		
//}

//This function prints the row-2 x column-2 part of the array, since that's the only
//portion of the array that we're really interested in. A live cell is marked
//by a '*', and a dead or vacant cell by a '-'.
void print(float *array)
{
	//Clears the screen so the program can start fresh.
	//system("cls");
	for (int i = 0; i < row-1; i++)
	{
		for (int j = 0; j < column-1; j++)
		{
			if (array[i*column + j] == 1)
				cout << '*';
			else
				cout << '-';
		}
		cout << endl;
	}
}

void main()
{
	float *gen0;// double gen0[row][column];
	float *todo;// [row][column];
	//float *backup;// [row][column];
	char neighborhood;
	char again;
	char cont;
	bool comparison;
	string decoration;

	//alloc
	gen0 = (float*)malloc(sizeof(float)*row*column);
	todo = (float*)malloc(sizeof(float)*row*column);
	//backup = (float*)malloc(sizeof(float)*row*column);

	//Instructions on the program, along with the rules of the game.
	cout << endl << "This program is a C++ implementation of John Conway's Game of Life."
		<< endl << "With it, you can simulate how \"cells\" interact with each other." << endl
		<< endl << "The cell will checks its neighbour--all 8 surrounding cells"
		<< endl << "The rules of the \"Game of Life\" are as follows:" << endl
		<< endl << "R1. Any live cell with fewer than two live neighbors dies, as if caused by under-population."
		<< endl << "R2. Any live cell with two or three live neighbors lives on to the next generation."
		<< endl << "R3. Any live cell with more than three live neighbors dies for overcrowding."
		<< endl << "R4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction." << endl
		<< endl << "The initial configuration (Generation 0) of the board is determined randomly."
		<< endl << "Every hundred Generations you will get the option to end or continue the simulation."
		<< endl << "If a system becomes \"stable\" (meaning the system does not change from one"
		<< endl << "generation to the next), the simulation will end automatically." << endl << endl;
	
	//Loop for user if someone wants to keep simulating.
	do
	{
		//Set system pause to let the player finish reading those above
		system("pause");
		neighborhood = 'm';
		
		int i = 0;

		//Loop that does the bulk of the simulation.
		do
		{
			//Generates the initial random state of the game board.
			//srand(time(NULL));
			//The actual array is row x column, but it's easier to just leave the surrounding part of
			//the array blank so it doesn't effect the calculations in the life function above.
			//initalized the map
			for (int i = 0; i < row-1; i++)
			{
				for (int j = 0; j < column - 1; j++)
					gen0[i*column + j] = 0;// rand() % 2;
			}
			//test
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
					gen0[i*column + j] = 1;
			}

			//Determines how big the decoration should be.
			if (i < 10)
				decoration = "#############";
			else if (i >= 10 && i < 100)
				decoration = "##############";
			else if (i >= 100 && i < 1000)
				decoration = "###############";
			else if (i >= 1000 && i < 10000)
				decoration = "################";
			else
				decoration = "#################";

			//Prints the generation.  If i == 0, the gen0 array is copied to the 
			//todo array, and is printed before any functions act upon it.
			cout << decoration << endl << "Generation " << i
				<< ":" << endl << decoration << endl << endl;

			//Initializes the arrays by copying the gen0 array to the todo array.
			if (i == 0)
				copy(gen0, todo);
			//copy(todo, backup);
			//print(todo);
			
			clock_t CAstart, CAfinish;
			//time_t start, finish;
			CAstart = clock();
			//time(&start);
			life(todo, neighborhood);
			//time(&finish);
			CAfinish = clock();
			
			//time(&CAfinish);
			//clock_t CAduration = (double);
			//cout << "the CAS duration is " << (double)(CAfinish - CAstart) << endl;
			printf("CAmodel start time: %d ms\n", CAstart);
			printf("CAmodel end time: %d ms\n", CAfinish);
			//printf("%dms\n", start);
			//printf("%dms\n", finish);
			system("pause");

			i++;
			//Pauses the system for 1/10 of a second in order to give the screen
			//time to refresh.
			//system("sleep 1");
			//Checks whether the generation is a multiple of 100 to ask 
			//the user if they want to continue the simulation. If they
			//wish to end, the program breaks out of the loop to ask if
			//the user wishes to run another simulation.
			if (i % 100 == 1 && i != 1)
			{
				cout << endl;
				//Loop to check for proper inputs.
				do
				{
					cout << "Would you like to continue this simulation? (y/n): ";
					cin >> cont;
				} while (cont != 'y' && cont != 'n');
				if (cont == 'n')
					break;
			}
			//Compares the current generation with a backup generation.
			//If they aren't the same (they usually aren't) the system
			//clears the screen and repeats the process until they are
			//the same or the user chooses to quit.
			//comparison = compare(todo, backup);
			//if (comparison == false)
			//	system("cls");//system("clear");
			//if (comparison == true)
			//	cout << endl;
		} while (i < 100);// (comparison == false);
		//Loop to check for proper inputs.
		do
		{
			cout << "Would you like to run another simulation? (y/n): ";
			cin >> again;
		} while (again != 'y' && again != 'n');
	} while (again == 'y');
	free(gen0);
	free(todo);
}