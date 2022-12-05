/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasereno <dasereno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:08:36 by dasereno          #+#    #+#             */
/*   Updated: 2022/12/05 16:37:33 by dasereno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes_bonus/cub.h"

/*
-Singleton for all var
*/
t_var	*_var(void)
{
	static t_var	*var = NULL;

	if (var == NULL)
	{
		var = ft_malloc(sizeof(t_var));
		memset(var, 0, sizeof(t_var));
	}
	return (var);
}

t_log	*_log(void)
{
	static t_log	*log = NULL;

	if (log == NULL)
	{
		log = ft_malloc(sizeof(t_log));
		if (!log)
			ft_black_hole(137);
	}
	return (log);
}

t_image	*_image(void)
{
	static t_image	*image = NULL;

	if (!image)
	{
		image = ft_malloc(sizeof(t_image));
		if (!image)
			return (NULL);
		memset(image, 0, sizeof(t_image));
	}
	return (image);
}

t_server_data	*_server(void)
{
	static t_server_data	*server = NULL;

	if (!server)
		server = ft_malloc(sizeof(t_server_data) * 1);
	return (server);
}
