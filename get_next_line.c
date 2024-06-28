/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrochow <staafnet@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:36:05 by rgrochow          #+#    #+#             */
/*   Updated: 2024/06/28 20:03:32 by rgrochow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_add(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static char	*ft_get_line(char **str)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
		i++;
	line = ft_strndup(*str, i);
	if (!line || !(*str)[i])
	{
		free(*str);
		*str = NULL;
	}
	else if ((*str)[i])
	{
		tmp = ft_strdup(*str + i);
		free(*str);
		*str = tmp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	static char	buf[BUFFER_SIZE + 1];
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		size = read(fd, buf, BUFFER_SIZE);
		buf[size] = '\0';
		str = ft_add(str, buf);
		if (size <= 0 || ft_strchr(str, '\n'))
			break ;
	}
	if (size < 0 || (size == 0 && (!str || *str == '\0')))
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	return (ft_get_line(&str));
}
