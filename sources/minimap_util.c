/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:40:48 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 15:43:14 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_minimap(t_sto *inf, int x, int y, int color)
{//copied
	int		i;

	if (x >= 0 && x < inf->mnm_width && y >= 0 && y < inf->mnm_height)
	{
		i = (x * inf->mnm_bpp / 8) + (y * inf->mnm_size_line);
		inf->mnm_data_addr[i] = color;
		inf->mnm_data_addr[++i] = color >> 8;
		inf->mnm_data_addr[++i] = color >> 16;
	}
}

void	draw_line_minimap(t_sto *inf, t_cord head, t_cord tail, int color)
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
		put_pixel_minimap(inf, cur.x, cur.y, color);
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
