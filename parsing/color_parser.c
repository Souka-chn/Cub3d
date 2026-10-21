/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:45:56 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:45:58 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_trailing_spaces(const char *s, int i)
{
	int	j;

	j = i;
	while (s[j])
	{
		if (!ft_isspace((unsigned char)s[j]))
			return (0);
		j++;
	}
	return (1);
}

int	is_valid_number(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	while (*s && ft_isspace((unsigned char)*s))
		s++;
	if (!*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (ft_isspace((unsigned char)s[i]))
			return (check_trailing_spaces(s, i));
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_color_utils(char **start, char **end, int *result, int count)
{
	char	tmp;

	*end = *start;
	while (**end && **end != ',')
		(*end)++;
	tmp = **end;
	**end = '\0';
	if (!is_valid_number(*start))
		return (0);
	*result = ft_atoi(*start);
	if (*result < 0 || *result > 255)
		return (0);
	**end = tmp;
	if (count == 3)
		return (1);
	if (tmp == '\0' || tmp != ',')
		return (0);
	*start = *end + 1;
	while (**start && ft_isspace((unsigned char)**start))
		(*start)++;
	if (**start == '\0' || **start == ',')
		return (0);
	return (1);
}

int	check_rgb_format(char *start, char *str_copy, int result[3])
{
	char	*end;
	int		count;
	char	*p;

	count = 0;
	while (count < 3)
	{
		if (!parse_color_utils(&start, &end, &result[count], count + 1))
			return (free(str_copy), 0);
		count++;
		if (count == 3)
			p = end;
	}
	while (*p && ft_isspace((unsigned char)*p))
		p++;
	if (*p != '\0')
		return (0);
	return (1);
}

int	validate_color(const char *color_str, int result[3])
{
	char	*str_copy;
	char	*p;
	int		ret;

	if (!color_str || !*color_str)
		return (0);
	str_copy = ft_strdup(color_str);
	if (!str_copy)
		return (0);
	p = str_copy;
	while (*p && ft_isspace((unsigned char)*p))
		p++;
	ret = check_rgb_format(p, str_copy, result);
	free(str_copy);
	return (ret);
}
