/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:18:07 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/12/03 18:50:08 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	init_team_server(t_client_thread *c)
{
	int			i;

	if (c->id == 0)
	{
		c->serv->team_data[TRED].looses = 0;
		c->serv->team_data[TRED].wins = 0;
		c->serv->team_data[TRED].round_state = 0;
		c->serv->team_data[TBLUE].looses = 0;
		c->serv->team_data[TBLUE].wins = 0;
		c->serv->team_data[TBLUE].round_state = 0;
		i = 0;
		while (i < c->serv->linked_players / 2)
		{
			c->serv->team_data[TRED].players[i].id = c->serv->teams[0].array[i];
			c->serv->team_data[TRED].players[i].dead = 0;
			c->serv->team_data[TRED].players[i].kills = 0;
			c->serv->team_data[TRED].players[i].deaths = 0;
			c->serv->team_data[TBLUE].players[i].id
				= c->serv->teams[1].array[i];
			c->serv->team_data[TBLUE].players[i].dead = 0;
			c->serv->team_data[TBLUE].players[i].kills = 0;
			c->serv->team_data[TBLUE].players[i].deaths = 0;
			i++;
		}
	}
}

void	get_team_id(t_client_thread	*c)
{
	int	i;

	i = 0;
	while (i < c->serv->linked_players / 2)
	{
		if (c->serv->teams[0].array[i] == c->id)
		{
			c->team_id = i;
			c->team = 0;
		}
		if (c->serv->teams[1].array[i] == c->id)
		{
			c->team_id = i;
			c->team = 0;
		}
		i++;
	}
}

int	ft_routine(t_client_thread *client)
{
	if (wait_lobby(client))
		return (1);
	memset(&client->round_state_send, 0, sizeof(client->round_state_send));
	pthread_mutex_lock(client->mutex);
	client->restart = 0;
	client->serv->restart = 0;
	client->is_recv = 0;
	client->is_send = 0;
	client->serv->started = 0;
	client->serv->round_end = 0;
	restart_state(client);
	client->round_state_send[ROUND_END_WAIT] = 0;
	client->serv->round_state[ROUND_PLAY] = client->serv->linked_players;
	init_team_server(client);
	get_team_id(client);
	pthread_mutex_unlock(client->mutex);
	return (0);
}

int	ft_while_routine(t_client_thread *client)
{
	if (ft_recv_first_data(client))
		return (1);
	if (ft_send_all_data(client))
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
	if (send(client->socket, &(client->id), sizeof(client->id), 0) < 0)
		return (pthread_mutex_unlock(client->mutex), NULL);
	if (send_nb_players(client))
		return (pthread_mutex_unlock(client->mutex), NULL);
	pthread_mutex_unlock(client->mutex);
	while (1)
	{
		if (ft_routine(client))
			return (NULL);
		while (1)
		{
			if (ft_while_routine(client))
				return (NULL);
			if (client->restart)
				break ;
		}
	}
	return (NULL);
}
