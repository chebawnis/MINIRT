/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/11/17 21:07:49 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"


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

void init_pixel_screen(float (**pixel_screen)[3], t_program program)
{
	int		x_index, y_index = 0, index = 0;
	float	pixel_gap;
	float	start_x, start_z;

	*pixel_screen = malloc(RES_X * RES_Y * sizeof(float[3]));
	if (!*pixel_screen)
		return;

	pixel_gap = 1.0f / RES_X;

	// Centrer le plan d'écran devant la caméra :
	start_x = program.camera.camera.origin.x - 0.5f;  // centré sur X=10
	start_z = program.camera.camera.origin.z - ((float)RES_Y / (float)RES_X) / 2.0f;

	while (y_index < RES_Y)
	{
		x_index = 0;
		while (x_index < RES_X)
		{
			(*pixel_screen)[index][0] = start_x + (x_index * pixel_gap);
			(*pixel_screen)[index][1] = program.camera.camera.origin.y + program.camera.fov; // devant la caméra
			(*pixel_screen)[index][2] = start_z + (y_index * pixel_gap);
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

int	is_vector_hitting_sphere(t_vector vector, t_sphere sphere)
{
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

float dot(t_vector a, t_vector b)
{
    return (a.dir.x * b.dir.x + a.dir.y * b.dir.y + a.dir.z * b.dir.z);
}

t_vector sub(t_vector a, t_vector b)
{
    t_vector r;
    r.dir.x = a.dir.x - b.dir.x;
    r.dir.y = a.dir.y - b.dir.y;
    r.dir.z = a.dir.z - b.dir.z;
    return r;
}

t_vector mul(t_vector v, float n)
{
    t_vector r = v;
    r.dir.x *= n;
    r.dir.y *= n;
    r.dir.z *= n;
    return r;
}

int is_vector_hitting_cylinder(t_vector ray, t_cylinder cyl)
{
    t_vector A = cyl.center; // axe du cylindre (normalisé)
    t_vector OC;

    OC = sub(ray, cyl.center);

    // Projections perpendiculaires :
    float d_dot_a = dot(ray, A);
    float oc_dot_a = dot(OC, A);

    t_vector D_perp = sub(ray, mul(A, d_dot_a));
    t_vector OC_perp = sub(OC, mul(A, oc_dot_a));

    float a = dot(D_perp, D_perp);
    float b = 2.0f * dot(D_perp, OC_perp);
    float c = dot(OC_perp, OC_perp) - cyl.radius * cyl.radius;

    float discriminant = b*b - 4*a*c;

    return (discriminant >= 0.0f);
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

	if (is_vector_hitting_sphere(vector, program->map.spheres[0]) ||
		is_vector_hitting_cylinder(vector, program->map.cylinders[0]))
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
