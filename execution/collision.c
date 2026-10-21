/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:40:03 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:40:08 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_wall_at(t_data *data, int map_x, int map_y)
{
	char	cell;

	if (map_x < 0 || map_x >= data->config->map_w || map_y < 0
		|| map_y >= data->config->map_h)
		return (1);
	cell = data->config->map[map_y][map_x];
	if (cell == '1')
		return (1);
	if (cell == 'D')
		return (is_door_blocking(data, map_x, map_y));
	return (0);
}

int	check_collision_raycast(t_data *data, double from_x, double from_y,
		double to_x)
{
	double (dx), (dy), (distance), (check_x), (check_y), (to_y);
	int (steps), (i);
	to_y = data->player.move_to_y;
	dx = to_x - from_x;
	dy = to_y - from_y;
	distance = sqrt(dx * dx + dy * dy);
	steps = (int)(distance * 20);
	if (steps == 0)
		return (0);
	dx /= steps;
	dy /= steps;
	i = 0;
	while (i <= steps)
	{
		check_x = from_x + dx * i;
		check_y = from_y + dy * i;
		if (is_wall_at(data, (int)check_x, (int)check_y))
			return (1);
		i++;
	}
	return (0);
}

int	check_collision(t_data *data, double x, double y)
{
	double	radius;
	int		i;
	double	angle;
	double	check_x;
	double	check_y;

	radius = 0.15;
	if (is_wall_at(data, (int)x, (int)y))
		return (1);
	i = 0;
	while (i < 8)
	{
		angle = i * 2.0 * M_PI / 8.0;
		check_x = x + cos(angle) * radius;
		check_y = y + sin(angle) * radius;
		if (is_wall_at(data, (int)check_x, (int)check_y))
			return (1);
		i++;
	}
	return (0);
}

double	distance_to_wall(t_data *data, double x, double y, double dir_x)
{
	double	distance;
	double	step;
	double	check_x;
	double	check_y;
	double	dir_y;

	dir_y = data->player.temp_dir_y;
	distance = 0.0;
	step = 0.01;
	while (distance < 1.0)
	{
		check_x = x + dir_x * distance;
		check_y = y + dir_y * distance;
		if (is_wall_at(data, (int)check_x, (int)check_y))
			return (distance);
		distance += step;
	}
	return (1.0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	int	delta_x;

	if (data->mouse.first_move)
	{
		data->mouse.last_x = x;
		data->mouse.last_y = y;
		data->mouse.first_move = 0;
		return (0);
	}
	delta_x = x - data->mouse.last_x;
	if (delta_x != 0)
		rotate_with_mouse(data, delta_x);
	data->mouse.last_x = x;
	data->mouse.last_y = y;
	return (0);
}
