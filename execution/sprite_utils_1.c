/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:45:00 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:45:04 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprite_properties(t_data *data, int idx, double x)
{
	double	y;
	int		frame_count;

	y = data->temp_sprite_y;
	frame_count = data->temp_frame_count;
	data->sprites[idx].x = x;
	data->sprites[idx].y = y;
	data->sprites[idx].frame_count = frame_count;
	data->sprites[idx].current_frame = 0;
	data->sprites[idx].frame_duration = 0.15;
	data->sprites[idx].last_frame_time = get_current_time();
}

void	cleanup_sprite_frames(t_data *data, int sprite_idx, int up_to)
{
	while (--up_to >= 0)
	{
		if (data->sprites[sprite_idx].frames[up_to].img)
			mlx_destroy_image(data->mlx,
				data->sprites[sprite_idx].frames[up_to].img);
	}
}

int	load_sprite_frame(t_data *data, int sprite_idx, int i, char *path)
{
	t_texture	*tex;

	tex = &data->sprites[sprite_idx].frames[i];
	tex->img = mlx_xpm_file_to_image(data->mlx, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		write(STDERR_FILENO, "Error: Failed to load sprite frame ", 36);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		cleanup_sprite_frames(data, sprite_idx, i);
		return (-1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		write(STDERR_FILENO, "Error: Failed to get sprite data\n", 33);
		mlx_destroy_image(data->mlx, tex->img);
		cleanup_sprite_frames(data, sprite_idx, i);
		return (-1);
	}
	return (0);
}

int	load_all_frames(t_data *data, int sprite_idx, char **frame_paths,
		int frame_count)
{
	int	i;

	i = 0;
	while (i < frame_count)
	{
		if (load_sprite_frame(data, sprite_idx, i, frame_paths[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	add_animated_sprite(t_data *data, double x, double y, char **frame_paths)
{
	int	sprite_idx;
	int	frame_count;

	if (!data || !frame_paths)
		return (-1);
	frame_count = count_frames(frame_paths);
	if (frame_count <= 0 || data->sprite_count >= MAX_SPRITES)
		return (-1);
	sprite_idx = find_free_sprite_slot(data);
	if (sprite_idx == -1)
		return (-1);
	data->temp_sprite_y = y;
	data->temp_frame_count = frame_count;
	init_sprite_properties(data, sprite_idx, x);
	if (load_all_frames(data, sprite_idx, frame_paths, frame_count) == -1)
		return (-1);
	data->sprites[sprite_idx].active = 1;
	data->sprite_count++;
	return (sprite_idx);
}
