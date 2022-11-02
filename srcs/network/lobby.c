/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/02 14:08:55 by yobougre         ###   ########.fr       */
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

static void	ft_can_start(t_client_thread *client, int nb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < nb)
	{
		if (client->serv->player_data[i].is_start)
		{
			client->serv->player_data[client->id].is_start = 1;
			pthread_mutex_unlock(client->mutex);
			return ;
		}
		++i;
	}
	pthread_mutex_unlock(client->mutex);
}

static int	ft_has_start(t_client_thread *client, int nb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < nb)
	{
		if (!client->serv->player_data[i].is_start)
			return (pthread_mutex_unlock(client->mutex), 1);
		++i;
	}
	client->serv->started = 1;
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_recv_first_data_lobby(t_client_thread *client, int nb)
{
	pthread_mutex_lock(client->mutex);
	if (recv(client->socket, &(client->player_data), 
				sizeof(t_obj), 0) < 0)
		return (pthread_mutex_unlock(client->mutex), 1);
	client->serv->player_data[client->id] = client->player_data;
	client->is_send = 0;
	client->is_recv = 1;
	pthread_mutex_unlock(client->mutex);
	while (ft_has_recv(client, nb))
	{}
	return (0);
}

int	ft_send_all_data_lobby(t_client_thread *client, int nb)
{
	t_obj	o_player[MAX_PLAYER];
	int		i;

	i = 0;
	ft_can_start(client, nb);
	memset(&o_player, 0, sizeof(o_player));
	pthread_mutex_lock(client->mutex);
	while (i < nb)
	{
		o_player[i] = client->serv->player_data[i];
		++i;
	}
	if (send(client->socket, &o_player, sizeof(o_player), 0) < 0)
		return (pthread_mutex_unlock(client->mutex), 1);
	client->is_send = 1;
	pthread_mutex_unlock(client->mutex);
	while (ft_has_sent(client, nb))
	{}
	pthread_mutex_lock(client->mutex);
	client->is_recv = 0;
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
		if (send(client->socket, &nb, sizeof(int), 0) < 0)
			return (1);
		if (ft_recv_first_data_lobby(client, nb))
			return (1);
		if (ft_send_all_data_lobby(client, nb))
			return (1);
		if (!ft_has_start(client, nb))
			return (printf("je sors bien de wait_lobby\n"), 0);
	}
	return (0);
}
