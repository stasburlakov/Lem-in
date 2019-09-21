/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljonnel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 07:44:17 by ljonnel-          #+#    #+#             */
/*   Updated: 2019/02/20 07:44:19 by ljonnel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_check_or_free(int fd, char **ptr)
{
	ft_strdel(&ptr[fd]);
	return (0);
}

int				ft_check_line(int fd, char **line, char **ptr, int ret)
{
	int			i;
	char		*tmp;

	i = 0;
	if (ret < 0)
		return (-1);
	if (ret == 0 && (ptr[fd] == NULL || ptr[fd][0] == '\0'))
		return (ft_check_or_free(fd, ptr));
	while (ptr[fd][i] != '\n' && ptr[fd][i] != '\0')
		i++;
	if (ptr[fd][i] == '\n')
	{
		*line = ft_strsub(ptr[fd], 0, i);
		tmp = ft_strdup(ptr[fd] + i + 1);
		ft_strdel(&ptr[fd]);
		ptr[fd] = tmp;
	}
	else if (ptr[fd][i] == '\0')
	{
		*line = ft_strdup(ptr[fd]);
		ft_strdel(&ptr[fd]);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	*ptr[4864];
	char		*tmp;

	if (line == NULL || fd < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!ptr[fd])
			if (!(ptr[fd] = ft_strnew(1)))
				return (-1);
		buf[ret] = '\0';
		tmp = ft_strjoin(ptr[fd], buf);
		free(ptr[fd]);
		ptr[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (ft_check_line(fd, line, ptr, ret));
}
