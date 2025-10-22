/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/10/22 20:23:43 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef	struct s_plan
{
	t_point	a;
	t_point	b;
	t_point	c;
}	t_plan;

typedef struct s_vector
{
	t_point		vector_point;
	t_point		from;
}	t_vector;

typedef struct s_sphere
{
	float		center[3];
	float		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_vector	center;
	float		radius;
}	t_cylinder;

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

int	launch_vec(vector, indice)
{
	// vecteur doit partir de camera_fov et passer par i,
	//
	// verifier le premier objet touche par le vecteur, noter le point de collision
	// et noter la nature de l'objet,
	//
	// launch_vec(bounce(vector, point_collision, objet*), indice - reflexion_index)
	// * "plan", "circle" ou "cylindre" (pour l'instant) 
}

int	lauch_map(map)
{
	while (i < total_pixel)
	{
		lauch_vec(get_vector(i, camera_fov));
		i ++;
		//passer au pixel d'apres
	}
	
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("argc est egal a 2");
		(void)argv[1];
	}
	return (0);
}
