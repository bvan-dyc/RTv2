/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-dyc <bvan-dyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:15:22 by bvan-dyc          #+#    #+#             */
/*   Updated: 2017/11/07 17:48:19 by bvan-dyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include "../libft/libft.h"
# include "../Includes/get_next_line.h"

# include <stdio.h>
# include <stdbool.h>

# define WIN_W			1080
# define WIN_H			720

# define PARANUMSIZE	0
# define STARTOBJECTS	0

# define KEY_ESC		53
# define KEY_UP			126
# define KEY_DOWN		125
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_A			0
# define KEY_B			11
# define KEY_D			2
# define KEY_E			14
# define KEY_F			3
# define KEY_G			5
# define KEY_H			4
# define KEY_I			34
# define KEY_J			38
# define KEY_M			46
# define KEY_N			45
# define KEY_P			35
# define KEY_R			15
# define KEY_S			1
# define KEY_T			17
# define KEY_U			32
# define KEY_W			13
# define KEY_Y			16
# define KEY_PLUS		69
# define KEY_MINUS		78

# define WHITE			0xFFFFFF
# define BLACK			0x000000
# define RED			0xFF5733
# define GREEN			0x28B463
# define BLUE			0x2E86C1
# define YELLOW			0xF1C40F
# define PINK			0x8D7787
# define ORANGE			0xF39C12
# define PURPLE			0x7D3C98
# define BROWN			0xCC8000
# define LGRAY			0x777777
# define DGRAY			0x333333

# define KEY_PRESS_MASK (1L<<0)
# define KEY_PRESS 2
# define CROSS_PRESS 17

# define TRUE	1
# define FALSE	0

# define COLOR		0
# define POSITION	1
# define SIZE		2
# define DIRECTION	3
# define CAMERA		4
# define FILTER		5

# define PI		3.14159265

# define LIGHT		0
# define PLANE		1
# define SPHERE 	2
# define CONE		3
# define CYL		4
# define TRIANGLE	5
# define DISK		6

# define NOARGS			0
# define TOOMANYARGS 	1
# define INVALIDFILE 	2
# define INVALIDFORMAT 	3

# define DEFAULT		0
# define GRAYSCALE 		1
# define SEPIA 			2
# define INVERTED 		3

# define EPSILON 		0.000001

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_ray
{
	t_vector		start;
	t_vector		dir;
	t_vector		dist;
	float			red;
	float			green;
	float			blue;
	int				level;
	float			coef;
	int				inshadow;
	t_vector		scaled;
	t_vector		hitpoint;
	float			reflect;
	t_vector		tmp;
}					t_ray;

typedef struct		s_colour
{
	float			red;
	float			green;
	float			blue;
}					t_colour;

typedef struct		s_light
{
	t_vector		pos;
	t_colour		colour;
}					t_light;

typedef struct		s_inter
{
	double			det;
	double			a;
	double			b;
	double			c;
	double			discr;
	double			t0;
	double			t1;
	t_vector		dist;
	int				ret;
	t_vector		norm;
}					t_inter;

typedef struct		s_triter
{
	double 			det;
	double 			invdet;
	t_vector 		edge1;
	t_vector 		edge2;
	t_vector 		s1;
	t_vector 		s2;
	t_vector 		s3;
	double 			tmp;
	double 			u;
	double			v;
}					t_triter;

typedef struct		s_item
{
	int				type;
	t_vector		pos;
	t_vector		dir;
	int				size;
	t_colour		colour;
	float			reflection;
	float			refraction;
	t_vector		p1;
	t_vector		p2;
	t_vector		p3;
	t_vector		min;
	t_vector		max;
}					t_item;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img_ptr;
	char			*img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				disableshadow;
	char			**scene;
	int				ss;
	int				numitems;
	int				numlights;
	int				culight;
	int				citem;
	t_light			*lights;
	t_item			*items;
	float			reflect;
	float			lambert;
	t_vector		campos;
	t_vector		camdir;
	t_vector		norm;
	int				hidemenu;
	int				maxlvl;
	int				select;
	int				mode;
	t_colour		filter;
	int				filtermode;
	int 			increment;
}					t_env;

void				pixel_put(t_env *e, int x, int y, int color);
void				fill_image(t_env *e, int color);
int					expose_hook(t_env *e);
void				env_init(t_env *e, char *file);
void				shadow_print(t_env *e, int x, int y, char *s);
int					key_hook(int keycode, t_env *e);
void				rt_draw(t_env *e);
t_vector			rt_vectoradd(t_vector *v1, t_vector *v2);
t_vector			rt_vectorscale(double c, t_vector *v);
double				rt_vecdot(t_vector *v1, t_vector *v2);
t_vector			rt_vectorsub(t_vector *v1, t_vector *v2);
char				**makescene(t_env *e, char *file);
int					parsecore(t_env *e);
void				print_tab(char **tab, int size);
int					rt_intersectsphere(t_ray *r, t_item *s, double *t);
int					rt_intersectplane(t_ray *r, t_item *p, double *t);
void				rt_vectornorm(t_vector *v);
t_vector			rt_vectornorm_r(t_vector *v);
t_vector 			rt_vectorcross(t_vector *v1, t_vector *v2);
int					rt_intersectcylinder(t_ray *r, t_item *c, double *t);
int					rt_intersectcone(t_ray *r, t_item *c, double *t);
int 				rt_intersectdisk(t_ray *r, t_item *d, double *t);
void				rt_error(int error);
void				rt_rayinit(t_ray *ray, int x, int y, t_env *e);
void				rt_lambert(t_env *e, t_ray *ray, t_ray *lightray, \
t_light currlight);
void				rt_copylight(t_env *e, t_light *currlight, int j);
int					rt_makesphere(t_env *e, int *red);
int					rt_makecylcone(t_env *e, int *red, int type);
int					rt_maketriangle(t_env *e, int *red);
int					rt_makedisk(t_env *e, int *red);
int					rt_makeplane(t_env *e, int *red);
int					rt_makelight(t_env *e, int *red);
void				rt_envfreer(t_env *e);
void				display_data(t_env *e);
t_vector			rt_rotatevector(t_vector vector, t_vector rotator);
t_vector 			rt_rotatex(t_vector v, double alpha);
t_vector 			rt_rotatey(t_vector v, double alpha);
t_vector 			rt_rotatez(t_vector v, double alpha);
int					rt_intersecttriangle(t_env *e, t_ray *r, t_item *t, double *result, int state);
void				shadow_print(t_env *e, int x, int y, char *s);
void				display_menu(t_env *e);
#endif
