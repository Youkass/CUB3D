/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:48:55 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 16:44:59 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

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
		memset(&data->clients[i].round_state_send, 0,
			sizeof(data->clients[i].round_state_send));
		data->clients[i].mutex = &data->mutex;
		data->clients[i].mutex_start = &data->mutex_start;
		data->clients[i].mutex_linked = &data->mutex_linked;
		++i;
	}
	return (EXIT_SUCCESS);
}

int	ft_init_in_while(t_server_data *data, int i)
{
	data->clients[i].csize = sizeof(data->clients[i].sockclient);
	data->clients[i].serv = data;
	data->clients[i].restart = 0;
	data->clients[i].is_recv = 0;
	data->clients[i].socket = accept(data->socket,
			(struct sockaddr *)&(data->server), &(data->clients[i].csize));
	data->clients[i].start = 0;
	data->clients[i].id = i;
	if (data->clients[i].socket < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_connect_clients(t_server_data *data)
{
	int				i;
	pthread_attr_t	tattr;

	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	i = 0;
	data->linked_players = 0;
	while (i < data->nb_players)
	{
		if (ft_init_in_while(data, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (pthread_create(&(data->clients[i].thread_id), &tattr,
				client_routine, &(data->clients[i])))
			return (EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < data->nb_players)
	{
		if (pthread_join((data->clients[i++].thread_id), NULL) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_only(int nb, int r, int type)
{
	if (type == 1)
	{
		if (r >= nb && mod(r - 1, N_RSTATE) < nb && mod(r - 2, N_RSTATE) < nb
			&& mod(r - 3, N_RSTATE) < nb && mod(r - 4, N_RSTATE) < nb
			&& mod(r - 5, N_RSTATE) < nb)
			return (1);
	}
	else
	{
		if (r < nb && mod(r - 1, N_RSTATE) < nb && mod(r - 2, N_RSTATE) < nb
			&& mod(r - 3, N_RSTATE) < nb && mod(r - 4, N_RSTATE) < nb
			&& mod(r - 5, N_RSTATE) < nb)
			return (1);
	}
	return (0);
}

void	ft_init_dt(t_client_thread *client, t_send_server_game *data)
{
	int					i;
	int					j;

	i = 0;
	while (i < client->serv->linked_players)
	{
		data->player[i] = client->serv->player_data[i];
		j = 0;
		while (j < _player()->shoot_n)
		{
			data->player[i].shott[j] = client->serv->player_data[i].shott[j];
			data->player[i].shott[j].pos
				= client->serv->player_data[i].shott[j].pos;
			j++;
		}
		++i;
	}
}
