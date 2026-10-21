/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:43:54 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:43:56 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_ceiling(t_data *data, int x, int draw_start, int ceiling_color)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(data, x, y, ceiling_color);
		y++;
	}
}

void	draw_floor(t_data *data, int x, int draw_end, int floor_color)
{
	int	y;

	y = draw_end;
	while (y < WIN_HEIGHT)
	{
		put_pixel(data, x, y, floor_color);
		y++;
	}
}

void	draw_wall_stripe(t_data *data, int x, t_ray *ray, int tex_x)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_texture_color(data, get_texture_index(ray, data), tex_x,
				tex_y);
		put_pixel(data, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_data *data, int x, t_ray *ray)
{
	int	tex_x;
	int	floor_color;
	int	ceiling_color;

	tex_x = calculate_tex_x(data, ray);
	ceiling_color = (data->config->ceil[0] << 16)
		| (data->config->ceil[1] << 8) | data->config->ceil[2];
	floor_color = (data->config->floor[0] << 16)
		| (data->config->floor[1] << 8) | data->config->floor[2];
	draw_ceiling(data, x, ray->draw_start, ceiling_color);
	draw_wall_stripe(data, x, ray, tex_x);
	draw_floor(data, x, ray->draw_end, floor_color);
}

int	render_frame(t_data *data)
{
	double	current_time;

	update_player_movement(data);
	update_doors(data);
	current_time = get_current_time();
	update_sprite_animations(data, current_time);
	cast_rays(data);
	render_sprites(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
