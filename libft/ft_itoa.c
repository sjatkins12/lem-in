/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:58:39 by satkins           #+#    #+#             */
/*   Updated: 2016/07/19 23:00:46 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa(int n)
{
	int				digit;
	int				i[2];
	unsigned int	num;
	char			*str;
	char			*tmp;

	if ((str = ft_strnew(11)) == NULL)
		return (NULL);
	i[1] = n < 0 ? -1 : 1;
	num = i[1] * n;
	i[0] = 10;
	if (num == 0)
		return (ft_strcpy(str, "0"));
	while (num > 0 && i[0] > 0)
	{
		digit = num % 10;
		str[i[0]] = '0' + digit;
		i[0]--;
		num /= 10;
	}
	if (i[1] == -1)
		str[i[0]--] = '-';
	tmp = ft_strdup(str + i[0] + 1);
	free(str);
	return (tmp);
}
