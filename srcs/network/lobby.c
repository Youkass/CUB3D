/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/24 18:00:24 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_recv_first_data_lobby(t_client_thread *client)
{
	if (!client->is_recv)
	{
		if (recv(client->socket, &(client->player_data), 
			sizeof(client->player_data), 0) < 0)
			return (1);
		client->is_recv = 1;
		pthread_mutex_lock(client->mutex);
		_server()->player_data[client->id].id = client->player_data.id;
		pthread_mutex_unlock(client->mutex);
		printf("%s\n", client->player_data.pseudo);
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
		if (!_server()->clients[i].is_recv)
		{
			pthread_mutex_unlock(client->mutex);
			return (1);
		}
		++i;
	}
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_send_all_data_lobby(t_client_thread *client)
{
	int		i;
	int		nb;
	int		j;
	t_obj	data;
	int		len;

	int	useless;
	pthread_mutex_lock(client->mutex);
	nb = client->serv->linked_players;
	pthread_mutex_unlock(client->mutex);
	i = 0;
	if (!ft_is_get(client))
		return (1);
	if (send(client->socket, &nb, sizeof(nb), 0) < 0)
		return (1);
	if (recv(client->socket, &useless, sizeof(useless), 0) < 0)
				return (1);
	while (i < nb)
	{
		pthread_mutex_lock(client->mutex);
		data = _server()->player_data[i];
		pthread_mutex_unlock(client->mutex);
		if (send(client->socket, &data.id, sizeof(data.id), 0) < 0)
			return (1);
		if (recv(client->socket, &useless, sizeof(useless), 0) < 0)
			return (1);
		len = ft_strlen(data.pseudo);
		j = 0;
		while (j < len + 1)
		{
			if (send(client->socket, &data.pseudo[j], sizeof(data.pseudo[j]), 0) < 0)
				return (1);
			j++;
		}
		recv(client->socket, &len, sizeof(int), 0);
		i++;
	}
	client->is_recv = 0;
	return (0);
}

int	wait_lobby(t_client_thread *client)
{
	int	okay;

	while (1)
	{
		pthread_mutex_lock(client->mutex);
		okay = client->serv->linked_players;
		if (client->serv->started == 1)
		{
			pthread_mutex_unlock(client->mutex);
			break ;
		}
		pthread_mutex_unlock(client->mutex);
		if (send(client->socket, &okay, sizeof(int), 0) < 0)
			return (0);
		recv(client->socket, &okay, sizeof(int), 0);
		if (okay == -1)
			break;
		if (send(client->socket, &okay, sizeof(int), 0) < 0)
			return (0);
		if (ft_recv_first_data_lobby(client) == EXIT_FAILURE)
			return (0);
		if (ft_send_all_data_lobby(client) == EXIT_FAILURE)
			return (0);
		usleep(1000);
	}
	if (client->id == 0)
	{
		pthread_mutex_lock(client->mutex);
		client->serv->started = 1;
		pthread_mutex_unlock(client->mutex);
	}
	else
	{
		okay = -1;
		if (send(client->socket, &okay, sizeof(okay), 0) < 0)
			return (0);
	}
	if (recv(client->socket, &(okay), sizeof(okay), 0) < 0)
		return (0);
	if (send(client->socket, &okay, sizeof(okay), 0) < 0)
		return (0);
	if (recv(client->socket, &(okay), sizeof(okay), 0) < 0)
		return (0);
	return (1);
}
