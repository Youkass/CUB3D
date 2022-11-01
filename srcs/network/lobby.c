/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/31 16:59:00 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_recv_first_data_lobby(t_client_thread *client)
{
	if (!client->is_recv)
	{
		pthread_mutex_lock(client->mutex);
		if (recv(client->socket, &(client->player_data), 
			sizeof(t_obj), 0) < 0)
			return (1);
		client->is_recv = 1;
		client->serv->player_data[client->id] = client->player_data;
		pthread_mutex_unlock(client->mutex);
	}
	return (0);
}

int	ft_is_get_lobby(t_client_thread *client)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < client->serv->linked_players)
	{
		if (!client->serv->clients[i].is_recv)
		{
			pthread_mutex_unlock(client->mutex);
			return (1);
		}
		++i;
	}
	pthread_mutex_unlock(client->mutex);
	return (0);
}

static int	ft_has_start(t_client_thread *client)
{
	pthread_mutex_lock(client->mutex);
	if (client->serv->started)
		return (pthread_mutex_unlock(client->mutex), 1);
	return (pthread_mutex_unlock(client->mutex), 0);
}

int	ft_send_all_data_lobby(t_client_thread *client)
{
	static __thread int i = 0;
	int		nb;
	t_obj	data;

	pthread_mutex_lock(client->mutex);
	if (send(client->socket, &client->serv->linked_players, sizeof(int), 0) < 0)
		return (pthread_mutex_unlock(client->mutex), 1);
	nb = client->serv->linked_players;
	pthread_mutex_unlock(client->mutex);
	if (client->id == 0)
	{
		pthread_mutex_lock(client->mutex);
		if (recv(client->socket, &(client->serv->started), sizeof(int), 0) < 0)
			return (pthread_mutex_unlock(client->mutex), 1);
		pthread_mutex_unlock(client->mutex);
	}
	else if (client->id != 0)
	{
		pthread_mutex_lock(client->mutex);
		if (send(client->socket, &(client->serv->started), sizeof(int), 0) < 0)
			return (pthread_mutex_unlock(client->mutex), 1);
		pthread_mutex_unlock(client->mutex);
	}
	if (ft_has_start(client))
		return (0);
	while (i < nb)
	{
		memset(&data, 0, sizeof(data));
		pthread_mutex_lock(client->mutex);
		data = client->serv->player_data[i];
		printf("client->id : %d\n", client->id);
		printf("pseudo send to the id : %s\n", data.pseudo);
		if (send(client->socket, &data, sizeof(data), 0) < 0)
			return (1);
		pthread_mutex_unlock(client->mutex);
		i++;
	}
	return (0);
}

int	wait_lobby(t_client_thread *client)
{
	while (1)
	{
		if (ft_recv_first_data_lobby(client))
			return (1);
		if (ft_send_all_data_lobby(client))
			return (1);
		pthread_mutex_lock(client->mutex);
		if (client->serv->started)
			return (pthread_mutex_unlock(client->mutex), 0);
		pthread_mutex_unlock(client->mutex);
	}
	return (0);
}
