/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:32:57 by denissereno       #+#    #+#             */
/*   Updated: 2022/12/05 17:54:42 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	ft_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(char *nbr)
{
	int			nega;
	long long	output;
	int			i;

	output = 0;
	i = 0;
	nega = 1;
	while (ft_space(nbr[i]))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			nega *= -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
		output = (output * 10) + (nbr[i++] - 48);
	return (output * nega);
}

void	ft_black_hole(int exit_code)
{
	t_list	*tmp;
	int		i;

	tmp = _lst();
	i = 0;
	while (i < 4)
	{
		if (_var()->dir[i].img != NULL)
			mlx_destroy_image(_mlx()->mlx, _var()->dir[i].img);
		i++;
	}
	if (_img()->img)
		mlx_destroy_image(_mlx()->mlx, _img()->img);
	mlx_destroy_window(_mlx()->mlx, _mlx()->mlx_win);
	mlx_destroy_display(_mlx()->mlx);
	close(_var()->fd);
	free(_mlx()->mlx);
	ft_lstclear(&tmp, free);
	exit(exit_code);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}

int	ft_check_map_name(char *name)
{
	int	fd;

	if (!name || ft_strlen(name) < 4)
		return (-1);
	if (ft_strcmp(name + (ft_strlen(name) - 4), ".cub"))
	{
		printf("Error\nInvalid map extension\n");
		return (-1);
	}
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nInvalid file\n");
		return (-1);
	}
	return (fd);
}
