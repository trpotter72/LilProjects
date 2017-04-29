#include <iostream>

//Can only have two roombas per col
bool check_rows(char** grid, int cols, int rows)
{
	for(int i = 0; i < rows; i++)
	{
		int roombas = 0;
		for(int j = 0; j < cols; j++)
		{
			if(grid[i][j]=='R')
			{
				roombas++;
			}

		}
		if(roombas > 2)
		{
			return false;
		}
	}
	return true;
}

//Can only have one roomba per col
bool check_cols(char** grid, int cols, int rows)
{
	for(int i = 0; i < cols; i++)
	{
		int roombas = 0;
		for(int j = 0; j < rows; j++)
		{
			if(grid[j][i]=='R')
			{
				roombas++;
			}

		}
		if(roombas != 1)
		{
			return false;
		}
	}
	return true;
}

//Checks relative postions
bool valid_diagonals(char** grid, int cols, int rows)
{
	if(grid[0][0] != 'R')
	{
		return false;
	}

	if(rows >= cols)
	{
		for (int i = 0; i < cols; i++)
		{
			if (grid[i][i]!='R')
			{
				return false;
			}
		}
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			if (grid[i][i]!='R')
			{
				return false;
			}
		}

		if(cols >= 2*rows)
		{
			for(int i = 0; i < rows-1; i++)
			{
				std::cout<< "grid:" << rows-i-1 << rows+i-1 << std::endl;
				if (grid[rows-i-1][i+rows-1]!='R')
				{
					return false;
				}
			}
		}
		else
		{
			for(int i = 0; i < cols-rows+1; i++)
			{
				std::cout<< "grid:" << rows-i << rows+i << std::endl;
				if (grid[rows-i-1][i+rows-1]!='R')
				{
					return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	int cols = 0;
	int rows = 0;

	std::cin >> cols >> rows;

	char** grid = new char*[rows];

	//Loops through rows;
	for(int i = 0; i < rows; i ++)
	{
		grid[i] = new char[cols];
		for(int j = 0; j < cols; j++)
		{
			std::cin >> grid[i][j];
		}
	}

	/*if(!check_cols(grid, cols, rows))
	{
		std::cout << "no";
	}
	else if (!check_rows(grid, cols, rows))
	{
		std::cout << "no";
	}*/
	if (!valid_diagonals(grid, cols, rows))
	{
		std::cout << "no";
	}

	else
	{
		std::cout << "yes";
	}
}
