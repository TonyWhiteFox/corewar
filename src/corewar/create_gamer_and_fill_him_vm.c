/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_gamer_and_fill_him_vm.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:37:04 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 19:04:08 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		skip_empty(t_virt *v, int i, char tmp_ch)
{
	while (i > 0)
	{
		if (read(v->fd, &(tmp_ch), 1) < 0)
			close_fd_send_error_close(v, "Error reading file!");
		if (tmp_ch != 0)
			close_fd_send_error_close(v, "Haven't NULL byte!");
		i--;
	}
}

void		read_name(t_virt *v, t_gamer *new_gamer)
{
	if (!(new_gamer->name = (char *)malloc(129)))
		memory_error();
	ft_bzero(new_gamer->name, 129);
	if ((read(v->fd, new_gamer->name, 128)) < 0)
		close_fd_send_error_close(v, "Error reading file!");
}

int			get_int_in_fd(t_virt *v, int i, int tmp_int, unsigned char tmp_ch)
{
	while (i < 4)
	{
		if (read(v->fd, &(tmp_ch), 1) != 1)
			close_fd_send_error_close(v, "Error reading file!");
		tmp_int += tmp_ch << (8 * (3 - i));
		i++;
	}
	return (tmp_int);
}

void		create_gamer_and_fill_him(t_virt *v, t_gamer *new_gamer,
										t_gamer *temp_gamer)
{
	if (!(new_gamer = (t_gamer *)malloc(sizeof(t_gamer))))
		memory_error();
	new_gamer->num = v->number;
	new_gamer->next = NULL;
	temp_gamer = v->gamer;
	if (!(v->gamer))
		v->gamer = new_gamer;
	else
	{
		while (temp_gamer->next)
			temp_gamer = temp_gamer->next;
		temp_gamer->next = new_gamer;
	}
	if (get_int_in_fd(v, 0, 0, 0) != COREWAR_EXEC_MAGIC)
		close_fd_send_error_close(v, "Header error COREWAR_EXEC_MAGIC");
	read_name(v, new_gamer);
	skip_empty(v, 4, 0);
	read_size(v, new_gamer);
	read_comment(v, new_gamer);
	skip_empty(v, 4, 0);
	read_body(v, new_gamer, 0, 0);
}
