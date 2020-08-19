/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmaneera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 17:50:33 by kmaneera          #+#    #+#             */
/*   Updated: 2020/08/18 21:16:27 by kmaneera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sto	*ini_inf(void)
{
	t_sto *inf;

	if (!(inf = (t_sto*)ft_memalloc(sizeof(t_sto))))
		errexit("Error\nFail to allocate memory");
	if (!(inf->map = (t_map*)ft_memalloc(sizeof(t_map))))
		errexit("Error\nFail to allocate memory");
	if (!(inf->player = (t_py*)ft_memalloc(sizeof(t_py))))
		errexit("Error\nFail to allocate memory");
	if (!(inf->sprites = (t_sprite**)ft_memalloc(sizeof(t_sprite*))))
		errexit("Error\nFail to allocate memory");
	inf->fov_an = FOV_ANG * (0.0174533); //convert degree into radian
	return (inf);
}


void	ini_mlx(t_sto *inf)
{
	if(!(inf->mlx = mlx_init()))
		errexit("Error\nMLX initization error!");
	if (inf->s_width > S_WIDTH)
		inf->s_width = S_WIDTH;
	if (inf->s_height > S_HEIGHT)
		inf->s_height = S_HEIGHT;
	if (!(inf->win = mlx_new_window(inf->mlx, inf->s_width, inf->s_height, "2Dto3D")))
		errexit("Error\nMLX initization error!");
	if (!(inf->img = mlx_new_image(inf->mlx, inf->s_width, inf->s_height)))
		errexit("Error\nMLX initization error!");
	inf->data_addr = mlx_get_data_addr(inf->img, &(inf->bpp), &(inf->size_line), &(inf->endian));
	if (!(inf->mnm_img = mlx_new_image(inf->mlx, inf->mnm_width, inf->mnm_height)))
		errexit("Error\nMLX initization error!");
	inf->mnm_data_addr = mlx_get_data_addr(inf->mnm_img, &(inf->mnm_bpp), &(inf->mnm_size_line), &(inf->endian));
}

void	artwork(t_sto *inf)
{
	add_bg(inf);
	raycastall(inf);
	putwall(inf);
	putsprites(inf);
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
	if (!inf->enable_minimap)
		minimap(inf);
}

int		main(int ac, char **av)
{
	t_sto	*inf;
	int		fd;

	if (ac == 2 || ac == 3)
	{
		inf = ini_inf();
		if (!((fd = open(av[1], O_RDONLY)) >= 0))
			errexit("Error\nCannot open the map!");
		readmap(inf, fd);
		ini_mlx(inf);
		loadtex(inf);
		artwork(inf);
		if (ac == 3)
			take_screenshot(inf, av[2]);
		mlx_hook(inf->win, X_EVENT_KEY_PRESS, 0, &key_press, inf);
		mlx_hook(inf->win, X_EVENT_KEY_RELEASE, 0, &key_release, inf);
		mlx_hook(inf->win, X_EVENT_EXIT, 0, &exit_hook, inf);
		mlx_loop_hook(inf->mlx, &engine, inf);
		mlx_loop(inf->mlx);
	}
	errexit("Error\nUsage: ./cub3d <map> (--save)");
	return (1);
}