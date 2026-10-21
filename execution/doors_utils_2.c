/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:40:55 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:40:56 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

int	is_door_at_position(t_data *data, int x, int y)
{
	return (get_door_at_position(data, x, y) != NULL);
}

void	update_opening_door(t_door *door, double delta_time)
{
	door->progress += DOOR_SPEED * delta_time * 60.0;
	if (door->progress >= 1.0)
	{
		door->progress = 1.0;
		door->state = DOOR_OPEN;
	}
}

void	update_closing_door(t_data *data, t_door *door, double delta_time)
{
	double	px;
	double	py;
	double	dist;

	px = data->player.x;
	py = data->player.y;
	dist = sqrt((px - (door->x + 0.5)) * (px - (door->x + 0.5)) + (py - (door->y
					+ 0.5)) * (py - (door->y + 0.5)));
	if ((int)px == door->x && (int)py == door->y)
		door->state = DOOR_OPENING;
	else if (dist < 0.65)
		door->state = DOOR_OPENING;
	else
	{
		door->progress -= DOOR_SPEED * delta_time * 60.0;
		if (door->progress <= 0.0)
		{
			door->progress = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
}
