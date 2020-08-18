/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:53:30 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 14:54:25 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_ceiling(t_sto *inf, char *line)
{
	char	**elems;
	char	**colors;
	int		i;
	int		rgb[3];

	elems = ft_strsplit(line, ' ');
	if (inf->map->ceiling_isget || get_now(line, ' ') != 2 ||\
			(get_now(elems[1], ',') != 3))
		errexit("Error\nInvalid ceiling color specification!");
	colors = ft_strsplit(elems[1], ',');
	i = 0;
	while (i < 3)
		if (!ft_isnumber_base(colors[i++], 10))
			errexit("Error\nInvalid ceiling color specification!");
	if (((rgb[0] = ft_atoi(colors[0])) < 0) ||\
			((rgb[1] = ft_atoi(colors[1])) < 0) ||\
			((rgb[2] = ft_atoi(colors[2])) < 0))
			errexit("Error\nInvalid ceiling color specification!");
	inf->map->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	inf->map->ceiling_isget = 1;
	inf->map->get_elem++;
	ft_strsplit_free(colors);
	ft_strsplit_free(elems);
}

void	read_floor(t_sto *inf, char *line)
{
	char	**elems;
	char	**colors;
	int		rgb[3];
	int		i;

	elems = ft_strsplit(line, ' ');
	if (inf->map->floor_isget || get_now(line, ' ') != 2 ||\
			(get_now(elems[1], ',') != 3))
		errexit("Error\nInvalid floor color specification!");
	colors = ft_strsplit(elems[1], ',');
	i = 0;
	while (i < 3)
		if (!ft_isnumber_base(colors[i++], 10))
			errexit("Error\nInvalid floor color specification!");
	if (((rgb[0] = ft_atoi(colors[0])) < 0) ||\
			((rgb[1] = ft_atoi(colors[1])) < 0) ||\
			((rgb[2] = ft_atoi(colors[2])) < 0))
			errexit("Error\nInvalid floor color specification!");
	inf->map->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	inf->map->floor_isget = 1;
	inf->map->get_elem++;
	ft_strsplit_free(colors);
	ft_strsplit_free(elems);
}

void	read_res(t_sto *inf, char *line)
{
	char	**elems;

	if (inf->map->res_isget || get_now(line, ' ') != 3)
		errexit("Error\nInvalid resolution specification!");
	elems = ft_strsplit(line, ' ');
	if (!ft_isnumber_base(elems[1], 10) || !ft_isnumber_base(elems[2], 10))
		errexit("Error\nInvalid resolution specification!");
	if (((inf->s_width = ft_atoi(elems[1])) <= 0) ||\
		((inf->s_height = ft_atoi(elems[2])) <= 0))
		errexit("Error\nInvalid resolution specification");
	ft_strsplit_free(elems); //this may cause seg-fault!
	inf->map->res_isget = 1;
	inf->map->get_elem++;
	if (!(inf->rays = (t_ray*)ft_memalloc(sizeof(t_ray) * inf->s_width)))
		errexit("Error\nFail to allocate memory!");
}