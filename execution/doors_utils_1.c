/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:40:43 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:40:44 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_doors(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_DOORS)
	{
		data->doors[i].x = -1;
		data->doors[i].y = -1;
		data->doors[i].state = DOOR_CLOSED;
		data->doors[i].progress = 0.0;
		data->doors[i].last_time = 0.0;
		i++;
	}
	data->door_count = 0;
}

void	parse_doors_from_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	data->door_count = 0;
	while (y < data->config->map_h && data->door_count < MAX_DOORS)
	{
		x = 0;
		while (x < data->config->map_w && data->door_count < MAX_DOORS)
		{
			if (data->config->map[y][x] == 'D')
			{
				data->doors[data->door_count].x = x;
				data->doors[data->door_count].y = y;
				data->doors[data->door_count].state = DOOR_CLOSED;
				data->doors[data->door_count].progress = 0.0;
				data->doors[data->door_count].last_time = get_current_time();
				data->door_count++;
			}
			x++;
		}
		y++;
	}
}

t_door	*get_door_at_position(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

int	is_door_blocking(t_data *data, int x, int y)
{
	t_door	*door;

	door = get_door_at_position(data, x, y);
	if (!door)
		return (0);
	return (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING
		|| (door->state == DOOR_OPENING && door->progress < 0.8));
}

double	get_door_openness(t_data *data, int x, int y)
{
	t_door	*door;

	door = get_door_at_position(data, x, y);
	if (!door)
		return (0.0);
	if (door->state == DOOR_CLOSED)
		return (0.0);
	else if (door->state == DOOR_OPEN)
		return (1.0);
	else
		return (door->progress);
}
