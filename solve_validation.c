/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:48:37 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 16:01:00 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "boolean.h"
#include "direction.h"

extern int	g_size;

int			*set_array(int **grid, int *axis)
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

t_bool		check_row(int **grid, int *axis, int *col_row[4], int direction)
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

t_bool		check_col(int **grid, int *axis, int *col_row[4], int direction)
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

t_bool		find_zero(int *arr)
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
