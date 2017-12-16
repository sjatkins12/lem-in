/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 11:17:34 by satkins           #+#    #+#             */
/*   Updated: 2017/12/13 11:17:36 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	move_ant(t_room *src, t_room *dst, int *first)
{
	if (*first)
		write(1, " ", 1);
	write(1, "L", 1);
	ft_putnbr(src->ant);
	write(1, "-", 1);
	ft_putstr(dst->room_num);
	if (dst->e_spec != end)
		dst->ant = src->ant;
	else
		++(dst->ant);
	if (src->e_spec != start)
		src->ant = 0;
	else
		--(src->ant);
	*first = 1;
	dst->move = 1;
}

static void	get_ant_recursive(t_room *room, int *first, t_farm *f)
{
	t_list	*iter;

	iter = room->connections;
	while (iter && !room->ant)
	{
		if (((t_room *)iter->content)->dist >= room->dist &&
			((t_room *)iter->content)->ant && !((t_room *)iter->content)->move)
			if (((t_room *)iter->content)->dist > room->dist || (f->ants > 1
				&& f->start->connections->next && f->end->connections->next))
				move_ant((t_room *)iter->content, room, first);
		iter = iter->next;
	}
	iter = room->connections;
	while (iter)
	{
		if (((t_room *)iter->content)->dist > room->dist &&
			!((t_room *)iter->content)->ant)
			get_ant_recursive((t_room *)iter->content, first, f);
		iter = iter->next;
	}
}

void		start_turn(t_farm *farm)
{
	t_list	*iter;
	int		first;
	t_room	*room;

	first = 0;
	room = farm->lst;
	while (room)
	{
		room->move = 0;
		room = room->next;
	}	
	iter = farm->end->connections;
	while (iter)
	{
		if (((t_room *)iter->content)->ant)
			move_ant((t_room *)iter->content, farm->end, &first);
		iter = iter->next;
	}
	iter = farm->end->connections;
	while (iter)
	{
		get_ant_recursive(((t_room *)iter->content), &first, farm);
		iter = iter->next;
	}
	write(1, "\n", 1);
}
