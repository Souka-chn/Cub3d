/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:44:09 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:44:11 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->img_addr + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_data *data, int tex_index, int tex_x, int tex_y)
{
	t_texture	*tex;
	char		*pixel;

	if (tex_index < 0 || tex_index >= 5)
		return (0);
	tex = &data->textures[tex_index];
	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height)
		return (0);
	pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel
				/ 8));
	return (*(int *)pixel);
}

int	calculate_tex_x(t_data *data, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = data->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = data->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}
