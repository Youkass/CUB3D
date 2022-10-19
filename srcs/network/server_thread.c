/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:18:07 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/10/19 18:30:50 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	ft_exit(int signal)
{
	(void)signal;
	pthread_mutex_unlock(&_server()->mutex);
	printf("server fermé\n");
	free(_server());
	exit(1);
}

int	ft_init_client_thread(t_server_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_players)
	{
		data->clients[i].nb_players = data->nb_players;
		data->clients[i].id = i;
		data->clients[i].mutex = &_server()->mutex;
		data->clients[i].is_recv = 0;
		if (pthread_mutex_init(data->clients[i].mutex, NULL))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_connect_clients(t_server_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_players)
	{
		data->clients[i].csize = sizeof(data->clients[i].sockclient);
		data->clients[i].socket = accept(data->socket,
			(struct sockaddr *)&(data->server), &(data->clients[i].csize));
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
			ft_exit(1);
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

int	is_shoot_touch(t_vector2F a, t_vector2F b, t_vector2F c, float r)
{
	float		r2;
	float		len;
	t_vector2F	n;
	float		dist;
	float		index;

	a = (t_vector2F){a.x - c.x, a.y - c.y};
	b = (t_vector2F){b.x - c.x, b.y - c.y};
	r2 = r * r;
	if (a.x * a.x + a.y * a.y <= r2)
		return (1);
	if (b.x * b.x + b.y * b.y <= r2)
		return (1);
	len = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	n.x = b.y - a.y;
	n.y = a.x - b.x;
	dist = n.x * a.x + n.y * a.y;
	dist = dist * dist;
	if (dist > len * r2)
		return (0);
	index = (a.x*(a.x - b.x) + a.y*(a.y - b.y));
	if (index < 0)
		return (0);
	if (index > len)
		return (0);
	return (1);
}

void	shoot(t_client_thread *client)
{
	int	i;

	i = 0;
	while (i < client->nb_players)
	{
		if (is_shoot_touch((t_vector2F){_server()->player_data[client->id].x, _server()->player_data[client->id].y},
			(t_vector2F){_server()->player_data[client->id].x + (_server()->player_data[client->id].dx * 150), _server()->player_data[client->id].y
			+ (_server()->player_data[client->id].dy * 150)}, (t_vector2F){_server()->player_data[i].x,
			_server()->player_data[i].y}, 1))
		{
			printf("hey\n");
			_server()->player_data[i].death_start = get_clock(_server()->clock);
			_server()->player_data[i].is_dead = 1;
			_server()->player_data[i].death_n = 0;
		}
		i++;
	}
}

/*
-Function that call every routine before sending all data. It iterate through
all player.
*/

void	routine_before_send(t_client_thread *client)
{
	int	i;

	i = 0;
	while (i < client->nb_players)
	{
		//CALL FUNCTION IN THIS WHILE
		if (_server()->player_data[i].shooted == 1)
		{
			shoot(client);
			_server()->player_data[i].shooted = 0;
		}
		i++;
	}
}

void	ft_send_all_data(t_client_thread *client)
{
	int		i;
	t_obj	data;

	i = 0;
	if (!ft_is_get(client))
		return ;
	//routine_before_send(client);
	while (i < client->nb_players)
	{
		if (i != client->id)
		{
			pthread_mutex_lock(client->mutex);
			data = _server()->player_data[i];
			if (send(client->socket, &data, sizeof(data), 0) < 0)
				ft_exit(1);
			pthread_mutex_unlock(client->mutex);
		}
		++i;
	}
	client->is_recv = 0;
}

void	*client_routine(void *client_t)
{
	t_client_thread	*client;

	client = (t_client_thread *)client_t;
	if (send(client->socket, &(client->id), sizeof(client->id), 0) < 0)
		ft_exit(1);
	while (1)
	{
		if (ft_recv_first_data(client) == EXIT_FAILURE)
			ft_exit(1);
		ft_send_all_data(client);
	}
	return (NULL);
}
