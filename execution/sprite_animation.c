/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:44:32 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:44:33 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_sprite_dimensions(int *sprite_screen_x,
		int *sprite_height, int *sprite_width, t_data *data)
{
	double	transform_x;
	double	transform_y;

	transform_x = data->temp_transform_x;
	transform_y = data->temp_transform_y;
	*sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));
	*sprite_height = abs((int)(WIN_HEIGHT / transform_y));
	*sprite_width = abs((int)(WIN_HEIGHT / transform_y));
}

void	calculate_draw_bounds(int sprite_height, int sprite_width,
		int sprite_screen_x, int bounds[4])
{
	bounds[0] = -sprite_height / 2 + WIN_HEIGHT / 2;
	if (bounds[0] < 0)
		bounds[0] = 0;
	bounds[1] = sprite_height / 2 + WIN_HEIGHT / 2;
	if (bounds[1] >= WIN_HEIGHT)
		bounds[1] = WIN_HEIGHT - 1;
	bounds[2] = -sprite_width / 2 + sprite_screen_x;
	if (bounds[2] < 0)
		bounds[2] = 0;
	bounds[3] = sprite_width / 2 + sprite_screen_x;
	if (bounds[3] >= WIN_WIDTH)
		bounds[3] = WIN_WIDTH - 1;
}

void	render_sprite_column(t_data *data, t_texture *frame, int stripe,
		int bounds[4])
{
	double	transform_y;

	int (tex_x), (y), (d), (tex_y), (color), (s_w), (s_h), (sprite_screen_x);
	s_w = data->temp_sprite_width;
	s_h = data->temp_sprite_height;
	sprite_screen_x = data->temp_sprite_screen_x;
	transform_y = data->temp_transform_y;
	tex_x = (int)(256 * (stripe - (-s_w / 2 + sprite_screen_x))
			* frame->width / s_w) / 256;
	if (transform_y <= 0 || stripe <= 0 || stripe >= WIN_WIDTH || tex_x < 0
		|| tex_x >= frame->width || transform_y >= data->z_buffer[stripe])
		return ;
	y = bounds[0];
	while (y < bounds[1])
	{
		d = y * 256 - WIN_HEIGHT * 128 + s_h * 128;
		tex_y = ((d * frame->height) / s_h) / 256;
		if (tex_y >= 0 && tex_y < frame->height)
		{
			color = get_sprite_pixel(frame, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(data, stripe, y, color);
		}
		y++;
	}
}

void	render_single_sprite(t_data *data, t_animated_sprite *sprite)
{
	int			bounds[4];
	t_texture	*current_frame;

	double (transform_x), (transform_y);
	int (sprite_screen_x), (sprite_height), (sprite_width), (stripe);
	if (!sprite->active || sprite->frame_count == 0)
		return ;
	current_frame = &sprite->frames[sprite->current_frame];
	calculate_sprite_transform(data, sprite, &transform_x, &transform_y);
	if (transform_y <= 0.1)
		return ;
	data->temp_transform_x = transform_x;
	data->temp_transform_y = transform_y;
	calculate_sprite_dimensions(&sprite_screen_x, &sprite_height,
		&sprite_width, data);
	data->temp_sprite_width = sprite_width;
	data->temp_sprite_height = sprite_height;
	data->temp_sprite_screen_x = sprite_screen_x;
	calculate_draw_bounds(sprite_height, sprite_width, sprite_screen_x, bounds);
	stripe = bounds[2];
	while (stripe < bounds[3])
	{
		render_sprite_column(data, current_frame, stripe, bounds);
		stripe++;
	}
}

void	render_sprites(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < MAX_SPRITES)
	{
		if (data->sprites[i].active)
			render_single_sprite(data, &data->sprites[i]);
		i++;
	}
}
