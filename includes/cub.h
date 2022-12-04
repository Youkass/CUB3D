/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/10/19 15:08:54 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "struct.h"
# include "includes.h"

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/utils/list.c                          */
/* -------------------------------------------------------------------------- */
t_list	*ft_lstnew(void *content);
int	ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lst_dellast(t_list **lst);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/utils/singletons/singleton.c                  */
/* -------------------------------------------------------------------------- */
t_data	*_img(void);
t_mlx	*_mlx(void);
t_media	*_media(void);
t_obj	*_player(void);
t_raycasting	**_ray(void);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/utils/singletons/singleton_2.c                 */
/* -------------------------------------------------------------------------- */
t_obj	*_player2(void);
t_spritecasting	*_pc(void);
t_menu	*_menu(void);
t_weapon	**_weapon(void);
t_team	**_team(void);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/utils/singletons/singleton_3.c                 */
/* -------------------------------------------------------------------------- */
t_var	*_var(void);
t_log	*_log(void);
t_image	*_image(void);
t_server_data	*_server(void);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/utils/garbage/garbage.c                     */
/* -------------------------------------------------------------------------- */
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstclear_img(t_list **lst);
void	ft_lstclear_media(t_list **lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*_lst(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/garbage/garbage_2.c                    */
/* -------------------------------------------------------------------------- */
t_list	*_lstimg(void);
t_list	*_lstmedia(void);
t_list	*ft_new_node(void *content);
void	*ft_malloc(int size);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/garbage/garbage_3.c                    */
/* -------------------------------------------------------------------------- */
void	ft_black_hole(int exit_code);
void	exit_say_error_2(int exit_code);
void	exit_say_error(int exit_code);

/* -------------------------------------------------------------------------- */
/*                FILE = srcs/utils/collisions/collisions_3.c                 */
/* -------------------------------------------------------------------------- */
void	*detect_neighbors(void);
int	is_neighbor(t_vector2D pos);

/* -------------------------------------------------------------------------- */
/*                FILE = srcs/utils/collisions/collisions_2.c                 */
/* -------------------------------------------------------------------------- */
t_vector2F	init_potential_dist(int up);
t_nb	*_nb(void);
void	ft_compute_nb(float overlap);
t_vector2F	ft_cal_nearest(int i);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/utils/collisions/collisions.c                  */
/* -------------------------------------------------------------------------- */
void	*compute_nb(int i);
int	check_neighbor(int up);
int	circle_circle_col(t_obj *pl);
int	circle_collide(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/sounds/sound_2.c                     */
/* -------------------------------------------------------------------------- */
int	ft_play_end_round(void);
int	ft_play_end_game(void);
void	ft_check_end_songs(void);
int	ft_check_enemie_team(void);
int	ft_check_my_team(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/sounds/sound_3.c                     */
/* -------------------------------------------------------------------------- */
void	ft_init_media(void);
int	ft_check_game_music(void);
void	ft_init_ran(void);
void	ft_start_from_start(ma_sound *sound);
void	ft_play_end_sound(ma_sound *sound);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/sounds/sound.c                      */
/* -------------------------------------------------------------------------- */
void	ft_play_music(int index);
void	play_shots_sound(t_obj player, t_media *media);
void	ft_play_shot_sound(t_obj player);
void	ft_play_own_shot(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/utils/sounds/sound_4.c                     */
/* -------------------------------------------------------------------------- */
void	ft_add_sound(int index_1, int index_2, char *path);
void	ft_init_game_music(void);
void	ft_init_sound(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/utils/restart.c                         */
/* -------------------------------------------------------------------------- */
void	replace_player(void);
void	restart_player(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/clock.c                          */
/* -------------------------------------------------------------------------- */
struct timeval	start_clock(void);
unsigned long	get_clock(struct timeval start);
unsigned long	get_time(unsigned long start);
unsigned long	get_time_server(unsigned long start, struct timeval clock);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/hooks/movements_2.c                    */
/* -------------------------------------------------------------------------- */
void	crouch(int mode);
int	ft_up_head(void);
int	ft_right(void);
int	ft_left(void);
void	movements(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/utils/hooks/escape.c                      */
/* -------------------------------------------------------------------------- */
void	escape_menu(void);
void	escape_game(void);
void	escape_server(void);
int	ft_escape(void);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/utils/hooks/key_hooks.c                     */
/* -------------------------------------------------------------------------- */
void	mouse_menu(void);
void	crouch_sprint(void);
void	open_door(void);
void	key_hook(void);
int	ft_game_hook(int keycode);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/utils/hooks/movements.c                     */
/* -------------------------------------------------------------------------- */
int	ft_down_head(void);
int	ft_forward(void);
int	ft_back(void);
int	ft_strafe_left(void);
int	ft_strafe_right(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/hooks/key_hooks_2.c                    */
/* -------------------------------------------------------------------------- */
void	weapons(void);
int	ft_is_wall(t_vector2D pos);
void	reload_hook(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/utils/click.c                          */
/* -------------------------------------------------------------------------- */
void	click(void);
int	click_update(void);
int	click_delay(void);
int	is_neutral(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/utils/malloc_hooks_enum.c                    */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/raycasting/raycasting_utils.c                  */
/* -------------------------------------------------------------------------- */
int	intersects(t_circle circle, t_rect rect);
void	ft_put_pixel(t_data *a, t_data *b, t_vector2D pos_a, t_vector2D pos_b);
void	ft_put_pixel_color(t_data *a, char color[4], int x, int y);
void	ft_put_pixel_color_unsigned(t_data *a, unsigned char c[4], int x, int y);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/raycasting/player_casting_2.c                  */
/* -------------------------------------------------------------------------- */
void	put_pixel_from_mode(t_obj *player, int stripe, int y);
void	choose_mode(t_obj *player, t_obj *my_player);
int	nearest(t_obj *player);
void	swap_pl(t_obj *player, int i, int j);
int	compute_distance(t_vector2F a, t_vector2F b);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/raycasting/player_casting.c                   */
/* -------------------------------------------------------------------------- */
void	sort_by_distance(t_obj *player);
void	player_casting(void);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/raycasting/player_casting_3.c                  */
/* -------------------------------------------------------------------------- */
void	choose_tex(int tex_mode, int walk_tex, int stripe, int tex_dir);
void	normal_player(t_obj *player, int stripe, int y);
void	walking_player(t_obj *player, int stripe, int y);
void	dead_player(t_obj *player, int stripe, int y);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/raycasting/raycasting.c                     */
/* -------------------------------------------------------------------------- */
void	dda(t_raycasting *r);
void	compute_drawing_data(t_raycasting *r);
void	draw_wall(t_raycasting *r);
void	*ray_draw(void *t);
void	draw_rays(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/raycasting/raycasting_2.c                    */
/* -------------------------------------------------------------------------- */
void	init_ray(t_raycasting *r);
void	init_dda(t_raycasting *r);
void	cast_bullet(t_obj player, int i);
void	dda_condition(t_raycasting *r);

/* -------------------------------------------------------------------------- */
/*                  FILE = srcs/raycasting/bullet_casting.c                   */
/* -------------------------------------------------------------------------- */
void	init_cast_bul(int i, t_obj *player, t_obj *my_player);
void	draw_bul(void);
void	bullet_casting(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/raycasting/spritecasting.c                   */
/* -------------------------------------------------------------------------- */
void	sprite_casting(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/raycasting/name_casting.c                    */
/* -------------------------------------------------------------------------- */
void	name_casting(void);

/* -------------------------------------------------------------------------- */
/*                           FILE = srcs/kill_log.c                           */
/* -------------------------------------------------------------------------- */
t_elem	*new_log(int id1, int id2);
void	print_log(t_list	*li);

/* -------------------------------------------------------------------------- */
/*                 FILE = srcs/network_client/network_utils.c                 */
/* -------------------------------------------------------------------------- */
int	end_of_line(char *s);
char	*ft_get_host_ip(void);
t_obj	ft_get_data(t_obj *player);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/network_client/client_4.c                    */
/* -------------------------------------------------------------------------- */
char	*ft_get_ip_input(void);
int	ft_init_client_first(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/network_client/client_2.c                    */
/* -------------------------------------------------------------------------- */
void	restart_round(void);
void	render_kill_log(void);
void	update_health(int i, t_send_server_game serv);
void	get_data(int i, t_send_server_game serv);
void	ft_round_handling(int *incremented, t_send_server_game serv);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/network_client/client.c                     */
/* -------------------------------------------------------------------------- */
void	round_handling(int *incremented, t_send_server_game serv);
void	ft_pong_client(void);

/* -------------------------------------------------------------------------- */
/*                   FILE = srcs/network_client/client_3.c                    */
/* -------------------------------------------------------------------------- */
int	ft_init_client_next(void);
int	ft_init_client(void);
void	ft_copy_data_first(t_obj *player);
void	ft_copy_data_next(t_obj *player, int i);
void	ft_copy_data_before_pong(t_obj *player);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/network/recv.c                         */
/* -------------------------------------------------------------------------- */
void	ft_help_first_recv(t_client_thread *client, t_send_client_game data);
int	ft_recv_first_data(t_client_thread *client);
int	ft_is_get(t_client_thread *client);
int	ft_is_send(t_client_thread *client);
void	ft_next(t_client_thread *client, t_send_server_game *data);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/network/round_2.c                        */
/* -------------------------------------------------------------------------- */
int	round_play(int round, t_send_server_game *data, t_client_thread *c, int f);
void	ft_round_end(t_client_thread *client);
int	round_end(t_send_server_game *data, t_client_thread *client);
int	ft_first_big_if(t_client_thread *client);
void	ft_scnd_big_if(t_client_thread *client);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/network/lobby.c                         */
/* -------------------------------------------------------------------------- */
int	ft_send_all_data_lobby(t_client_thread *client, int nb);
int	ft_player_team(t_client_thread *client, int id);
int	ft_update(t_client_thread *client);
int	wait_lobby(t_client_thread *client);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/network/round_1.c                        */
/* -------------------------------------------------------------------------- */
int	round_end_wait(t_send_server_game *data, t_client_thread *client);
int	ft_if_wait(t_client_thread *client);
int	round_wait_start(t_send_server_game *data, t_client_thread *client);
int	round_start(int *round, t_send_server_game *data, t_client_thread *client);
void	round_leaderboard(t_send_server_game *data, t_client_thread *client);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/network/send.c                         */
/* -------------------------------------------------------------------------- */
int	ft_send_all_data(t_client_thread *client);
int	send_nb_players(t_client_thread *client);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/network/server.c                        */
/* -------------------------------------------------------------------------- */
void	restart_state(t_client_thread	*c);
int	ft_init_server(t_server_data *data);
void	ft_exit(int signal);
int	main(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/network/server_thread.c                     */
/* -------------------------------------------------------------------------- */
void	init_team_server(t_client_thread *c);
void	get_team_id(t_client_thread	*c);
int	ft_routine(t_client_thread *client);
int	ft_while_routine(t_client_thread *client);
void	*client_routine(void *client_t);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/network/init.c                         */
/* -------------------------------------------------------------------------- */
int	ft_init_client_thread(t_server_data *data);
int	ft_init_in_while(t_server_data *data, int i);
int	ft_connect_clients(t_server_data *data);
int	check_only(int nb, int r, int type);
void	ft_init_dt(t_client_thread *client, t_send_server_game *data);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/network/lobby_2.c                        */
/* -------------------------------------------------------------------------- */
int	ft_has_recv(t_client_thread *client, int nb);
int	ft_has_sent(t_client_thread *client, int nb);
int	ft_has_start(t_client_thread *client);
int	ft_recv_first_data_lobby(t_client_thread *client, int nb);
void	ft_send_next(t_send_server *o_player, t_client_thread *client, int nb);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/math/math_2.c                          */
/* -------------------------------------------------------------------------- */
int	normalise_between(t_vector2D r, t_vector2D t, int nb);
float	normalise_between2f(t_vector2F r, t_vector2F t, int nb);
int	mod(int a, int b);
float	rad_to_deg(float rad);
float	deg_to_rad(float deg);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/math/vector/operator2D.c                    */
/* -------------------------------------------------------------------------- */
t_vector2D	div_2d(t_vector2D a, t_vector2D b);
t_vector2D	mult_2d(t_vector2D a, t_vector2D b);
t_vector3F	add_3f(t_vector3F a, t_vector3F b);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/math/vector/tools.c                       */
/* -------------------------------------------------------------------------- */
t_vector2F	dist_2f(t_vector2F a, t_vector2F b);
t_vector3F	dist_3f(t_vector3F a, t_vector3F b);
t_vector2F	velocity_ms(t_vector2F dist, float time_ms);
t_vector3F	velocity_ms3f(t_vector3F dist, float time_ms);
float	get_time_velo3f(float dist, float time_ms_per_unit);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/math/vector/operator2F.c                    */
/* -------------------------------------------------------------------------- */
t_vector2F	div_2f(t_vector2F a, t_vector2F b);
t_vector2F	mult_2f(t_vector2F a, t_vector2F b);
float	fdot(t_vector2F a, t_vector2F b);
t_vector2F	sub_2f(t_vector2F a, t_vector2F b);
t_vector2F	add_2f(t_vector2F a, t_vector2F b);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/math/vector/tools_2.c                      */
/* -------------------------------------------------------------------------- */
t_vector2F	velocity_get_point(t_vector2F start, t_vector2F velo, int time_ms);
t_vector3F	velocity_get_point3f(t_vector3F start, t_vector3F velo, int time_ms);
float	one_dist2f(t_vector2F a, t_vector2F b);
float	one_dist3f(t_vector3F a, t_vector3F b);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/math/math.c                           */
/* -------------------------------------------------------------------------- */
float	mag(t_vector2F v);
t_vector2F	norm(t_vector2F v);
float	max_f(float a, float b);
float	min_f(float a, float b);
float	min(int a, int b);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/parsing/parsing.c                        */
/* -------------------------------------------------------------------------- */
int	check_map(char **map, int start);
int	get_longest_line(char **map);
char	*copy_line_and_add(char *str, int size);
char	**resize_map(char **map);
void	copy_map_static(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/parsing/args_2.c                        */
/* -------------------------------------------------------------------------- */
void	jump_spaces(int *i, char *str, int k);
void	is_error(int tmp, int k, int j);
void	parse_color(char *str, int index, int *nb);
int	is_nb_args(int	*tab);
int	is_empty(char *str);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/parsing_2.c                       */
/* -------------------------------------------------------------------------- */
int	is_char_in_range(t_vector2D pos, char **map);
int	is_player(char c);
void	get_team_pos(char c, t_vector2D pos);
void	body_map(t_vector2D *pt, t_vector2D *it, char **map, int *longest);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/parsing_3.c                       */
/* -------------------------------------------------------------------------- */
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*read_file(int fd);
t_vector2D	get_pos(char **map, char c);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/parsing/args_3.c                        */
/* -------------------------------------------------------------------------- */
void	parse_dir(char *str, int index, int *nb);
void	parse_new_textures(char *str, int index, int *nb);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/parsing/args.c                         */
/* -------------------------------------------------------------------------- */
int	is_map(char *str);
int	mandatory_args(char *str, int nb_types[16]);
int	specials_args(char *str, int nb_types[16]);
int	get_args(char **map, int i, int *index, int nb_types[16]);
void	parse_args(char **map);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/parsing/parsing_4.c                       */
/* -------------------------------------------------------------------------- */
size_t	ft_strlen(const char *s);
int	count_words(char const *s, char c);
char	*ft_strncpy_split(char const *src, size_t n);
int	is_wall(char c);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/dyn_array_2.c                          */
/* -------------------------------------------------------------------------- */
void	arr_fill(t_array *a, int value);
void	print_arr(t_array *a);
int	ft_in_array(t_array *a, int value);
t_vector2F	get_90_angle(int dir);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/generate_2.c                        */
/* -------------------------------------------------------------------------- */
void	gen_menu_bars(void);
t_vector2D	*_butp(void);
t_vector2D	*_butpl(void);
void	gen_menu_buttons(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/render.c                          */
/* -------------------------------------------------------------------------- */
void	menu_leaderboard(void);
void	menu_pseudo(void);
void	menu_ip(void);
void	menu_option(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/mouse_hook.c                        */
/* -------------------------------------------------------------------------- */
void	check_button_state_mouse(int kc);
void	check_button_state_mouse_pl(int kc);
void	check_button_state_mouse_options(int kc);
int	menu_mouse_hook(int keycode);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/generate_3.c                        */
/* -------------------------------------------------------------------------- */
t_data	generate_image(char *path);
void	gen_bar(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/intro_2.c                         */
/* -------------------------------------------------------------------------- */
void	ft_open_intro_sprites(void);
void	ft_intro_sprite_to_image(int i1, int i2, t_vector2D v1, t_vector2D v2);
void	ft_init_youri(unsigned long *start, unsigned long *c, t_vector2D *pos);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/recv_utils.c                        */
/* -------------------------------------------------------------------------- */
int	ft_recv_players(t_send_server *o_player, int size);
int	ft_recv_one(int socket, t_send_client *player, int size);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/menu/generate.c                         */
/* -------------------------------------------------------------------------- */
void	gen_alpha(void);
void	gen_bgs(void);
void	gen_menu_images(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/loop_4.c                          */
/* -------------------------------------------------------------------------- */
void	compute_hitbox_buttons(int i);
void	check_button_state(void);
void	compute_hitbox_pl(int i);
void	check_button_state_pl(void);
void	check_action_state_bar(int i);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/menu/render_2.c                         */
/* -------------------------------------------------------------------------- */
int	get_ratio(int kills, int deaths);
void	sort_team(void);
void	menu_lobby(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/utils_2.c                         */
/* -------------------------------------------------------------------------- */
t_data	ft_put_img_to_img_scale(t_data b, t_data l, t_vector2D p, t_vector2F s);
t_data	ft_put_image_to_image(t_data big, t_data lil, t_vector2D pos);
t_data	ft_put_image_to_image_create(t_data big, t_data lil, t_vector2D pos);
int	ft_chk_sprite(t_vector2D *it, t_vector2D pos, t_vector2D s, t_vector2D *r);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/utils_3.c                         */
/* -------------------------------------------------------------------------- */
void	restart_button(void);
int	ft_hitbox(t_vector2D hitbox[4], t_vector2D pos);
void	draw_pixel(t_data *big, t_data lil, t_vector2D it, t_vector2D rel_pos);
void	draw_pixel_create(t_data *big, t_data lil, t_vector2D it, t_vector2D r);
void	ft_init_rel2(t_vector2D *rel_pos, t_vector2F *it, t_vector2D p);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/menu/intro.c                          */
/* -------------------------------------------------------------------------- */
t_vector2D	ft_draw_youri(void);
t_vector2D	ft_draw_darian(void);
void	ft_end_intro(t_vector2D *double_pos);
void	ft_intro(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/menu/render_3.c                         */
/* -------------------------------------------------------------------------- */
void	draw_lobby(void);
void	draw_leaderboard(void);
void	update_key(void);
void	draw_pseudo_box(char	*pseudo, int i, int team);
void	draw_pseudo_box_leader(char	*pseudo, int id, int i, int team);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/generate_4.c                        */
/* -------------------------------------------------------------------------- */
void	gen_serv_but(void);
void	butpl_hitbox(void);
void	o_state_hitbox(t_vector2D btn[7]);
void	butp_hitbox(void);
void	generate_button_state(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/menu/loop.c                           */
/* -------------------------------------------------------------------------- */
int	menu_hook_pseudo(int keycode);
int	menu_hook_ip_4(int keycode);
int	menu_hook_ip_3(int keycode);
int	menu_hook_ip_2(int keycode);
int	menu_hook_ip(int keycode);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/menu/utils.c                          */
/* -------------------------------------------------------------------------- */
t_data	ft_put_sprt_to_img(t_data l, t_vector2D p, t_vector2D sp, t_vector2D s);
void	draw_pixel_color(t_data *big, t_vector2D rel_pos, char pix[4]);
void	draw_vertical_line(t_data *img, t_vector2D pos, int h);
void	draw_bar_fill(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/dragbar.c                         */
/* -------------------------------------------------------------------------- */
void	s_bar_drag(void);
void	m_bar_drag(void);
void	drag_bar(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/menu/menu_lobby.c                        */
/* -------------------------------------------------------------------------- */
void	team_data(int i);
void	get_pseudos(void);
void	menu_pong(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/loop_2.c                          */
/* -------------------------------------------------------------------------- */
int	menu_loop(void);
int	menu_hook(int keycode);
int	is_nb_keycode(int k);
int	get_nb_keycode(int k);
int	menu_hook_pseudo_2(int keycode, int *n);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/menu/render_4.c                         */
/* -------------------------------------------------------------------------- */
void	draw_bg(char color[4]);
int	perc(int a, int b);
void	menu_start(void);
void	menu_player(void);
void	ft_draw_lobby(int size_box, t_vector2D size_box_minus);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/menu/loop_3.c                          */
/* -------------------------------------------------------------------------- */
void	check_action_state_options(int i);
void	check_button_state_options(void);
void	planet_clock(void);
void	menu_call_hook(void);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/key.c                              */
/* -------------------------------------------------------------------------- */
void	get_key(int keycode);
int	ft_release(int keycode);

/* -------------------------------------------------------------------------- */
/*                            FILE = srcs/mouse.c                             */
/* -------------------------------------------------------------------------- */
int	ft_expose(void *data);
int	ft_rotate(double rot_speed);
int	mouse_rotate(void);
int	ft_mouse_release(int keycode);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/drawing/draw_text_2.c                      */
/* -------------------------------------------------------------------------- */
int	is_allow_alpha(char c);
char	char_up(char c);
void	draw_text(char *text, t_vector2D pos, char color[4]);
t_data	ft_draw_char(t_data big, t_data lil, t_vector2D pos, char color[4]);
int	ft_chk_draw(t_vector2D *it, t_vector2D p, t_data lil, t_vector2D scale);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/drawing/draw_player.c                      */
/* -------------------------------------------------------------------------- */
t_vector2D	ft_first_vector(void);
t_vector2D	ft_scnd_vector(void);
int	ft_return_xp(t_obj *player, t_obj *my_player);
int	ft_return_yp(t_obj *player, t_obj *my_player);
float	ft_return_radius(t_obj *player);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/drawing/draw_player_2.c                     */
/* -------------------------------------------------------------------------- */
int	ft_return_xp_2(void);
int	ft_return_yp_2(void);
float	ft_return_radius_2(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/drawing/draw_map.c                       */
/* -------------------------------------------------------------------------- */
void	draw_player_map(void);
void	ft_draw_map(void);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/drawing/draw_text.c                       */
/* -------------------------------------------------------------------------- */
void	ft_init_rel(t_vector2D *rel_pos, t_vector2D p);
t_data	ft_draw_char_scale(t_data lil, t_vector2D p, t_vector2D s, char c[4]);
void	draw_text_scale(char *text, t_vector2D pos, t_vector2D scale, char c[4]);
t_data	create_text_img(char *text, char color[4]);
void	draw_rectangle(t_vector2D a, t_vector2D size, char color[4]);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/drawing/draw_map_2.c                      */
/* -------------------------------------------------------------------------- */
t_obj	*ft_copy_map_line(char *line, int index);
int	ft_malloc_map(void);
void	ft_draw_wall(t_vector2D pos);
void	ft_draw_floor(t_vector2D pos);
void	drawcircle(int xp, int yp, float radius, int color);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/drawing/draw_map_3.c                      */
/* -------------------------------------------------------------------------- */
void	ft_find_wall_scale(void);
void	ft_give_id(void);

/* -------------------------------------------------------------------------- */
/*                           FILE = srcs/clock_2.c                            */
/* -------------------------------------------------------------------------- */
void	walk_clock(void);
void	death_clock(void);
void	reload_clock(void);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/team.c                             */
/* -------------------------------------------------------------------------- */
void	init_player_team(void);
int	get_id_by_pseudo(char *pseudo);
void	init_teams(void);

/* -------------------------------------------------------------------------- */
/*                            FILE = srcs/tools.c                             */
/* -------------------------------------------------------------------------- */
t_vector2D	pos(int x, int y);
t_vector2F	posf(float x, float y);
t_vector3F	pos3f(float x, float y, float z);
char	*ft_strdup(const char *s);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/loop_hook.c                           */
/* -------------------------------------------------------------------------- */
int	ft_hook(int keycode);
int	ft_mouse_hook(int keycode);
int	ft_loop_hook(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/main_utils.c                          */
/* -------------------------------------------------------------------------- */
int	ft_strcmp(char *s1, char *s2);
int	ft_check_map_name(char *name);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/init/init_2.c                          */
/* -------------------------------------------------------------------------- */
void	ft_init_player2(void);
void	generate_dsprite(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/init/init_3.c                          */
/* -------------------------------------------------------------------------- */
void	init_var(void);
void	init_data_shot(t_obj *player);
void	init_image(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/init/init.c                           */
/* -------------------------------------------------------------------------- */
void	generate_dsprite_red(void);
void	ft_init_player_pos(void);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/init/init_4.c                          */
/* -------------------------------------------------------------------------- */
void	ft_init_one(void);
void	init_weapons(void);
void	ft_init_key_next(void);
void	init_key(void);
void	ft_init_var_next(void);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/mlx_utils/mlx_utils.c                      */
/* -------------------------------------------------------------------------- */
void	recompute_array_shot(int index);
void	update_bullets3f(void);
void	set_spectate(void);
int	ft_loop(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/mlx_utils/sky.c                         */
/* -------------------------------------------------------------------------- */
void	draw_sky(void);
void	pixel_sky(t_int	var, int xo);
void	*ft_draw_void(void *r);
void	thread_sky(t_vector2D r[10]);
void	draw_void_thread(void);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/mlx_utils/mlx_utils_3.c                     */
/* -------------------------------------------------------------------------- */
void	ft_init_mlx(void);

/* -------------------------------------------------------------------------- */
/*                    FILE = srcs/mlx_utils/mlx_utils_2.c                     */
/* -------------------------------------------------------------------------- */
void	ft_init_img(void);
void	ft_pixel_put(float x, float y, int color);
void	ft_reload_frame(void);
void	ft_fps(void);
void	check_death(void);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/mlx_utils/sky_2.c                        */
/* -------------------------------------------------------------------------- */
void	ft_next_while_draw_sky(t_vector2D pt);
void	ft_norme_while_draw_sky(int offst, int pitch, t_vector2D *pl_coord);
void	ft_norme_draw_sky(t_vector2D *pl_coord);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/mlx_utils/render.c                       */
/* -------------------------------------------------------------------------- */
void	render_health(t_vector2D a);
void	ft_is_not_knife(void);
void	draw_death(void);
void	ft_loop_multi(void);
void	ft_if_round_end_wait(void);

/* -------------------------------------------------------------------------- */
/*                        FILE = srcs/mlx_utils/hud.c                         */
/* -------------------------------------------------------------------------- */
void	hud_hit_and_touch(void);
void	hud(void);

/* -------------------------------------------------------------------------- */
/*                          FILE = srcs/dyn_array.c                           */
/* -------------------------------------------------------------------------- */
void	init_array(t_array *a, int size);
int	kill_push(int value);
int	arr_push(t_array *a, int value);
void	arr_pop(t_array *a, int id);
void	arr_destroy(t_array *a);

/* -------------------------------------------------------------------------- */
/*                     FILE = srcs/shoot/shoot_utils_2.c                      */
/* -------------------------------------------------------------------------- */
void	shoot_alone3f(void);
void	shoot_touched(int i, int *touched, t_vector3F closest3f);
int	is_wall_closest(t_vector2F closest);

/* -------------------------------------------------------------------------- */
/*                      FILE = srcs/shoot/shoot_utils.c                       */
/* -------------------------------------------------------------------------- */
t_vector2F	closest_point(t_vector2F a, t_vector2F b, t_vector2F c);
void	push_and_kill(int i);
void	shoot_type(int type, int i);
int	is_shoot_touch(t_vector2F a, t_vector2F b, t_circle c, t_vector2F *closest);
int	is_touch_pl(t_vector3F closest3f, t_obj player);

/* -------------------------------------------------------------------------- */
/*                       FILE = srcs/shoot/shoot_wall.c                       */
/* -------------------------------------------------------------------------- */
int	nearest_wall3d(t_vector3F	*closest);

/* -------------------------------------------------------------------------- */
/*                         FILE = srcs/shoot/shoot.c                          */
/* -------------------------------------------------------------------------- */
int	is_player_can_kill(int i, t_vector2F *closest);
void	no_player_touched(int touched, t_vector3F closest3f);
void	singleplayer_shoot(void);
void	shoot(void);
void	init_shot3f(t_vector3F start, t_vector3F end);

/* -------------------------------------------------------------------------- */
/*                           FILE = srcs/ft_itoa.c                            */
/* -------------------------------------------------------------------------- */
int	size_nb(int nb);
char	*ft_itoa(int n);

/* -------------------------------------------------------------------------- */
/*                             FILE = srcs/main.c                             */
/* -------------------------------------------------------------------------- */
void	ft_print_tab(char **s);
int	ft_game(void);
void	ft_print_map(void);
int	main(int argc, char **argv);


#endif
