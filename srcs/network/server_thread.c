/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:18:07 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/11/12 10:21:02 by denissereno      ###   ########.fr       */
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
		memset(&data->clients[i].round_state_send, 0,
			sizeof(data->clients[i].round_state_send));
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

/*
TYPE:
1 = r >= nb;
0 = r < nb
*/

int	check_only(int nb, int r, int type)
{
	if (type == 1)
	{
		if (r >= nb && mod(r- 1, N_RSTATE) < nb && mod(r- 2, N_RSTATE) < nb
			&& mod(r- 3, N_RSTATE) < nb && mod(r- 4, N_RSTATE) < nb
			&& mod(r- 5, N_RSTATE)< nb)
			return (1);
	}
	else
	{
		if (r < nb && mod(r- 1, N_RSTATE) < nb && mod(r- 2, N_RSTATE) < nb
		&& mod(r- 3, N_RSTATE) < nb && mod(r- 4, N_RSTATE) < nb
		&& mod(r- 5, N_RSTATE)< nb)
		return (1);
	}
	return (0);
}

int	round_play(int round, t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_PLAY] >= client->nb_players)
	{
		if (round > 0 && client->round_state_send[ROUND_START] != -1)
		{
			client->serv->round_state[ROUND_START]--;
			client->round_state_send[ROUND_START] = -1;
		}
		data->round_state = ROUND_PLAY;
	}
	if (((client->serv->team_data[TRED].round_state == LOOSE
		|| client->serv->team_data[TBLUE].round_state == WIN)
		|| (client->serv->team_data[TRED].round_state == WIN
		|| client->serv->team_data[TBLUE].round_state == LOOSE))
		&& !client->round_state_send[ROUND_END])
	{
		++client->serv->round_state[ROUND_END];
		client->round_state_send[ROUND_END] = 1;
	}
	return (0);

}

int	round_end(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_END] >= client->nb_players) // SI TOUT LES THREADS SONT ROUND_END ON ENVOIE NOS DATA
	{
		data->round_state = ROUND_END;
		if ((client->serv->team_data[TRED].round_state == LOOSE
			|| client->serv->team_data[TBLUE].round_state == WIN))
		{
			data->round_winner = TBLUE;
			++client->serv->team_data[TBLUE].wins;
			--client->serv->team_data[TRED].looses;
		}
		else if ((client->serv->team_data[TRED].round_state == WIN
			|| client->serv->team_data[TBLUE].round_state == LOOSE))
		{
			data->round_winner = TRED;
			++client->serv->team_data[TRED].wins;
			--client->serv->team_data[TBLUE].looses;
		}
		if (client->round_state_send[ROUND_PLAY] != -1)
		{
			--client->serv->round_state[ROUND_PLAY];
			client->round_state_send[ROUND_PLAY] = -1;
		}
		client->round_state_send[ROUND_START] = 0;
		client->round_state_send[ROUND_WAIT_START] = 0;
		if (!client->round_state_send[ROUND_END_WAIT])
		{
			++client->serv->round_state[ROUND_END_WAIT];
			client->round_state_send[ROUND_END_WAIT] = 1;
		}
		return (1);
	}
	return (0);
}

int	round_end_wait(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_END_WAIT] >= client->nb_players)
	{
		if (client->round_state_send[ROUND_END] != -1)
		{
			--client->serv->round_state[ROUND_END];
			if (client->id == 0)
			{
				client->serv->start = get_clock(client->serv->clock);
				client->serv->clock_started = 1;
			}
		}
		if (client->serv->clock_started && get_time_server(client->serv->start,
			client->serv->clock) >= 3000000
		&& (!client->round_state_send[ROUND_WAIT_START] || !client->round_state_send[ROUND_LEADERBOARD]) )
		{
			if ((client->serv->team_data[TRED].wins >= NB_ROUNDS
			|| client->serv->team_data[TBLUE].wins >= NB_ROUNDS)
			&& !client->round_state_send[ROUND_LEADERBOARD])
			{
				++client->serv->round_state[ROUND_LEADERBOARD];
				client->round_state_send[ROUND_LEADERBOARD] = 1;
			}
			else
			{
				client->round_state_send[ROUND_WAIT_START] = 1;
				client->serv->round_state[ROUND_WAIT_START]++;
			}
			if (client->serv->round_state[ROUND_WAIT_START] >= client->nb_players
			|| client->serv->round_state[ROUND_LEADERBOARD] >= client->nb_players)
				client->serv->clock_started = 0;
		}
		data->round_state = ROUND_END_WAIT;
		client->round_state_send[ROUND_END_WAIT] = 0;
		client->round_state_send[ROUND_END] = -1;
		client->round_state_send[ROUND_PLAY] = 0;
		return (1);
	}
	return (0);
}

int	round_wait_start(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_WAIT_START] >= client->nb_players)
	{
		if (client->round_state_send[ROUND_END_WAIT] != -1)
		{
			--client->serv->round_state[ROUND_END_WAIT];
			if (client->id == 0)
			{
				client->serv->start = get_clock(client->serv->clock);
				client->serv->clock_started = 1;
			}
		}
		if (client->serv->clock_started && get_time_server(client->serv->start,
			client->serv->clock) >= 3000000
		&& !client->round_state_send[ROUND_START])
		{
			client->round_state_send[ROUND_START] = 1;
			++client->serv->round_state[ROUND_START];
		}
		client->round_state_send[ROUND_END_WAIT] = -1;
		data->round_state = ROUND_WAIT_START;
		return (1);
	}
	return (0);
}

int	round_start(int *round, t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_START] >= client->nb_players)
	{
		if (client->round_state_send[ROUND_WAIT_START] != -1)
			client->serv->round_state[ROUND_WAIT_START]--;
		if (client->round_state_send[ROUND_PLAY] == 0)
			client->serv->round_state[ROUND_PLAY]++;
		client->round_state_send[ROUND_PLAY] = 1;
		client->round_state_send[ROUND_WAIT_START] = -1;
		client->round_state_send[ROUND_END_WAIT] = 0;
		client->round_state_send[ROUND_END] = 0;
		data->round_state = ROUND_START;
		client->serv->clock_started = 0;
		client->serv->team_data[0].round_state = MATCH;
		client->serv->team_data[1].round_state = MATCH;
		*round += 1;
		return (1);
	}
	return (0);
}

void	round_leaderboard(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_LEADERBOARD] >= client->nb_players)
	{
		if (client->round_state_send[ROUND_END_WAIT] != -1)
		{
			--client->serv->round_state[ROUND_END_WAIT];
			client->round_state_send[ROUND_END_WAIT] = -1;
		}
		client->serv->match_finished = 1;
		data->match_finished = 1;
		data->round_state = ROUND_LEADERBOARD;
	}
}

int	ft_send_all_data(t_client_thread *client)
{
	int					i;
	t_send_server_game	data;
	static __thread int	round = 0;

	i = 0;
	pthread_mutex_lock(client->mutex);
	while (i < client->nb_players)
	{
		data.player[i] = client->serv->player_data[i];
		++i;
	}
	data.round_state = -1;
	data.round_winner = -1;
	data.blue_alive = client->serv->blue_alive;
	data.red_alive = client->serv->red_alive;
	data.player_alive = client->serv->player_alive;
	round_play(round, &data, client);
	round_end_wait(&data, client);
	round_leaderboard(&data, client);
	round_end(&data, client);
	round_wait_start(&data, client);
	round_start(&round, &data, client);
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

//void	check_team(t_client_thread *c, int team, int team2)
//{
//	int	i;
//	int	n;

//	i = 0;
//	n = 0;
//	while (i < c->nb_players / 2)
//	{
//		printf("[%d] = > %d\n", i, c->serv->player_data[i].is_dead);
//		if (c->serv->player_data[i].is_dead == 1)
//		{
//			printf("ONE_DEAD\n");
//			n++;
//		}
//		i++;
//	}
//	if (n >= c->nb_players / 2)
//	{
//		printf("FINITO!!!\n");
//		c->serv->team_data[team].round_state = LOOSE;
//		c->serv->team_data[team2].round_state = WIN;
//	}
//}

void	check_team(t_client_thread *c)
{
	int			i;
	t_vector2D	n;

	i = 0;
	n = pos(0, 0);
	while (i < c->nb_players)
	{
		if (c->serv->player_data[i].is_dead == 1)
		{
			if (c->serv->player_data[i].team == TEAM_RED)
				++n.x;
			else if (c->serv->player_data[i].team == TEAM_BLUE)
				++n.y;
		}
		i++;
	}
	if (n.x >= c->nb_players / 2)
	{
		c->serv->team_data[TRED].round_state = LOOSE;
		c->serv->team_data[TBLUE].round_state = WIN;
	}
	else if (n.y >= c->nb_players / 2)
	{
		c->serv->team_data[TBLUE].round_state = LOOSE;
		c->serv->team_data[TRED].round_state = WIN;
	}
}

void	update_team_array(t_client_thread *c)
{
	if (c->id != 0)
		return ;
	pthread_mutex_lock(c->mutex);
	check_team(c);
	int	i;
	int	team;
	c->serv->player_alive = c->nb_players;
	c->serv->red_alive = c->nb_players / 2;
	c->serv->blue_alive = c->nb_players / 2;
	i = 0;
	while (i < c->nb_players)
	{
		if (c->serv->player_data[i].is_dead == 1)
		{
			--c->serv->player_alive;
			if (c->serv->player_data[i].team == TEAM_RED)
				--c->serv->red_alive;
			else
				--c->serv->blue_alive;
		}
		if (c->serv->player_data[i].shooted.id != -1
		&& c->serv->player_data[i].shooted.id < c->nb_players
		&& ((c->serv->player_data[i].shooted.shoot == 1 && 
		c->serv->player_data[c->serv->player_data[i].shooted.id].health -
		_weapon()[c->serv->player_data[i].weapon_id]->power <= 0)
		|| (c->serv->player_data[i].shooted.shoot == 2 && 
		c->serv->player_data[c->serv->player_data[i].shooted.id].health -
		_weapon()[c->serv->player_data[i].weapon_id]->headshot <= 0) ||
		(c->serv->player_data[i].shooted.shoot == 3 && 
		c->serv->player_data[c->serv->player_data[i].shooted.id].health -
		_weapon()[c->serv->player_data[i].weapon_id]->footshot <= 0)))
		{
			team = c->serv->player_data[i].team;
			if (team == 2)
				--team;
			++c->serv->player_data[i].kills;
			team = c->serv->player_data[c->serv->player_data[i].shooted.id].team;
			if (team == 2)
				--team;
			++c->serv->player_data[c->serv->player_data[i].shooted.id].deaths;
		}
		i++;
	}
	pthread_mutex_unlock(c->mutex);
}

int	ft_update_team(t_client_thread *c)
{
	update_team_array(c);
	return (0);
}

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
		while (i < c->nb_players / 2)
		{
			c->serv->team_data[TRED].players[i].id = c->serv->teams[0].array[i];
			c->serv->team_data[TRED].players[i].dead = 0;
			c->serv->team_data[TRED].players[i].kills = 0;
			c->serv->team_data[TRED].players[i].deaths = 0;
			c->serv->team_data[TBLUE].players[i].id = c->serv->teams[1].array[i];
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
	while (i < c->nb_players / 2)
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
	init_team_server(client);
	get_team_id(client);
	pthread_mutex_unlock(client->mutex);
	while (1)
	{
		if (ft_recv_first_data(client))
			return (NULL);
		if (ft_update_team(client))
			return (NULL);
		if (ft_send_all_data(client))
			return (NULL);
	}
	return (NULL);
}


/*
tout le monde sur ROUND_PLAY.

Quand thread sais la victoire passe a ROUND_END.

Si round_end == NB PLAYER alors anoncer la victoire aux clients et passer
chaque thread a ROUND_END_WAIT et enlever chacun ROUND_END au meme moment.

Et ainsi de suite.


*/