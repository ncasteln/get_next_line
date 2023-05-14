/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:48:51 by ncasteln          #+#    #+#             */
/*   Updated: 2023/05/14 13:49:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen_mod(char *str) // ---------- not original libft -----------
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_mod(char *str, int c) // ---------- not original libft -----------
{
	char	*p;
	int		i;

	// if (!str)
	// 	return (NULL);
	p = (char *) str;
	i = 0;
	while (p[i])
	{
		if (p[i] == (char) c)
			return (p + i);
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((!dest) && (!src))
		return (NULL);
	while (i < n)
	{
		*((char *)dest + i) = *((char *)src + i);
		i++;
	}
	return (dest);
}

char	*ft_substr_mod(char *s, unsigned int start, size_t n)
{
	char	*p;
	size_t	i;

	if (ft_strlen_mod(s + start) < n)
		n = ft_strlen_mod(s + start);
	p = malloc ((n + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while ((i < n) && s[start])
	{
		p[i] = s[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin_mod(char *line, char *buff) // ------ change to ** to assign to NULL
{
	int		line_len;
	int		buff_len;
	char	*new_line;

	line_len = ft_strlen_mod(line);
	buff_len = ft_strlen_mod(buff);
	new_line = malloc ((line_len + buff_len + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	ft_memcpy(new_line, line, line_len);
	ft_memcpy(new_line + line_len, buff, buff_len);
	new_line[line_len + buff_len] = '\0';
	free(line);
	return (new_line);
}
