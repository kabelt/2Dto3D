/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:44:33 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 16:33:19 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawsprite_stripe(t_sto *inf, int x_start, int stripe_no, int height)
{
	int		y_start;
	int		y;
	int		color;
	double	xtex;
	double	ytex;

	y_start = ((double)-height / 2.) + ((double)inf->s_height / 2) +\
							((((double)inf->tex[4].height / (double)height)));
	y = y_start;
	xtex = (double)stripe_no / (double)height * (double)64;
	while (y < y_start + height)
	{
		ytex = ((double)(y - y_start) / (double)height) * inf->tex[4].width;
		if (!inf->enable_light)
			color = getpix(xtex, ytex, inf->tex[4],\
							(double)height / (double)inf->s_height);
		else
			color = getpix(xtex, ytex, inf->tex[4], 1);
		if (color != 0)
			put_pixel(inf, x_start + stripe_no , y, color);
		y++;
	}
}

void	draw_eachsprite(t_sto *inf, int x_screen, int size)
{
	int	width;
	int	x_start;
	int	stripe_no;

	width = size;
	x_start = x_screen - (size / 2);
	stripe_no = 0;
	while (stripe_no < width)
	{
		drawsprite_stripe(inf, x_start, stripe_no, size);
		stripe_no++;
	}
}

void	draw_sprites2(t_sto *inf, t_sprite *i, double fov_min)
{
	if ((i->direct >= 0 && i->direct < M_PI) && \
	(i->dist < inf->rays[(int)((2 * M_PI - fov_min + i->direct) / 1.0472 * \
													inf->s_width) - 1].dist))
			draw_eachsprite(inf, (2 * M_PI - fov_min + i->direct) / 1.0472 * \
										inf->s_width, inf->pp_dist / i->dist);
	else if (i->dist < inf->rays[(int)((i->direct - fov_min) / 1.0472 * \
													inf->s_width) - 1].dist)
		draw_eachsprite(inf, (i->direct - fov_min) / 1.0472 * inf->s_width, \
													inf->pp_dist / i->dist);
}

void	draw_sprites(t_sto *inf, t_lst **list, double fov_min, double fov_max)
{
	t_lst		*tmp;
	t_sprite	*i;

	tmp = *list;
	while (tmp)
	{
		i = ((t_sprite*)tmp->content);
		if ((inf->player->rot_an >= 5.75959 || inf->player->rot_an <= 0.523599)\
		&& (i->direct > fov_min || i->direct < fov_max))
			draw_sprites2(inf, i, fov_min);
		else if ((i->direct > fov_min && i->direct < fov_max) && \
		(i->dist < inf->rays[(int)((i->direct - fov_min) \
						/ 1.0472 * inf->s_width) - 1].dist))
			draw_eachsprite(inf, (i->direct - fov_min) \
						/ 1.0472 * inf->s_width, inf->pp_dist / i->dist);
		tmp = tmp->next;
	}
}

void	putsprites(t_sto *inf)
{
	t_sprite	*tmp;
	t_lst		**list;
	double		fov_min;
	double		fov_max;

	tmp = *inf->sprites;
	while (tmp)
	{
		tmp->dist = sqrt(pow((inf->player->x - tmp->x), 2) + \
							pow((inf->player->y - tmp->y), 2));
		tmp = tmp->next;
	}
	list = sortsprite(inf);
	getdirection(inf, list, &fov_min, &fov_max);
	draw_sprites(inf, list, fov_min, fov_max);
	free_putsprites(list);
}