/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:46:30 by adichou           #+#    #+#             */
/*   Updated: 2025/02/04 09:22:25 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	int										pixel_index;

	if (x > 0 && y > 0 && x < RES_X && y < RES_Y)
	{
		pixel_index = (y * mlx->sl) + (x * mlx->bpp / 8);
		*(unsigned int *)(mlx->data + pixel_index) = color;
	}
}

void	display_lines(t_mlx *mlx, int p0[3], int p1[3])
{
	int										i;

	i = -1;
	while (++i < mlx->size_tab - 1)
	{
		p0[0] = (int)round(mlx->tab[i][0] + mlx->x_lag);
		p0[1] = (int)round(mlx->tab[i][1] + mlx->y_lag);
		p0[2] = (int)round(mlx->tab[i][3]);
		p1[0] = (int)round(mlx->tab[i + 1][0] + mlx->x_lag);
		p1[1] = (int)round(mlx->tab[i + 1][1] + mlx->y_lag);
		p1[2] = (int)round(mlx->tab[i + 1][3]);
		if ((i + 1) % (int)round(mlx->lrg_x) != 0)
			drawline(mlx, p0, p1);
	}
	i = (int)round(mlx->lrg_x) - 1;
	while (++i < mlx->size_tab)
	{
		p0[0] = (int)round(mlx->tab[i][0] + mlx->x_lag);
		p0[1] = (int)round(mlx->tab[i][1] + mlx->y_lag);
		p0[2] = (int)round(mlx->tab[i][3]);
		p1[0] = (int)round(mlx->tab[i - mlx->lrg_x][0] + mlx->x_lag);
		p1[1] = (int)round(mlx->tab[i - mlx->lrg_x][1] + mlx->y_lag);
		p1[2] = (int)round(mlx->tab[i - mlx->lrg_x][3]);
		drawline(mlx, p0, p1);
	}
}

void	display_dots(t_mlx *mlx)
{
	int										i;
	int										x;
	int										y;

	i = -1;
	x = 0;
	y = 0;
	while (++i < mlx->size_tab)
	{
		x = (int)round(mlx->tab[i][0]) + mlx->x_lag;
		y = (int)round(mlx->tab[i][1]) + mlx->y_lag;
		ft_pixel_put(mlx, x, y, (int)round(mlx->tab[i][3]));
	}
}
