/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:58:41 by adichou           #+#    #+#             */
/*   Updated: 2025/02/10 13:20:57 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	fdf(int fd, char *map)
{
	t_mlx									mlx;

	set_mlx(&mlx, fd);
	close(fd);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		free(mlx.tab);
		return (ft_putstr("Map Invalide\n"));
	}
	fill_tab(fd, mlx.tab, &mlx.lrg_x, &mlx.longueur_y);
	center_tab(mlx.tab, mlx.lrg_x, mlx.longueur_y);
	display_tab(&mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int										fd;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		fdf(fd, argv[1]);
		close(fd);
	}
	else
		ft_putstr("mets une map en argument mgl\n");
	return (0);
}
