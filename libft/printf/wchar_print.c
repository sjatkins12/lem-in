/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:54:51 by satkins           #+#    #+#             */
/*   Updated: 2017/11/30 13:54:53 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static void			uchar_print_helper(size_t len, t_flag arg_flags)
{
	if (!arg_flags.left_allign && arg_flags.pad_zero)
	{
		if (arg_flags.width_set && arg_flags.width > (int)len)
			while (arg_flags.width-- > (int)len)
				ft_putchar('0');
	}
	else if (arg_flags.width_set && arg_flags.width > (int)len)
		while (arg_flags.width-- > (int)len)
			ft_putchar(' ');
}

static size_t		two_byte(t_flag arg_flags, unsigned int chr)
{
	size_t			len;

	len = 2;
	if (arg_flags.left_allign)
	{
		ft_putchar((chr >> 6) + 0xC0);
		ft_putchar((chr & 0x3F) + 0x80);
		uchar_print_helper(len, arg_flags);
	}
	else
	{
		uchar_print_helper(len, arg_flags);
		ft_putchar((chr >> 6) + 0xC0);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	return (len);
}

static size_t		three_byte(t_flag arg_flags, unsigned int chr)
{
	size_t			len;

	len = 3;
	if (arg_flags.left_allign)
	{
		ft_putchar((chr >> 12) + 0xE0);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
		uchar_print_helper(len, arg_flags);
	}
	else
	{
		uchar_print_helper(len, arg_flags);
		ft_putchar((chr >> 12) + 0xE0);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	return (len);
}

static size_t		four_byte(t_flag arg_flags, unsigned int chr)
{
	size_t			len;

	len = 4;
	if (arg_flags.left_allign)
	{
		ft_putchar((chr >> 18) + 0xF0);
		ft_putchar(((chr >> 12) & 0x3F) + 0x80);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
		uchar_print_helper(len, arg_flags);
	}
	else
	{
		uchar_print_helper(len, arg_flags);
		ft_putchar((chr >> 18) + 0xF0);
		ft_putchar(((chr >> 12) & 0x3F) + 0x80);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	return (len);
}

size_t				uchar_print(long long num, t_flag arg_flags)
{
	unsigned int	chr;
	size_t			len;

	chr = (wchar_t)num;
	if (chr <= 0x7F)
		return (char_print(chr, arg_flags));
	if (chr <= 0x7FF)
		len = two_byte(arg_flags, chr);
	else if (chr <= 0xFFFF)
		len = three_byte(arg_flags, chr);
	else if (chr <= 0x10FFFF)
		len = four_byte(arg_flags, chr);
	else
		len = 0;
	return (len);
}
