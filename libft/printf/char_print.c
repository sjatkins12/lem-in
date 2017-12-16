/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:04:37 by satkins           #+#    #+#             */
/*   Updated: 2017/11/30 14:04:39 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

size_t				char_print(long long num, t_flag arg_flags)
{
	unsigned char	chr;
	size_t			len;

	chr = (unsigned char)num;
	len = 1;
	if (arg_flags.left_allign)
	{
		ft_putchar(chr);
		if (arg_flags.width_set)
			while (--arg_flags.width > 0 && (len++))
				ft_putchar(' ');
	}
	else
	{
		if (arg_flags.width_set)
			while (--arg_flags.width > 0 && (len++))
			{
				if (arg_flags.pad_zero)
					ft_putchar('0');
				else
					ft_putchar(' ');
			}
		ft_putchar(chr);
	}
	return (len);
}
