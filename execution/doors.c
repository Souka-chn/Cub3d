/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:41:06 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:41:07 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_doors(t_data *data)
{
	int		i;
	double	current_time;
	t_door	*door;
	double	delta_time;

	i = 0;
	current_time = get_current_time();
	while (i < data->door_count)
	{
		door = &data->doors[i];
		delta_time = current_time - door->last_time;
		if (door->state == DOOR_OPENING)
			update_opening_door(door, delta_time);
		else if (door->state == DOOR_CLOSING)
			update_closing_door(data, door, delta_time);
		door->last_time = current_time;
		i++;
	}
}

int	is_door_in_front(t_data *data, t_door *door)
{
	double	forward;
	double	side;

	double (dir_x), (dir_y), (dir_len);
	double (dx), (dy);
	dir_x = data->player.dir_x;
	dir_y = data->player.dir_y;
	dir_len = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (dir_len < 1e-6)
		return (0);
	dir_x /= dir_len;
	dir_y /= dir_len;
	dx = (door->x + 0.5) - data->player.x;
	dy = (door->y + 0.5) - data->player.y;
	forward = dx * dir_x + dy * dir_y;
	side = fabs(-dir_y * dx + dir_x * dy);
	if (forward > 0.0 && forward <= DOOR_INTERACT_DISTANCE && side <= 0.6)
		return (1);
	return (0);
}

double	get_forward_distance(t_data *data, t_door *door)
{
	double	dx;
	double	dy;
	double	dir_len;

	dx = (door->x + 0.5) - data->player.x;
	dy = (door->y + 0.5) - data->player.y;
	dir_len = sqrt(data->player.dir_x * data->player.dir_x + data->player.dir_y
			* data->player.dir_y);
	if (dir_len < 1e-6)
		return (1e9);
	return (dx * data->player.dir_x / dir_len + dy * data->player.dir_y
		/ dir_len);
}

void	toggle_door(t_door *door)
{
	if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
	else if (door->state == DOOR_OPEN)
		door->state = DOOR_CLOSING;
	else if (door->state == DOOR_OPENING)
		door->state = DOOR_CLOSING;
	else if (door->state == DOOR_CLOSING)
		door->state = DOOR_OPENING;
}

void	handle_door_interaction(t_data *data)
{
	int		i;
	t_door	*best;
	double	best_forward;
	double	forward;

	i = 0;
	best = NULL;
	best_forward = 1e9;
	while (i < data->door_count)
	{
		if (!((int)data->player.x == data->doors[i].x
				&& (int)data->player.y == data->doors[i].y)
			&& is_door_in_front(data, &data->doors[i]))
		{
			forward = get_forward_distance(data, &data->doors[i]);
			if (forward < best_forward)
			{
				best_forward = forward;
				best = &data->doors[i];
			}
		}
		i++;
	}
	if (best)
		toggle_door(best);
}
