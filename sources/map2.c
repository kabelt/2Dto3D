/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:39:48 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 14:44:20 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	addframe(t_sto *inf)
{
	int row;
	int i;

	row = 0;
	while (row < inf->map->map_height + 2)
	{
		inf->map->patn[row] = (int*)ft_memalloc(sizeof(int) * (inf->map->map_width + 2));
		i = 0;
		while (i < inf->map->map_width + 2)
		{
			if (i == 0 || i == inf->map->map_width + 1)
				inf->map->patn[row][i] = BORDER;
			else
			{
				if (row == 0 || row == inf->map->map_height + 1)
					inf->map->patn[row][i] = BORDER;
				else
					inf->map->patn[row][i] = S_OUT;
			}
			i++;
		}
		row++;
	}
}

void	convtroll_di(t_sto *inf, char *line, int row, int i)
{
	inf->player->y = row - .5;
	inf->player->x = i - .5;
	inf->map->patn[row][i] = SPWN;
	if (*line == 'N')
		inf->player->rot_an = 1.5 * M_PI;
	else if (*line == 'S')
		inf->player->rot_an = M_PI_2;
	else if (*line == 'E')
		inf->player->rot_an = 0;
	else if (*line == 'W')
		inf->player->rot_an = M_PI;
}

void	convtroll(t_sto *inf, char *line, int row)
{
	int	i;
	int	endline;

	i = 1;
	endline = 0;
	while (i < inf->map->map_width + 1)
	{
		if (*line == ' ' || endline)
			inf->map->patn[row][i] = S_OUT;
		else if (*line == '0')
			inf->map->patn[row][i] = S_IN;
		else if (*line == '1')
			inf->map->patn[row][i] = WALL;
		else if (*line == '2')
			inf->map->patn[row][i] = SPRITE;
		else if (*line == 'N' || *line == 'S'||\
				*line == 'E' || *line == 'W')
			convtroll_di(inf, line, row, i);
		if (*(line + 1))
			line++;
		else
			endline = 1;
		i++;
	}
}

void	convertmap(t_sto *inf, t_lst **tmp)
{//convert content stored in LL into 2D int array
	t_lst	*tmplst;
	t_lst	*tmplst2;
	int		row;

	tmplst = *tmp;
	row = 1;
	if (!(inf->map->patn = (int**)ft_memalloc(sizeof(int*) * (inf->map->map_height + 2))))
		errexit("Error\nFail to allocate memory!");
	addframe(inf);
	while (row < inf->map->map_height + 1)
	{
		convtroll(inf, tmplst->content, row);
		tmplst2 = tmplst;
		tmplst = tmplst->next;
		free(tmplst2->content);
		free(tmplst2);
		row++;
	}
	free(tmp);
	checkborder(inf);
	trimmap(inf);
	getspec(inf);
}
