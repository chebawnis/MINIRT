/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:27:34 by adichou           #+#    #+#             */
/*   Updated: 2025/11/10 22:53:41 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
