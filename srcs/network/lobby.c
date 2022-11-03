/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/02 17:36:02 by dasereno         ###   ########.fr       */
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

void	ft_can_start(t_client_thread *client, int nb)
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

int	ft_has_start(t_client_thread *client, int nb)
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

int	ft_recv_first_data_lobby(t_client_thread *client)
{
	t_send_client	cl;

	if (recv(client->socket, &(cl), sizeof(t_send_client), 0) < 0)
		return (pthread_mutex_unlock(client->mutex), 1);
	pthread_mutex_lock(client->mutex);
	client->player_data = cl.player;
	client->serv->player_data[client->id] = client->player_data;
	if (cl.start == 1)
		client->serv->started = 1;
	// nb = client->serv->linked_players;
	pthread_mutex_unlock(client->mutex);
	// while (ft_has_recv(client, nb))
	// {}
	return (0);
}

int	ft_send_all_data_lobby(t_client_thread *client)
{
	int				nb;
	t_send_server	pl;
	int		i;

	i = 0;
	memset(&pl.player, 0, sizeof(pl.player));
	memset(&pl, 0, sizeof(pl));
	pthread_mutex_lock(client->mutex);
	nb = client->serv->linked_players;
	while (i < nb)
	{
		pl.player[i] = client->serv->player_data[i];
		++i;
	}
	pl.start = 0;
	if (client->serv->started == 1)
		pl.start = 1;
	pl.linked_pl = nb;
	if (send(client->socket, &pl, sizeof(pl), 0) < 0)
		return (pthread_mutex_unlock(client->mutex), 1);
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	wait_lobby(t_client_thread *client)
{
	while (1)
	{
		// if (send(client->socket, &nb, sizeof(int), 0) < 0)
		// 	return (1);
		if (ft_recv_first_data_lobby(client))
			return (1);
		if (ft_send_all_data_lobby(client))
			return (1);
		if (client->serv->started == 1)
			break;
		// if (!ft_has_start(client, nb))
		// 	return (printf("je sors bien de wait_lobby\n"), 0);
	}
	return (0);
}
