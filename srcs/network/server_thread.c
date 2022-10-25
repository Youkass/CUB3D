/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:18:07 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/10/25 20:33:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
/*
void	ft_exit(int signal)
{
	(void)signal;
	pthread_mutex_unlock(&_server()->mutex);
	printf("client fermé\n");
}*/

int	ft_init_client_thread(t_server_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&_server()->mutex, NULL))
		return (EXIT_FAILURE);
	while (i < data->nb_players)
	{
		data->clients[i].nb_players = data->nb_players;
		data->clients[i].id = i;
		data->clients[i].mutex = &_server()->mutex;
		data->clients[i].is_recv = 0;
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_connect_clients(t_server_data *data)
{
	int	i;

	i = 0;
	data->linked_players = 0;
	while (i < data->nb_players)
	{
		data->clients[i].csize = sizeof(data->clients[i].sockclient);
		data->clients[i].serv = data;
		data->clients[i].socket = accept(data->socket,
			(struct sockaddr *)&(data->server), &(data->clients[i].csize));
		printf("client socket accepted : %d\n", data->clients[i].socket);
		if (data->clients[i].socket < 0)
			return (EXIT_FAILURE); //TODO
		if (pthread_create(&(data->clients[i].thread_id), NULL, client_routine, 
				&(data->clients[i])))
			return (EXIT_FAILURE); //TODO
		i++;
	}
	i = 0;
	while (i < data->nb_players)
		pthread_join((data->clients[i++].thread_id), NULL);
	return (EXIT_SUCCESS);
}

int	ft_recv_first_data(t_client_thread *client)
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

int	ft_is_get(t_client_thread *client)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < client->nb_players)
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

int	ft_send_all_data(t_client_thread *client)
{
	int		i;
	t_obj	data;

	i = 0;
	if (!ft_is_get(client))
		return (1);
	int	sync = 0;

	if (send(client->socket, &sync, sizeof(sync), 0) < 0)
		return (1);
	while (i < client->nb_players)
	{
		pthread_mutex_lock(client->mutex);
		data = _server()->player_data[i];
		pthread_mutex_unlock(client->mutex);
		if (send(client->socket, &data, sizeof(data), 0) < 0)
			return (1);
		++i;
	}
	client->is_recv = 0;
	return (0);
}

int	send_nb_players(t_client_thread *client)
{
	int		i;
	char	c;

	i = 0;
	c = 1;
	if (client->id == 0)
	{
		pthread_mutex_lock(client->mutex);
		client->serv->nb_players = client->nb_players;
		pthread_mutex_unlock(client->mutex);
	}
	if (client->id != 0)
	{
		pthread_mutex_lock(client->mutex);
		client->nb_players = client->serv->nb_players;
		if (send(client->socket, &(client->serv->nb_players), sizeof(client->id), 0) < 0)
			return (0);
		pthread_mutex_unlock(client->mutex);
	}
	while (c != 0)
	{
		recv(client->socket, &c, sizeof(c), 0);
		_server()->player_data[client->id].pseudo[i] = c;
		i++;
	}
	return (1);
}

void	*client_routine(void *client_t)
{
	t_client_thread	*client;

	client = (t_client_thread *)client_t;
	signal(SIGPIPE, SIG_IGN);
	pthread_mutex_lock(client->mutex);
	client->serv->linked_players += 1;
	pthread_mutex_unlock(client->mutex);
	if (send(client->socket, &(client->id), sizeof(client->id), 0) < 0)
		return (NULL);
	if (!send_nb_players(client))
		return (NULL);
	printf("can start lobbying\n");
	if (!wait_lobby(client))
		return (NULL);
	printf("on est la\n");
	while (1)
	{
		if (ft_recv_first_data(client) == EXIT_FAILURE)
			return (NULL);
		if (ft_send_all_data(client))
			return (NULL);
	}
	return (NULL);
}
