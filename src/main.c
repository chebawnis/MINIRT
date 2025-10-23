/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/10/24 00:48:48 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


t_vector	create_vector(t_point from, t_point to)
{
	t_vector	res;
	t_point		tmp;

	tmp.x = to.x - from.x;
	tmp.y = to.y - from.y;
	tmp.z = to.z - from.z;
	res.vector_point = tmp;
	res.from = from;
	return (res);
}

float	calcul_prod_scal(t_vector vec_1, t_vector vec_2)
{
	float	x_temp;
	float	y_temp;
	float	z_temp;

	x_temp = vec_1.vector_point.x * vec_2.vector_point.x;
	y_temp = vec_1.vector_point.y * vec_2.vector_point.y;
	z_temp = vec_1.vector_point.z * vec_2.vector_point.z;
	return (x_temp + y_temp + z_temp);
}

t_point	calcul_plan_norm(t_plan plan)
{
	t_vector		res;
	t_vector		ab;
	t_vector		ac;

	ab = create_vector(plan.a, plan.b);
	ac = create_vector(plan.a, plan.c);
	// scal(res, ab) doit etre egal a 0;
	// scal(res, ac) doit etre egal a 0;
	res.vector_point.x = ab.vector_point.y * ac.vector_point.z - ab.vector_point.z * ac.vector_point.y;
	res.vector_point.y = ab.vector_point.z * ac.vector_point.x - ab.vector_point.x * ac.vector_point.z;
	res.vector_point.z = ab.vector_point.x * ac.vector_point.y - ab.vector_point.y * ac.vector_point.x;
	res.from.x = 0;
	res.from.y = 0;
	res.from.z = 0;
	return (res.vector_point);
}

t_vector	sub_vec(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.vector_point.x = v1.vector_point.x - v2.vector_point.x;
	res.vector_point.y = v1.vector_point.y - v2.vector_point.y;
	res.vector_point.z = v1.vector_point.z - v2.vector_point.z;
	return (res);
}

t_vector	mult_vec(float n, t_vector v1)
{
	t_vector	res;

	res.vector_point.x = v1.vector_point.x * n;
	res.vector_point.y = v1.vector_point.y * n;
	res.vector_point.z = v1.vector_point.z * n;
	return (res);
}

t_vector	bounce_plan(t_vector v, t_vector norm_plan)
{
	t_vector	res;

	// res = v - 2(prod_scal(v, norm))norm
	res = sub_vec(v, mult_vec(2 * calcul_prod_scal(v, norm_plan), norm_plan));
	return (res);
}

t_vector	get_vector(t_point a, t_point b)
{
	t_vector	res;

	res.vector_point.x = b.x - a.x;
	res.vector_point.y = b.y - a.y;
	res.vector_point.z = b.z - a.z;
	return (res);
}

// int	launch_vec(vector, indice)
// {
	
// 	// vecteur doit partir de camera_fov et passer par i,
// 	//
// 	// verifier le premier objet touche par le vecteur, noter le point de collision
// 	// et noter la nature de l'objet,
// 	//
// 	// launch_vec(bounce(vector, point_collision, objet*), indice - reflexion_index)
// 	// * "plan", "circle" ou "cylindre" (pour l'instant) 
// }

// int	lauch_map(map)
// {
	
// 	while (i < total_pixel)
// 	{
// 		lauch_vec(get_vector(i, camera_fov));
// 		i ++;
// 		//passer au pixel d'apres
// 	}
	
// }

t_point	create_point(float x, float y, float z)
{
	t_point	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

void	init_program(t_program *program)
{
	program->x_size = RES_X;
	program->y_size = RES_Y;
	program->camera.camera = create_vector(create_point(10, 0, 10),
							create_point(10, program->camera.fov, 10));
	program->mlx.mlx = mlx_init();
	program->mlx.win =  mlx_new_window(program->mlx.mlx, RES_X, RES_Y, "MiniRT");
	program->mlx.img = mlx_new_image(program->mlx.mlx, RES_X, RES_Y);
	program->mlx.addr = mlx_get_data_addr(program->mlx.img, &(program->mlx.bpp),
						&(program->mlx.line_length), &(program->mlx.endian));
}

void	put_pixel(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char	*pixel;

	pixel = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int *)pixel = color;
}

void	pixelput(t_mlx mlx, int x, int y)
{
	put_pixel(mlx.addr, mlx.line_length, mlx.bpp, x, y, 0xFF0000);
}

void	get_image()
{

}

void	init_pixel_screen(float	*pixel_screen[3])
{
	int		x_index;
	int		y_index;
	float	pixel_gap;
	float	start[3];

	pixel_screen = malloc(RES_X * RES_Y * sizeof(float[3]));
	if (!pixel_screen)
		return ;
	pixel_gap = 1 / RES_X;
	start[0] = ;
	start[1] = ;
	start[2] = ;
	while (x_index < RES_X)
	{
		while (y_index < RES_Y)
		{
			y_index ++;
			pixel_screen[y_index][0] = ;
			pixel_screen[y_index][1] = ;
			pixel_screen[y_index][2] = ;
		}
		y_index = 0;
		x_index ++;
	}
	
}

int	minirt(void)
{
	t_program	*program;
	float 		(*pixel_screen)[3];

	program = malloc(sizeof(t_program));
	init_program(program);
	init_pixel_screen(&pixel_screen);

	// PROGRAMME PRINCIPAL
	

	
	get_image();
	mlx_put_image_to_window(program->mlx.mlx, program->mlx.win,
							program->mlx.img, 0, 0);
	

	mlx_loop(program->mlx.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		minirt();
		(void)argv[1];
	}
	return (0);
}
