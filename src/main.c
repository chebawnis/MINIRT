/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/11/10 23:58:33 by adichou          ###   ########.fr       */
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
	res.dir = tmp;
	res.origin = from;
	return (res);
}

float	calcul_prod_scal(t_vector vec_1, t_vector vec_2)
{
	float	x_temp;
	float	y_temp;
	float	z_temp;

	x_temp = vec_1.dir.x * vec_2.dir.x;
	y_temp = vec_1.dir.y * vec_2.dir.y;
	z_temp = vec_1.dir.z * vec_2.dir.z;
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
	res.dir.x = ab.dir.y * ac.dir.z - ab.dir.z * ac.dir.y;
	res.dir.y = ab.dir.z * ac.dir.x - ab.dir.x * ac.dir.z;
	res.dir.z = ab.dir.x * ac.dir.y - ab.dir.y * ac.dir.x;
	res.origin.x = 0;
	res.origin.y = 0;
	res.origin.z = 0;
	return (res.dir);
}

t_vector	sub_vec(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.dir.x = v1.dir.x - v2.dir.x;
	res.dir.y = v1.dir.y - v2.dir.y;
	res.dir.z = v1.dir.z - v2.dir.z;
	return (res);
}

t_vector	mult_vec(float n, t_vector v1)
{
	t_vector	res;

	res.dir.x = v1.dir.x * n;
	res.dir.y = v1.dir.y * n;
	res.dir.z = v1.dir.z * n;
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

	res.dir.x = b.x - a.x;
	res.dir.y = b.y - a.y;
	res.dir.z = b.z - a.z;
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

// void	print_pixel_screen(float (*pixel_screen)[3])
// {
// 	int i = 0;
// 	while (i < RES_X * RES_Y && i < 10)
// 	{
// 		printf("point %d;\n		X = %f\n		Y = %f\n		Z = %f\n\n\n",
// 				i, pixel_screen[i][0], pixel_screen[i][1], pixel_screen[i][2]);
// 		i ++;
// 	}
// }

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

	pixel_gap = 1.0f / RES_X; // distance entre pixels (même pour X et Y)
	start[0] = -0.5f; // centre horizontalement
	start[1] = 1.0f;  // plan à y = 1
	start[2] = -((float)RES_Y / (float)RES_X) / 2.0f; // centrer verticalement

	while (y_index < RES_Y)
	{
		x_index = 0;
		while (x_index < RES_X)
		{
			(*pixel_screen)[index][0] = start[0] + (x_index * pixel_gap);
			(*pixel_screen)[index][1] = program.camera.fov;
			(*pixel_screen)[index][2] = start[2] + (y_index * pixel_gap);
			x_index++;
			index++;
		}
		y_index++;
	}
}


void	print_pixel_screen(float	(**pixel_screen)[3])
{
	printf("coin haut gauche, X = %f, Y = %f, Z = %f\n", (*pixel_screen)[0][0], (*pixel_screen)[0][1], (*pixel_screen)[0][2]);
	printf("coin haut droit, X = %f, Y = %f, Z = %f\n", (*pixel_screen)[RES_X][0], (*pixel_screen)[RES_X][1], (*pixel_screen)[RES_X][2]);
	printf("coin bas gauche, X = %f, Y = %f, Z = %f\n", (*pixel_screen)[RES_X * RES_Y - RES_X][0], (*pixel_screen)[RES_X * RES_Y - RES_X][1], (*pixel_screen)[RES_X * RES_Y - RES_X][2]);
	printf("coin bas droit, X = %f, Y = %f, Z = %f\n", (*pixel_screen)[RES_X * RES_Y][0], (*pixel_screen)[RES_X * RES_Y][1], (*pixel_screen)[RES_X * RES_Y][2]);
}

int	is_vector_hitting(t_vector vector, t_map map)
{
	t_sphere	sphere = map.spheres[0];
	t_point		oc;
	float		a, b, c;
	float		discriminant;

	// O - C
	oc.x = vector.origin.x - sphere.center.x;
	oc.y = vector.origin.y - sphere.center.y;
	oc.z = vector.origin.z - sphere.center.z;

	// coefficients de l'équation quadratique
	a = vector.dir.x * vector.dir.x + vector.dir.y * vector.dir.y + vector.dir.z * vector.dir.z;
	b = 2.0f * (oc.x * vector.dir.x + oc.y * vector.dir.y + oc.z * vector.dir.z);
	c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - (sphere.radius * sphere.radius);

	discriminant = b * b - 4 * a * c;

	if (discriminant < 0.0f)
		return (0); // pas de collision
	else
		return (1); // le rayon touche la sphère
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
	t_vector	vector = create_vector(program->camera.camera.origin, tmp);

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
	print_point(program->camera.camera.origin, "camera from");
	print_point(program->camera.camera.dir, "camera dir");
	print_point(program->map.spheres->center, "sphere center");
	printf("sphere radius = %f\n", program->map.spheres->radius);
	(void)pixel_screen;
	int i = 0;
	while (i < RES_X * RES_Y)
	{
		pixelput(program->mlx, i % RES_X, i / RES_X, get_pixel_color(pixel_screen, i, program));
		i ++;
	}
	printf("test\n");
	
}


int	minirt(void)
{
	t_program	*program;
	float 		(*pixel_screen)[3];

	program = malloc(sizeof(t_program));
	init_program(program);
	pixel_screen = NULL;
	init_pixel_screen(&pixel_screen, *program);
	print_pixel_screen(&pixel_screen);
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
