/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   johnny.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:38:03 by gzenner           #+#    #+#             */
/*   Updated: 2025/10/23 14:17:56 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
the idea is to have a User Experience like this:

Johnny - Nano Clone
Instructions: '_save' for saving, '_open' for opening, '_exit' for exit

line1content var x = 5
line2content var y = 2
_save
_exit

first:
write the function that prints the instructions:
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define READ_BUFFER 1024 // how many bytes per line get stored?
#define LINES_BUFFER 1024 // how many lines get stored?

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

void	print_instructions(void)
{
	ft_putstr("Johnny - Nano Clone\n");
	ft_putstr("Instructions: \n'_save' for saving\n'_load' for loading\
		\n'_exit' for exit\n'_clear' to clear console\n");
}

void calloc_txt(char txt[], unsigned int length)
{
	unsigned int	i;

	i = 0;
	while (i++ < length)
		txt[i - 1] = 0;
}

void	calloc_content(char content[LINES_BUFFER][READ_BUFFER])
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i++ < LINES_BUFFER)
	{
		j = 0;
		while (j < READ_BUFFER)
			content[i - 1][j++] = 0;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int				diff;
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (!s1[i])
			return (0);
		++i;
	}
	diff = (unsigned char)s1[i] - (unsigned char)s2[i];
	if (diff < 0)
		return (-1);
	else if (diff > 0)
		return (1);
	return (0);
}

void	save(char content[LINES_BUFFER][READ_BUFFER])
{
	int				fd;
	unsigned int	i;
	unsigned int	j;

	fd = open("file.txt", O_WRONLY);
	if (!content || fd == -1)
	{
		ft_putstr("Error Saving.\n");
		return ;
	}
	i = 0;
	while (i < LINES_BUFFER)
	{
		j = 0;
		while (content[i][j])
			write(fd, &content[i][j++], 1);
		++i;
	}
	ft_putstr("File saved to file.txt!\n");
	close(fd);
}

void	load(char content[LINES_BUFFER][READ_BUFFER])
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	line;
	char			filebuffer[LINES_BUFFER * READ_BUFFER];
	int				bytes_read;
	int				fd;

	fd = open("file.txt", O_RDONLY);
	calloc_txt(filebuffer, LINES_BUFFER * READ_BUFFER);
	bytes_read = read(fd, filebuffer, 1024*1024*1024/*LINES_BUFFER * READ_BUFFER*/);
	printf("filebuffer: %s\n", filebuffer);
	ft_putstr("================");
	close(fd);
	if (bytes_read == -1)
	{
		ft_putstr("Error Reading File");
			return ;
	}
	filebuffer[bytes_read] = 0;
	j = 0;
	i = 0;
	line = 0;
	while (filebuffer[i])
	{
		content[line][j++] = filebuffer[i];
		if (filebuffer[i] == '\n')
		{
			++line;
			j = 0;
		}
		++i;
	}
	unsigned int	lines;

	lines = line;
	//content[line][0] = 0;
	line = 0;
	i = 0;
	/*while (line < lines)
	{
		ft_putstr(content[line++]);
	}*/
	ft_putstr(content[0]);
	ft_putstr(content[1]);
	ft_putstr(content[2]);
	ft_putstr(content[4]);
}

void	ft_cpyarr(char content[LINES_BUFFER][READ_BUFFER], char txt[], unsigned int *line)
{
	unsigned int	i;

	i = 0;
	while (txt[i++])
		content[*line][i - 1] = txt[i - 1];
	(*line)++;
}

int	main(void)
{
	unsigned int	line;
	int				bytes_read;
	char			txt[READ_BUFFER];
	char			content[LINES_BUFFER][READ_BUFFER];

	calloc_content(content);
	print_instructions();
	line = 0;
	while (1)
	{
		calloc_txt(txt, READ_BUFFER);
		bytes_read = read(0, txt, READ_BUFFER);
		if (bytes_read == -1)
		{
			ft_putstr("Error Reading Input");
			continue;
		}
		if (!ft_strcmp(txt, "_save\n"))
			save(content);
		if (!ft_strcmp(txt, "_load\n"))
			load(content);
		if (!ft_strcmp(txt, "_exit\n"))
			break;
		ft_cpyarr(content, txt, &line);
	}
	return (0);
}
