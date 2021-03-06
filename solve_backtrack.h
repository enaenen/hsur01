/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_backtrack.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 16:06:03 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 16:44:15 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_BACKTRACK_H
# define SOLVE_BACKTRACK_H

# include "boolean.h"
# include "solve_validation.h"

void		is_empty(int **grid, int *axis);

t_bool		has_duplicated(int **grid, int *axis, int guess);

t_bool		is_valid(int **grid, int *axis, int *col_row[4]);

t_bool		test(int **grid, int *axis, int guess, int *col_row[4]);

t_bool		backtracking(int **grid, int *col_row[4]);

#endif
