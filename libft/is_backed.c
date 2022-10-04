/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_backed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alukongo <alukongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:41:08 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/12 13:17:40 by alukongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	is_backed(char *str, int i)
{
	int	backed;

	backed = 0;
	while (i >= 0)
	{
		if (str[i] == '\\')
			backed++;
		else
			break ;
		i--;
		if (i == -1)
			break ;
	}
	return (backed % 2);
}
