/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:19:19 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 15:37:26 by jikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESS_H
# define INPUT_PROCESS_H

# include "boolean.h"

int		*create_col_row(char *str, int offset);

int		**create_grid(void);

t_bool	validate_col_row(int *col_row[4]);

#endif
