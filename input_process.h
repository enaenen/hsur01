/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:19:19 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 14:56:45 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESS_H
# define INPUT_PROCESS_H

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

# include "boolean.h"

int		*create_col_row(char *str, int offset);

int		**create_grid(void);

t_bool	validate_col_row(int *col_row[4]);

#endif
