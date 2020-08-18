/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:51:32 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 14:52:58 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_north(t_sto *inf, char *line)
{
	char	**elems;

	elems = ft_strsplit(line, ' ');
	if (inf->map->north_isget || get_now(line, ' ') != 2)
		errexit("Error\nThere is a problem with north texture specification!");
	inf->tex[0].path = ft_strdup(elems[1]);
	ft_strsplit_free(elems);
	inf->map->north_isget = 1;
	inf->map->get_elem++;
}

void	read_south(t_sto *inf, char *line)
{
	char	**elems;

	elems = ft_strsplit(line, ' ');
	if (inf->map->south_isget || get_now(line, ' ') != 2)
		errexit("Error\nThere is a problem with south texture specification!");
	inf->tex[1].path = ft_strdup(elems[1]);
	ft_strsplit_free(elems);
	inf->map->south_isget = 1;
	inf->map->get_elem++;
}

void	read_west(t_sto *inf, char *line)
{
	char	**elems;

	elems = ft_strsplit(line, ' ');
	if (inf->map->west_isget || get_now(line, ' ') != 2)
		errexit("Error\nThere is a problem with west texture specification!");
	inf->tex[2].path = ft_strdup(elems[1]);
	ft_strsplit_free(elems);
	inf->map->west_isget = 1;
	inf->map->get_elem++;
}

void	read_east(t_sto *inf, char *line)
{
	char	**elems;

	elems = ft_strsplit(line, ' ');
	if (inf->map->east_isget || get_now(line, ' ') != 2)
		errexit("Error\nThere is a problem with east texture specification!");
	inf->tex[3].path = ft_strdup(elems[1]);
	ft_strsplit_free(elems);
	inf->map->east_isget = 1;
	inf->map->get_elem++;
}

void	read_sprite(t_sto *inf, char *line)
{
	char	**elems;

	elems = ft_strsplit(line, ' ');
	if (inf->map->sprite_isget || get_now(line, ' ') != 2)
		errexit("Error\nThere is a problem with sprite texture specification!");
	inf->tex[4].path = ft_strdup(elems[1]); //just added
	ft_strsplit_free(elems);
	inf->map->sprite_isget = 1;
	inf->map->get_elem++;
}