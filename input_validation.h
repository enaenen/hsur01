/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchae <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:16:53 by wchae             #+#    #+#             */
/*   Updated: 2021/03/06 14:17:15 by wchae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_VALIDATION_H
# define INPUT_VALIDATION_H

# include "boolean.h"

t_bool	is_valid_space(char *c);

t_bool	is_number(char c);

int		count_numbers(char *str);

t_bool	is_valid_space(char *c);

t_bool	input_validation(char *str, int nbr_count);

#endif
