/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:43:25 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:43:26 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_east_west_direction(t_data *data, t_config *cfg)
{
	if (cfg->player_dir == 'E')
	{
		data->player.dir_x = 1.0;
		data->player.dir_y = 0.0;
		data->player.plane_x = 0.0;
		data->player.plane_y = 0.66;
	}
	else if (cfg->player_dir == 'W')
	{
		data->player.dir_x = -1.0;
		data->player.dir_y = 0.0;
		data->player.plane_x = 0.0;
		data->player.plane_y = -0.66;
	}
}

void	init_player(t_data *data)
{
	t_config	*cfg;

	cfg = data->config;
	data->player.x = (double)cfg->player_x + 0.5;
	data->player.y = (double)cfg->player_y + 0.5;
	if (cfg->player_dir == 'N')
	{
		data->player.dir_x = 0.0;
		data->player.dir_y = -1.0;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0.0;
	}
	else if (cfg->player_dir == 'S')
	{
		data->player.dir_x = 0.0;
		data->player.dir_y = 1.0;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0.0;
	}
	else
		set_east_west_direction(data, cfg);
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	calculate_step_and_side_dist(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y)
			* ray->delta_dist_y;
	}
}

int	get_texture_index(t_ray *ray, t_data *data)
{
	char	map_char;

	map_char = data->config->map[ray->map_y][ray->map_x];
	if (map_char == 'D')
		return (4);
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->step_y > 0)
			return (1);
		else
			return (0);
	}
}
