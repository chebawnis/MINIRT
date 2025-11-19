/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:51:39 by adichou           #+#    #+#             */
/*   Updated: 2025/11/17 20:09:37 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_cylinder	create_cylinder(t_vector center, float radius)
{
	t_cylinder	res;

	res.center = center;
	res.radius = radius;
	return (res);
}
t_sphere	create_sphere(t_point center, float radius)
{
	t_sphere	res;

	res.center = center;
	res.radius = radius;
	return (res);
}

t_map	init_map(void)
{
	t_map	res;

	res.spheres = malloc(3 * sizeof(t_sphere));
	res.spheres[0] = create_sphere(create_point(10, 20, 10), 10);
	res.cylinders = malloc(3 * sizeof(t_cylinder));
	res.cylinders[0] = create_cylinder(create_vector(create_point(10, 20, 0), create_point(10, 20, 20)), 10);
	return res;
}

void	init_program(t_program *program)
{
	program->x_size = RES_X;
	program->y_size = RES_Y;
	program->camera.fov = 0.3 ;
	program->camera.camera = create_vector(create_point(10, 0, 10),
							create_point(10, program->camera.fov, 10));
	program->mlx.mlx = mlx_init();
	program->mlx.win =  mlx_new_window(program->mlx.mlx, RES_X, RES_Y, "MiniRT");
	program->mlx.img = mlx_new_image(program->mlx.mlx, RES_X, RES_Y);
	program->mlx.addr = mlx_get_data_addr(program->mlx.img, &(program->mlx.bpp),
						&(program->mlx.line_length), &(program->mlx.endian));
	program->map = init_map();
}
