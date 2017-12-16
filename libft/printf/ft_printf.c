/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 11:12:16 by satkins           #+#    #+#             */
/*   Updated: 2017/10/27 11:12:19 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_arg_handler.h"

static size_t		print_perc(t_flag arg_flags)
{
	size_t			len;

	len = 0;
	if (arg_flags.width_set)
	{
		if (arg_flags.left_allign)
		{
			ft_putchar('%');
			while (--arg_flags.width > 0 && (++len))
				ft_putchar(' ');
		}
		else
		{
			if (arg_flags.pad_zero)
				while (--arg_flags.width > 0 && (++len))
					ft_putchar('0');
			else
				while (--arg_flags.width > 0 && (++len))
					ft_putchar(' ');
			ft_putchar('%');
		}
	}
	else
		ft_putchar('%');
	return (len + 1);
}

static size_t		print_wid(t_flag arg_flags, size_t len)
{
	if (len < (size_t)arg_flags.width)
	{
		while (arg_flags.width-- > 0)
		{
			if (!arg_flags.left_allign && arg_flags.pad_zero)
				ft_putchar('0');
			else
				ft_putchar(' ');
		}
		len = (size_t)arg_flags.width;
	}
	return (len);
}

static size_t		handle_arg(char **format, char *arg, va_list *ap)
{
	t_flag			arg_flags;
	size_t			len;

	ft_bzero(&arg_flags, sizeof(t_flag));
	len = 0;
	if ((*arg != '\0' || !(*format = arg)) && flag_check(&arg_flags, &arg))
	{
		if ((*arg == 'i' || *arg == 'd' || *arg == 'c'
			|| *arg == 'D' || *arg == 'C') && (*format = arg + 1))
			return (print_wid(arg_flags, signed_print(ap, arg_flags, *arg)));
		else if ((*arg == 'u' || *arg == 'o' || *arg == 'x' || *arg == 'X' ||
			*arg == 'O' || *arg == 'U') && (*format = arg + 1))
			return (print_wid(arg_flags, unsigned_print(ap, arg_flags, *arg)));
		else if (*arg == 's' && arg_flags.e_length != l && (*format = arg + 1))
			return (print_wid(arg_flags, str_print(ap, arg_flags)));
		else if ((*arg == 'S' || *arg == 's') && (*format = arg + 1))
			return (print_wid(arg_flags, wstr_print(ap, arg_flags)));
		else if (*arg == 'p' && (*format = arg + 1))
			return (print_wid(arg_flags, ptr_print(ap, arg_flags)));
		else if (*arg == '%' && (*format = arg + 1))
			return (print_wid(arg_flags, print_perc(arg_flags)));
		*format = *arg ? arg + 1 : arg;
		len = *arg ? char_print(*arg, arg_flags) : len;
	}
	return (print_wid(arg_flags, len));
}

static size_t		formatter(va_list *ap, char *format)
{
	char			*next_arg;
	size_t			len;

	len = 0;
	next_arg = ft_strchr(format, '%');
	while (*next_arg != '\0')
	{
		len += next_arg - format;
		ft_putnstr(format, next_arg - format);
		len += handle_arg(&format, ++next_arg, ap);
		next_arg = ft_strchr(format, '%');
	}
	ft_putstr(format);
	len += ft_strlen(format);
	return (len);
}

size_t				ft_printf(char *format, ...)
{
	size_t			len;
	va_list			ap;

	len = 0;
	if (format)
	{
		va_start(ap, format);
		len = formatter(&ap, format);
		va_end(ap);
	}
	return ((int)len);
}
