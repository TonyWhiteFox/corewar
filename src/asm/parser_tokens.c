/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 22:50:05 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 22:50:06 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include <errno.h>

void	parse_prog_comment(t_serv *s)
{
	size_t		len;

	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr && s->tok_ptr->type == STRING)
	{
		len = ft_strlen(s->tok_ptr->content);
		if (len > COMMENT_LENGTH)
			ft_error(ERR_COMMENT_LEN, s, ERANGE);
		if (!*s->header.comment)
			ft_strcpy(s->header.comment, s->tok_ptr->content);
		else
			ft_error(ERR_COMMENT_DBL, s, EINVAL);
	}
	else
		ft_error(ERR_COMMENT_LEN, s, EINVAL);
}

void	parse_prog_name(t_serv *s)
{
	size_t		len;

	s->tok_ptr = s->tok_ptr->next;
	if (s->tok_ptr && s->tok_ptr->type == STRING && s->tok_ptr->content &&
	*s->tok_ptr->content)
	{
		len = ft_strlen(s->tok_ptr->content);
		if (!len || len > PROG_NAME_LENGTH)
			ft_error(ERR_NAME_LEN, s, ERANGE);
		if (!*s->header.prog_name)
			ft_strcpy(s->header.prog_name, s->tok_ptr->content);
		else
			ft_error(ERR_NAME_DOUBLE, s, EINVAL);
	}
	else
		ft_error(ERR_NAME_LEN, s, EINVAL);
}

void	parse_label(t_serv *s)
{
	if (s->last_instr)
		add_instr(s, s->last_instr);
	s->last_instr = init_instr(s);
	s->last_instr->label = s->tok_ptr->content;
}

int		parse_op(t_serv *s)
{
	t_op		*op;

	if ((op = get_op(s->tok_ptr->content)))
	{
		if (s->last_instr)
			s->last_instr->op = op;
		else
		{
			s->last_instr = init_instr(s);
			s->last_instr->op = op;
		}
		return (1);
	}
	return (0);
}

void	parse_string(t_serv *s)
{
	if (parse_op(s))
		parse_arguments(s);
	else
		ft_error(ERR_PARSE_STRING, s, EINVAL);
}
