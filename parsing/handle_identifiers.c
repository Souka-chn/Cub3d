/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_identifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:46:06 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:46:07 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *line, int out[3])
{
	if (!validate_color(line, out))
		print_error("Invalid color format. Expected: R,G,B with values 0-255");
}

void	handle_other_identifiers(char *line, t_config *cfg)
{
	if (!ft_strncmp(line, "DO ", 3) || (!ft_strncmp(line, "DO", 2)
			&& (line[2] == '\t' || line[2] == '\0')))
	{
		if (cfg->has_do)
			print_error("Duplicate DO");
		cfg->tex_do = strdup_trim(line + 2);
		cfg->has_do = 1;
	}
	else if (*line == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (cfg->has_f)
			print_error("Duplicate F");
		parse_color(line + 1, cfg->floor);
		cfg->has_f = 1;
	}
	else if (*line == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		if (cfg->has_c)
			print_error("Duplicate C");
		parse_color(line + 1, cfg->ceil);
		cfg->has_c = 1;
	}
}

void	handle_remaining_identifiers(char *line, t_config *cfg)
{
	if (!ft_strncmp(line, "WE ", 3) || (!ft_strncmp(line, "WE", 2)
			&& (line[2] == '\t' || line[2] == '\0')))
	{
		if (cfg->has_we)
			print_error("Duplicate WE");
		cfg->tex_we = strdup_trim(line + 2);
		cfg->has_we = 1;
	}
	else if (!ft_strncmp(line, "EA ", 3) || (!ft_strncmp(line, "EA", 2)
			&& (line[2] == '\t' || line[2] == '\0')))
	{
		if (cfg->has_ea)
			print_error("Duplicate EA");
		cfg->tex_ea = strdup_trim(line + 2);
		cfg->has_ea = 1;
	}
	else
		handle_other_identifiers(line, cfg);
}

void	handle_identifier(char *line, t_config *cfg)
{
	if (!ft_strncmp(line, "NO ", 3) || (!ft_strncmp(line, "NO", 2)
			&& (line[2] == '\t' || line[2] == '\0')))
	{
		if (cfg->has_no)
			print_error("Duplicate NO");
		cfg->tex_no = strdup_trim(line + 2);
		cfg->has_no = 1;
	}
	else if (!ft_strncmp(line, "SO ", 3) || (!ft_strncmp(line, "SO", 2)
			&& (line[2] == '\t' || line[2] == '\0')))
	{
		if (cfg->has_so)
			print_error("Duplicate SO");
		cfg->tex_so = strdup_trim(line + 2);
		cfg->has_so = 1;
	}
	else
		handle_remaining_identifiers(line, cfg);
}

int	is_identifier_line(char *trimmed)
{
	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "NO\t", 3)
		|| !ft_strncmp(trimmed, "NO", 2))
		return (1);
	if (!ft_strncmp(trimmed, "SO ", 3) || !ft_strncmp(trimmed, "SO\t", 3)
		|| !ft_strncmp(trimmed, "SO", 2))
		return (1);
	if (!ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "WE\t", 3)
		|| !ft_strncmp(trimmed, "WE", 2))
		return (1);
	if (!ft_strncmp(trimmed, "EA ", 3) || !ft_strncmp(trimmed, "EA\t", 3)
		|| !ft_strncmp(trimmed, "EA", 2))
		return (1);
	if (*trimmed == 'F' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (1);
	if (*trimmed == 'C' && (trimmed[1] == ' ' || trimmed[1] == '\t'))
		return (1);
	return (0);
}
