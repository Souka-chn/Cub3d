/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:47:31 by schernan          #+#    #+#             */
/*   Updated: 2025/10/20 22:47:34 by schernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <ctype.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define MINIMAP_SIZE 200
# define MINIMAP_SCALE 10
# define MINIMAP_X 20
# define MINIMAP_Y 20
# define MINIMAP_CELL_SIZE 20
# define MINIMAP_PLAYER_SIZE 4
# define MINIMAP_VIEW_DISTANCE 100

# define MAX_DOORS 50
# define DOOR_SPEED 0.05
# define KEY_E 101
# define DOOR_INTERACT_DISTANCE 1.5

# define MAX_SPRITES 10
# define MAX_FRAMES 8

typedef enum e_door_state
{
	DOOR_CLOSED = 0,
	DOOR_OPENING = 1,
	DOOR_OPEN = 2,
	DOOR_CLOSING = 3
}						t_door_state;

typedef struct s_door
{
	int					x;
	int					y;
	t_door_state		state;
	double				progress;
	double				last_time;
}						t_door;

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define MOVE_SPEED 0.08
# define ROT_SPEED 0.08

# define MOUSE_SENSITIVITY 0.001
# define MOUSE_WRAP_MARGIN 100

typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_texture;

typedef struct s_animated_sprite
{
	double				x;
	double				y;
	t_texture			frames[MAX_FRAMES];
	int					frame_count;
	int					current_frame;
	double				frame_duration;
	double				last_frame_time;
	int					active;
}						t_animated_sprite;

typedef struct s_minimap
{
	int					size;
	int					scale;
	int					x;
	int					y;
	int					cell_size;
	int					player_size;
	int					view_distance;
	int					wall_color;
	int					floor_color;
	int					player_color;
	int					fov_color;
	int					bg_color;
	int					border_color;
	int					temp_end_y;
}						t_minimap;

typedef struct s_config
{
	char				*tex_no;
	char				*tex_so;
	char				*tex_we;
	char				*tex_ea;
	char				*tex_do;
	int					floor[3];
	int					ceil[3];
	char				**map;
	int					map_w;
	int					map_h;
	int					player_x;
	int					player_y;
	char				player_dir;
	int					has_no;
	int					has_so;
	int					has_we;
	int					has_ea;
	int					has_do;
	int					has_f;
	int					has_c;
}						t_config;

typedef struct s_player
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				move_to_y;
	double				temp_dir_y;
}						t_player;

typedef struct s_ray
{
	double				camera_x;
	double				ray_dir_x;
	double				ray_dir_y;
	int					map_x;
	int					map_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				side_dist_x;
	double				side_dist_y;
	int					step_x;
	int					step_y;
	int					hit;
	int					side;
	double				perp_wall_dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_ray;

typedef struct s_keys
{
	int					w;
	int					s;
	int					a;
	int					d;
	int					left;
	int					right;
	int					esc;
	int					e;
}						t_keys;

typedef struct s_mouse
{
	int					x;
	int					y;
	int					last_x;
	int					last_y;
	int					first_move;
	int					ignore_next;
}						t_mouse;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*img_addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_texture			textures[5];
	t_animated_sprite	sprites[MAX_SPRITES];
	int					sprite_count;
	double				z_buffer[WIN_WIDTH];
	t_config			*config;
	t_player			player;
	t_keys				keys;
	t_mouse				mouse;
	t_minimap			minimap;
	t_door				doors[MAX_DOORS];
	int					door_count;
	double				temp_transform_x;
	double				temp_transform_y;
	int					temp_sprite_width;
	int					temp_sprite_height;
	int					temp_sprite_screen_x;
	double				temp_sprite_y;
	int					temp_frame_count;
}						t_data;

void					parse_file(const char *path, t_config *cfg);
void					free_lines_array(char **lines, int count);

void					parse_map(char **lines, int n, int start,
							t_config *cfg);

int						find_max_width(t_config *cfg);
void					validate_map(t_config *cfg);

int						validate_file_extension(const char *filename);
int						validate_texture_file(const char *path);
void					free_config(t_config *cfg);

int						validate_color(const char *color_str, int result[3]);

void					parse_color(char *line, int out[3]);

void					print_error(const char *msg);
int						ft_isspace(unsigned char c);
char					*strdup_trim(const char *s);
char					*skip_spaces(char *s);
void					trim_newline(char *line);

void					parse_color(char *line, int out[3]);
void					handle_identifier(char *line, t_config *cfg);
int						is_identifier_line(char *trimmed);

int						validate_file_extension(const char *filename);
int						validate_texture_file(const char *path);
void					free_config(t_config *cfg);
void					validate_config(t_config *cfg);

int						load_texture(t_data *engine, const char *path,
							int index);
void					free_textures(t_data *engine);
int						load_all_textures(t_data *engine);

void					init_player(t_data *data);
void					cast_rays(t_data *data);
void					perform_dda(t_data *data, t_ray *ray);
void					init_ray(t_data *data, t_ray *ray, int x);
void					calculate_step_and_side_dist(t_data *data, t_ray *ray);
void					dda_step(t_ray *ray);
void					check_hit(t_data *data, t_ray *ray);
void					calculate_draw_limits(t_data *data, t_ray *ray);
void					set_north_direction(t_data *data);
void					set_south_direction(t_data *data);
void					set_east_direction(t_data *data);
void					set_west_direction(t_data *data);
int						get_texture_index(t_ray *ray, t_data *data);

int						render_frame(t_data *data);
void					draw_vertical_line(t_data *data, int x, t_ray *ray);
void					put_pixel(t_data *data, int x, int y, int color);
int						get_texture_color(t_data *data, int tex_index,
							int tex_x, int tex_y);
int						calculate_tex_x(t_data *data, t_ray *ray);

void					init_keys(t_data *data);
int						handle_key_press(int key, t_data *data);
int						handle_key_release(int key, t_data *data);
void					update_player_movement(t_data *data);
void					move_player(t_data *data, double move_x, double move_y);
void					rotate_player(t_data *data, double rot_speed);

void					init_mouse(t_data *data);
int						handle_mouse_move(int x, int y, t_data *data);
void					rotate_with_mouse(t_data *data, int delta_x);

int						start_engine(t_config *cfg);

void					init_sprites(t_data *data);
int						add_animated_sprite(t_data *data, double x, double y,
							char **frame_paths);
void					update_sprite_animations(t_data *data,
							double current_time);
void					render_sprites(t_data *data);
void					free_sprites(t_data *data);
void					parse_sprites_from_map(t_data *data,
							char **sprite_frames, int frame_count);
int						count_frames(char **frame_paths);
int						find_free_sprite_slot(t_data *data);
void					init_sprite_properties(t_data *data, int idx,
							double x);
void					cleanup_sprite_frames(t_data *data, int sprite_idx,
							int up_to);
int						load_sprite_frame(t_data *data, int sprite_idx, int i,
							char *path);
int						load_all_frames(t_data *data, int sprite_idx,
							char **frame_paths, int frame_count);
void					calculate_sprite_transform(t_data *data,
							t_animated_sprite *sprite, double *transform_x,
							double *transform_y);
void					calculate_sprite_dimensions(int *sprite_screen_x,
							int *sprite_height, int *sprite_width,
							t_data *data);
void					calculate_draw_bounds(int sprite_height,
							int sprite_width, int sprite_screen_x,
							int bounds[4]);
void					render_sprite_column(t_data *data, t_texture *frame,
							int stripe, int bounds[4]);
void					render_single_sprite(t_data *data,
							t_animated_sprite *sprite);
int						get_sprite_pixel(t_texture *tex, int x, int y);
int						process_sprite_at_position(t_data *data,
							char **sprite_frames, int x, int y);
int						find_free_sprite_slot(t_data *data);
int						count_frames(char **frame_paths);

void					init_minimap(t_data *data);
void					render_minimap(t_data *data);
void					draw_minimap_cell(t_data *data, int x, int y,
							int color);
void					draw_minimap_player(t_data *data);
void					draw_minimap_fov(t_data *data);
void					draw_minimap_border(t_data *data);
void					draw_player_pixel(t_data *data, int x, int y);
void					draw_player_circle(t_data *data, int px_x, int px_y,
							int size);
void					draw_fov_line(t_data *data, int px_x, int px_y,
							int end_x);
void					draw_border_pixel(t_data *data, int center_x,
							int center_y);
int						is_border_pixel(int x, int y, int radius);
void					render_minimap_grid(t_data *data);
void					render_minimap_elements(t_data *data);

void					init_doors(t_data *data);
void					parse_doors_from_map(t_data *data);
void					update_doors(t_data *data);
void					handle_door_interaction(t_data *data);
int						is_door_at_position(t_data *data, int x, int y);
t_door					*get_door_at_position(t_data *data, int x, int y);
int						is_door_blocking(t_data *data, int x, int y);
double					get_door_openness(t_data *data, int x, int y);
void					update_opening_door(t_door *door, double delta_time);
void					update_closing_door(t_data *data, t_door *door,
							double delta_time);
void					toggle_door(t_door *door);

double					get_current_time(void);

double					distance_to_wall(t_data *data, double x, double y,
							double dir_x);
int						check_collision(t_data *data, double x, double y);
int						check_collision_raycast(t_data *data, double from_x,
							double from_y, double to_x);

#endif
