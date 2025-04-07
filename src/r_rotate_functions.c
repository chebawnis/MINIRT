/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_rotate_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:58:37 by adichou           #+#    #+#             */
/*   Updated: 2025/02/01 03:18:50 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	r_rotate_x(float **tab, int size_tab)
{
	int										i;
	float									x;
	float									z;

	i = 0;
	while (i < size_tab)
	{
		x = (tab[i][0] * cos(-ROTATESPEED)) - (tab[i][1] * sin(-ROTATESPEED));
		z = (tab[i][0] * sin(-ROTATESPEED)) + (tab[i][1] * cos(-ROTATESPEED));
		tab[i][0] = x;
		tab[i][1] = z;
		i ++;
	}
}

void	r_rotate_y(float **tab, int size_tab)
{
	int										i;
	float									x;
	float									z;

	i = 0;
	while (i < size_tab)
	{
		x = (tab[i][0] * cos(-ROTATESPEED)) - (tab[i][2] * sin(-ROTATESPEED));
		z = (tab[i][0] * sin(-ROTATESPEED)) + (tab[i][2] * cos(-ROTATESPEED));
		tab[i][0] = x;
		tab[i][2] = z;
		i ++;
	}
}

void	r_rotate_z(float **tab, int size_tab)
{
	int										i;
	float									x;
	float									z;

	i = 0;
	while (i < size_tab)
	{
		x = (tab[i][1] * cos(-ROTATESPEED)) - (tab[i][2] * sin(-ROTATESPEED));
		z = (tab[i][1] * sin(-ROTATESPEED)) + (tab[i][2] * cos(-ROTATESPEED));
		tab[i][1] = x;
		tab[i][2] = z;
		i ++;
	}
}
