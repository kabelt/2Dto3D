#ifndef LEM_IN_H
# define LEM_IN_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <key.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <stdio.h>

# define MIN(A, B) 	(((A) < (B)) ? (A) : (B))
# define MAX(A, B) 	(((A) > (B)) ? (A) : (B))

# define ABS(X) 		(((X) < 0) ? (-(X)) : (X))

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_EXIT			17

//screen
# define S_WIDTH 1000
# define S_HEIGHT 800

# define VALIDMAPCHAR " 012NEWS"

//controls
# define ESC 53

//map
# define TILE_SIZE	100
# define MNM_TILESIZE 10
# define FOV_ANG	60
# define S_IN		0
# define WALL		1
# define NORTH		2
# define SOUTH		3
# define WEST		4
# define EAST		5
# define SPRITE		6
# define S_OUT		7
# define BORDER		8
# define SPWN		9

typedef struct	s_lst
{
	void		*content;
	struct s_lst *next;
}				t_lst;

typedef struct s_cord
{
	int			y;
	int			x;
}				t_cord;

typedef struct 	s_map
{
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
	int			**patn;
	int			spwn_di; //sprawn direction 1N 2S 3E 4W
	int			get_elem; //counting the number of get info 8,9
	int			res_isget;
	int 		north_isget;
	int			east_isget;
	int			west_isget;
	int			south_isget;
	int			sprite_isget;
	int			floor_isget;
	int			ceiling_isget;
}				t_map;

typedef struct s_py
{
	double		x;
	double		y;
	int			radius; //determine how large we want the dot to be in the map
	int			turndi;
	int			walkdi;
	double		rot_an;
	int			movespeed;
	double		rotspeed;
}				t_py;

typedef struct 	s_ray
{
	double		dist;
	double		x;
	double		y;
	int			side;
}				t_ray;

typedef struct	s_tex
{
	char	*path;
	void	*img;
	void	*data_addr;
	t_cord	start;
	t_cord	end;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;

typedef struct 	s_sprite
{
	double			x;
	double			y;
	double			dist; //distance from the player at a given moment
	double			direct; //the direction of the sprite in relative to the player
	struct s_sprite	*next;
}				t_sprite;

typedef struct	s_sto
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;

	void		*mnm_img;
	char		*mnm_data_addr;
	int			mnm_width;
	int			mnm_height;
	int			mnm_size_line;
	int			mnm_bpp;
	int			mnm_tilesize;

	int			bpp;//bits_per_pixel;
	int			size_line;
	int			endian;
	int			s_width;
	int			s_height;
	double		fov_an;
	t_ray		*rays;
	// double		max_dist;
	t_map		*map; //subject to change
	t_py		*player;

	int			di_up;
	int			di_right;

	double		pp_dist; //distance from player to the projection plane

	//engine
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
	int			rot_left;
	int			rot_right;

	t_sprite	**sprites;

	//texture
	t_tex		tex[5]; //store paths of the textures

	bool		enable_light;
	bool		enable_minimap;
}				t_sto;



typedef struct				s_save
{
	int						height;
	int						width;
	int						pad;
	unsigned char			*file_header;
	unsigned char			*img_header;
	int						fd;
}							t_save;


//main

//map
void 	readmap(t_sto *inf, int fd);
void	errexit(char *str);

void    read_ceiling(t_sto *inf, char *line);
void    read_floor(t_sto *inf, char *line);
void    read_res(t_sto *inf, char *line);
void    read_content(t_sto *inf, char *line, int fd);

void    read_north(t_sto *inf, char *line);
void    read_east(t_sto *inf, char *line);
void    read_west(t_sto *inf, char *line);
void    read_south(t_sto *inf, char *line);
void    read_sprite(t_sto *inf, char *line);

void    addframe(t_sto *inf);
void    convtroll_di(t_sto *inf, char *line, int row, int i);
void    convtroll(t_sto *inf, char *line, int row);
void    convertmap(t_sto *inf, t_lst **tmp);

void    trimmap(t_sto *inf);
void    checkborder(t_sto *inf);
void    getspec(t_sto *inf);

//rc
void    raycastall(t_sto *inf);

//engine
int     exit_hook(t_sto *inf);
int     key_press(int key, t_sto *inf);
int     key_release(int key, t_sto *inf);
int     engine(t_sto *inf);

//keyboard
void	control(t_sto *inf);
int		key_press(int key, t_sto *inf);


//move
void 	move(t_sto *inf, int key);
void    move_w(t_sto *inf);
void    move_s(t_sto *inf);
void    move_a(t_sto *inf);
void    move_d(t_sto *inf);
void    rotate_left(t_sto *inf);
void    rotate_right(t_sto *inf);


//art
void	artwork(t_sto *inf);
void    add_bg(t_sto *inf);


//3d
void    putwall(t_sto *inf);
int		getpix(double xtex, double ytex, t_tex tex, double perc);

//color
// int     shader(t_sto *inf, int head, int tail, int stripe_height);
int     shader(t_sto *inf, int head, int tail, double dist);

//texture
int		loadtex(t_sto *inf);

//minimap
void	minimap(t_sto *inf);
void	put_pixel_minimap(t_sto *inf, int x, int y, int color);
void	draw_line_minimap(t_sto *inf, t_cord head, t_cord tail, int color);

//util
int		get_now(const char *s, char c);
void	errexit(char *str);
void	put_pixel(t_sto *inf, int x, int y, int color);

//list

void	lst_add_back(t_lst **alst, t_lst *new);
void	lst_add(t_lst **alst, t_lst *new);
t_lst	*lstnew(void *content);

//sprite
void	putsprites(t_sto *inf);

//sprite_util
void sprite_add_back(t_sto *inf, t_sprite *new);
void sprite_add(t_sto *inf, t_sprite *new);
void    lst_add_rightplace(t_lst **alst, t_lst *new);
t_lst   **sortsprite(t_sto *inf);
void    free_putsprites(t_lst **list);
void    getdirection(t_sto *inf, t_lst **list, double *fov_min, double *fov_max);

//bmp
int		take_screenshot(t_sto *inf, char *str);

#endif