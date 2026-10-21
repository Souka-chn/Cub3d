/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:42:07 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:42:09 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_minimap_border(t_data *data)
{
	int	center_x;
	int	center_y;
	int	radius;
	int	x;
	int	y;

	center_x = data->minimap.x + data->minimap.size / 2;
	center_y = data->minimap.y + data->minimap.size / 2;
	radius = data->minimap.size / 2;
	y = -radius - 2;
	while (y <= radius + 2)
	{
		x = -radius - 2;
		while (x <= radius + 2)
		{
			if (is_border_pixel(x, y, radius))
				draw_border_pixel(data, center_x + x, center_y + y);
			x++;
		}
		y++;
	}
}

void	draw_background(t_data *data)
{
	int	minimap_x;
	int	minimap_y;

	minimap_y = 0;
	while (minimap_y < data->minimap.scale)
	{
		minimap_x = 0;
		while (minimap_x < data->minimap.scale)
		{
			draw_minimap_cell(data, minimap_x, minimap_y,
				data->minimap.bg_color);
			minimap_x++;
		}
		minimap_y++;
	}
}

void	draw_map_cell_type(t_data *data, char cell, int mm_x, int mm_y)
{
	t_door	*door;

	if (cell == '1')
		draw_minimap_cell(data, mm_x, mm_y, data->minimap.wall_color);
	else if (cell == 'D')
	{
		door = get_door_at_position(data, mm_x, mm_y);
		if (door && door->state == DOOR_OPEN)
			draw_minimap_cell(data, mm_x, mm_y, 0x00FF00);
		else
			draw_minimap_cell(data, mm_x, mm_y, 0x800000);
	}
	else if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E'
		|| cell == 'W')
		draw_minimap_cell(data, mm_x, mm_y, data->minimap.floor_color);
}

void	draw_map_tiles(t_data *data, int pl_x, int pl_y, int half)
{
	int	minimap_x;
	int	minimap_y;
	int	map_x;
	int	map_y;

	minimap_y = 0;
	while (minimap_y < data->minimap.scale)
	{
		minimap_x = 0;
		while (minimap_x < data->minimap.scale)
		{
			map_x = pl_x - half + minimap_x;
			map_y = pl_y - half + minimap_y;
			if (map_x >= 0 && map_x < data->config->map_w && map_y >= 0
				&& map_y < data->config->map_h)
				draw_map_cell_type(data, data->config->map[map_y][map_x],
					minimap_x, minimap_y);
			else
				draw_minimap_cell(data, minimap_x, minimap_y, 0x101010);
			minimap_x++;
		}
		minimap_y++;
	}
}

void	render_minimap(t_data *data)
{
	int	half_scale;
	int	player_map_x;
	int	player_map_y;

	half_scale = data->minimap.scale / 2;
	player_map_x = (int)data->player.x;
	player_map_y = (int)data->player.y;
	draw_background(data);
	draw_map_tiles(data, player_map_x, player_map_y, half_scale);
	draw_minimap_fov(data);
	draw_minimap_player(data);
	draw_minimap_border(data);
}
