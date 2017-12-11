/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 19:07:18 by alngo             #+#    #+#             */
/*   Updated: 2017/11/29 21:43:49 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				key_hook(int key, t_env *e)
{
	if (key == 53)
		checkout(e, "Bye bye !");
	return (0);
}

int				key_pressed(int key, t_env *e)
{
	if (key == 53)
		checkout(e, "Bye bye !");
	else
		printf("[%d]\n", key);
	return (0);
}
