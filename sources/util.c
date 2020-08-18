/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 15:07:24 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 15:12:09 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_sto *inf, int x, int y, int color)
{
	int		i;

	if (x >= 0 && x < inf->s_width && y >= 0 && y < inf->s_height)
	{
		i = (x * inf->bpp / 8) + (y * inf->size_line);
		inf->data_addr[i] = color;
		inf->data_addr[++i] = color >> 8;
		inf->data_addr[++i] = color >> 16;
	}
}

void	errexit(char *str)
{
	write(1, "\e[91m", 5);
	ft_putendl(str);
	exit(1);
}

int	get_now(const char *s, char c)
{
	int		now;

	now = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			now++;
		while (*s && *s != c)
			s++;
	}
	return (now);
}