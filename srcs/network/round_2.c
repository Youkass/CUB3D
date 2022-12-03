/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:44:31 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:47:37 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	round_play(int round, t_send_server_game *data, t_client_thread *c, int f)
{
	if (c->serv->round_state[ROUND_PLAY] >= c->serv->linked_players)
	{
		if (round > 0 && c->round_state_send[ROUND_START] != -1
			&& c->serv->round_state[ROUND_START] > 0)
		{
			c->serv->round_state[ROUND_START]--;
			c->round_state_send[ROUND_START] = -1;
		}
		data->round_state = ROUND_PLAY;
		c->serv->round_state[ROUND_LEADERBOARD] = 0;
	}
	if (f && !c->round_state_send[ROUND_END])
	{
		++c->serv->round_state[ROUND_END];
		c->round_state_send[ROUND_END] = 1;
	}
	return (0);
}

void	ft_round_end(t_client_thread *client)
{
	if (client->round_state_send[ROUND_PLAY] != -1
		&& client->serv->round_state[ROUND_PLAY] > 0)
	{
		--client->serv->round_state[ROUND_PLAY];
		client->round_state_send[ROUND_PLAY] = -1;
	}
	client->round_state_send[ROUND_START] = 0;
	client->round_state_send[ROUND_WAIT_START] = 0;
	if (!client->round_state_send[ROUND_END_WAIT]
		&& client->serv->round_state[ROUND_END_WAIT]
		< client->serv->linked_players)
	{
		++client->serv->round_state[ROUND_END_WAIT];
		client->round_state_send[ROUND_END_WAIT] = 1;
	}
}

int	round_end(t_send_server_game *data, t_client_thread *client)
{
	if (client->serv->round_state[ROUND_END] >= client->serv->linked_players)
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
		ft_round_end(client);
		return (1);
	}
	return (0);
}

int	ft_first_big_if(t_client_thread *client)
{
	if (client->serv->clock_started && get_time_server(client->serv->start,
			client->serv->clock) >= 3000000
		&& (!client->round_state_send[ROUND_WAIT_START]
			|| !client->round_state_send[ROUND_LEADERBOARD]))
		return (1);
	return (0);
}

void	ft_scnd_big_if(t_client_thread *client)
{
	if ((client->serv->team_data[TRED].wins >= NB_ROUNDS
			|| client->serv->team_data[TBLUE].wins >= NB_ROUNDS)
		&& !client->round_state_send[ROUND_LEADERBOARD]
		&& client->serv->round_state[ROUND_LEADERBOARD]
		< client->serv->linked_players)
	{
		++client->serv->round_state[ROUND_LEADERBOARD];
		client->round_state_send[ROUND_LEADERBOARD] = 1;
	}
	else if (client->serv->round_state[ROUND_WAIT_START]
		< client->serv->linked_players)
	{
		client->round_state_send[ROUND_WAIT_START] = 1;
		client->serv->round_state[ROUND_WAIT_START]++;
	}
	if (client->serv->round_state[ROUND_WAIT_START]
		>= client->serv->linked_players
		|| client->serv->round_state[ROUND_LEADERBOARD]
		>= client->serv->linked_players)
		client->serv->clock_started = 0;
}
