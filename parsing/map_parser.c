/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:46:15 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:46:17 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pad_map_line(char **line, int len, int maxw)
{
	char	*new;

	if (len < maxw)
	{
		new = malloc(maxw + 1);
		ft_memcpy(new, *line, len);
		ft_memset(new + len, ' ', maxw - len);
		new[maxw] = '\0';
		free(*line);
		*line = new;
	}
}

void	pad_map(t_config *cfg)
{
	int	maxw;
	int	i;
	int	len;

	maxw = find_max_width(cfg);
	cfg->map_w = maxw;
	i = 0;
	while (i < cfg->map_h)
	{
		len = ft_strlen(cfg->map[i]);
		pad_map_line(&cfg->map[i], len, maxw);
		i++;
	}
}

int	find_map_end(char **lines, int n, int start)
{
	int	map_end;
	int	len;

	map_end = n - 1;
	while (map_end >= start)
	{
		len = ft_strlen(lines[map_end]);
		while (len > 0 && (lines[map_end][len - 1] == '\n' || lines[map_end][len
			- 1] == '\r'))
			len--;
		if (len > 0)
			break ;
		map_end--;
	}
	return (map_end);
}

void	parse_map_line(t_config *cfg, char **lines, int start, int i)
{
	char	*line;
	int		len;

	line = lines[start + i];
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	if (len == 0)
		print_error("Empty line found in map");
	cfg->map[i] = malloc(len + 1);
	if (!cfg->map[i])
		print_error("Memory allocation failed for map line");
	ft_memcpy(cfg->map[i], line, len);
	cfg->map[i][len] = '\0';
}

void	parse_map(char **lines, int n, int start, t_config *cfg)
{
	int	map_end;
	int	i;

	map_end = find_map_end(lines, n, start);
	cfg->map_h = map_end - start + 1;
	cfg->map = malloc(sizeof(char *) * cfg->map_h);
	if (!cfg->map)
		print_error("Memory allocation failed for map");
	i = 0;
	while (i < cfg->map_h)
	{
		parse_map_line(cfg, lines, start, i);
		i++;
	}
	pad_map(cfg);
	validate_map(cfg);
}
