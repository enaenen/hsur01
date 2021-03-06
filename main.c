/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:54:16 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 16:56:07 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#define ERROR "Error\n"
#include "boolean.h"
#include "input_validation.h"
#include "input_process.h"
#include "solve_validation.h"
#include "print_grid.h"
#include "solve_backtrack.h"

int		g_size;

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
	int		*col_row[4];
	int		**grid;
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
	return (success);
}

int		main(int argc, char **argv)
{
	t_bool	error;
	int		nbr_count;

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
