/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:44:41 by adichou           #+#    #+#             */
/*   Updated: 2025/02/01 03:19:20 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	zoom_tab(float **tab, float size_tab)
{
	int										i;

	i = 0;
	while (i < size_tab)
	{
		tab[i][0] *= ZOOMSPEED;
		tab[i][1] *= ZOOMSPEED;
		tab[i][2] *= ZOOMSPEED;
		i ++;
	}
}

void	dezoom_tab(float **tab, float size_tab)
{
	int										i;

	i = 0;
	while (i < size_tab)
	{
		tab[i][0] *= DEZOOMSPEED;
		tab[i][1] *= DEZOOMSPEED;
		tab[i][2] *= DEZOOMSPEED;
		i ++;
	}
}
