/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:42:34 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 15:37:53 by jikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "boolean.h"
#include "input_validation.h"
#include "direction.h"

extern int	g_size;

int		**create_grid(void)
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

int		*create_col_row(char *str, int offset)
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
