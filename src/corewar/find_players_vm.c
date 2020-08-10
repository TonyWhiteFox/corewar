/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_players_vm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:35:39 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:01:19 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		read_gamers(char *av, t_virt *v)
{
	if (v->total_gamers >= MAX_PLAYERS)
		exit(ft_printf("Exceeded the player limit\n"));
	v->total_gamers++;
	v->fd = open(av, O_RDONLY);
	if (v->fd < 1)
		exit(ft_printf("Unreadable file!\n"));
	if (v->number == 0)
		v->number = v->total_gamers * (-1);
	create_gamer_and_fill_him(v, NULL, NULL);
	close(v->fd);
}

void		check_format(char *av, int i)
{
	if (i > 4)
		if (ft_strequ(&(av[i - 4]), ".cor"))
			return ;
	exit(ft_printf("Invalid file format\n"));
}

int			find_player(int ac, char **av, t_virt *v, int i)
{
	if (ft_strequ(av[i], "-n") && i + 2 < ac &&
			ft_is_positive_number(av[i + 1]))
	{
		v->number = ft_atoi(av[i + 1]);
		if (v->number < 1 || v->number > MAX_PLAYERS)
			return (0);
		check_format(av[i + 2], ft_strlen(av[i + 2]));
		read_gamers(av[i + 2], v);
		return (3);
	}
	v->number = 0;
	check_format(av[i], ft_strlen(av[i]));
	read_gamers(av[i], v);
	return (1);
}
