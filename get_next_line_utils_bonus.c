/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helabiad <helabiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 16:56:44 by helabiad          #+#    #+#             */
/*   Updated: 2026/11/19 17:24:11 by helabiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	s_len;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	return (s_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = 0;
	while (dst_len < size && dst[dst_len] != '\0')
		dst_len++;
	if (dst_len == size)
		return (src_len + size);
	i = 0;
	while (dst_len + i < size - 1 && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_size;
	char	*dst;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_size = s1_len + s2_len;
	dst = malloc (total_size + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, total_size + 1);
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	size_t					i;
	unsigned char			target;
	const unsigned char		*ptr_s;

	ptr_s = (const unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (ptr_s[i] != '\0')
	{
		if (ptr_s[i] == target)
			return ((char *)(ptr_s + i));
		i++;
	}
	if (ptr_s[i] == target)
		return ((char *)(ptr_s + i));
	return (NULL);
}
