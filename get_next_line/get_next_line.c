/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deddaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:27:55 by deddaidi          #+#    #+#             */
/*   Updated: 2024/12/05 20:30:13 by deddaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *buf)
{
	ssize_t	b;
	char	*line;

	b = 1;
	line = (char *)malloc(BUFFER_SIZE + 1);
	while (b != 0)
	{
		b = read(fd, line, BUFFER_SIZE);
		if (b == -1)
		{
			free(line);
			return (NULL);
		}
		line[b] = '\0';
		buf = ft_strjoin_g(buf, line);
		if (check_newline(line))
			break ;
	}
	free(line);
	return (buf);
}

char	*sub_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] && buf[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*clean(char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] && buf[i] == '\n')
		i++;
	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	str = malloc((ft_strlen(buf) - i) + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (buf[i])
		str[j++] = buf[i++];
	str[j] = '\0';
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = sub_line(buffer);
	buffer = clean(buffer);
	if (line == NULL)
		free(buffer);
	return (line);
}
