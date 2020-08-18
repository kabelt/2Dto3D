/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:49:48 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 13:49:48 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freeall(t_sto *inf)
{
	int i = 0;
	while (i < inf->map->map_height)
		free(inf->map->patn[i++]);
	free(inf->map->patn);
	free(inf->map);
	i = 0;
	while (i < 5)
		free(inf->tex[i++].path);
	free(inf->rays);
}

int     exit_hook(t_sto *inf)
{
	freeall(inf);
	system("leaks -q cub3d");
    exit(0);
}

int     key_press(int key, t_sto *inf)
{
	if (key == MAIN_PAD_W)
		inf->move_up = 1;
	else if (key == MAIN_PAD_S)
		inf->move_down = 1;
	if (key == MAIN_PAD_A)
		inf->move_left = 1;
	else if (key == MAIN_PAD_D)
		inf->move_right = 1;
	if (key == ARROW_LEFT)
		inf->rot_left = 1;
	else if (key == ARROW_RIGHT)
		inf->rot_right = 1;
	return (0);
}

int     key_release(int key, t_sto *inf)
{
	if (key == MAIN_PAD_W)
		inf->move_up = 0;
	else if (key == MAIN_PAD_S)
		inf->move_down = 0;
	else if (key == MAIN_PAD_A)
		inf->move_left = 0;
	else if (key == MAIN_PAD_D)
		inf->move_right = 0;
	else if (key == ARROW_LEFT)
		inf->rot_left = 0;
	else if (key == ARROW_RIGHT)
		inf->rot_right = 0;
	else if (key == MAIN_PAD_ESC)
		exit_hook(inf);
	else if (key == MAIN_PAD_L)
	{
		inf->enable_light = !(inf->enable_light);
		artwork(inf);
	}
	else if (key == MAIN_PAD_M)
	{
		inf->enable_minimap = !(inf->enable_minimap);
		artwork(inf);
	}
	return (0);
}

int     engine(t_sto *inf)
{
    if (inf->move_up)
        move_w(inf);
    if (inf->move_down)
        move_s(inf);
    if  (inf->move_left)
        move_a(inf);
    if  (inf->move_right)
        move_d(inf);
    if (inf->rot_left)
        rotate_left(inf);
    if (inf->rot_right)
        rotate_right(inf);
	return (0);
}
