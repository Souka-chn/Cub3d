/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:42:45 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:42:52 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	check_hit(t_data *data, t_ray *ray)
{
	char	map_char;

	if (ray->map_x < 0 || ray->map_x >= data->config->map_w || ray->map_y < 0
		|| ray->map_y >= data->config->map_h)
		ray->hit = 1;
	else
	{
		map_char = data->config->map[ray->map_y][ray->map_x];
		if (map_char == '1')
			ray->hit = 1;
		else if (map_char == 'D')
		{
			if (is_door_blocking(data, ray->map_x, ray->map_y))
				ray->hit = 1;
		}
		else if (map_char != '0' && map_char != ' ' && map_char != 'N'
			&& map_char != 'S' && map_char != 'E' && map_char != 'W'
			&& map_char != 'A')
			ray->hit = 1;
	}
}

void	calculate_draw_limits(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		dda_step(ray);
		check_hit(data, ray);
	}
	calculate_draw_limits(data, ray);
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		calculate_step_and_side_dist(data, &ray);
		perform_dda(data, &ray);
		data->z_buffer[x] = ray.perp_wall_dist;
		draw_vertical_line(data, x, &ray);
		x++;
	}
}
