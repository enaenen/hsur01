/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:51:01 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 16:01:25 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_VALIDATION_H
# define SOLVE_VALIDATION_H

# include "boolean.h"
# include "direction.h"

int		*set_array(int **grid, int *axis);

t_bool	check_row(int **grid, int *axis, int *col_row[4], int direction);

t_bool	check_col(int **grid, int *axis, int *col_row[4], int direction);

t_bool	find_zero(int *arr);

#endif
