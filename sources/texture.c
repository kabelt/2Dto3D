#include "cub3d.h"

int  loadtex(t_sto *inf)
{
    int i = 0;
    int fd = 0;
    while (i < 5)
    {
        if ((fd = open(inf->tex[i].path, O_RDONLY) == -1))
            errexit("Error\nInvalid texture file");
        if ((inf->tex[i].img = mlx_xpm_file_to_image(inf->mlx,\
            inf->tex[i].path, &inf->tex[i].width, &inf->tex[i].height)))
            inf->tex[i].data_addr = mlx_get_data_addr(inf->tex[i].img,\
            &inf->tex[i].bpp, &inf->tex[i].size_line, &inf->tex[i].endian);
        else
            return (0);
        close(fd);
        i++;
    }
    return (1);
}