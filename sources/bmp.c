/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 13:39:57 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 13:48:32 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

int		bmp_writeheader(int fd, int h, int w)
{
	unsigned char	hd[54];
	int				filesize;

	ft_bzero(hd, 54);
	filesize = 54 + (w * 4 * h); //in bytes
	hd[0] = (unsigned char)('B');
	hd[1] = (unsigned char)('M');
	int_to_char(hd + 2, filesize);
	hd[10] = (unsigned char)(54);
	hd[14] = (unsigned char)(40);
	int_to_char(hd + 18, w);
	int_to_char(hd + 22, h);
	hd[26] = (unsigned char)(1);
	hd[28] = (unsigned char)(32);
	if	(write(fd, hd, 54))
		return (1);
	return (0);
}


int		bmp_writedata(int fd, t_sto *inf)
{
	int				x;
	int				y;
	int				pixel;

	y = inf->s_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < inf->s_width)
		{
			pixel = (*(int*)(inf->data_addr + (inf->size_line * (int)y) + (4 * (int)x)));
			if (write(fd, &pixel, 3) < 0)
				return (0);
			if (write(fd, "\0", 1) < 0)
				return (0);
			x++;
		}
		y--;
	}
	return (1);
}

int		take_screenshot(t_sto *inf, char *str)
{
	int fd;
	
	if (ft_strcmp("--save", str) != 0)
		errexit("ERROR\nInvalid second argument");
	if ((fd = open("screenshot.bmp",\
		O_WRONLY | O_CREAT, 0777 | O_TRUNC)) < 0 \
		|| !bmp_writeheader(fd, inf->s_height, inf->s_width)\
		|| !bmp_writedata(fd, inf))
		errexit("Error\nFail to make a screenshot! :(");
	write(1, "\e[92m", 5);
	ft_putendl("Screenshot created! :)");
	write(1, "\x1b[0m", 5);
	close(fd);
	return (1);
}