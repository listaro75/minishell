/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhanarte <mhanarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:37:17 by mhanarte          #+#    #+#             */
/*   Updated: 2025/04/24 13:33:00 by mhanarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *s1, char *s2)
{
	char	*temp;

	if (!s1 && !s2)
		return (NULL);
	temp = ft_strjoin(s1, s2);
	if (!temp)
	{
		free(s2);
		return (NULL);
	}
	free(s1);
	return (temp);
}

char	*new_rest(char *rest)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (!rest)
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	if (!rest[i])
		return (free(rest), NULL);
	temp = NULL;
	if (ft_strlen(rest) - i > 0)
		temp = ft_calloc((ft_strlen(rest) - i), sizeof(char));
	if (!temp)
		return (free(rest), NULL);
	j = 0;
	i++;
	while (rest[i])
		temp[j++] = rest[i++];
	return (free(rest), temp);
}

char	*new_line(char *rest, char *line)
{
	int	i;

	i = 0;
	if (!rest[i] || !rest)
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	line = ft_calloc((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (rest[i] != '\n' && rest[i])
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *rest)
{
	char	*buffer;
	int		byte;

	if (!rest)
		rest = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(rest), NULL);
	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
			return (free(buffer), free(rest), NULL);
		buffer[byte] = '\0';
		rest = ft_free(rest, buffer);
		if (!rest)
			return (free(buffer), NULL);
		if (ft_strchr(rest, '\n'))
			break ;
	}
	return (free(buffer), rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest[4096];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest[fd] = read_file(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	line = new_line(rest[fd], line);
	if (!line)
	{
		free(rest[fd]);
		rest[fd] = NULL;
		return (NULL);
	}
	rest[fd] = new_rest(rest[fd]);
	if (!rest[fd] || rest[fd][0] == '\0')
	{
		free(rest[fd]);
		rest[fd] = NULL;
	}
	return (line);
}
