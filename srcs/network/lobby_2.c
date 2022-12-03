/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:51:11 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:52:33 by dasereno         ###   ########.fr       */
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

int	ft_has_start(t_client_thread *client)
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
		;
	return (0);
}

void	ft_send_next(t_send_server *o_player, t_client_thread *client, int nb)
{
	int	i;

	i = 0;
	if (client->serv->started)
		o_player->start = 1;
	else
		o_player->start = 0;
	while (i < nb)
	{
		o_player->player[i] = client->serv->player_data[i];
		++i;
	}
}
