/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/10/25 17:54:12 by adichou          ###   ########.fr       */
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

t_point	create_point(float x, float y, float z)
{
	t_point	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_map	init_map(void)
{
	t_map	res;

	res.spheres = malloc(3 * sizeof(t_sphere));
	res.spheres[0].center = create_point(10, 20, 10);
	res.spheres[0].radius = 10;
	return res;
}

void	init_program(t_program *program)
{
	program->x_size = RES_X;
	program->y_size = RES_Y;
	program->camera.fov = 1;
	program->camera.camera = create_vector(create_point(10, 0, 10),
							create_point(10, program->camera.fov, 10));
	program->mlx.mlx = mlx_init();
	program->mlx.win =  mlx_new_window(program->mlx.mlx, RES_X, RES_Y, "MiniRT");
	program->mlx.img = mlx_new_image(program->mlx.mlx, RES_X, RES_Y);
	program->mlx.addr = mlx_get_data_addr(program->mlx.img, &(program->mlx.bpp),
						&(program->mlx.line_length), &(program->mlx.endian));
	program->map = init_map();
}

void	put_pixel(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char	*pixel;

	pixel = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int *)pixel = color;
}

void	pixelput(t_mlx mlx, int x, int y, int color)
{
	put_pixel(mlx.addr, mlx.line_length, mlx.bpp, x, y, color);
}

void	print_pixel_screen(float (*pixel_screen)[3])
{
	int i = 0;
	while (i < RES_X * RES_Y && i < 10)
	{
		printf("point %d;\n		X = %f\n		Y = %f\n		Z = %f\n\n\n",
				i, pixel_screen[i][0], pixel_screen[i][1], pixel_screen[i][2]);
		i ++;
	}
}

void	print_point(t_point	point, char *str)
{
	printf("%s X = %f\n", str, point.x);
	printf("%s Y = %f\n", str, point.y);
	printf("%s Z = %f\n", str, point.z);
}

void	init_pixel_screen(float	(**pixel_screen)[3], t_program program)
{
	int		x_index;
	int		y_index = 0;
	int		index = 0;
	float	pixel_gap;
	float	start[3];

	*pixel_screen = malloc(RES_X * RES_Y * sizeof(float[3]));
	if (!*pixel_screen)
		return ;
	pixel_gap = 1.0f / RES_X;
	start[0] = 9.5;
	start[2] = 10 + ((float)RES_X / (float)RES_Y / 2);
	while (y_index < RES_Y)
	{
		x_index = 0;
		while (x_index < RES_X)
		{
			(*pixel_screen)[index][0] = start[0] + (x_index * pixel_gap);
			(*pixel_screen)[index][1] = program.camera.fov;
			(*pixel_screen)[index][2] = start[2] + (y_index * pixel_gap);
			x_index ++;
			index ++;
		}
		y_index ++;
	}
}

int	is_vector_hitting(t_vector vector, t_map map)
{
	// printf("sphere center X = %f\n", map.spheres[0].center.x);
	// printf("sphere center y = %f\n", map.spheres[0].center.y);
	// printf("sphere center z = %f\n", map.spheres[0].center.z);
	// printf("sphere radius = %f\n", map.spheres[0].radius);

	t_sphere	sphere = map.spheres[0];

	t_point o = vector.from;
	t_point c = sphere.center;

	// direction d = v - o
	float dx = vector.vector_point.x;
	float dy = vector.vector_point.y;
	float dz = vector.vector_point.z;

	// coefficients de l'équation
	float a = dx*dx + dy*dy + dz*dz;
	float ox_cx = o.x - c.x;
	float oy_cy = o.y - c.y;
	float oz_cz = o.z - c.z;
	float b = 2 * (dx*ox_cx + dy*oy_cy + dz*oz_cz);
	float c_term = ox_cx*ox_cx + oy_cy*oy_cy + oz_cz*oz_cz - sphere.radius * sphere.radius;

	float delta = b*b - 4*a*c_term;

	if (delta < 0)
		return (0); // pas d’intersection

	// on calcule les solutions
	float t1 = (-b - sqrtf(delta)) / (2 * a);
	float t2 = (-b + sqrtf(delta)) / (2 * a);

	// si au moins une est >= 0, le vecteur touche la sphère
	if (t1 >= 0 || t2 >= 0)
		return (1);
	return (0);
}

int	get_pixel_color(float (**pixel_screen)[3], int i, t_program *program)
{
	int	res;

	(void)pixel_screen;
	(void)program;

	t_point		tmp;
	tmp.x = (*pixel_screen)[i][0];
	tmp.y = (*pixel_screen)[i][1];
	tmp.z = (*pixel_screen)[i][2];
	t_vector	vector = create_vector(program->camera.camera.from, tmp);

	if (is_vector_hitting(vector, program->map))
		res = 0xFF0000;
	else
		res = 0;
	return (res);
}

void	get_image(float (**pixel_screen)[3], t_program *program)
{
	// creer des vecteurs qui passent par la camera et par les points de pixel_screen
	// avec la fonction sub_vec()
	
	printf("FOV = %f\n", program->camera.fov);
	print_point(program->camera.camera.from, "camera from");
	print_point(program->camera.camera.vector_point, "camera dir");
	print_point(program->map.spheres->center, "sphere center");
	printf("sphere radius = %f\n", program->map.spheres->radius);
	(void)pixel_screen;
	int i = 0;
	while (i < RES_X * RES_Y)
	{
		pixelput(program->mlx, i % RES_X, i / RES_X, get_pixel_color(pixel_screen, i, program));
		i ++;
	}
	
}


int	minirt(void)
{
	t_program	*program;
	float 		(*pixel_screen)[3];

	program = malloc(sizeof(t_program));
	init_program(program);
	pixel_screen = NULL;
	init_pixel_screen(&pixel_screen, *program);
	// print_pixel_screen(pixel_screen);
	// PROGRAMME PRINCIPAL
	

	
	get_image(&pixel_screen, program);
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
