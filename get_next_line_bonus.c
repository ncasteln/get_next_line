/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:47:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/05/12 15:32:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	get_right_len(char *line, int left_len)
{
	int	i;

	i = 0;
	while (line[left_len])
	{
		left_len++;
		i++;
	}
	return (i);
}

static int	get_left_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (i);
}

static char	*split(char **line)
{
	char	*left;
	char	*temp;
	int		left_len;
	int		right_len;

	left_len = get_left_len(*line);
	left = ft_substr(*line, 0, left_len);
	right_len = get_right_len(*line, left_len);
	if (right_len == 0)
	{
		temp = NULL;
		free(*line);
		*line = NULL;
	}
	else
	{
		temp = *line;
		*line = ft_substr(*line, left_len, right_len);
		free(temp);
	}
	return (left);
}

static char	*init_buffer(char **buff, int fd)
{
	if (fd >= 0)
	{
		if (BUFFER_SIZE > 0)
		{
			*buff = malloc ((BUFFER_SIZE + 1) * sizeof(char));
			if (!*buff)
				return (NULL);
			return (*buff);
		}
	}
	return (NULL);
}

static void	*error(char **line, char **buff)
{
	if (*line)
		return (free(*buff), *buff = NULL, free(*line), *line = NULL, NULL);
	return (free(*buff), *buff = NULL, NULL);
}

char	*get_next_line(int fd)
{
	static char	*line[MAX_FD];
	char		*buff;
	int			n_read;

	buff = init_buffer(&buff, fd);
	if (!buff)
		return (NULL);
	n_read = 1;
	while (n_read > 0 && !(ft_strchr(line[fd], '\n')))
	{
		n_read = read(fd, buff, BUFFER_SIZE);
		if (n_read == -1)
			return (error(&line[fd], &buff));
		buff[n_read] = '\0';
		if (n_read > 0)
		{
			line[fd] = ft_strjoin(line[fd], buff);
			if (!line[fd])
				return (free(buff), buff = NULL, NULL);
		}
		else // n_read == 0 || n_read == -1
		{
			if (line[fd])
				return (free(buff), buff = NULL, split(&line[fd]));
			else
				return (free(buff), buff = NULL, NULL);
		}
	}
	return (free(buff), buff = NULL, split(&line[fd]));
}
