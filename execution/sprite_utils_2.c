/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:45:13 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:45:14 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_sprite_animations(t_data *data, double current_time)
{
	int					i;
	t_animated_sprite	*sprite;
	double				elapsed;

	if (!data)
		return ;
	i = 0;
	while (i < MAX_SPRITES)
	{
		sprite = &data->sprites[i];
		if (sprite->active && sprite->frame_count > 1)
		{
			elapsed = current_time - sprite->last_frame_time;
			if (elapsed >= sprite->frame_duration)
			{
				sprite->current_frame = (sprite->current_frame + 1)
					% sprite->frame_count;
				sprite->last_frame_time = current_time;
			}
		}
		i++;
	}
}

int	get_sprite_pixel(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (!tex || !tex->addr || x < 0 || x >= tex->width || y < 0
		|| y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void	calculate_sprite_transform(t_data *data, t_animated_sprite *sprite,
		double *transform_x, double *transform_y)
{
	double (sprite_x), (sprite_y), (inv_det);
	sprite_x = sprite->x - data->player.x;
	sprite_y = sprite->y - data->player.y;
	inv_det = 1.0 / (data->player.plane_x * data->player.dir_y
			- data->player.dir_x * data->player.plane_y);
	*transform_x = inv_det * (data->player.dir_y * sprite_x - data->player.dir_x
			* sprite_y);
	*transform_y = inv_det * (-data->player.plane_y * sprite_x
			+ data->player.plane_x * sprite_y);
}

void	free_sprites(t_data *data)
{
	int (i), (j);
	if (!data)
		return ;
	i = 0;
	while (i < MAX_SPRITES)
	{
		if (data->sprites[i].active)
		{
			j = 0;
			while (j < data->sprites[i].frame_count)
			{
				if (data->sprites[i].frames[j].img)
				{
					mlx_destroy_image(data->mlx,
						data->sprites[i].frames[j].img);
					data->sprites[i].frames[j].img = NULL;
				}
				j++;
			}
			data->sprites[i].active = 0;
		}
		i++;
	}
	data->sprite_count = 0;
}
