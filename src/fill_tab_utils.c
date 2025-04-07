/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:54:00 by adichou           #+#    #+#             */
/*   Updated: 2025/02/04 08:26:09 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

size_t	count_values(int fd)
{
	char									*line;
	size_t									count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count += countwords(line);
		free (line);
	}
	return (count);
}

float	ft_hextoi(const char *str)
{
	int										i;
	float									result;

	i = 0;
	result = 0;
	while (i < 6 && str[i] && str[i] != '\n' && str[i] != ' ')
	{
		result *= 16;
		if (str[i] >= '0' && str[i] <= '9')
			result += str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += str[i] - 'a' + 10;
		else
			return (-1);
		i ++;
	}
	return (result);
}

void	fill_line(char *line, float **tab, int line_i, int *pts_i)
{
	int										i;
	int										j;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		tab[*pts_i][0] = j * MULTIPLICATEUR;
		tab[*pts_i][1] = line_i * MULTIPLICATEUR;
		tab[*pts_i][2] = ft_atoi(line + i) * ZMULTIPLICATEUR;
		while (line[i] != ' ' && line[i] != '\0' && line[i] != ',')
			i ++;
		tab[*pts_i][3] = FDF_COLOR;
		if (line[i] == ',')
		{
			tab[*pts_i][3] = ft_hextoi(line + i + 3);
			while (line[i] != ' ' && line[i] && line[i] != '\n')
				i ++;
			i ++;
		}
		(*pts_i)++;
		j ++;
	}
}

void	fill_tab(int fd, float **tab, int	*largeur_x, int *longueur_y)
{
	int										points_lus;
	int										lineindex;
	char									*line;

	points_lus = 0;
	lineindex = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		*largeur_x = countwords(line);
		fill_line(line, tab, lineindex, &points_lus);
		lineindex ++;
		free (line);
	}
	*longueur_y = lineindex;
}
