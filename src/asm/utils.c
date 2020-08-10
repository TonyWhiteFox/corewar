/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 21:00:17 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 21:00:19 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "asm.h"

void			ft_lstdel_content(void *content, size_t size)
{
	free(content);
	*(&size) = 0;
}

void			ft_error(char *err, t_serv *s, int err_code)
{
	errno = err_code;
	perror(err);
	free(s->line);
	if (s)
	{
		ft_lstdel(&s->memguru, &ft_lstdel_content);
		free(s->line);
		free(s);
	}
	exit(1);
}

size_t			len_to_end(t_serv *s, char end)
{
	size_t	len;

	len = 0;
	while (*s->ptr2 != end)
	{
		if (!*s->ptr2++)
			ft_error(ERR_STR_SPLIT, s, EINVAL);
		len++;
	}
	return (len);
}

void			skip_whitespace(t_serv *s)
{
	while (s->ptr1 && *s->ptr1 && ft_strchr(WHITESPACE_CHARS, *s->ptr1))
		s->ptr1++;
}

t_bytes			ft_atoi_check(char *nb)
{
	size_t		i;
	t_bytes		ret;

	ret.num = -1;
	i = ft_strlen(nb);
	if (i > 2 && nb[0] == '0' && (nb[1] == 'x' || nb[1] == 'X' || nb[1] == 'b'))
	{
		if (nb[1] == 'x' || nb[1] == 'X')
			ret.unum4 = ft_atoi_base(nb, 16);
		else if (nb[1] == 'b')
			ret.unum4 = ft_atoi_base(nb, 2);
		else
			errno = EDOM;
	}
	else
		ret.num = ft_atoi(nb);
	return (ret);
}
