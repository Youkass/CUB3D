/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/11/01 16:21:47 by yobougre         ###   ########.fr       */
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
		client->serv->player_data[client->id] = client->player_data;
		client->is_recv = 1;
		printf("server has recv data from id : %d\n", client->id);
		printf("pseudo recv : %s\n", client->player_data.pseudo);
		pthread_mutex_unlock(client->mutex);
	}
	return (0);
}

static int	ft_has_start(t_client_thread *client)
{
	pthread_mutex_lock(client->mutex);
	if (client->serv->started)
		return (pthread_mutex_unlock(client->mutex), 1);
	return (pthread_mutex_unlock(client->mutex), 0);
}


int	ft_send_all_data_lobby(t_client_thread *client, int nb)
{
	static __thread int i = 0;
	static __thread int flag = 0;
	t_obj	data;

	if (nb <= client->nb_players && !flag)
	{
		if (nb == client->nb_players)
			++flag;
		while (i < nb)
		{
			memset(&data, 0, sizeof(data));
			pthread_mutex_lock(client->mutex);
			data = client->serv->player_data[i];
			printf("send to id : %d ; pseudo : %s\n", client->id, data.pseudo);
			if (send(client->socket, &data, sizeof(data), 0) < 0)
				return (1);
			pthread_mutex_unlock(client->mutex);
			i++;
		}
	}
	else
	{
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
	}
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
		printf("id : %d, recv nb : %d\n", client->id, nb);
		if (ft_recv_first_data_lobby(client))
			return (1);
		if (ft_send_all_data_lobby(client, nb))
			return (1);
		pthread_mutex_lock(client->mutex);
		if (client->serv->started)
			return (pthread_mutex_unlock(client->mutex), 0);
		pthread_mutex_unlock(client->mutex);
	}
	return (0);
}
