/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:46:33 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:46:35 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_file_lines(int fd, char **lines)
{
	int		n;
	char	*line;

	n = 0;
	while (n < 1024)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines[n] = line;
		n++;
	}
	return (n);
}

int	check_map_line(char *line)
{
	char	*p;

	p = line;
	while (*p && *p != '\n' && *p != '\r')
	{
		if (!ft_strchr(" 01NSEW", *p))
			return (0);
		p++;
	}
	return (1);
}

int	find_map_start(char **lines, int n, t_config *cfg)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < n)
	{
		trim_newline(lines[i]);
		trimmed = skip_spaces(lines[i]);
		if (*trimmed == '\0')
		{
			i++;
			continue ;
		}
		if (*trimmed && !is_identifier_line(trimmed))
		{
			if (check_map_line(lines[i]))
				return (i);
		}
		handle_identifier(trimmed, cfg);
		i++;
	}
	return (-1);
}

void	free_lines_array(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
}

void	parse_file(const char *path, t_config *cfg)
{
	int		fd;
	char	*lines[1024];
	int		n;
	int		map_start;

	if (!validate_file_extension(path))
		print_error("File must have .cub extension");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		print_error("Cannot open file .cub");
	n = read_file_lines(fd, lines);
	close(fd);
	if (n == 0)
		print_error("Empty file");
	map_start = find_map_start(lines, n, cfg);
	if (map_start == -1)
		print_error("No map found");
	validate_config(cfg);
	parse_map(lines, n, map_start, cfg);
	free_lines_array(lines, n);
}
