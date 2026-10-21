/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:41:16 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:41:17 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_destroy(void *param)
{
	t_data	*engine;

	engine = (t_data *)param;
	if (engine)
	{
		free_sprites(engine);
		free_textures(engine);
		if (engine->img)
			mlx_destroy_image(engine->mlx, engine->img);
		if (engine->win)
			mlx_destroy_window(engine->mlx, engine->win);
		if (engine->mlx)
		{
			mlx_destroy_display(engine->mlx);
			free(engine->mlx);
		}
	}
	exit(0);
	return (0);
}

int	init_data_mlx(t_data *engine)
{
	engine->mlx = mlx_init();
	if (!engine->mlx)
	{
		write(STDERR_FILENO, "Error: mlx_init failed\n", 23);
		return (0);
	}
	engine->win = mlx_new_window(engine->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!engine->win)
	{
		write(STDERR_FILENO, "Error: mlx_new_window failed\n", 29);
		mlx_destroy_display(engine->mlx);
		free(engine->mlx);
		return (0);
	}
	return (1);
}

int	init_engine_and_image(t_data *engine)
{
	int	i;

	if (!init_data_mlx(engine))
		return (0);
	engine->img = mlx_new_image(engine->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!engine->img)
	{
		write(STDERR_FILENO, "Error: Failed to create image buffer\n", 38);
		return (0);
	}
	engine->img_addr = mlx_get_data_addr(engine->img, &engine->bits_per_pixel,
			&engine->line_length, &engine->endian);
	if (!engine->img_addr)
	{
		write(STDERR_FILENO, "Error: Failed to get image data\n", 33);
		return (0);
	}
	i = 0;
	while (i < WIN_WIDTH)
		engine->z_buffer[i++] = 1000000.0;
	return (1);
}

void	init_game_and_hooks(t_data *engine)
{
	char	*sprite_frames[7];

	init_player(engine);
	init_keys(engine);
	init_mouse(engine);
	init_minimap(engine);
	init_doors(engine);
	parse_doors_from_map(engine);
	init_sprites(engine);
	sprite_frames[0] = "./textures/sprite_frame1.xpm";
	sprite_frames[1] = "./textures/sprite_frame2.xpm";
	sprite_frames[2] = "./textures/sprite_frame3.xpm";
	sprite_frames[3] = "./textures/sprite_frame4.xpm";
	sprite_frames[4] = "./textures/sprite_frame5.xpm";
	sprite_frames[5] = "./textures/sprite_frame6.xpm";
	sprite_frames[6] = NULL;
	parse_sprites_from_map(engine, sprite_frames, 6);
	mlx_hook(engine->win, 17, 0, handle_destroy, engine);
	mlx_hook(engine->win, 2, 1L << 0, handle_key_press, engine);
	mlx_hook(engine->win, 3, 1L << 1, handle_key_release, engine);
	mlx_hook(engine->win, 6, 1L << 6, handle_mouse_move, engine);
	mlx_loop_hook(engine->mlx, render_frame, engine);
}

int	start_engine(t_config *cfg)
{
	t_data	engine;

	if (!cfg)
	{
		write(STDERR_FILENO, "Error: Configuration null\n", 27);
		return (0);
	}
	engine.mlx = NULL;
	engine.win = NULL;
	engine.img = NULL;
	engine.img_addr = NULL;
	engine.config = cfg;
	if (!init_engine_and_image(&engine))
	{
		handle_destroy(&engine);
		return (0);
	}
	if (!load_all_textures(&engine))
	{
		handle_destroy(&engine);
		return (0);
	}
	init_game_and_hooks(&engine);
	mlx_loop(engine.mlx);
	return (1);
}
