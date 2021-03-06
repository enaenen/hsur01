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

int	g_size;

typedef enum
{
	true = 1,
	false = 0
}	t_bool;

t_bool	backtracking(int **grid, int *col_row[4]);
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

t_bool	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int	count_numbers(char *str)
{
	int	count;
	
	count = 0;
	while (*str)
	{
		if (is_number(*str))
			count++;
		str++;
	}
	return (count);
}

t_bool	is_valid_space(char *c)
{
	if (is_number(*(c - 1)) && *c == ' ' && is_number(*(c + 1)))
		return (true);
	return (false);
}

t_bool	input_validation(char *str, int nbr_count)
{
	int	index;

	if (nbr_count != g_size * 4 || g_size < 3 || g_size > 9)
		return (false);
	index = 1;
	while (str[index])
	{
		if (!is_valid_space(&str[index]))
			return (false);
		index += 2;
	}
	return (true);
}

int	**create_grid(void)
{
	int	row;
	int	col;
	int	**grid;
	
	grid = (int **)malloc((g_size) * sizeof(int *));
	row = 0;
	while (row < g_size)
	{
		grid[row] = (int *)malloc((g_size) * sizeof(int));
		col = 0;
		while (col <= g_size)
		{
			grid[row][col] = 0;
			col++;
		}
		row++;
	}
	grid[g_size] = 0;
	return (grid);
}

int	*create_col_row(char *str, int offset)
{
	int	index;
	int	*col_row;
	
	col_row = (int *)malloc((g_size) * sizeof(int));
	index = 0;
	while (index < g_size && *str)
	{
		if (is_number(*str))
		{
			if (offset)
				offset--;
			else
			{
				col_row[index] = *str - '0';
				index++;
			}
		}
		str++;
	}
	return (col_row);
}

t_bool	validate_col_row(int *col_row[4])
{
	int	max;
	int	index;

	max = g_size + 1;
	index = 0;
	while (index < g_size)
	{
		if ((col_row[UP][index] + col_row[DOWN][index]) > max)
			return (false);
		if ((col_row[LEFT][index] + col_row[RIGHT][index]) > max)
			return (false);
		index++;
	}
	return (true);
}

int	*is_empty(int **grid)
{
	int	row;
	int	col;
	int	*axis;
	
	axis = (int *)malloc(2 * sizeof(int));
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
				return (axis);
			}
			col++;
		}
		row++;
	}
	return (axis);
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
t_bool	recursive(int **grid, int *empty, int guess, int *col_row[4])
{
	while (guess <= g_size)
	{
		grid[empty[ROW]][empty[COL]] = guess;
		if (test(grid, empty, guess, col_row))
		{
			if (backtracking(grid, col_row))
			{
				free(empty);
				return (true);
			}
			else
				grid[empty[ROW]][empty[COL]] = 0;
		}
		else
			grid[empty[ROW]][empty[COL]] = 0;
		guess++;
	}
	free(empty);
	return (false);
}

t_bool	backtracking(int **grid, int *col_row[4])
{
	int	*empty;
	int	guess;

	guess = 1;
	empty = is_empty(grid);
	if (empty[0] == -1)
		return (true);
	return (recursive(grid, empty, guess, col_row));
}

void	print_grid(int **grid)
{
	int	row;
	int	col;

	row = 0;
	while (row < g_size)
	{
		col = 0;
		while (col < g_size)
		{
			ft_putchar((char)(grid[row][col] + '0'));
			if (col != g_size - 1)
				ft_putstr(" ");
			col++;
		}
		if (row != g_size)
			ft_putstr("\n");
		row++;
	}
}

void	free_grid(int **grid)
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
	free_grid(grid);
	free_grid(col_row);
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
