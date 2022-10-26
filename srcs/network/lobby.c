/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lobby.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:24:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/10/26 18:40:20 by yobougre         ###   ########.fr       */
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
		_server()->player_data[client->id] = client->player_data;
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
	static __thread int i = 0;
	int		nb;
	t_obj	data;

	if (recv(client->socket, &nb, sizeof(nb), 0)< 0)
		return (1);
	pthread_mutex_lock(client->mutex);
	if (nb == -1 && client->id == 0)
		client->serv->started = 1;
	nb = client->serv->linked_players;
	if (client->serv->started == 1)
		nb = -1;
	if (nb == -1 && client->id == 0)
	{
		pthread_mutex_unlock(client->mutex);
		return (0);
	}
	pthread_mutex_unlock(client->mutex);
	if (send(client->socket, &nb, sizeof(nb), 0) < 0)
		return (1);
	if (nb == -1)
		return (0);
	if (!ft_is_get(client))
		return (1);
	while (i < nb)
	{
		pthread_mutex_lock(client->mutex);
		data = _server()->player_data[i];
		pthread_mutex_unlock(client->mutex);
		if (send(client->socket, &data, sizeof(data), 0) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	wait_lobby(t_client_thread *client)
{
	int	link;

	(void)link;
	while (1)
	{
		if (ft_recv_first_data_lobby(client) == EXIT_FAILURE)
			return (0);
		if (ft_send_all_data_lobby(client) == EXIT_FAILURE)
			return (0);
		if (client->serv->started == 1)
			break ;
	}
	link = 0;
//	if (recv(client->socket, &link, sizeof(link), 0)< 0)
//		return (1);
//	if (send(client->socket, &link, sizeof(link), 0)< 0)
//		return (1);
	return (1);
}
