/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/09 01:48:04 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	ft_has_recv(t_client_thread *client, int nb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < nb)
	{
		if (!client->serv->clients[i].is_recv)
			return (pthread_mutex_unlock(client->mutex), 1);
		++i;
	}
	pthread_mutex_unlock(client->mutex);
	return (0);
}

static int	ft_has_sent(t_client_thread *client, int nb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < nb)
	{
		if (!client->serv->clients[i].is_send)
			return (pthread_mutex_unlock(client->mutex), 1);
		++i;
	}
	pthread_mutex_unlock(client->mutex);
	return (0);
}

static int	ft_has_start(t_client_thread *client)
{
	pthread_mutex_lock(client->mutex);
	if (!client->serv->started)
		return (pthread_mutex_unlock(client->mutex), 1);
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_recv_first_data_lobby(t_client_thread *client, int nb)
{
	t_send_client	player;
	
	memset(&player, 0, sizeof(player));
	if (ft_recv_one(client->socket, &player, 
				sizeof(t_send_client)))
		return (1);
	pthread_mutex_lock(client->mutex);
	if (player.flag || player.player.pseudo[0])
		client->serv->player_data[client->id] = player.player;
	client->is_send = 0;
	client->is_recv = 1;
	if (player.start)
		client->serv->started = 1;
	pthread_mutex_unlock(client->mutex);
	client->player_data = player.player;
	while (ft_has_recv(client, nb))
	{}
	return (0);
}

int	ft_send_all_data_lobby(t_client_thread *client, int nb)
{
	t_send_server	o_player;
	int		i;

	i = 0;
	memset(&o_player, 0, sizeof(o_player));
	memset(&o_player.player, 0, sizeof(t_obj[MAX_PLAYER]));
	pthread_mutex_lock(client->mutex);
	if (client->serv->started)
		o_player.start = 1;
	else
		o_player.start = 0;
	while (i < nb)
	{
		o_player.player[i] = client->serv->player_data[i];
		++i;
	}
	pthread_mutex_unlock(client->mutex);
	o_player.linked_pl = nb;
	o_player.flag = 1;
	if (send(client->socket, &o_player, sizeof(t_send_server), 0) < 0)
		return (1);
	i = 0;
	pthread_mutex_lock(client->mutex);
	client->is_send = 1;
	pthread_mutex_unlock(client->mutex);
	while (ft_has_sent(client, nb))
	{}
	pthread_mutex_lock(client->mutex);
	client->is_recv = 0;
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_player_team(t_client_thread *client, int id)
{
	int	i;

	i = 0;
	while (i < client->serv->nb_blue)
	{
		if (id == client->serv->teams[1].array[i++])
			return (2);
	}
	i = 0;
	while (i < client->serv->nb_red)
	{
		if (id == client->serv->teams[0].array[i++])
			return (0);
	}
	return (1);
}

int	ft_update(t_client_thread *client)
{
	pthread_mutex_lock(client->mutex);
	if (client->player_data.team == TEAM_RED && client->serv->player_data[client->id].change_team == 1)
	{
		arr_pop(&client->serv->teams[1], client->id);
		if (!arr_push(&client->serv->teams[0], client->id))
			client->serv->player_data[client->id].team = TEAM_VOID;
		client->serv->player_data[client->id].change_team = 0;
	}
	else if (client->player_data.team == TEAM_BLUE && client->serv->player_data[client->id].change_team == 1)
	{
		arr_pop(&client->serv->teams[0], client->id);
		if (!arr_push(&client->serv->teams[1], client->id))
			client->serv->player_data[client->id].team = TEAM_VOID;
		client->serv->player_data[client->id].change_team = 0;
	}
	else if (client->serv->player_data[client->id].change_team == 1)
	{
		arr_pop(&client->serv->teams[0], client->id);
		arr_pop(&client->serv->teams[1], client->id);
		client->serv->player_data[client->id].change_team = 0;
	}
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	wait_lobby(t_client_thread *client)
{
	int	nb;

	while (1)
	{
		pthread_mutex_lock(client->mutex);
		nb = client->serv->linked_players;
		pthread_mutex_unlock(client->mutex);
		if (ft_recv_first_data_lobby(client, nb))
			return (1);
		if (ft_update(client))
			return (1);
		if (ft_send_all_data_lobby(client, nb))
			return (1);
		if (!ft_has_start(client))
			return (printf("je sors bien de wait_lobby\n"), 0);
	}
	return (0);
}
