/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:54:09 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/03 18:54:57 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_init_client_next(void)
{
	int	i;

	i = 0;
	if (recv(_var()->socket, &(_var()->map), sizeof(_var()->map),
			MSG_WAITALL) <= 0)
		return (EXIT_FAILURE);
	if (recv(_var()->socket, &(_var()->map_width),
			sizeof(_var()->map_width), MSG_WAITALL) <= 0)
		return (EXIT_FAILURE);
	if (recv(_var()->socket, &(_var()->map_height),
			sizeof(_var()->map_height), MSG_WAITALL) <= 0)
		return (EXIT_FAILURE);
	while (i < _var()->map_height)
	{
		printf("=> %s\n", _var()->map[i]);
		++i;
	}
	ft_malloc_map();
	return (EXIT_SUCCESS);
}

int	ft_init_client(void)
{
	int			ret;
	int			soc;

	soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	_var()->socket = soc;
	if (_var()->is_host == SERVER)
		_var()->client.sin_addr.s_addr = inet_addr(ft_get_host_ip());
	else if (_var()->is_host == CLIENT)
		_var()->client.sin_addr.s_addr = inet_addr(_var()->ip);
	_var()->client.sin_family = AF_INET;
	_var()->client.sin_port = htons(30000);
	ret = connect(_var()->socket,
			(const struct sockaddr *)&(_var()->client), sizeof(_var()->client));
	if (ret < 0)
		return (EXIT_FAILURE);
	if (ft_init_client_first() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (_player()->id != 0)
	{
		if (ft_init_client_next() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_copy_data_first(t_obj *player)
{
	player->nr = _player()->nr;
	player->is_crouching = _player()->is_crouching;
	player->team = _player()->team;
	player->change_team = _player()->change_team;
	player->plane = _player()->plane;
	player->pitch = _player()->pitch;
	player->norm_pitch = _player()->norm_pitch;
	player->id = _player()->id;
	player->x = _player()->x;
	player->y = _player()->y;
	player->z = _player()->z;
	player->c = _player()->c;
	player->dx = _player()->dx;
	player->kills = _player()->kills;
	player->deaths = _player()->deaths;
	player->dy = _player()->dy;
	player->da = _player()->da;
	player->old_dx = _player()->old_dx;
	player->old_dy = _player()->old_dy;
	player->angle = _player()->angle;
	player->is_walking = _player()->is_walking;
	player->is_dead = _player()->is_dead;
	player->start_dead = _player()->start_dead;
	player->death_n = _player()->death_n;
	player->death_start = _player()->death_start;
}

void	ft_copy_data_next(t_obj *player, int i)
{
	player->shooted = _player()->shooted;
	player->old_plane = _player()->old_plane;
	player->hb = _player()->hb;
	player->pitch = _player()->pitch;
	player->health = _player()->health;
	player->weapon_id = _player()->weapon_id;
	i = 0;
	while (i < NB_WEAPONS)
	{
		player->ammo[i] = _player()->ammo[i];
		player->full_ammo[i] = _player()->full_ammo[i];
		i++;
	}
	player->shoot_n = _player()->shoot_n;
	player->exchange = _player()->exchange;
	player->is_start = _player()->is_start;
	player->is_shooting = _player()->is_shooting;
	i = 0;
	while (i < _player()->shoot_n)
	{
		player->shott[i] = _player()->shott[i];
		player->shott[i].pos = _player()->shott[i].pos;
		i++;
	}
}

void	ft_copy_data_before_pong(t_obj *player)
{
	int	i;

	i = 0;
	while (i < (int)_player()->nr)
	{
		player->kill_round[i] = _player()->kill_round[i];
		i++;
	}
	ft_copy_data_first(player);
	ft_copy_data_next(player, i);
	memset(player->pseudo, 0, sizeof(player->pseudo));
	strcpy(player->pseudo, _player()->pseudo);
}
