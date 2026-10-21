/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:47:04 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:47:06 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_file_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".cub", 4));
}

int	validate_texture_file(const char *path)
{
	int	fd;

	if (!path || !*path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void	validate_all_textures(t_config *cfg)
{
	if (!validate_texture_file(cfg->tex_no))
		print_error("North texture file not found or not readable");
	if (!validate_texture_file(cfg->tex_so))
		print_error("South texture file not found or not readable");
	if (!validate_texture_file(cfg->tex_we))
		print_error("West texture file not found or not readable");
	if (!validate_texture_file(cfg->tex_ea))
		print_error("East texture file not found or not readable");
	if (cfg->has_do && !validate_texture_file(cfg->tex_do))
		print_error("Door texture file not found or not readable");
}

void	validate_config(t_config *cfg)
{
	if (!cfg->has_no || !cfg->has_so || !cfg->has_we || !cfg->has_ea
		|| !cfg->has_f || !cfg->has_c)
		print_error("Missing identifier(s)");
	validate_all_textures(cfg);
}

void	free_config(t_config *cfg)
{
	int	i;

	if (!cfg)
		return ;
	free(cfg->tex_no);
	free(cfg->tex_so);
	free(cfg->tex_we);
	free(cfg->tex_ea);
	free(cfg->tex_do);
	if (cfg->map)
	{
		i = 0;
		while (i < cfg->map_h)
		{
			free(cfg->map[i]);
			i++;
		}
		free(cfg->map);
	}
	ft_memset(cfg, 0, sizeof(t_config));
}
