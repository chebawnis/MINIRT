/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:31:05 by adichou           #+#    #+#             */
/*   Updated: 2025/02/10 13:18:59 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_mlx(t_mlx *mlx, int fd)
{
	int										i;

	i = 0;
	mlx->x_lag = RES_X / 2;
	mlx->y_lag = RES_Y / 2;
	mlx->size_tab = count_values(fd);
	ft_memset(mlx->keys, 0, sizeof(mlx->keys));
	mlx->tab = malloc(mlx->size_tab * sizeof(float *));
	mlx->poudreuse = 1;
	while (i < mlx->size_tab)
	{
		mlx->tab[i] = malloc(4 * sizeof(float));
		if (!mlx->tab[i])
		{
			while (--i >= 0)
				free(mlx->tab[i]);
			free(mlx->tab);
			return ;
		}
		i ++;
	}
}

int	close_window(t_mlx *mlx)
{
	int										i;

	i = 0;
	while (i < mlx->size_tab)
	{
		free(mlx->tab[i]);
		i ++;
	}
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_window(mlx->ptr, mlx->winptr);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	free(mlx->tab);
	exit(0);
	return (0);
}

void	display(t_mlx *mlx)
{
	int										*buff;
	int										total;
	int										p0[3];
	int										p1[3];
	int										i;

	buff = (int *)mlx->data;
	total = RES_X * RES_Y;
	i = -1;
	while (++ i < total)
		buff[i] = BACKGROUNDCOLOR;
	if (mlx->poudreuse == -1)
		display_dots(mlx);
	else
		display_lines(mlx, p0, p1);
	mlx_put_image_to_window(mlx->ptr, mlx->winptr, mlx->img, 0, 0);
}

void	set_display(t_mlx *mlx)
{
	int										i;
	int										x;
	int										y;
	int										rx;
	int										ry;

	i = 0;
	x = mlx->x_lag;
	y = mlx->y_lag;
	rx = RES_X / 6;
	ry = RES_Y / 6;
	if (!mlx->tab || !*mlx->tab)
		return ;
	while (mlx->tab[0][0] + x > rx && mlx->tab[0][0] + y > ry)
		zoom_tab(mlx->tab, mlx->size_tab);
	while (i < 5)
	{
		rotate_x(mlx->tab, mlx->size_tab);
		rotate_y(mlx->tab, mlx->size_tab);
		rotate_z(mlx->tab, mlx->size_tab);
		i ++;
	}
}

void	display_tab(t_mlx *mlx)
{
	set_display(mlx);
	mlx->ptr = mlx_init();
	mlx->winptr = mlx_new_window(mlx->ptr, RES_X, RES_Y, "FENETRE");
	mlx->img = NULL;
	mlx->img = mlx_new_image(mlx->ptr, RES_X, RES_Y);
	if (!mlx->img)
		return ;
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->endian);
	display(mlx);
	mlx_hook(mlx->winptr, 17, 0, close_window, mlx);
	mlx_hook(mlx->winptr, 2, (1L << 0), key_hook, mlx);
	mlx_hook(mlx->winptr, 3, (1L << 1), key_release_hook, mlx);
	mlx_loop_hook(mlx->ptr, loop_hook, mlx);
	mlx_loop(mlx->ptr);
}
