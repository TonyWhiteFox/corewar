/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 08:57:59 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/05 08:58:01 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <errno.h>

static unsigned char	type_code(int8_t type)
{
	if (type == T_DIR)
		return (DIR_CODE);
	else if (type == T_REG)
		return (REG_CODE);
	else if (type == T_IND)
		return (IND_CODE);
	else
		return (0);
}

unsigned char			arg_coding_byte(t_instr *ptr)
{
	unsigned char	b0;
	unsigned char	b1;
	unsigned char	b2;
	unsigned char	b3;
	unsigned char	ret;

	b0 = type_code(ptr->args[0].type) << 6;
	b1 = type_code(ptr->args[1].type) << 4;
	b2 = type_code(ptr->args[2].type) << 2;
	b3 = 0;
	ret = b0 | b1 | b2 | b3;
	return (ret);
}

int						get_offset(t_serv *s, t_instr *instr, char *label)
{
	t_instr		*ptr;

	ptr = s->instr;
	while (ptr)
	{
		if (label && ptr->label && !ft_strcmp(label, ptr->label))
			return (ptr->byte - instr->byte);
		ptr = ptr->next;
	}
	ft_error(ERR_WRONG_LABEL, s, EINVAL);
	return (0);
}

unsigned int			swap_bytes(unsigned int num, size_t len)
{
	unsigned int	b0;
	unsigned int	b1;
	unsigned int	b2;
	unsigned int	b3;
	unsigned int	res;

	res = 0;
	if (len == 4)
	{
		b0 = (num & 0x000000ff) << 24u;
		b1 = (num & 0x0000ff00) << 8u;
		b2 = (num & 0x00ff0000) >> 8u;
		b3 = (num & 0xff000000) >> 24u;
		res = b0 | b1 | b2 | b3;
	}
	else if (len == 2)
	{
		b0 = (num & 0x00ff) << 8u;
		b1 = (num & 0xff00) >> 8u;
		res = b0 | b1;
	}
	return (res);
}

void					code_labels(t_serv *s)
{
	t_list		*list;
	t_arg		*arg;
	int			i;

	list = s->arg_labels;
	while (list)
	{
		i = -1;
		while (++i < 3)
		{
			arg = &(((t_instr *)list->content)->args[i]);
			if (arg->is_label)
			{
				arg->value.num = get_offset(s, list->content, arg->token);
				if (arg->type == T_IND || (arg->type == T_DIR
						&& ((t_instr *)list->content)->op->reduced_dir_size))
					arg->code_size = IND_SIZE;
				else
					arg->code_size = DIR_SIZE;
				arg->code.unum4 = swap_bytes(arg->value.unum4, arg->code_size);
			}
		}
		list = list->next;
	}
}
