/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:40:24 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:40:28 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_keys(t_data *data)
{
	data->keys.w = 0;
	data->keys.s = 0;
	data->keys.a = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
	data->keys.esc = 0;
	data->keys.e = 0;
}

int	handle_key_press(int key, t_data *data)
{
	if (key == KEY_W)
		data->keys.w = 1;
	else if (key == KEY_S)
		data->keys.s = 1;
	else if (key == KEY_A)
		data->keys.a = 1;
	else if (key == KEY_D)
		data->keys.d = 1;
	else if (key == KEY_LEFT)
		data->keys.left = 1;
	else if (key == KEY_RIGHT)
		data->keys.right = 1;
	else if (key == KEY_ESC)
		data->keys.esc = 1;
	else if (key == KEY_E)
	{
		data->keys.e = 1;
		handle_door_interaction(data);
	}
	return (0);
}

int	handle_key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->keys.w = 0;
	else if (key == KEY_S)
		data->keys.s = 0;
	else if (key == KEY_A)
		data->keys.a = 0;
	else if (key == KEY_D)
		data->keys.d = 0;
	else if (key == KEY_LEFT)
		data->keys.left = 0;
	else if (key == KEY_RIGHT)
		data->keys.right = 0;
	else if (key == KEY_ESC)
		data->keys.esc = 0;
	else if (key == KEY_E)
		data->keys.e = 0;
	return (0);
}

void	init_mouse(t_data *data)
{
	data->mouse.x = WIN_WIDTH / 2;
	data->mouse.y = WIN_HEIGHT / 2;
	data->mouse.last_x = WIN_WIDTH / 2;
	data->mouse.last_y = WIN_HEIGHT / 2;
	data->mouse.first_move = 1;
	data->mouse.ignore_next = 0;
}

void	rotate_with_mouse(t_data *data, int delta_x)
{
	double	rotation_angle;

	if (delta_x > 50)
		delta_x = 50;
	else if (delta_x < -50)
		delta_x = -50;
	rotation_angle = delta_x * MOUSE_SENSITIVITY;
	rotate_player(data, rotation_angle);
}
