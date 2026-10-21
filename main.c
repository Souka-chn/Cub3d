/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:47:21 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:47:22 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_config	cfg;

	memset(&cfg, 0, sizeof(t_config));
	if (ac != 2)
	{
		write(2, "Usage: ", 7);
		write(2, av[0], ft_strlen(av[0]));
		write(2, " file.cub\n", 10);
		return (1);
	}
	parse_file(av[1], &cfg);
	if (!start_engine(&cfg))
	{
		write(STDERR_FILENO, "Error: Engine failed\n", 21);
		free_config(&cfg);
		return (1);
	}
	free_config(&cfg);
	return (0);
}
