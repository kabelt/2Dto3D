/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:32:51 by kmaneera          #+#    #+#             */
/*   Updated: 2020/04/23 14:37:41 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_emptyline(char **line, int fd)
{
	if (*line[0] == 0)
	{
		free(*line);
		get_next_line(fd, line);
	}
}

void	addlinetolist(t_sto *inf, t_lst **tmp, char *line)
{
	char *ptr;

	ptr = line;
	while (*ptr)
	{
		if (ft_strchr(VALIDMAPCHAR, *ptr))
			ptr++;
		else
			errexit("Error\nInvalid map pattern!");
	}
	if ((int)ft_strlen(line) > inf->map->map_width)
		inf->map->map_width = ft_strlen(line);
	lst_add_back(tmp, lstnew(ft_strdup(line)));
	inf->map->map_height++;
	free(line);
}

void	read_content(t_sto *inf, char *line, int fd)
{
	int		gnl_rt;
	t_lst	**tmp;

	if (inf->map->get_elem != 8)
		errexit("Error\nInvalid map! :(");
	if (!(tmp = (t_lst**)ft_memalloc(sizeof(t_lst*))))
		errexit("Error\nFail to allocate memory!");
	addlinetolist(inf, tmp, line);
	while ((gnl_rt = get_next_line(fd, &line)))
	{
		if (line[0] == 0)
		{
			inf->map->get_elem++;
			return (free(line));
		}
		addlinetolist(inf, tmp, line);
	}
	convertmap(inf, tmp);
	inf->map->get_elem++;
}

void	readline(t_sto *inf, char *line, int fd)
{
	if (line[0] == 'R')
		return (read_res(inf, line));
	else if (line[0] == 'N' && line[1] == 'O')
		return (read_north(inf, line));
	else if (line[0] == 'S' && line[1] == 'O')
		return (read_south(inf, line));
	else if (line[0] == 'W' && line[1] == 'E')
		return (read_west(inf, line));
	else if (line[0] == 'E' && line[1] == 'A')
		return (read_east(inf, line));
	else if (line[0] == 'S')
		return (read_sprite(inf, line));
	else if (line[0] == 'F')
		return (read_floor(inf, line));
	else if (line [0] == 'C')
		return (read_ceiling(inf, line));
	else if (line [0] == ' ' || line[0] == '1')
		return (read_content(inf, line, fd));
	else
		errexit("Error\nInvalid map!");
}

void	readmap(t_sto *inf, int fd)
{
	char	*line;
	int		gnl_rt;

	line = NULL;
	while ((gnl_rt = get_next_line(fd, &line)))
	{
		is_emptyline(&line, fd);
		readline(inf, line, fd);
		if (inf->map->get_elem != 9)
			free(line);
	}
	if (inf->map->get_elem != 9)
		errexit("Error\nInsufficient information to process!");
}