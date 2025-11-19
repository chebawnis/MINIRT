/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calculs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:45:27 by adichou           #+#    #+#             */
/*   Updated: 2025/11/17 18:53:00 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
