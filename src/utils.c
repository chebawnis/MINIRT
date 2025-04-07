/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adichou <adichou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:39:49 by adichou           #+#    #+#             */
/*   Updated: 2025/02/03 06:54:05 by adichou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	gnl_split(int *buf_read, int fd, char buffer[], int *buf_pos)
{
	*buf_read = read(fd, buffer, 5);
	if (*buf_read == -1)
		return (0);
	*buf_pos = 0;
	return (1);
}

char	*get_next_line(int fd)
{
	static char		buffer[5];
	static int		buf_read;
	static int		buf_pos;
	int				i;
	char			line[50000];

	i = 0;
	while (1)
	{
		if (buf_pos >= buf_read)
		{
			if (gnl_split(&buf_read, fd, &buffer[0], &buf_pos) == 0)
				return (NULL);
			if (buf_read == 0)
				break ;
		}
		line[i++] = buffer[buf_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int	countwords(char const *s)
{
	int								i;
	int								count;
	char							c;

	i = 0;
	count = 0;
	c = ' ';
	if (!s)
		return (0);
	if (c == '\0')
		return (1);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

float	v_abs(float n)
{
	if (n > 0)
		return (n);
	return (n * -1);
}

int	ft_putstr(char *str)
{
	int										i;

	i = 0;
	while (str[i])
		ft_putchar_fd(str[i ++], 1);
	return (0);
}
