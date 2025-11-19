/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:27:34 by adichou           #+#    #+#             */
/*   Updated: 2025/11/17 21:08:36 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
#include "../lib/minilibx-linux/mlx.h"
#include "../lib/LIBFT/libft.h"
#include "X11/X.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

# ifndef RES_X
#  define RES_X 1920
# endif
# ifndef RES_Y
#  define RES_Y 1080
# endif

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
}	t_point;

typedef	struct s_plan
{
	t_point		a;
	t_point		b;
	t_point		c;
}	t_plan;

typedef struct s_vector
{
	t_point		dir;
	t_point		origin;
}	t_vector;

typedef struct s_sphere
{
	t_point		center;
	float		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	center;
	float		radius;
}	t_cylinder;

typedef struct s_camera
{
	t_vector	camera;
	float		fov;
}	t_camera;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}	t_mlx;

typedef struct s_map
{
	t_plan		*plans;
	t_sphere	*spheres;
	t_cylinder	*cylinders;
}	t_map;

typedef struct s_program
{
	int			x_size;
	int			y_size;
	t_camera	camera;
	t_mlx		mlx;
	t_map		map;
}	t_program;

t_vector		sub_vec(t_vector v1, t_vector v2);
t_vector		mult_vec(float n, t_vector v1);
float			calcul_prod_scal(t_vector vec_1, t_vector vec_2);
t_map			init_map(void);
void			init_program(t_program *program);
t_vector		create_vector(t_point from, t_point to);
t_point			calcul_plan_norm(t_plan plan);
t_vector		bounce_plan(t_vector v, t_vector norm_plan);
t_vector		get_vector(t_point a, t_point b);
t_point			create_point(float x, float y, float z);
t_map			init_map(void);
void			put_pixel(char *addr, int line_length, int bpp, int x, int y, int color);
void			pixelput(t_mlx mlx, int x, int y, int color);
void			print_point(t_point	point, char *str);
void			init_pixel_screen(float (**pixel_screen)[3], t_program program);
void			print_pixel_screen(float	(**pixel_screen)[3]);
int				is_vector_hitting_sphere(t_vector vector, t_sphere sphere);
int				get_pixel_color(float (**pixel_screen)[3], int i, t_program *program);
void			get_image(float (**pixel_screen)[3], t_program *program);
int				minirt(void);

#endif
