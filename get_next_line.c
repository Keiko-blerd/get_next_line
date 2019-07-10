/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhlatshw <nhlatshw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 03:42:43 by nhlatshw          #+#    #+#             */
/*   Updated: 2019/07/10 11:40:33 by nhlatshw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	add_line(char **s_char, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*s_char)[len] != '\n' && (*s_char)[len] != '\0')
		len++;
	if ((*s_char)[len] == '\n')
	{
		*line = ft_strsub(*s_char, 0, len);
		tmp = ft_strdup(&((*s_char)[len + 1]));
		free(*s_char);
		*s_char = tmp;
		if ((*s_char)[0] == '\0')
			ft_strdel(s_char);
	}
	else
	{
		*line = ft_strdup(*s_char);
		ft_strdel(s_char);
	}
	return (1);
}

static int	output(char **s_char, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && s_char[fd] == NULL)
		return (0);
	else
		return (add_line(&s_char[fd], line));
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*s[FD_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (output(s, line, ret, fd));
}
