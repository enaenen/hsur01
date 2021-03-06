/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:41:16 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 11:42:33 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	g_size;

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
