/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:45:24 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:45:26 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_xpm_image(t_data *engine, t_texture *tex, const char *path)
{
	tex->img = mlx_xpm_file_to_image(engine->mlx, (char *)path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		write(STDERR_FILENO, "Error: Failed to load texture ", 31);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(engine->mlx, tex->img);
		tex->img = NULL;
		write(STDERR_FILENO, "Error: Failed to get texture data\n", 35);
		return (0);
	}
	return (1);
}

int	load_texture(t_data *engine, const char *path, int index)
{
	t_texture	*tex;

	if (!engine || !path || index < 0 || index >= 5)
		return (0);
	tex = &engine->textures[index];
	tex->img = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bits_per_pixel = 0;
	tex->line_length = 0;
	tex->endian = 0;
	return (load_xpm_image(engine, tex, path));
}

void	free_textures(t_data *engine)
{
	int	i;

	if (!engine || !engine->mlx)
		return ;
	i = 0;
	while (i < 5)
	{
		if (engine->textures[i].img)
		{
			mlx_destroy_image(engine->mlx, engine->textures[i].img);
			engine->textures[i].img = NULL;
			engine->textures[i].addr = NULL;
		}
		i++;
	}
}

int	load_door_texture(t_data *engine)
{
	if (engine->config->has_do)
	{
		if (!load_texture(engine, engine->config->tex_do, 4))
		{
			free_textures(engine);
			return (0);
		}
	}
	return (1);
}

int	load_all_textures(t_data *engine)
{
	if (!engine || !engine->config)
		return (0);
	if (!load_texture(engine, engine->config->tex_no, 0))
		return (0);
	if (!load_texture(engine, engine->config->tex_so, 1))
	{
		free_textures(engine);
		return (0);
	}
	if (!load_texture(engine, engine->config->tex_we, 2))
	{
		free_textures(engine);
		return (0);
	}
	if (!load_texture(engine, engine->config->tex_ea, 3))
	{
		free_textures(engine);
		return (0);
	}
	return (load_door_texture(engine));
}
