/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pragolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 10:10:43 by pragolan          #+#    #+#             */
/*   Updated: 2018/06/30 14:31:18 by pragolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strjoin_free(const char *s1, const char *s2, int i_res)
{
	char	*str1;

	if (!(str1 = (char *)malloc((i_res + ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	ft_strcpy(str1, s1);
	ft_strcat(str1, s2);
	free((char *)s1);
	return (str1);
}

static char	*ft_strsub_free(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (!(str = (char *)ft_memalloc((len + 1) * sizeof(char))))
		return (NULL);
	else
	{
		while (len)
		{
			str[i] = s[start];
			i++;
			start++;
			len--;
		}
	}
	str[i] = '\0';
	free((char *)s);
	return (str);
}

static char	*whatsleft(char **line, char *temp)
{
	int iter;

	iter = 0;
	while (temp[iter] != '\0')
	{
		if (temp[iter] == '\n')
		{
			*line = ft_strsub(temp, 0, iter);
			iter++;
			return (ft_strsub_free(temp, iter, (ft_strlen(temp)) - iter));
		}
		iter++;
	}
	*line = ft_strsub(temp, 0, iter);
	return (ft_strsub_free(temp, iter, (ft_strlen(temp) + 1) - iter));
}

int			get_next_line(const int fd, char **line)
{
	int			i_res;
	char		buf[BUFF_SIZE + 1];
	static char	*all_lines[12288] = {NULL};
	char		*temp;

	if (fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	if (!all_lines[fd])
		all_lines[fd] = (char *)ft_memalloc(sizeof(char) * 1);
	while ((i_res = read(fd, buf, BUFF_SIZE)))
	{
		buf[i_res] = '\0';
		all_lines[fd] = strjoin_free(all_lines[fd], buf, i_res);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	temp = all_lines[fd];
	if (ft_strlen(temp) == 0)
		return (0);
	else
	{
		all_lines[fd] = whatsleft(line, temp);
		return (1);
	}
}
