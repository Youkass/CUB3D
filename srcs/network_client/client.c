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
	buf = malloc(sizeof(char) * BUFFER_SIZE);
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
	printf("je reçois mon id : %d\n", _player()->id);
	if (recv(_var()->socket, &(_var()->nb_player), sizeof(int), 0) < 0)
		return (EXIT_FAILURE);
	printf("je sors de la fonction\n");
	return (EXIT_SUCCESS);
}

void	ft_copy_data_before_pong(t_obj *player)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	player->team = _player()->team;
	player->change_team = _player()->change_team;
	player->id = _player()->id;
	player->x = _player()->x;
	player->y = _player()->y;
	player->z = _player()->z;
	player->c = _player()->c;
	player->dx = _player()->dx;
	player->dy = _player()->dy;
	player->da = _player()->da;
	player->old_dx = _player()->old_dx;
	player->old_dy = _player()->old_dy;
	player->angle = _player()->angle;
	player->move_speed = _player()->move_speed;
	player->rot_speed = _player()->rot_speed;
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
    player->ammo = _player()->ammo;
	player->shoot_n = _player()->shoot_n;
	player->exchange = _player()->exchange;
	player->is_start = _player()->is_start;
	while (i < _player()->shoot_n)
	{
		player->shott[i] = _player()->shott[i];
		while (j < SHOT_FRAME)
		{
			player->shott[i].n_pos[j] = _player()->shott[i].n_pos[j];
			j++;
		}
		i++;
	}
	memset(player->pseudo, 0, sizeof(player->pseudo));
	strcpy(player->pseudo, _player()->pseudo);
}

// void	ft_pong_client(void)
// {
// 	t_obj	player;
// 	int		i;
	
// 	i = 0;
// 	memset(&player, 0, sizeof(player));
// 	ft_copy_data_before_pong(&player);
// 	if (send(_var()->socket, &player, sizeof(player), 0)< 0)
// 		return ;
// 	while (i < _var()->linked_players)
// 	{
// 		if (recv(_var()->socket, &player, sizeof(player), 0) < 0)
// 			return ;
// 		if (player.shooted.shoot == 1 && player.shooted.id == _player()->id)
// 			_player()->health -= _weapon()[player.weapon_id].power;
// 		if (player.shooted.shoot == 1 && i == _player()->id)
// 		{
// 			_player()->shooted.shoot = 0;
// 			_player()->shooted.id = -1;
// 		}
// 		_var()->o_player[i] = player;
// 		_var()->o_player[i].id = i;
// 		++i;
// 	}
// }

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

void	ft_pong_client(void)
{
	t_send_server_game	serv;
	t_obj				my_player;	
	int					i;
	static int			incremented = 0;
	
	i = 0;

	memset(&my_player, 0, sizeof(my_player));
	ft_copy_data_before_pong(&my_player);
	if (send(_var()->socket, &my_player, sizeof(my_player), 0) < 0)
		return ;
	memset(&serv, 0, sizeof(serv));
	if (recv(_var()->socket, &serv, sizeof(serv), MSG_WAITALL) < 0)
		return ;
	while (i < _var()->linked_players)
	{
		if (serv.player[i].is_shooting > 0)
			ft_play_sound(i);
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
		_var()->o_player[i] = serv.player[i];
		_var()->o_player[i].id = i;
		//_player()->team = serv.player[i].team;
		++i;
	}
	_var()->round_state = serv.round_state;
	if (_var()->round_state == ROUND_END)
	{
		printf("%d WIN THE ROUND\n", serv.round_winner);
		if (serv.round_winner == TRED && incremented == 0)
		{
			_var()->last_round_winner = TRED;
			++_team()[TEAM_RED]->win;
			++_team()[TEAM_BLUE]->loose;
			incremented += 1;
		}
		else if (serv.round_winner == TBLUE && incremented == 0)
		{
			_var()->last_round_winner = TBLUE;
			++_team()[TEAM_BLUE]->win;
			++_team()[TEAM_RED]->loose;
			incremented += 1;
		}
		_var()->freeze = 1;
	}
	else if (_var()->round_state == ROUND_END_WAIT)
	{
		incremented = 0;
		_var()->freeze = 1;
	}
	if (_var()->round_state == ROUND_WAIT_START)
	{
		restart_player();
		init_player_team();
	}
	if (_var()->round_state == ROUND_START)
		_var()->freeze = 0;
}
