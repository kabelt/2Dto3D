/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 16:30:54 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 16:31:23 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	sprite_add_back(t_sto *inf, t_sprite *new)
{
	t_sprite	*tmp;

	if (!inf->sprites || !new)
		return ;
	if (!(*(inf->sprites)))
		*(inf->sprites) = new;
	else
	{
		tmp = *(inf->sprites);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	sprite_add(t_sto *inf, t_sprite *new)
{
	if (!inf->sprites || !new)
		return ;
	new->next = *(inf->sprites);
	*(inf->sprites) = new;
}

void	lst_add_rightplace(t_lst **alst, t_lst *new)
{
	t_lst	*tmp_h;
	t_lst	*tmp_t;

	tmp_h = *alst;
	while (tmp_h)
	{
		tmp_t = tmp_h;
		tmp_h = tmp_h->next;
		if (tmp_h && (((t_sprite*)tmp_h->content)->dist < \
									((t_sprite*)new->content)->dist))
		{
			new->next = tmp_h;
			tmp_t->next = new;
			return ;
		}
	}
	tmp_t->next = new;
}


void	free_putsprites(t_lst **list)
{
	t_lst	*tmp;
	t_lst	*tmp2;

	tmp = *list;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	free(list);
}