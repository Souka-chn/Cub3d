/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:46:24 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:46:25 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_max_width(t_config *cfg)
{
	int	maxw;
	int	i;
	int	len;

	maxw = 0;
	i = 0;
	while (i < cfg->map_h)
	{
		len = ft_strlen(cfg->map[i]);
		if (len > maxw)
			maxw = len;
		i++;
	}
	return (maxw);
}

int	count_players(t_config *cfg)
{
	char	ch;

	int (player_count), (r), (c);
	player_count = 0;
	r = 0;
	while (r < cfg->map_h)
	{
		c = 0;
		while (c < cfg->map_w)
		{
			ch = cfg->map[r][c];
			if (!ft_strchr(" 01NSEWDA", ch))
				print_error("Invalid character in map");
			if (ft_strchr("NSEW", ch))
			{
				player_count++;
				cfg->player_x = c;
				cfg->player_y = r;
				cfg->player_dir = ch;
			}
			c++;
		}
		r++;
	}
	return (player_count);
}

void	check_cell_closed(t_config *cfg, int r, int c)
{
	char	up;
	char	down;
	char	left;
	char	right;
	char	*msg;

	if (r == 0 || c == 0 || r == cfg->map_h - 1 || c == cfg->map_w - 1)
		print_error("Map not closed: player or empty space at border");
	up = cfg->map[r - 1][c];
	down = cfg->map[r + 1][c];
	left = cfg->map[r][c - 1];
	right = cfg->map[r][c + 1];
	if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
	{
		msg = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("Map not closed at (",
							ft_itoa(c)), ", "), ft_itoa(r)), ")");
		print_error(msg);
	}
}

void	check_map_closed(t_config *cfg)
{
	int		r;
	int		c;
	char	ch;

	r = 0;
	while (r < cfg->map_h)
	{
		c = 0;
		while (c < cfg->map_w)
		{
			ch = cfg->map[r][c];
			if (ch == '0' || ch == 'D' || ch == 'A' || ft_strchr("NSEW", ch))
				check_cell_closed(cfg, r, c);
			c++;
		}
		r++;
	}
}

void	validate_map(t_config *cfg)
{
	if (count_players(cfg) != 1)
		print_error("Map must have exactly one player");
	check_map_closed(cfg);
}
