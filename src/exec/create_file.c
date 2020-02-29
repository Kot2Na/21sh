/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:57:50 by mdelphia          #+#    #+#             */
/*   Updated: 2020/02/29 20:38:23 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
// для чтения из файла
static int	read_file(t_red_stream *stream_list)
{
	if ((stream_list->fd_file = open(stream_list->stream_name, O_RDWR)) < 0)
	{
		ft_putstr_fd ("42sh: no such file or directory: ", 2);
		ft_putstr_fd(stream_list->stream_name, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	return (stream_list->fd_file);
}

int			create_file(t_red_stream *stream_list)
{
	if (stream_list->flag_file > 0)	// если нужно создать файл или открыть его для записи в него
	{
		if ((stream_list->fd_file = new_or_open_file(stream_list->stream_name,
				stream_list->flag_file)) < 0)
			return (-1);
	}
	else if (stream_list->flag_file < 0)	// если нужно открыть для чтения
	{
		if ((stream_list->fd_file = read_file(stream_list)) < 0)
			return (-1);
	}
	return (stream_list->fd_file);
}
