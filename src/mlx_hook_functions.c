/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:35:14 by adichou           #+#    #+#             */
/*   Updated: 2025/02/04 08:33:32 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
		close_window(mlx);
	else if (keycode == 114)
	{
		mlx->poudreuse *= -1;
		display(mlx);
	}
	else if (keycode < 256)
		mlx->keys[keycode] = 1;
	return (0);
}

int	key_release_hook(int keycode, t_mlx *mlx)
{
	if (keycode < 256)
		mlx->keys[keycode] = 0;
	return (0);
}

int	loop_hook_bis(t_mlx *mlx)
{
	if (mlx->keys[119])
		mlx->y_lag -= MOVSPEED;
	if (mlx->keys[115])
		mlx->y_lag += MOVSPEED;
	if (mlx->keys[97])
		mlx->x_lag -= MOVSPEED;
	if (mlx->keys[100])
		mlx->x_lag += MOVSPEED;
	return (0);
}

int	loop_hook(t_mlx *mlx)
{
	if (mlx->keys[105])
		r_rotate_x(mlx->tab, mlx->size_tab);
	if (mlx->keys[111])
		rotate_z(mlx->tab, mlx->size_tab);
	if (mlx->keys[112])
		rotate_x(mlx->tab, mlx->size_tab);
	if (mlx->keys[107])
		rotate_y(mlx->tab, mlx->size_tab);
	if (mlx->keys[108])
		r_rotate_z(mlx->tab, mlx->size_tab);
	if (mlx->keys[59])
		r_rotate_y(mlx->tab, mlx->size_tab);
	if (mlx->keys[101])
		zoom_tab(mlx->tab, mlx->size_tab);
	if (mlx->keys[113])
		dezoom_tab(mlx->tab, mlx->size_tab);
	loop_hook_bis(mlx);
	display(mlx);
	usleep(16666);
	return (0);
}
