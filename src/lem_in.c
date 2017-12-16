/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:28:53 by satkins           #+#    #+#             */
/*   Updated: 2017/12/13 15:28:56 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_to_list(t_farm *farm, t_room *room)
{
	t_room	*iter;

	if (!farm->lst)
		farm->lst = room;
	else
	{
		iter = farm->lst;
		while (iter->next)
			iter = iter->next;
		iter->next = room;
	}
	if (room->e_spec == start)
		farm->start = room;
	if (room->e_spec == end)
		farm->end = room;
}

t_room		*reader(char **line, int ants)
{
	int		o_flag;
	char	*i;
	t_room	*room;

	o_flag = 0;
	if (!ft_strncmp(*line, "##start", 7) || !ft_strncmp(*line, "##end", 7))
	{
		if ((*line)[2] == 's')
			o_flag = 1;
		else
			o_flag = 2;
		ft_putendl(*line);
		free(*line);
		if (get_next_line(0, line) <= 0)
			handle_error(*line);
	}
	if ((i = ft_strchr(*line, ' ')) && ft_strchr(i + 1, ' '))
	{
		while (*(++i) != ' ')
			if (!ft_isdigit(*i))
				handle_error(*line);
		while (*(++i) != '\0')
			if (!ft_isdigit(*i))
				handle_error(*line);
		if (!(room = ft_memalloc(sizeof(t_room))))
			handle_error(*line);
		if (o_flag == 1 && (room->e_spec = start))
			room->ant = ants;
		else if (o_flag)
			room->e_spec = end;
		room->room_num = ft_strnew(ft_strchr(*line, ' ') - *line);
		ft_strncpy(room->room_num, *line, ft_strchr(*line, ' ') - *line);
		return (room);
	}
	return (NULL);
}

void		read_connections(t_farm *farm, char *line)
{
	t_room	*room[2];
	size_t	len;
	int		ret;
	int		flag;

	ret = 1;
	if (!line)
		handle_error(NULL);
	while (ret > 0)
	{
		flag = 0;
		if (*line != '#')
		{
			if (!ft_strchr(line, '-'))
				handle_error(line);
			len = ft_strchr(line, '-') - line;
			room[0] = farm->lst;
			while (room[0])
			{
				if (!ft_strncmp(room[0]->room_num, line, len))
					break ;
				room[0] = room[0]->next;
			}
			if (!room[0])
				handle_error(line);
			room[1] = farm->lst;
			while (room[1])
			{
				if (!ft_strncmp(room[1]->room_num, line + len + 1, ft_strlen(room[1]->room_num)))
				{
					flag = 1;
					if (room[1]->connections)
						ft_lstadd(&(room[1]->connections), ft_lstnew(room[0], sizeof(t_room)));
					else
						room[1]->connections = ft_lstnew(room[0], sizeof(t_room));
					if (room[0]->connections)
						ft_lstadd(&(room[0]->connections), ft_lstnew(room[1], sizeof(t_room)));
					else
						room[0]->connections = ft_lstnew(room[1], sizeof(t_room));
					room[1] = NULL;
				}
				else
					room[1] = room[1]->next;
			}
			if (!flag)
				handle_error(line);
		}
		ft_putendl(line);
		free(line);
		ret = get_next_line(0, &line);
	}
}

void		read_rooms(t_farm *farm)
{
	char	*line;
	int		ants;
	t_room	*room;

	ants = 0;
	while (!ants && get_next_line(0, &line) > 0)
	{
		if (is_numstr(line))
			ants = ft_atoi(line);
		else if (line[0] != '#')
			handle_error(line);
		ft_putendl(line);
		free(line);
	}
	while (get_next_line(0, &line) > 0 && (*line == '#' || !ft_strchr(line, '-')))
	{
		if (!(*line == '#' && line[1] != '#'))
		{
			if ((room = reader(&line, ants)))
				add_to_list(farm, room);
			else if (!(*line == '#' && line[1] == '#'))
				handle_error(line);
		}
		ft_putendl(line);
		free(line);
	}
	read_connections(farm, line);
}

t_room		*del_room(t_room *room)
{
	t_list	*iter;
	t_room	*hold;

	iter = room->connections;
	while (iter)
	{
		iter = room->connections->next;
		free(room->connections);
		room->connections = iter;
	}
	free(room->room_num);
	hold = room->next;
	free(room);
	return (hold);
}

int			main(void)
{
	t_farm	*farm;
	t_room	*iter;

	farm = (t_farm *)ft_memalloc(sizeof(t_farm));
	if (!farm)
		handle_error(NULL);
	read_rooms(farm);
	if (!(farm->end && farm->start && farm->start->e_spec && farm->start->ant))
		handle_error(NULL);
	farm->ants = farm->start->ant;
	set_distances(farm->end);
	if (farm->start->dist == 0)
		handle_error(NULL);
	ft_putendl("");
	while (farm->end->ant < farm->ants)
		start_turn(farm);
	iter = farm->lst;
	while (iter)
		iter = del_room(iter);
	free(farm);
}
