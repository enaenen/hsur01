/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:40:44 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 14:55:13 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "boolean.h"

extern int	g_size;

t_bool		is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int			count_numbers(char *str)
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

t_bool		is_valid_space(char *c)
{
	if (is_number(*(c - 1)) && *c == ' ' && is_number(*(c + 1)))
		return (true);
	return (false);
}

t_bool		input_validation(char *str, int nbr_count)
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
