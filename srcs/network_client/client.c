/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:45:15 by yobougre          #+#    #+#             */
/*   Updated: 2022/10/18 00:22:03 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_get_ip_input(void)
{
	char	*buf;
	int		r; 
	printf("Enter Host Ip on the next line : \n");
	buf = ft_malloc(sizeof(char) * BUFFER_SIZE);
	if (!buf)
		return (NULL);
	r = read(STDIN_FILENO, buf, BUFFER_SIZE);
	if (r < 0)
		return (NULL);
	buf[r] = 0; return (buf);
}

int	ft_init_client(void)
{
	int			ret;
	
	_var()->socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_var()->is_host == SERVER)
		_var()->client.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	else if (_var()->is_host == CLIENT) 
		_var()->client.sin_addr.s_addr = inet_addr(_var()->ip);
	_var()->client.sin_family = AF_INET;
	_var()->client.sin_port = htons(30000);
	ret = connect(_var()->socket,
		(const struct sockaddr *)&(_var()->client), sizeof(_var()->client));
	if (ret < 0)
		return (EXIT_FAILURE);
	printf("je suis connecté\n");
	if (recv(_var()->socket, &(_player()->id), sizeof(int), 0) < 0)
		return (EXIT_FAILURE);
	//if (_player()->id == 1)
	//{
	//	_player()->spectate = 1;
	//	_player()->spec_id = 0;
	//}
	printf("je reçois mon id : %d\n", _player()->id);
	if (recv(_var()->socket, &(_var()->nb_player), sizeof(int), 0) < 0)
		return (EXIT_FAILURE);
	if (recv(_var()->socket, &(_var()->pid), sizeof(int), 0) < 0)
		return (EXIT_FAILURE);
	printf("je sors de la fonction\n");
	return (EXIT_SUCCESS);
}

void	ft_copy_data_before_pong(t_obj *player)
{
	int	i;

	i = 0;
	//player->kill_round.n = _player()->kill_round.n;
	//player->kill_round.size = _player()->kill_round.size;
	while (i < (int)_player()->nr)
	{
		player->kill_round[i] = _player()->kill_round[i];
		i++;
	}
	i = 0;
	player->nr = _player()->nr;
	player->is_crouching = _player()->is_crouching;
	player->team = _player()->team;
	player->change_team = _player()->change_team;
	player->plane = _player()->plane;
	player->pitch = _player()->pitch;
	player->norm_pitch = _player()->norm_pitch;
	player->id = _player()->id;
	player->x = _player()->x;
	player->y = _player()->y;
	player->z = _player()->z;
	player->c = _player()->c;
	player->dx = _player()->dx;
	player->kills = _player()->kills;
	player->deaths = _player()->deaths;
	player->dy = _player()->dy;
	player->da = _player()->da;
	player->old_dx = _player()->old_dx;
	player->old_dy = _player()->old_dy;
	player->angle = _player()->angle;
	player->is_walking = _player()->is_walking;
	player->is_dead = _player()->is_dead;
	player->start_dead = _player()->start_dead;
	player->death_n = _player()->death_n;
	player->death_start = _player()->death_start;
	player->shooted = _player()->shooted;
	player->old_plane = _player()->old_plane;
	player->hb = _player()->hb;
	player->pitch = _player()->pitch;
    player->health = _player()->health;
    player->weapon_id = _player()->weapon_id;
	i = 0;
	while (i < NB_WEAPONS)
	{
		player->ammo[i] = _player()->ammo[i];
		player->full_ammo[i] = _player()->full_ammo[i];
		i++;
	}
	player->shoot_n = _player()->shoot_n;
	player->exchange = _player()->exchange;
	player->is_start = _player()->is_start;
	player->is_shooting = _player()->is_shooting;
	i = 0;
	while (i < _player()->shoot_n)
	{
		player->shott[i] = _player()->shott[i];
		player->shott[i].pos = _player()->shott[i].pos;
		i++;
	}
	memset(player->pseudo, 0, sizeof(player->pseudo));
	strcpy(player->pseudo, _player()->pseudo);
}

void	print_data_recv(t_obj	*player)
{
	printf("-----RECV FROM %d-----\n", player->id);
	printf("I RECEIVED :\n	POS = %f, %f\n	HEALTH = %d\n	ANGLE = %f\n	DIR = %f, %f\n	SHOOT_N = %d\n	EXCHANGE = %d\n\n",
	player->x, player->y, player->health, player->angle, player->dx, player->dy, player->shoot_n, player->exchange);
}

void	restart_round(void)
{
	init_player_team();
}

void	render_kill_log()
{
	int		i;
	t_list	*tmp;
	t_elem	*log;

	tmp = _log()->log;
	i = 0;
	while (tmp && i < 5)
	{
		log = (t_elem *)tmp->content;
		draw_text_scale(
			ft_strjoin(_var()->o_player[log->ids[0]].pseudo, ft_strjoin(
				" killed ", _var()->o_player[log->ids[1]].pseudo)),
				pos(200, 50 + i * 20), pos(4, 4), WHITE);
		tmp = tmp->next;
		i++;
	}
}

void	ft_pong_client(void)
{
	t_send_server_game	serv;
	t_send_client_game	client;
	int					i;
	static int			incremented = 0;
	
	i = 0;
	memset(&client, 0, sizeof(client));
	ft_copy_data_before_pong(&client.player);
	client.blue_wins = _team()[TEAM_BLUE]->win;
	client.red_wins = _team()[TEAM_RED]->win;
	client.round_end = 0;
	if (incremented == 1 &&( _var()->alive[TRED] == 0 || _var()->alive[TBLUE] == 0))
		incremented++;
	if (incremented == 2)
		client.round_end = 1;
	client.restart = 0;
	if(_var()->restart == 1)
	{
		client.restart = 1;
		_var()->restart = 0;
	}
	if (send(_var()->socket, &client, sizeof(client), 0) <= 0)
	{
		_var()->mode = MENU;
		_menu()->mode = MENU_START;
		restart_player();
		mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
		return ;
	}
	_player()->is_shooting = 0;
	memset(&serv, 0, sizeof(serv));
	_var()->alive[TRED] = 0;
	_var()->alive[TBLUE] = 0;
	if (recv(_var()->socket, &serv, sizeof(serv), MSG_WAITALL) <= 0)
	{
		_var()->mode = MENU;
		_menu()->mode = MENU_START;
		restart_player();
		mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
		return ;
	}
	_var()->linked_players = serv.linked_players;
	while (i < _var()->linked_players)
	{
		if (serv.player[i].is_shooting > 0 && i != _player()->id)
			ft_play_shot_sound(serv.player[i]);
		if (serv.player[i].shooted.shoot == 1 && serv.player[i].shooted.id == _player()->id)
			_player()->health -= _weapon()[serv.player[i].weapon_id]->power;
		else if (serv.player[i].shooted.shoot == 2 && serv.player[i].shooted.id == _player()->id)
			_player()->health -= _weapon()[serv.player[i].weapon_id]->headshot;
		else if (serv.player[i].shooted.shoot == 3 && serv.player[i].shooted.id == _player()->id)
			_player()->health -= _weapon()[serv.player[i].weapon_id]->footshot;
		if (serv.player[i].shooted.shoot > 0 && i == _player()->id)
		{
			_player()->shooted.shoot = 0;
			_player()->shooted.id = -1;
		}
		if (serv.player[i].team == TEAM_BLUE && !serv.player[i].is_dead)
			_var()->alive[TBLUE]++;
		if (serv.player[i].team == TEAM_RED && !serv.player[i].is_dead)
			_var()->alive[TRED]++;
		if (_var()->o_player[i].kills < serv.player[i].kills)
			ft_lstadd_back(&_log()->log, ft_lstnew((void *)new_log(serv.player
				[i].id, serv.player[i].kill_round[serv.player[i].nr - 1])));

		int	j = 0;
		while (j < serv.player[i].shoot_n)
		{
			_var()->o_player[i].shott[j] = serv.player[i].shott[j];
			_var()->o_player[i].shott[j].pos = serv.player[i].shott[j].pos;
			++j;
		}
		_var()->o_player[i] = serv.player[i];
		++i;
	}
	if (_var()->alive[TBLUE] == 0 && !incremented)
	{
		_var()->last_round_winner = TRED;
		++_team()[TEAM_RED]->win;
		++_team()[TEAM_BLUE]->loose;
		incremented = 1;
	}
	else if (_var()->alive[TRED] == 0 && !incremented)
	{
		_var()->last_round_winner = TBLUE;
		++_team()[TEAM_BLUE]->win;
		++_team()[TEAM_RED]->loose;
		incremented = 1;
	}
	_var()->round_state = serv.round_state;
	if (serv.round_state == ROUND_LEADERBOARD && serv.match_finished == 1)
		_var()->match_finished = 1;
	else if (_var()->round_state == ROUND_END_WAIT)
	{
		_var()->freeze = 1;
	}
	if (_var()->round_state == ROUND_WAIT_START)
	{
		restart_player();
		init_player_team();
	}
	if (_var()->round_state == ROUND_START)
	{
		incremented = 0;
		_var()->freeze = 0;
	}
	if (_var()->match_finished)
	{
		_var()->mode = MENU;
		_menu()->mode = MENU_LEADERBOARD;
		_var()->freeze = 0;
		incremented = 0;
	}
	if (serv.restart == 1)
	{
		restart_player();
		_var()->mode = MENU;
		_menu()->mode = MENU_LOBBY;
		_var()->freeze = 0;
	}
}

