/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_backtrack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:03:33 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 16:19:53 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "direction.h"
#include "boolean.h"

extern int	g_size;

void		is_empty(int **grid, int *axis)
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

t_bool		has_duplicate(int **grid, int *axis, int guess)
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

t_bool		is_valid(int **grid, int *axis, int *col_row[4])
{
	int		*col_array;
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

t_bool		test(int **grid, int *axis, int guess, int *col_row[4])
{
	t_bool	test_duplicate;
	t_bool	test_valid;

	test_duplicate = has_duplicate(grid, axis, guess);
	test_valid = is_valid(grid, axis, col_row);
	return (!test_duplicate && test_valid);
}

t_bool		backtracking(int **grid, int *col_row[4])
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
