/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:34:27 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 16:33:40 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_lst	**sortsprite(t_sto *inf)
{
	t_lst		**list;
	t_sprite	*tmp;
	int			first;

	list = (t_lst**)ft_memalloc(sizeof(t_lst*));
	first = 1;
	tmp = *(inf->sprites);
	while (tmp)
	{
		if (!(*list) || tmp->dist > ((t_sprite*)((*(list))->content))->dist)
			lst_add(list, lstnew(tmp));
		else
			lst_add_rightplace(list, lstnew(tmp));
		tmp = tmp->next;
	}
	return (list);
}

void    getdirection(t_sto *inf, t_lst **list, double *fov_min, double *fov_max)
{
	t_lst		*tmp;
	t_sprite	*i;

	*fov_min = inf->player->rot_an - (inf->fov_an / 2);
	*fov_min += *fov_min < 0 ? 2 * M_PI : 0;
	*fov_max = inf->player->rot_an + (inf->fov_an / 2);
	*fov_max -= *fov_max > 2 * M_PI ? 2 * M_PI : 0;
	tmp = *list;
	while (tmp)
	{
		i = ((t_sprite*)tmp->content);
		i->direct = atan2((i->y - inf->player->y), (i->x - inf->player->x));
		i->direct += i->direct < 0 ? 2 * M_PI : 0;
		tmp = tmp->next;
	}
}
