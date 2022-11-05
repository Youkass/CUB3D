/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/05 12:05:40 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_has_recv(t_client_thread *client, int nb)
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

int	ft_has_sent(t_client_thread *client, int nb)
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

int	ft_recv_first_data_lobby(t_client_thread *client)
{
	t_send_client	player;
	
	memset(&player, 0, sizeof(player));
	if (ft_recv_one(client->socket, &player, 
				sizeof(t_send_client)))
		return (1);
	pthread_mutex_lock(client->mutex);
	if (player.flag || player.player.pseudo)
		client->serv->player_data[client->id] = player.player;
	client->is_send = 0;
	client->is_recv = 1;
	if (player.start)
		client->serv->started = 1;
	printf("NB : %d RECV FROM ID : %d\n", nb , client->id);
	pthread_mutex_unlock(client->mutex);
	// while (ft_has_recv(client, nb))
	// {}
	return (0);
}

int	ft_send_all_data_lobby(t_client_thread *client)
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
	printf("SEND TO ID : %d\n", client->id);
	client->is_send = 1;
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	wait_lobby(t_client_thread *client)
{
	while (1)
	{
		pthread_mutex_lock(client->mutex);
		nb = client->serv->linked_players;
//		printf("client->id : %d nb : %d\n", client->id, nb);
		pthread_mutex_unlock(client->mutex);
//		if (send(client->socket, &nb, sizeof(int), 0) < 0)
//			return (1);
		if (ft_recv_first_data_lobby(client, nb))
			return (1);
		if (ft_send_all_data_lobby(client, nb))
			return (1);
		//usleep(20000);
		if (!ft_has_start(client))
			return (printf("je sors bien de wait_lobby\n"), 0);
	}
	return (0);
}
