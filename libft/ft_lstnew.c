/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:55:39 by dasereno          #+#    #+#             */
/*   Updated: 2022/08/31 13:35:14 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, t_alloc **alloc)
{
	t_list	*li;

	li = ft_malloc(sizeof(*li), alloc);
	if (!li)
		return (NULL);
	li->content = content;
	li->next = NULL;
	return (li);
}
