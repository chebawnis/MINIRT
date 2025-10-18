/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/10/18 19:13:00 by adichou          ###   ########.fr       */
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
}

float	calcul_prod_scal(t_vector vec_1, t_vector vec_2)
{
	float	x_temp;
	float	y_temp;
	float	z_temp;

	x_temp = vec_1.from.x * vec_2.from.x;
	y_temp = vec_1.from.y * vec_2.from.y;
	z_temp = vec_1.from.z * vec_2.from.z;
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
	res =  
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
