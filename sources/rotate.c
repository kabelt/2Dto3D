/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:36:33 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 13:36:45 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    rotate_left(t_sto *inf)
{
    double rot_speed;

    rot_speed = 0.03;
    inf->player->rot_an = fmod(inf->player->rot_an - M_PI_2 * rot_speed, 2 * M_PI);
    if (inf->player->rot_an < 0)
        inf->player->rot_an += 2 * M_PI;
    artwork(inf);
}

void    rotate_right(t_sto *inf)
{
    double rot_speed;

    rot_speed = 0.03;
    inf->player->rot_an = fmod(inf->player->rot_an + M_PI_2 * rot_speed, 2 * M_PI);
    artwork(inf);
}