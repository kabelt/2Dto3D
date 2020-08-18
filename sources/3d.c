/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:00:32 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 16:35:13 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			getpix(double xtex, double ytex, t_tex tex, double perc)
{
	int	color;
	int	red;
	int	green;
	int	blue;

	color = (*(int*)(tex.data_addr + (4 * tex.width * (int)ytex) +\
										(4 * (int)xtex)));
	perc *= 2;
	perc = perc > 1 ? 1 : perc;
	red = (color >> 16) * perc;
	green = ((color >> 8) & 0xFF) * perc;
	blue = (color & 0xFF) * perc;
	return ((red) << 16 | (green) << 8 | (blue));
}

void		putstripe(t_sto *inf, int stripe_no, int stripe_height)
{
	double	xtex;
	double	ytex;
	int		y;
	int		y_start;
	int		color;

	y_start = (inf->s_height / 2) - (stripe_height / 2);
	y = y_start;
	if (inf->rays[stripe_no].side == 0 || inf->rays[stripe_no].side == 1)
		xtex = (inf->rays[stripe_no].x - floor(inf->rays[stripe_no].x)) * 64.;
	else
		xtex = (inf->rays[stripe_no].y - floor(inf->rays[stripe_no].y)) * 64.;
	while (y < y_start + stripe_height)
	{
		ytex = ((double)(y - y_start) / (double)stripe_height) * (double)64;
		if (!inf->enable_light)
			color = getpix(xtex, ytex, inf->tex[inf->rays[stripe_no].side],\
								(double)stripe_height / (double)inf->s_height);
		else
			color = getpix(xtex, ytex, inf->tex[inf->rays[stripe_no].side], 1);
		put_pixel(inf, stripe_no , y, color);
		y++;
	}
}

void		putwall(t_sto *inf)
{
	int	stripe_no;
	int	stripe_height;

	stripe_no = 0;
	while (stripe_no < inf->s_width)
	{
		stripe_height = inf->pp_dist / inf->rays[stripe_no].dist;
		putstripe(inf, stripe_no, stripe_height);
		stripe_no++;
	}
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
}
