/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:42:22 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:42:23 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	apply_movement(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + move_x;
	new_y = data->player.y + move_y;
	data->player.move_to_y = new_y;
	if (!check_collision_raycast(data, data->player.x, data->player.y, new_x)
		&& !check_collision(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
	}
	else if (!check_collision(data, new_x, data->player.y))
		data->player.x = new_x;
	else if (!check_collision(data, data->player.x, new_y))
		data->player.y = new_y;
	else if (!check_collision(data, data->player.x + move_x * 0.3,
			data->player.y))
		data->player.x += move_x * 0.3;
	else if (!check_collision(data, data->player.x, data->player.y + move_y
			* 0.3))
		data->player.y += move_y * 0.3;
}

void	move_player(t_data *data, double move_x, double move_y)
{
	double	move_length;
	double	wall_dist;
	double	speed_factor;

	move_length = sqrt(move_x * move_x + move_y * move_y);
	if (move_length == 0)
		return ;
	data->player.temp_dir_y = move_y / move_length;
	wall_dist = distance_to_wall(data, data->player.x, data->player.y, move_x
			/ move_length);
	speed_factor = 1.0;
	if (wall_dist < 0.3)
		speed_factor = wall_dist / 0.3;
	apply_movement(data, move_x * speed_factor, move_y * speed_factor);
}

void	rotate_player(t_data *data, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(rot_speed)
		- data->player.dir_y * sin(rot_speed);
	data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y
		* cos(rot_speed);
	data->player.plane_x = data->player.plane_x * cos(rot_speed)
		- data->player.plane_y * sin(rot_speed);
	data->player.plane_y = old_plane_x * sin(rot_speed) + data->player.plane_y
		* cos(rot_speed);
}

void	handle_movement_keys(t_data *data)
{
	double	move_x;
	double	move_y;

	if (data->keys.s)
	{
		move_x = -data->player.dir_x * MOVE_SPEED;
		move_y = -data->player.dir_y * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	if (data->keys.a)
	{
		move_x = -data->player.plane_x * MOVE_SPEED;
		move_y = -data->player.plane_y * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	if (data->keys.d)
	{
		move_x = data->player.plane_x * MOVE_SPEED;
		move_y = data->player.plane_y * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
}

void	update_player_movement(t_data *data)
{
	double	move_x;
	double	move_y;

	if (data->keys.esc)
		exit(0);
	if (data->keys.left)
		rotate_player(data, -ROT_SPEED);
	if (data->keys.right)
		rotate_player(data, ROT_SPEED);
	if (data->keys.w)
	{
		move_x = data->player.dir_x * MOVE_SPEED;
		move_y = data->player.dir_y * MOVE_SPEED;
		move_player(data, move_x, move_y);
	}
	handle_movement_keys(data);
}
