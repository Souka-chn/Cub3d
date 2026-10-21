/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:41:31 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:41:33 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_minimap(t_data *data)
{
	data->minimap.size = MINIMAP_SIZE;
	data->minimap.scale = MINIMAP_SCALE;
	data->minimap.x = MINIMAP_X;
	data->minimap.y = MINIMAP_Y;
	data->minimap.cell_size = MINIMAP_CELL_SIZE;
	data->minimap.player_size = MINIMAP_PLAYER_SIZE;
	data->minimap.view_distance = MINIMAP_VIEW_DISTANCE;
	data->minimap.wall_color = 0x808080;
	data->minimap.floor_color = 0xFFFFFF;
	data->minimap.player_color = 0xFF0000;
	data->minimap.fov_color = 0xFF0000;
	data->minimap.bg_color = 0x000000;
	data->minimap.border_color = 0x404040;
}

void	draw_minimap_cell(t_data *data, int x, int y, int color)
{
	int (pixel_x), (pixel_y), (dx), (dy), (distance_sq);
	int (cell_x), (cell_y), (center_x), (center_y), (radius);
	center_x = data->minimap.x + data->minimap.size / 2;
	center_y = data->minimap.y + data->minimap.size / 2;
	radius = data->minimap.size / 2;
	cell_y = 0;
	while (cell_y < data->minimap.cell_size)
	{
		cell_x = 0;
		while (cell_x < data->minimap.cell_size)
		{
			pixel_x = data->minimap.x + x * data->minimap.cell_size + cell_x;
			pixel_y = data->minimap.y + y * data->minimap.cell_size + cell_y;
			dx = pixel_x - center_x;
			dy = pixel_y - center_y;
			distance_sq = dx * dx + dy * dy;
			if (distance_sq <= radius * radius)
			{
				put_pixel(data, pixel_x, pixel_y, color);
			}
			cell_x++;
		}
		cell_y++;
	}
}

void	draw_player_pixel(t_data *data, int px, int py)
{
	if (px >= data->minimap.x && px < data->minimap.x + data->minimap.size
		&& py >= data->minimap.y && py < data->minimap.y + data->minimap.size)
	{
		put_pixel(data, px, py, data->minimap.player_color);
	}
}

void	draw_player_circle(t_data *data, int px_x, int px_y, int size)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			if (x * x + y * y <= size * size)
			{
				px = px_x + x;
				py = px_y + y;
				draw_player_pixel(data, px, py);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_data *data)
{
	int	half_scale;
	int	player_map_x;
	int	player_map_y;

	double (frac_x), (frac_y);
	int (player_pixel_x), (player_pixel_y);
	half_scale = data->minimap.scale / 2;
	player_map_x = (int)data->player.x;
	player_map_y = (int)data->player.y;
	frac_x = data->player.x - player_map_x;
	frac_y = data->player.y - player_map_y;
	player_pixel_x = data->minimap.x + (half_scale * data->minimap.cell_size)
		+ (int)(frac_x * data->minimap.cell_size);
	player_pixel_y = data->minimap.y + (half_scale * data->minimap.cell_size)
		+ (int)(frac_y * data->minimap.cell_size);
	draw_player_circle(data, player_pixel_x, player_pixel_y,
		data->minimap.player_size);
}
