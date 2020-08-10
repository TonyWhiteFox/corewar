/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:01:54 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 13:01:55 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	char	*ret;
	size_t	len;
	size_t	len1;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len = len1 + n;
	ret = ft_strnew(len);
	if (!ret)
		return (NULL);
	ft_strcat(ret, s1);
	while (len1 < len)
	{
		if (*s2)
			ret[len1] = *s2;
		else
			ret[len1] = 0;
		len1++;
		s2++;
	}
	return (ret);
}
