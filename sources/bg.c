/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:52:00 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 15:12:03 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(t_sto *inf, t_cord head, t_cord tail, int color)
{//copied
	t_cord	delta;
	t_cord	sign;
	t_cord	cur;
	int		error[2];

	delta.x = ABS(tail.x - head.x);
	delta.y = ABS(tail.y - head.y);
	sign.x = head.x < tail.x ? 1 : -1;
	sign.y = head.y < tail.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = head;
	while (cur.x != tail.x || cur.y != tail.y)
	{
		put_pixel(inf, cur.x, cur.y, color);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void		drawrec(t_sto *inf, t_cord from, t_cord to, int color)
{
	t_cord head;
	t_cord tail;
	int i = 0;

	while (i < to.y - from.y)
	{
		head.x = from.x;
		head.y = from.y + i;
		tail.x = to.x;
		tail.y = from.y + i;
		draw_line(inf, head, tail, color);
		i++;
	}
}

void		add_bg(t_sto *inf)
{
	t_cord from;
	t_cord to;

	from.x = 0;
	from.y = 0;
	to.x = inf->s_width;
	to.y = inf->s_height / 2;
	drawrec(inf, from, to, inf->map->ceiling_color);
	from.x = 0;
	from.y = inf->s_height / 2;
	to.x = inf->s_width;
	to.y = inf->s_height;
	drawrec(inf, from, to, inf->map->floor_color);
}