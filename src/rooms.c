/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:25:03 by satkins           #+#    #+#             */
/*   Updated: 2017/12/12 18:25:07 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	recusive_set_distances(t_room *current, int distance)
{
	t_list	*iter;

	iter = current->connections;
	while (iter)
	{
		if ((!((t_room *)iter->content)->dist ||
			((t_room *)iter->content)->dist > distance) &&
			((t_room *)iter->content)->e_spec != end)
		{
			((t_room *)iter->content)->dist = distance;
			recusive_set_distances((t_room *)iter->content, distance + 1);
		}
		iter = iter->next;
	}
}

void	set_distances(t_room *end)
{
	end->dist = 0;
	recusive_set_distances(end, 1);
}
