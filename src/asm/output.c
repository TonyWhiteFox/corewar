/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 21:31:45 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 21:31:55 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <errno.h>

static void		write_header_code(t_serv *s)
{
	unsigned int	uint;

	uint = swap_bytes(s->header.magic, 4);
	write(s->fd_out, &uint, 4);
	write(s->fd_out, s->header.prog_name, PROG_NAME_LENGTH);
	write(s->fd_out, "\0\0\0\0", 4);
	uint = swap_bytes(s->header.prog_size, 4);
	write(s->fd_out, &uint, 4);
	write(s->fd_out, s->header.comment, COMMENT_LENGTH);
	write(s->fd_out, "\0\0\0\0", 4);
}

static void		write_instr_code(t_serv *s)
{
	t_instr		*ptr;
	int			i;

	ptr = s->instr;
	while (ptr)
	{
		if (ptr->op)
			write(s->fd_out, &ptr->op->code, 1);
		if (ptr->op && ptr->op->is_acb)
			write(s->fd_out, &ptr->acb, 1);
		i = -1;
		while (++i < 3 && (ptr->args[i].type))
			write(s->fd_out, &ptr->args[i].code, ptr->args[i].code_size);
		ptr = ptr->next;
	}
}

static void		write_code(t_serv *s)
{
	write_header_code(s);
	write_instr_code(s);
}

static void		open_file(t_serv *s)
{
	char	*file;
	size_t	len;
	char	*tmp;

	file = NULL;
	tmp = NULL;
	len = ft_strlen(s->filename);
	if (!(tmp = ft_strndup(s->filename, len - 2)))
		ft_error(ERR_MALLOC, s, ENOMEM);
	if (!(file = ft_strjoin(tmp, ".cor")))
		ft_error(ERR_MALLOC, s, ENOMEM);
	if ((s->fd_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_error(ERR_CREATE_FILE, s, EBADF);
	ft_printf("Writing output program to %s\n", file);
	free(tmp);
	free(file);
}

void			output(t_serv *s)
{
	if (!*s->header.prog_name)
		ft_error(ERR_NAME_LEN, s, EINVAL);
	if (s->flag & FLAG_DUMP)
		print_dump(s);
	else
	{
		open_file(s);
		write_code(s);
		close(s->fd_out);
	}
}
