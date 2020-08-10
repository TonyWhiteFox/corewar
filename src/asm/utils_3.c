/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 15:26:27 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/04 15:26:29 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "asm.h"
#include "libft.h"

static int				convert_nb(char c, int base)
{
	int		result;

	if (c >= '0' && c <= '9')
		result = c - 48;
	else if (c >= 'a' && c <= 'z')
		result = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		result = c - 65 + 10;
	else
		result = -1;
	if (result < base && result != -1)
		return (result);
	else
	{
		return (-1);
	}
}

static ssize_t			length_number(char *str, int base)
{
	ssize_t		length;

	length = 0;
	while (str[length])
	{
		if (convert_nb(str[length], base) == -1)
			break ;
		length++;
	}
	return (length);
}

static unsigned long	ft_power(unsigned long n, int pow)
{
	if (!pow)
		return (1);
	else if (pow > 0)
		n *= ft_power(n, --pow);
	else
		n /= ft_power(n, ++pow);
	return (n);
}

int						ft_atoi_base(char *nb, int base)
{
	int		result;
	int		length;

	if (base == 10)
		return ((int)ft_atoi(nb));
	while (*nb == ' ' || *nb == '\t' || *nb == '\n'
			|| *nb == '\v' || *nb == '\r' || *nb == '\f')
		nb++;
	result = 0;
	length = length_number(nb, base) - 1;
	while (*nb && length >= 0 && convert_nb(*nb, base) != -1)
	{
		result += convert_nb(*nb, base) * ft_power(base, length);
		nb++;
		length--;
	}
	return (result);
}

size_t					get_str_len(t_serv *s)
{
	size_t	len;

	len = 0;
	if (*s->ptr1 == '\"')
	{
		s->ptr1++;
		s->ptr2++;
		len = len_to_end(s, '\"');
	}
	else
	{
		while (*s->ptr2 && ft_strchr(LABEL_CHARS, *s->ptr2))
		{
			if (!*s->ptr2)
				ft_error(ERR_STR_SPLIT, s, ERANGE);
			len++;
			s->ptr2++;
		}
	}
	return (len);
}
