/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:46:43 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 14:48:36 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

extern int	g_size;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
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
