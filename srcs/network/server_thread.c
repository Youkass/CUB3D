/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:18:07 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/10/17 23:40:55 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

int	ft_init_client(t_server *data)
{
	int	i;

	i = 0;
	while (i < data->nb_players)
	{
		data->clients[i].nb_players = data->nb_players;
		data->clients[i].id = i;
		if (pthread_mutex_init(&data->clients[i].mutex, NULL))
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_connect_clients(t_server	*data)
{
	int	i;

	while (i < data->nb_players)

}

void	*client_routine(void *client_t)
{
	t_client_thread	*client;

	client = (t_client_thread *)client_t;
	while (i < client->nb_players)
	{
		pthread_mutex_lock(&(client.mutex);
		client->player_data = _server()->player_data[client->id];
		pthread_mutex_unlock(&(client.mutex);
	}
	recv(client->socket, )
}
