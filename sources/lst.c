/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:49:37 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 13:34:25 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lst_add_back(t_lst **alst, t_lst *new)
{
	t_lst *tmp;

	if (!alst || !new)
	{
		return ;
	}
	if (!(*alst))
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lst_add(t_lst **alst, t_lst *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

//the memory of the content must be already allocated!
//t_lst	*lstnew(void const *content)
t_lst	*lstnew(void *content)
{
	t_lst *list;

	if (!(list = (t_lst*)ft_memalloc(sizeof(t_lst))))
		return (NULL);
	if (!content)
		list->content = NULL;
	else
        list->content = content;
	list->next = NULL;
	return (list);
}
