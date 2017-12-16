/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:32:47 by satkins           #+#    #+#             */
/*   Updated: 2017/11/16 14:32:49 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static void	get_zeros(int *zeros, int *spaces, size_t *len, t_flag arg_flag)
{
	*spaces = 0;
	*zeros = 0;
	if (arg_flag.precision_set && arg_flag.precision > (int)*len)
		*zeros = arg_flag.precision - (int)*len;
	if (arg_flag.prefix)
		*len += 2;
	if (arg_flag.width_set && arg_flag.width > (int)*len + *zeros)
		*spaces = arg_flag.width - ((int)*len + *zeros);
	*len += *spaces + *zeros;
}

static void	print_prefix(int caps)
{
	if (caps)
		ft_putstr("0X");
	else
		ft_putstr("0x");
}

static void	left_print(t_flag arg_flag, int spaces, int zeros, char *str)
{
	if (arg_flag.prefix)
		print_prefix(arg_flag.caps);
	while (zeros-- > 0)
		ft_putchar('0');
	ft_putstr(str);
	while (spaces-- > 0)
		ft_putchar(' ');
}

static void	right_print(t_flag arg_flag, int spaces, int zeros, char *str)
{
	if (arg_flag.pad_zero && !arg_flag.precision_set)
	{
		if (arg_flag.prefix)
			print_prefix(arg_flag.caps);
		while (spaces-- > 0)
			ft_putchar('0');
		ft_putstr(str);
	}
	else
	{
		while (spaces-- > 0)
			ft_putchar(' ');
		if (arg_flag.prefix)
			print_prefix(arg_flag.caps);
		while (zeros-- > 0)
			ft_putchar('0');
		ft_putstr(str);
	}
}

size_t		hex_print(unsigned long long int num, t_flag arg_flag, char caps)
{
	size_t	len;
	char	*str;
	int		zeros;
	int		spaces;

	if (num == 0 && arg_flag.precision_set)
		str = "\0";
	else
		str = ft_ullitoa_base(num, 16);
	if (num == 0)
		arg_flag.prefix = 0;
	if ((arg_flag.caps = caps))
		ft_toupper_str(str);
	len = ft_strlen(str);
	get_zeros(&zeros, &spaces, &len, arg_flag);
	if (arg_flag.left_allign)
		left_print(arg_flag, spaces, zeros, str);
	else
		right_print(arg_flag, spaces, zeros, str);
	return (len);
}
