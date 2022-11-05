/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:18:07 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/11/05 15:34:40 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
/*
void	ft_exit(int signal)
{
	(void)signal;
	pthread_mutex_unlock(data->mutex);
	printf("client fermé\n");
}*/
int	ft_init_client_thread(t_server_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->mutex), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(data->mutex_start), NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&(data->mutex_linked), NULL))
		return (EXIT_FAILURE);
	while (i < data->nb_players)
	{
		data->clients[i].nb_players = data->nb_players;
		data->clients[i].id = i;
		data->clients[i].mutex = &data->mutex;
		data->clients[i].mutex_start = &data->mutex_start;
		data->clients[i].mutex_linked = &data->mutex_linked;
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
		data->clients[i].is_recv = 0;
		data->clients[i].socket = accept(data->socket,
			(struct sockaddr *)&(data->server), &(data->clients[i].csize));
		data->clients[i].start = 0;
		data->clients[i].id = i;
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
	if (recv(client->socket, &(client->player_data),
				sizeof(client->player_data), MSG_WAITALL) < 0)
		return (1);
	pthread_mutex_lock(client->mutex);
	client->is_recv = 1;
	client->is_send = 0;
	client->serv->player_data[client->id] = client->player_data;
	pthread_mutex_unlock(client->mutex);
	while (ft_is_get(client))
	{}
	return (0);
}

int	ft_is_get(t_client_thread *client)
{
	int	i;

	i = 0;
	while (i < client->nb_players)
	{
		pthread_mutex_lock(client->mutex);
		if (!client->serv->clients[i].is_recv)
		{
			pthread_mutex_unlock(client->mutex);
			return (1);
		}
		pthread_mutex_unlock(client->mutex);
		++i;
	}
	return (0);
}

int ft_is_send(t_client_thread *client)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < client->nb_players)
	{
		if (!client->serv->clients[i].is_send)
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
	t_obj	data[MAX_PLAYER];

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < client->nb_players)
	{
		data[i] = client->serv->player_data[i];
		++i;
	}
	pthread_mutex_unlock(client->mutex);
	if (send(client->socket, &data, sizeof(data), 0) < 0)
		return (1);
	pthread_mutex_lock(client->mutex);
	client->is_send = 1;
	pthread_mutex_unlock(client->mutex);
	while (ft_is_send(client))
	{}
	pthread_mutex_lock(client->mutex);
	client->is_recv = 0;
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	send_nb_players(t_client_thread *client)
{
	if (send(client->socket, &(client->nb_players), sizeof(int), 0) < 0)
		return (1);
	return (0);
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
	if (send_nb_players(client))
		return (NULL);
	if (wait_lobby(client))
		return (NULL);
	pthread_mutex_lock(client->mutex);
	client->is_recv = 0;
	client->is_send = 0;
	pthread_mutex_unlock(client->mutex);
	while (1)
	{
		if (ft_recv_first_data(client))
			return (NULL);
		if (ft_send_all_data(client))
			return (NULL);
	}
	return (NULL);
}
