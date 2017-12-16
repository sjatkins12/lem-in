/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:31:12 by satkins           #+#    #+#             */
/*   Updated: 2017/11/14 19:37:16 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ret_line(char **hold_over, char **line)
{
	char		*ptr;
	char		*tmp;

	ptr = ft_strchr(*hold_over, '\n');
	*ptr = '\0';
	*line = ft_strdup(*hold_over);
	tmp = *hold_over;
	*hold_over = ft_strdup(ptr + 1);
	free(tmp);
	return (1);
}

int				ret_final(char **hold_over, char **line)
{
	*line = ft_strdup(*hold_over);
	if (**hold_over)
		ft_bzero((void *)*hold_over, sizeof(*hold_over));
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	*hold_over[5000];
	int			bytes_read;
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || fd > 4999 || line == NULL || (read(fd, buff, 0)) < 0)
		return (-1);
	if (!hold_over[fd])
		hold_over[fd] = ft_strnew(0);
	bytes_read = 1;
	while (ft_strchr(hold_over[fd], '\n') == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFF_SIZE);
		buff[bytes_read] = 0;
		hold_over[fd] = ft_strnjoin(hold_over[fd], buff, 1);
	}
	if (ft_strchr(hold_over[fd], '\n'))
		return (ret_line(&(hold_over[fd]), line));
	if (hold_over[fd] && *hold_over[fd])
		return (ret_final(&(hold_over[fd]), line));
	*line = NULL;
	return (0);
}
