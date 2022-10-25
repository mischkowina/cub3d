/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:29:51 by ialinaok          #+#    #+#             */
/*   Updated: 2022/10/25 15:03:33 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char));
	*line = '\0';
	if (buffer[0] != '\0')
		join_line(&line, buffer);
	while (!ft_strchr(line, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE);
		check = read(fd, buffer, BUFFER_SIZE);
		if (check <= 0 && !(*line))
			return (done_reading(&line));
		buffer[check] = '\0';
		join_line(&line, buffer);
		if (check < BUFFER_SIZE && !ft_strchr(line, '\n'))
		{
			ft_bzero(buffer, BUFFER_SIZE);
			break ;
		}
	}
	return (line);
}

char	*done_reading(char **line)
{
	free(*line);
	return (NULL);
}

void	join_line(char **line, char *buffer)
{
	char	*tmp;
	char	*find_nl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	find_nl = ft_strchr(buffer, '\n');
	tmp = allocate_tmp(line, find_nl, ft_strlen(buffer));
	if (!tmp)
		return ;
	while (line[0][j])
		tmp[i++] = line[0][j++];
	j = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		tmp[i++] = buffer[j++];
	if (buffer[j] == '\n')
	{
		tmp[i++] = buffer[j++];
		move_leftovers(buffer, ++find_nl);
	}
	tmp[i] = '\0';
	free(line[0]);
	line[0] = tmp;
}

char	*allocate_tmp(char **line, char *find_nl, int bufflen)
{
	char	*tmp;

	if (find_nl)
		tmp = malloc(ft_strlen(*line) + bufflen - ft_strlen(find_nl) + 2);
	else
		tmp = malloc(ft_strlen(*line) + bufflen + 1);
	return (tmp);
}

void	move_leftovers(char *buffer, char *find_nl)
{
	int	i;

	i = 0;
	while (find_nl[i])
	{
		buffer[i] = find_nl[i];
		i++;
	}
	buffer[i] = '\0';
}
