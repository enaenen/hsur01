#include <unistd.h>
#include <stdlib.h>
#define ERROR "Error\n"
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ROW 0
#define COL 1
#define L_T_R 1
#define R_T_L -1
#define U_T_D 1
#define D_T_U -1

#include "boolean.h"
#include "input_validation.h"
#include "input_process.h"
#include "print_grid.h"

int	g_size;

void	is_empty(int **grid, int *axis)
{
	int	row;
	int	col;

	axis[0] = -1;
	axis[1] = -1;
	row = 0;
	while (row < g_size)
	{
		col = 0;
		while (col < g_size)
		{
			if (grid[row][col] == 0)
			{
				axis[0] = row;
				axis[1] = col;
				return ;
			}
			col++;
		}
		row++;
	}
	return ;
}

t_bool	has_duplicate(int **grid, int *axis, int guess)
{
	int	col;
	int	row;
	
	col = -1;
	row = -1;
	while (col < g_size)
	{
		col++;
		if (col == axis[1] || col == g_size)
			continue;
		if (grid[axis[0]][col] == guess)
			return (true);
	}
	while (row < g_size)
	{
		row++;
		if (row == axis[0] || row == g_size)
			continue;
		if (grid[row][axis[1]] == guess)
			return (true);
	}
	return (false);
}

t_bool	find_zero(int *arr)
{
	int	index;
	
	index = 0;
	while (index < g_size)
	{
		if (arr[index] == 0)
			return (true);
		index++;
	}
	return (false);
}

int	*set_array(int **grid, int *axis)
{
	int	*array;
	int	index;

	index = 0;
	array = (int *)malloc((g_size) * sizeof(int));
	while (index < g_size)
	{
		array[index] = grid[index][axis[1]];
		index++;
	}
	return (array);
}

t_bool	check_row(int **grid, int *axis, int *col_row[4], int direction)
{
	int	column;
	int	seen;
	int	memory;
	int	current;
	
	column = 0;
	seen = 0;
	memory = -1;
	while (column < g_size)
	{
		current = grid[axis[0]][column];
		if (direction == R_T_L)
			current = grid[axis[0]][g_size - 1 - column];
		if (current > memory)
		{
			memory = current;
			seen++;
		}
		column++;
	}
	if (direction == R_T_L)
		return (seen == col_row[RIGHT][axis[0]]);
	else
		return (seen == col_row[LEFT][axis[0]]);
}

t_bool	check_col(int **grid, int *axis, int *col_row[4], int direction)
{
	int	row;
	int	seen;
	int	memory;
	int	current;

	row = 0;
	seen = 0;
	memory = -1;
	while (row < g_size)
	{
		current = grid[row][axis[1]];
		if (direction == D_T_U)
			current = grid[g_size - 1 - row][axis[1]];
		if (current > memory)
		{
			memory = current;
			seen++;
		}
		row++;
	}
	if (direction == D_T_U)
		return (seen == col_row[DOWN][axis[1]]);
	else
		return (seen == col_row[UP][axis[1]]);
}

t_bool	is_valid(int **grid, int *axis, int *col_row[4])
{
	int	*col_array;
	t_bool	row_has_zero;
	t_bool	col_has_zero;

	col_array = set_array(grid, axis);
	row_has_zero = find_zero(grid[axis[0]]);
	col_has_zero = find_zero(col_array);
	free(col_array);
	if (row_has_zero && col_has_zero)
		return (true);
	if (!row_has_zero && col_has_zero)
	{
		return (check_row(grid, axis, col_row, L_T_R)
		&& check_row(grid, axis, col_row, R_T_L));
	}
	if (row_has_zero && !col_has_zero)
		return (check_col(grid, axis, col_row, U_T_D)
		&& check_col(grid, axis, col_row, D_T_U));
	return (check_row(grid, axis, col_row, L_T_R)
	&& check_row(grid, axis, col_row, R_T_L)
	&& check_col(grid, axis, col_row, U_T_D)
	&& check_col(grid, axis, col_row, D_T_U));
}

t_bool	test(int **grid, int *axis, int guess, int *col_row[4])
{
	t_bool	test_duplicate;
	t_bool	test_valid;

	test_duplicate = has_duplicate(grid, axis, guess);
	test_valid = is_valid(grid, axis, col_row);

	return (!test_duplicate && test_valid);
}

t_bool	backtracking(int **grid, int *col_row[4])
{
	int	empty[2];
	int	guess;

	guess = 1;
	is_empty(grid, empty);
	if (empty[0] == -1)
		return (true);
	while (guess <= g_size)
	{
		grid[empty[ROW]][empty[COL]] = guess;
		if (test(grid, empty, guess, col_row))
		{
			if (backtracking(grid, col_row))
				return (true);
			else
				grid[empty[ROW]][empty[COL]] = 0;
		}
		else
			grid[empty[ROW]][empty[COL]] = 0;
		guess++;
	}
	return (false);
}

void	free_arr(int **grid)
{
	int	index;

	index = 0;
	while (index < g_size)
	{
		free(grid[index]);
		index++;
	}
}

t_bool	solve(char *str)
{
	int	*col_row[4];
	int	**grid;
	t_bool	success;

	col_row[UP] = create_col_row(str, g_size * UP);
	col_row[DOWN] = create_col_row(str, g_size * DOWN);
	col_row[LEFT] = create_col_row(str, g_size * LEFT);
	col_row[RIGHT] = create_col_row(str, g_size * RIGHT);
	grid = create_grid();
	if (!validate_col_row(col_row))
		return (false);
	success = backtracking(grid, col_row);
	if (success)
		print_grid(grid);
	free_arr(grid);
	free_arr(col_row);
	return (success);
}

int	main(int argc, char **argv)
{
	t_bool	error;
	int	nbr_count;
	
	error = (argc != 2);
	if (!error)
	{
		nbr_count = count_numbers(argv[1]);
		g_size = nbr_count / 4;
		error = !input_validation(argv[1], nbr_count);
		if (!error)
			error = !solve(argv[1]);
	}
	if (error)
	{
		ft_putstr(ERROR);
		return (-1);
	}
	return (0);
}
