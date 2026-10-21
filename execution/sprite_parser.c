/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:44:47 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:44:49 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_frames(char **frame_paths)
{
	int	frame_count;

	frame_count = 0;
	while (frame_paths[frame_count] && frame_count < MAX_FRAMES)
		frame_count++;
	return (frame_count);
}

int	find_free_sprite_slot(t_data *data)
{
	int	sprite_idx;

	sprite_idx = 0;
	while (sprite_idx < MAX_SPRITES && data->sprites[sprite_idx].active)
		sprite_idx++;
	if (sprite_idx >= MAX_SPRITES)
		return (-1);
	return (sprite_idx);
}

int	process_sprite_at_position(t_data *data, char **sprite_frames, int x, int y)
{
	double	sprite_x;
	double	sprite_y;
	int		result;

	if (data->config->map[y][x] != 'A')
		return (0);
	sprite_x = (double)x + 0.5;
	sprite_y = (double)y + 0.5;
	result = add_animated_sprite(data, sprite_x, sprite_y, sprite_frames);
	if (result >= 0)
	{
		data->config->map[y][x] = '0';
		return (1);
	}
	return (0);
}

void	parse_sprites_from_map(t_data *data, char **sprite_frames,
		int frame_count)
{
	int	y;
	int	x;
	int	sprite_count;

	if (!data || !data->config || !data->config->map || !sprite_frames)
		return ;
	(void)frame_count;
	sprite_count = 0;
	y = 0;
	while (y < data->config->map_h)
	{
		x = 0;
		while (x < data->config->map_w)
		{
			sprite_count += process_sprite_at_position(data, sprite_frames, x,
					y);
			x++;
		}
		y++;
	}
}

void	init_sprites(t_data *data)
{
	int	i;
	int	j;

	data->sprite_count = 0;
	i = 0;
	while (i < MAX_SPRITES)
	{
		data->sprites[i].active = 0;
		data->sprites[i].x = 0.0;
		data->sprites[i].y = 0.0;
		data->sprites[i].frame_count = 0;
		data->sprites[i].current_frame = 0;
		data->sprites[i].frame_duration = 0.2;
		data->sprites[i].last_frame_time = 0.0;
		j = 0;
		while (j < MAX_FRAMES)
		{
			data->sprites[i].frames[j].img = NULL;
			data->sprites[i].frames[j].addr = NULL;
			data->sprites[i].frames[j].width = 0;
			data->sprites[i].frames[j].height = 0;
			j++;
		}
		i++;
	}
}
