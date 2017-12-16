/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:17:54 by satkins           #+#    #+#             */
/*   Updated: 2017/12/12 18:17:57 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "libft.h"

typedef struct s_room
{
	int					dist;
	char				*room_num;
	t_list				*connections;
	int					ant;
	int					move;
	struct s_room		*next;
	enum
	{
				none,
				start,
				end
	}			e_spec;
}				t_room;

typedef struct s_farm
{
	int			room_count;
	int			ants;
	t_room		*start;
	t_room		*lst;
	t_room		*end;
}				t_farm;

void	set_distances(t_room *end);
void		start_turn(t_farm *farm);

#endif
