/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhlatshw <nhlatshw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 03:42:43 by nhlatshw          #+#    #+#             */
/*   Updated: 2019/07/19 14:05:34 by nhlatshw         ###   ########.fr       */
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
	return SUCCESS;
}

static int	read_line(int fd, char *buff, char **s_char, char **line)
{	
	int			ret;
	char		*tmp;
	
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (ret < 0)
			return READERR;
		buff[ret] = '\0';
		if (s_char[fd] == NULL)
			s_char[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s_char[fd], buff);
			free(s_char[fd]);
			s_char[fd] = tmp;
		}
		if (ft_strchr(s_char[fd], '\n'))
			break ;
	}
	if (ret == 0 && s_char[fd] == NULL)
		return LINEREAD;
	else
		return (add_line(&s_char[fd], line));
}

int			get_next_line(const int fd, char **line)
{
	static char	*s_char[2000];
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || line == NULL)   
		return READERR;
	return (read_line(fd, buff, s_char, line));
}
