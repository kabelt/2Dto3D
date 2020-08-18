/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:05:24 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 15:42:14 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	drawbox(t_sto *inf, int ymap, int xmap)
{
	int y;
	int x;
	int i;
	t_cord head;
	t_cord tail;

	y = inf->mnm_tilesize * ymap;
	x = inf->mnm_tilesize * xmap;
	i = 0;
	while (i < inf->mnm_tilesize)
	{
		head.y = y + i;
		head.x = x;
		tail.y = y + i;
		tail.x = x + inf->mnm_tilesize;
		draw_line_minimap(inf, head, tail, 0xA9A9A9);
		i++;
	}
}

static void drawdot(t_sto *inf, int y, int x, int size, int color)
{
	y -= size;
	x -= size;
	int i = 0;
	int j;

	while (i < (size*2 + 1))
	{
		j = 0;
		while (j < (size*2 + 1))
		{
			put_pixel_minimap(inf, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void drawfov(t_sto *inf, int y, int x)
{
	t_cord head;
	t_cord tail;
	double angle;

	angle = inf->player->rot_an - (inf->fov_an / 2);
	int i = 0;
	while (i < inf->s_width)
	{
		head.y = y;
		head.x = x;
		tail.y = inf->rays[i].y * inf->mnm_tilesize;
		tail.x = inf->rays[i].x * inf->mnm_tilesize;
		if (angle == inf->player->rot_an)
			draw_line_minimap(inf, head, tail, 0x0000FF);
		else
			draw_line_minimap(inf, head, tail, 0x003366);
		i++;
	}
}

static void putplayer(t_sto *inf)
{
	int y;
	int x;
	t_cord head;
	t_cord tail;

	y = inf->mnm_tilesize * inf->player->y;
	x = inf->mnm_tilesize * inf->player->x;
	drawdot(inf, y, x, 1, 0xFF0000);
	drawfov(inf, y, x);
	head.y = y;
	head.x = x;
	tail.y = y + sin(inf->player->rot_an) * 500;
	tail.x = x + cos(inf->player->rot_an) * 500;
	draw_line_minimap(inf, head, tail, 0xFF0000);
}

void	minimap(t_sto *inf)
{
	int x;
	int y;

	y = 0;
    ft_bzero(inf->mnm_data_addr, inf->mnm_width * inf->mnm_height *\
														(inf->mnm_bpp / 8));
	while (y < inf->map->map_height)
	{
		x = 0;
		while (x < inf->map->map_width)
		{
			if (inf->map->patn[y][x] == WALL)
				drawbox(inf, y, x);
			x++;
		}
		y++;
	}
	putplayer(inf);
	mlx_put_image_to_window(inf->mlx, inf->win, inf->mnm_img,\
					(int)(0.02 * inf->s_width), (int)(0.02 * inf->s_height));
}