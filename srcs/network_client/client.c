/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:34:29 by yobougre          #+#    #+#             */
/*   Updated: 2022/12/03 18:54:32 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	round_handling(int *incremented, t_send_server_game serv)
{
	if (_var()->alive[TBLUE] == 0 && !*incremented)
	{
		_var()->last_round_winner = TRED;
		++_team()[TEAM_RED]->win;
		++_team()[TEAM_BLUE]->loose;
		*incremented = 1;
	}
	else if (_var()->alive[TRED] == 0 && !*incremented)
	{
		_var()->last_round_winner = TBLUE;
		++_team()[TEAM_BLUE]->win;
		++_team()[TEAM_RED]->loose;
		*incremented = 1;
	}
	_var()->round_state = serv.round_state;
	if (serv.round_state == ROUND_LEADERBOARD && serv.match_finished == 1)
		_var()->match_finished = 1;
	else if (_var()->round_state == ROUND_END_WAIT)
		_var()->freeze = 1;
	ft_round_handling(incremented, serv);
	if (serv.round_state == ROUND_WAIT_START)
		_var()->time_start = serv.time;
}

static void	ft_if_not_send(void)
{
	_var()->mode = MENU;
	_menu()->mode = MENU_START;
	restart_player();
	mlx_mouse_show(_mlx()->mlx, _mlx()->mlx_win);
}

static int	ft_recv(int *incremented)
{
	int					i;
	t_send_server_game	serv;

	_player()->is_shooting = 0;
	i = 0;
	memset(&serv, 0, sizeof(serv));
	_var()->alive[TRED] = 0;
	_var()->alive[TBLUE] = 0;
	if (recv(_var()->socket, &serv, sizeof(serv), MSG_WAITALL) <= 0)
	{
		ft_if_not_send();
		return (1);
	}
	_var()->linked_players = serv.linked_players;
	while (i < _var()->linked_players)
	{
		get_data(i, serv);
		++i;
	}
	round_handling(incremented, serv);
	return (0);
}

static void	ft_pong_first(t_send_client_game *client)
{
	memset(client, 0, sizeof(*client));
	ft_copy_data_before_pong(&client->player);
}

void	ft_pong_client(void)
{
	t_send_client_game	client;
	static int			incremented = 0;

	ft_pong_first(&client);
	client.blue_wins = _team()[TEAM_BLUE]->win;
	client.red_wins = _team()[TEAM_RED]->win;
	client.round_end = 0;
	if (incremented == 1 && (_var()->alive[TRED] == 0
			|| _var()->alive[TBLUE] == 0))
		incremented++;
	if (incremented == 2)
		client.round_end = 1;
	client.restart = 0;
	if (_var()->restart == 1)
	{
		client.restart = 1;
		_var()->restart = 0;
	}
	if (send(_var()->socket, &client, sizeof(client), 0) <= 0)
	{
		ft_if_not_send();
		return ;
	}
	if (ft_recv(&incremented))
		return ;
}
