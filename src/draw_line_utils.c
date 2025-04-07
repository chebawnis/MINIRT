/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:18:56 by adichou           #+#    #+#             */
/*   Updated: 2025/02/06 04:06:18 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	get_steps(int d[2])
{
	if (d[0] > -d[1])
		return (d[0]);
	return (-d[1]);
}

void	init_color_steps(float step[3], int c_start, int c_end, int steps)
{
	step[0] = ((c_end >> 16) & 0xFF) - ((c_start >> 16) & 0xFF);
	step[1] = ((c_end >> 8) & 0xFF) - ((c_start >> 8) & 0xFF);
	step[2] = (c_end & 0xFF) - (c_start & 0xFF);
	if (steps > 0)
	{
		step[0] /= steps;
		step[1] /= steps;
		step[2] /= steps;
	}
}

int	calculate_color(int c_start, float step[3], int i)
{
	int										r;
	int										g;
	int										b;

	r = ((c_start >> 16) & 0xFF) + (step[0] * i);
	g = ((c_start >> 8) & 0xFF) + (step[1] * i);
	b = (c_start & 0xFF) + (step[2] * i);
	return ((r << 16) | (g << 8) | b);
}

void	update_position(int p0[3], int s[2], int *err, int d[2])
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 >= d[1])
	{
		*err += d[1];
		p0[0] += s[0];
	}
	if (e2 <= d[0])
	{
		*err += d[0];
		p0[1] += s[1];
	}
}

void	drawline(t_mlx *mlx, int p0[3], int p1[3])
{
	int		d[2];
	int		s[2];
	int		err;
	int		i;
	float	step[3];

	init_deltas(d, p0, p1);
	init_steps(s, p0, p1);
	init_color_steps(step, p0[2], p1[2], get_steps(d));
	err = d[0] + d[1];
	i = 0;
	while (1)
	{
		ft_pixel_put(mlx, p0[0], p0[1], calculate_color(p0[2], step, i));
		if (p0[0] == p1[0] && p0[1] == p1[1])
			break ;
		update_position(p0, s, &err, d);
		i++;
	}
}
