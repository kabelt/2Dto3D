/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:38:27 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 13:39:20 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int     canmove(t_sto *inf, double y, double x)
{
    if (inf->map->patn[(int)floor(y)][(int)floor(x)] == WALL ||\
        inf->map->patn[(int)floor(y)][(int)floor(x)] == SPRITE)
        return (0);
    return (1);
}

void    move_w(t_sto *inf)
{
    double new_x;
    double new_y;
    double check_x;
    double check_y;
    double move_speed;

    move_speed = 0.05;
    new_x = inf->player->x + cos(inf->player->rot_an) * move_speed;
    new_y = inf->player->y + sin(inf->player->rot_an) * move_speed;
    check_x = inf->player->x + cos(inf->player->rot_an) * (move_speed + 0.5);
    check_y = inf->player->y + sin(inf->player->rot_an) * (move_speed + 0.5);
    if ((canmove(inf, check_y, check_x)))
    {
        inf->player->x = new_x;
        inf->player->y = new_y;
        artwork(inf);
    }
}

void    move_s(t_sto *inf)
{
    double new_y;
    double new_x;
    double check_x;
    double check_y;
    double move_speed;

    move_speed = 0.05;
    new_y = inf->player->y - sin(inf->player->rot_an) * move_speed;
    new_x = inf->player->x - cos(inf->player->rot_an) * move_speed;
    check_y = inf->player->y - sin(inf->player->rot_an) * (move_speed + 0.5);
    check_x = inf->player->x - cos(inf->player->rot_an) * (move_speed + 0.5);
    if ((canmove(inf, check_y, check_x)))
    {
        inf->player->x = new_x;
        inf->player->y = new_y;
        artwork(inf);
    }
}

void    move_a(t_sto *inf)
{
    double new_y;
    double new_x;
    double check_x;
    double check_y;
    double move_speed;

    move_speed = 0.05;
    new_y = inf->player->y + sin(inf->player->rot_an - M_PI_2) * move_speed;
    new_x = inf->player->x + cos(inf->player->rot_an - M_PI_2) * move_speed;
    check_y = inf->player->y + sin(inf->player->rot_an - M_PI_2) * (move_speed + 0.5);
    check_x = inf->player->x + cos(inf->player->rot_an - M_PI_2) * (move_speed + 0.5);
    if ((canmove(inf, check_y, check_x)))
    {
        inf->player->x = new_x;
        inf->player->y = new_y;
        artwork(inf);
    }
}

void    move_d(t_sto *inf)
{
    double new_y;
    double new_x;
    double check_x;
    double check_y;
    double move_speed;

    move_speed = 0.05;
    new_y = inf->player->y + sin(inf->player->rot_an + M_PI_2) * move_speed;
    new_x = inf->player->x + cos(inf->player->rot_an + M_PI_2) * move_speed;
    check_y = inf->player->y + sin(inf->player->rot_an + M_PI_2) * (move_speed + 0.5);
    check_x = inf->player->x + cos(inf->player->rot_an + M_PI_2) * (move_speed + 0.5);
    if ((canmove(inf, check_y, check_x)))
    {
        inf->player->x = new_x;
        inf->player->y = new_y;
        artwork(inf);
    }
}
