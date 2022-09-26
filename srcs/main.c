/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denissereno <denissereno@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:29:24 by denissereno       #+#    #+#             */
/*   Updated: 2022/09/26 15:59:30 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int main(int argc, char **argv)
{
	t_mlx	data;

    if (argc != 2)
    {
        printf("Arguments error\n");
        return (1);
    }
    (void)argv;
    return (0);
}
