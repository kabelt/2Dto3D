/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:45:22 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 14:50:26 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	getspec(t_sto *inf)
{//get maxdist + all specs needed for minimap
	int	a;
	int	b;

	a = inf->map->map_height - 1;
	b = inf->map->map_width - 1;
	inf->pp_dist = ((inf->s_width / 2) / tan(inf->fov_an / 2)) * 0.5; //0.5 is put in arbritarily
	inf->mnm_tilesize = 0.01 * MIN(inf->s_width, inf->s_height);
	inf->mnm_width = inf->mnm_tilesize * (inf->map->map_width);
	inf->mnm_height = inf->mnm_tilesize * (inf->map->map_height);
}

void    add_sprite(t_sto *inf, int y, int x)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)ft_memalloc(sizeof(t_sprite))))
		errexit("Error\nFail to allocate memory!");
	new->x = x + 0.5;
	new->y = y + 0.5;
	sprite_add(inf, new);
}

void	tripmap_free(t_sto *inf, int **tmp)
{
	free(tmp[0]);
	free(tmp[inf->map->map_height + 1]);
	free(tmp);
}
void	trimmap(t_sto *inf)
{
	int	**tmp;
	int	y;
	int	x;

	tmp = inf->map->patn;
	if (!(inf->map->patn = (int**)ft_memalloc(sizeof(int*) * inf->map->map_height)))
		errexit("Error\nFail to allocate memory!");
	y = 0;
	while (y < inf->map->map_height)
	{
		x = 0;
		if (!(inf->map->patn[y] = (int*)ft_memalloc(sizeof(int) * inf->map->map_width)))
			errexit("Error\nFail to allocate memory!");
		while (x < inf->map->map_width)
		{
			inf->map->patn[y][x] = tmp[y + 1][x + 1];
			if (inf->map->patn[y][x] == SPRITE)
				add_sprite(inf, y, x);
			x++;
		}
		free(tmp[y + 1]);
		y++;
	}
	tripmap_free(inf, tmp);
}

void    checkborder(t_sto *inf)
{
	int	y;
	int	x;

	y = 1;
	while (y < inf->map->map_height + 1)
	{
		x = 1;
		while (x < inf->map->map_width + 1)
		{
			if (inf->map->patn[y][x] == S_IN && (inf->map->patn[y-1][x] == S_OUT ||\
			inf->map->patn[y+1][x] == S_OUT || inf->map->patn[y][x-1] == S_OUT ||\
			inf->map->patn[y][x+1] == S_OUT || inf->map->patn[y-1][x] == BORDER ||\
			inf->map->patn[y+1][x] == BORDER || inf->map->patn[y][x-1] == BORDER ||\
			inf->map->patn[y][x+1] == BORDER || inf->map->patn[y-1][x-1] == S_OUT ||\
			inf->map->patn[y-1][x+1] == S_OUT || inf->map->patn[y+1][x-1] == S_OUT ||\
			inf->map->patn[y+1][x+1] == S_OUT || inf->map->patn[y-1][x-1] == BORDER ||\
			inf->map->patn[y-1][x+1] == BORDER || inf->map->patn[y+1][x-1] == BORDER ||\
			inf->map->patn[y+1][x+1] == BORDER))
				errexit("Error\nThe map has no border!");
			x++;
		}
		y++;
	}
}
