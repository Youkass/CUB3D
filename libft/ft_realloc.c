/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darian <darian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:43:52 by darian            #+#    #+#             */
/*   Updated: 2022/06/28 13:43:58 by darian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *buf, int old_size, int new_size, t_alloc	**lst)
{
	void	*alloc;

	alloc = ft_malloc(new_size, lst);
	ft_memcpy(alloc, buf, old_size);
	return (alloc);
}
