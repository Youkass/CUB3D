/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:46:34 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:46:53 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	ft_lock(t_client_thread *client, t_send_server_game data)
{
	if (send(client->socket, &data, sizeof(data), 0) < 0)
		return (1);
	pthread_mutex_lock(client->mutex);
	client->is_send = 1;
	client->is_recv = 0;
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_send_all_data(t_client_thread *client)
{
	t_send_server_game	data;
	static __thread int	round = 0;

	pthread_mutex_lock(client->mutex);
	memset(&data, 0, sizeof(data));
	ft_init_dt(client, &data);
	if (client->serv->restart)
	{
		client->restart = 1;
		data.restart = 1;
		round = 0;
	}
	ft_next(client, &data);
	round_play(round, &data, client, client->serv->round_end);
	round_end_wait(&data, client);
	round_leaderboard(&data, client);
	round_end(&data, client);
	round_wait_start(&data, client);
	round_start(&round, &data, client);
	pthread_mutex_unlock(client->mutex);
	if (ft_lock(client, data))
		return (1);
	return (0);
}

static int	ft_help_send_zero(t_client_thread *client)
{
	if (recv(client->socket, &client->serv->map,
			sizeof(client->serv->map),
			MSG_WAITALL) <= 0)
		return (1);
	if (recv(client->socket, &client->serv->map_width,
			sizeof(client->serv->map_width),
			MSG_WAITALL) <= 0)
		return (1);
	if (recv(client->socket, &client->serv->map_height,
			sizeof(client->serv->map_height),
			MSG_WAITALL) <= 0)
		return (1);
	return (0);
}

static int	ft_help_send_else(t_client_thread *client)
{
	if (send(client->socket, &client->serv->map,
			sizeof(client->serv->map), 0) <= 0)
		return (1);
	if (send(client->socket, &client->serv->map_width,
			sizeof(client->serv->map_width), 0) <= 0)
		return (1);
	if (send(client->socket, &client->serv->map_height,
			sizeof(client->serv->map_height), 0) <= 0)
		return (1);
	return (0);
}

int	send_nb_players(t_client_thread *client)
{
	int	pid;

	pid = (int)getpid();
	if (send(client->socket, &(client->nb_players), sizeof(int), 0) <= 0)
		return (1);
	if (send(client->socket, &pid, sizeof(int), 0) <= 0)
		return (1);
	if (client->id == 0)
	{
		if (ft_help_send_zero(client))
			return (1);
	}
	else
	{
		if (ft_help_send_else(client))
			return (1);
	}
	return (0);
}
