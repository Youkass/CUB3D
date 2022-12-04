/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:44:31 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/04 20:14:39 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cub.h"

int	round_end_wait(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_END_WAIT]
		>= client->serv->linked_players)
	{
		if (client->round_state_send[ROUND_END] != -1
			&& client->serv->round_state[ROUND_END] > 0)
		{
			--client->serv->round_state[ROUND_END];
			if (client->id == 0)
			{
				client->serv->start = get_clock(client->serv->clock);
				client->serv->clock_started = 1;
			}
		}
		if (ft_first_big_if(client))
			ft_scnd_big_if(client);
		data->round_state = ROUND_END_WAIT;
		client->round_state_send[ROUND_END_WAIT] = 0;
		client->round_state_send[ROUND_END] = -1;
		client->round_state_send[ROUND_PLAY] = 0;
		return (1);
	}
	return (0);
}

int	ft_if_wait(t_client_thread *client)
{
	if (client->serv->clock_started && get_time_server(client->serv->start,
			client->serv->clock) >= 3000000
		&& !client->round_state_send[ROUND_START]
		&& client->serv->round_state[ROUND_START]
		< client->serv->linked_players)
		return (1);
	return (0);
}

int	round_wait_start(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_WAIT_START]
		>= client->serv->linked_players)
	{
		if (client->round_state_send[ROUND_END_WAIT] != -1
			&& client->serv->round_state[ROUND_END_WAIT] > 0)
		{
			--client->serv->round_state[ROUND_END_WAIT];
			if (client->id == 0)
			{
				client->serv->start = get_clock(client->serv->clock);
				client->serv->clock_started = 1;
			}
		}
		if (ft_if_wait(client))
		{
			client->round_state_send[ROUND_START] = 1;
			++client->serv->round_state[ROUND_START];
		}
		client->round_state_send[ROUND_END_WAIT] = -1;
		data->round_state = ROUND_WAIT_START;
		data->time = get_time_server(client->serv->start,
				client->serv->clock) / 1000000 + 1;
		return (1);
	}
	return (0);
}

int	round_start(int *round, t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_START] >= client->serv->linked_players)
	{
		if (client->round_state_send[ROUND_WAIT_START] != -1
			&& client->serv->round_state[ROUND_WAIT_START] > 0)
			client->serv->round_state[ROUND_WAIT_START]--;
		if (client->round_state_send[ROUND_PLAY] == 0
			&& client->serv->round_state[ROUND_PLAY]
			< client->serv->linked_players)
				client->serv->round_state[ROUND_PLAY]++;
		client->round_state_send[ROUND_PLAY] = 1;
		client->round_state_send[ROUND_WAIT_START] = -1;
		client->round_state_send[ROUND_END_WAIT] = 0;
		client->round_state_send[ROUND_END] = 0;
		data->round_state = ROUND_START;
		client->serv->clock_started = 0;
		client->serv->team_data[0].round_state = MATCH;
		client->serv->team_data[1].round_state = MATCH;
		client->serv->round_state[ROUND_LEADERBOARD] = 0;
		*round += 1;
		return (1);
	}
	return (0);
}

void	round_leaderboard(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_LEADERBOARD]
		>= client->serv->linked_players)
	{
		if (client->round_state_send[ROUND_END_WAIT] != -1
			&& client->serv->round_state[ROUND_END_WAIT] > 0)
		{
			--client->serv->round_state[ROUND_END_WAIT];
			client->round_state_send[ROUND_END_WAIT] = -1;
		}
		client->serv->match_finished = 1;
		data->match_finished = 1;
		data->round_state = ROUND_LEADERBOARD;
	}
}
