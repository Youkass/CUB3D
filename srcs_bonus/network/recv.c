/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:49:56 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

void	ft_help_first_recv(t_client_thread *client, t_send_client_game data)
{
	if (data.restart == 1)
		client->serv->restart = 1;
	client->player_data = data.player;
	if (client->id == 0)
	{
		client->serv->team_data[TBLUE].wins = data.blue_wins;
		client->serv->team_data[TRED].looses = data.blue_wins;
		client->serv->team_data[TRED].wins = data.red_wins;
		client->serv->team_data[TBLUE].looses = data.red_wins;
	}
	client->serv->round_end = data.round_end;
	client->is_recv = 1;
	client->is_send = 0;
	client->serv->player_data[client->id] = client->player_data;
}

int	ft_recv_first_data(t_client_thread *client)
{
	t_send_client_game	data;
	int					ret;

	memset(&data, 0, sizeof(data));
	ret = recv(client->socket, &(data), sizeof(data), MSG_WAITALL);
	if (ret < 0)
		return (1);
	pthread_mutex_lock(client->mutex);
	if (ret == 0)
	{
		client->serv->linked_players -= 1;
		pthread_mutex_unlock(client->mutex);
		return (1);
	}
	ft_help_first_recv(client, data);
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_is_get(t_client_thread *client)
{
	int	i;

	i = 0;
	while (1)
	{
		usleep(10000);
		pthread_mutex_lock(client->mutex);
		if (i >= client->serv->linked_players)
			break ;
		if (!client->serv->clients[i].is_recv)
		{
			pthread_mutex_unlock(client->mutex);
			return (1);
		}
		++i;
		pthread_mutex_unlock(client->mutex);
	}
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_is_send(t_client_thread *client)
{
	int	i;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < client->serv->linked_players)
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

void	ft_next(t_client_thread *client, t_send_server_game *data)
{
	data->round_state = -1;
	data->linked_players = client->serv->linked_players;
	data->round_winner = -1;
	data->blue_alive = client->serv->blue_alive;
	data->red_alive = client->serv->red_alive;
	data->player_alive = client->serv->player_alive;
}
