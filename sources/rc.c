#include "cub3d.h"

void    get_di(t_sto *inf, double ray_an)
{
    if ((ray_an > M_PI) && (ray_an < 2 * M_PI))
        inf->di_up = 1;
    else
        inf->di_up = 0;
    if ((ray_an < 0.5 * M_PI) || (ray_an > 1.5 * M_PI))
        inf->di_right = 1;
    else
        inf->di_right = 0;
}

t_ray check_verti(t_sto *inf, double ray_an)
{
    double x;
    double y;
    double ystep = tan(ray_an);
    double xstep = 1;
    t_ray   res;

    //find first intersection
    get_di(inf, ray_an);
    if (inf->di_right)
        x = ceil(inf->player->x);
    else
        x = floor(inf->player->x);
    y = inf->player->y + ((x - inf->player->x) * tan(ray_an));
    int i = 0;
    xstep *= inf->di_right ? 1 : -1;
    if (inf->di_up && ystep > 0)
        ystep *= -1;
    if (!inf->di_up && ystep < 0)
        ystep *= -1;
    while (x >= 0 && x < inf->map->map_width && y >= 0 && y < inf->map->map_height)
    {
        if (!inf->di_right) //leftward check the next left cord
        {
            if (inf->map->patn[(int)floor(y)][(int)floor(x) - 1] == WALL)
            {
                res.side = 2; //left
                break;
            }
        }
        else
        {
            if (inf->map->patn[(int)floor(y)][(int)floor(x)] == WALL)
            {
                res.side = 3; //right
                break;
            }
        }
        i++;
        x += xstep;
        y += ystep; 
    }
    res.x = x;
    res.y = y;
    res.dist = sqrt(pow(x - inf->player->x, 2) + pow(y - inf->player->y, 2));
    return (res);
}

t_ray  check_hori(t_sto *inf, double ray_an)
{
    double x;
    double y;
    double ystep = 1;
    double xstep = 1 / tan(ray_an);
    t_ray   res;

    get_di(inf, ray_an);
    if (inf->di_up)
        y = floor(inf->player->y);
    else
        y = ceil(inf->player->y);
    x = inf->player->x + ((y - inf->player->y) / tan(ray_an));
    ystep *= inf->di_up ? -1 : 1;
    if (inf->di_right && xstep < 0)
        xstep *= -1;
    if (!inf->di_right && xstep > 0)
        xstep *= -1;
    while (x >= 0 && x < inf->map->map_width && y >= 0 && y < inf->map->map_height)
    {
        if (inf->di_up && (int)floor(y) - 1 >= 0) //upward > need to check the next upper box
        {
            if (inf->map->patn[(int)floor(y) - 1][(int)floor(x)] == WALL)
            {
                res.side = 0; //up
                break;
            }
        }
        else
        {
            if (inf->map->patn[(int)floor(y)][(int)floor(x)] == WALL)
            {
                res.side = 1; //down
                break;
            }
        }
        x += xstep;
        y += ystep;
    }
    res.x = x;
    res.y = y;
    res.dist = sqrt(pow(x - inf->player->x, 2) + pow(y - inf->player->y, 2));
    return (res);
}

t_ray  raycasteach(t_sto *inf, double ray_an)
{
    t_ray   hori;
    t_ray   verti;
    t_ray   res;
    verti = check_verti(inf, ray_an);
    hori = check_hori(inf, ray_an);
    if (verti.dist < hori.dist)
        res = verti;
    else
        res = hori;
    res.dist *= cos(ray_an - inf->player->rot_an);
    return (res);
}

void    raycastall(t_sto *inf)
{ //+ adjustment to make ray_an to be between 0,360
    double ray_an;
    int ray_no;

    ray_no = 0;
    ray_an = inf->player->rot_an - (inf->fov_an / 2);
    ray_an += ray_an < 0? 2 * M_PI : 0;
    ray_an += ray_an < 0? 2 * M_PI : 0;
    while (ray_no < inf->s_width)
    {
        inf->rays[ray_no] = raycasteach(inf, ray_an);
        ray_an += inf->fov_an / (inf->s_width);
        if (ray_an == 2 * M_PI)
            ray_an = 0;
        else if (ray_an > 2 * M_PI)
            ray_an = ray_an - 2 * M_PI;
        ray_no++;
    }
}