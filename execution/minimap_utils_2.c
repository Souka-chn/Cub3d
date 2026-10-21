/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:41:42 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:41:43 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_fov_line(t_data *data, int px_x, int px_y, int end_x)
{
	int		i;
	double	t;
	int		px;
	int		py;
	int		end_y;

	end_y = data->minimap.temp_end_y;
	i = 0;
	while (i <= 20)
	{
		t = i / 20.0;
		px = px_x + (int)((end_x - px_x) * t);
		py = px_y + (int)((end_y - px_y) * t);
		if (px >= data->minimap.x && px < data->minimap.x + data->minimap.size
			&& py >= data->minimap.y && py < data->minimap.y
			+ data->minimap.size)
			put_pixel(data, px, py, 0xFF0000);
		i++;
	}
}

void	calc_fov_endpoints(t_data *data, int *ends, int px_x, int px_y)
{
	double (left_angle), (right_angle);
	double (left_dir_x), (left_dir_y);
	double (right_dir_x), (right_dir_y);
	left_angle = -0.25;
	right_angle = 0.25;
	left_dir_x = data->player.dir_x * cos(left_angle) - data->player.dir_y
		* sin(left_angle);
	left_dir_y = data->player.dir_x * sin(left_angle) + data->player.dir_y
		* cos(left_angle);
	right_dir_x = data->player.dir_x * cos(right_angle) - data->player.dir_y
		* sin(right_angle);
	right_dir_y = data->player.dir_x * sin(right_angle) + data->player.dir_y
		* cos(right_angle);
	ends[0] = px_x + (int)(left_dir_x * 30);
	ends[1] = px_y + (int)(left_dir_y * 30);
	ends[2] = px_x + (int)(right_dir_x * 30);
	ends[3] = px_y + (int)(right_dir_y * 30);
}

void	draw_minimap_fov(t_data *data)
{
	int	half_scale;
	int	player_pixel_x;
	int	player_pixel_y;
	int	ends[4];

	half_scale = data->minimap.scale / 2;
	player_pixel_x = data->minimap.x + (half_scale * data->minimap.cell_size)
		+ (int)((data->player.x - (int)data->player.x)
			* data->minimap.cell_size);
	player_pixel_y = data->minimap.y + (half_scale * data->minimap.cell_size)
		+ (int)((data->player.y - (int)data->player.y)
			* data->minimap.cell_size);
	calc_fov_endpoints(data, ends, player_pixel_x, player_pixel_y);
	data->minimap.temp_end_y = ends[1];
	draw_fov_line(data, player_pixel_x, player_pixel_y, ends[0]);
	data->minimap.temp_end_y = ends[3];
	draw_fov_line(data, player_pixel_x, player_pixel_y, ends[2]);
}

void	draw_border_pixel(t_data *data, int cx, int cy)
{
	int	px;
	int	py;

	px = cx;
	py = cy;
	if (px >= 0 && px < WIN_WIDTH && py >= 0 && py < WIN_HEIGHT)
		put_pixel(data, px, py, data->minimap.border_color);
}

int	is_border_pixel(int x, int y, int radius)
{
	int	distance_sq;
	int	outer_radius;
	int	inner_radius;

	distance_sq = x * x + y * y;
	outer_radius = radius + 2;
	inner_radius = radius - 1;
	if (distance_sq >= inner_radius * inner_radius
		&& distance_sq <= outer_radius * outer_radius)
		return (1);
	return (0);
}
