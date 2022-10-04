/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:52:50 by darian            #+#    #+#             */
/*   Updated: 2022/09/12 18:30:02 by denissereno      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_lstclear
void	ft_malloc_clear(t_alloc **lst)
{
	t_alloc	*tmp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			tmp = (*lst)->next;
			if ((*lst)->ptr)
				free((*lst)->ptr);
			free(*lst);
			*lst = tmp;
		}
	}
}

//ft_lst_addback
void	malloc_add(t_alloc **alst, t_alloc *new)
{
	t_alloc	*tmp;

	tmp = *alst;
	if (tmp == NULL)
	{
		*alst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

//ft_lstnew
t_alloc	*malloc_new(void *content)
{
	t_alloc	*li;

	li = malloc(sizeof(*li));
	if (!li)
		return (NULL);
	li->ptr = content;
	li->next = NULL;
	return (li);
}

void	*ft_malloc(int size, t_alloc	**lst)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		ft_malloc_clear(lst);
		ft_putstr_fd("minishell: malloc: memory error\n", 2);
		exit (1);
		return (NULL);
	}
	malloc_add(lst, malloc_new(alloc));
	return (alloc);
}
