/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:24:11 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 17:24:12 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "op.h"
#include "asm.h"
#include "libft.h"

void		parse_num(t_serv *s)
{
	int		len;

	len = 0;
	s->ptr2 = s->ptr1;
	if (*s->ptr2 == '-' || *s->ptr2 == '+')
	{
		len++;
		s->ptr2++;
	}
	while (*s->ptr2 && *s->ptr2 != SEPARATOR_CHAR && *s->ptr2 != '\n'
		&& !ft_strchr(WHITESPACE_CHARS, *s->ptr2))
	{
		if (!*s->ptr2 || !ft_isdigit(*s->ptr2))
			ft_error(ERR_WRONG_VALUE, s, EINVAL);
		len++;
		s->ptr2++;
	}
	add_token(s, init_token(s, NUM, s->ptr1, len));
	s->ptr1 += len;
}

void		parse_comment(t_serv *s)
{
	size_t	len;

	s->ptr1++;
	s->ptr2 = s->ptr1;
	len = len_to_end(s, '\n');
	add_token(s, init_token(s, COMMENT, s->ptr1, len));
	s->ptr1 += len;
	if (*s->ptr1 == '\"')
		s->ptr1++;
}

void		parse_str(t_serv *s)
{
	size_t	len;

	s->ptr2 = s->ptr1;
	len = get_str_len(s);
	if (*s->ptr2 == LABEL_CHAR)
	{
		add_token(s, init_token(s, LABEL, s->ptr1, len));
		len++;
	}
	else
		add_token(s, init_token(s, STRING, s->ptr1, len));
	s->ptr1 += len;
	if (*s->ptr1 == '\"')
		s->ptr1++;
}

void		parse_command(t_serv *s)
{
	size_t		len;

	s->ptr2 = s->ptr1;
	if (!ft_strncmp(s->ptr1, NAME_CMD_STRING,
			(len = ft_strlen(NAME_CMD_STRING))))
		add_token(s, init_token(s, PROG_NAME, s->ptr1, len));
	else if (!ft_strncmp(s->ptr1, COMMENT_CMD_STRING,
			(len = ft_strlen(COMMENT_CMD_STRING))))
		add_token(s, init_token(s, PROG_COMMENT, s->ptr1, len));
	else
		ft_error(ERR_COMMAND, s, EINVAL);
	s->ptr1 += len;
}

void		parse_ref_label(t_serv *s)
{
	size_t	len;

	s->ptr1++;
	s->ptr2 = s->ptr1;
	len = 0;
	while (ft_strchr(LABEL_CHARS, *s->ptr2++))
		len++;
	if (!len)
		ft_error(ERR_WRONG_LABEL, s, EINVAL);
	add_token(s, init_token(s, LABEL_REF, s->ptr1, len));
	s->ptr1 += len;
}
