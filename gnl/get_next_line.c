/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:33:50 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 18:21:33 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_until_newline(int fd, char *resto)
{
	int		bytes;
	char	*buffer;

	bytes = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_strfree(&resto));
	buffer[0] = '\0';
	while (bytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			resto = ft_strjoin_gnl(resto, buffer);
		}
	}
	ft_strfree(&buffer);
	if (bytes == -1)
		return (ft_strfree(&resto));
	return (resto);
}

char	*ft_get_new_line(char *resto)
{
	char	*linea;
	char	*salto_linea;
	int		len;

	if (!resto)
		return (NULL);
	salto_linea = ft_strchr_gnl(resto, '\n');
	if (salto_linea)
		len = (salto_linea - resto) + 1;
	else
		len = ft_strlen_gnl(resto);
	linea = ft_substr_gnl(resto, 0, len);
	if (linea == NULL)
		return (NULL);
	return (linea);
}

char	*ft_save_rest(char *resto)
{
	char	*salto_linea;
	char	*nuevo_resto;
	int		len;

	if (!resto)
		return (NULL);
	salto_linea = ft_strchr_gnl(resto, '\n');
	if (salto_linea == NULL)
		return (ft_strfree(&resto));
	len = (salto_linea - resto) + 1;
	if (resto[len] == '\0')
		return (ft_strfree(&resto));
	nuevo_resto = ft_substr_gnl(resto, len, ft_strlen_gnl(resto) - len);
	if (nuevo_resto == NULL)
		return (ft_strfree(&resto));
	ft_strfree(&resto);
	return (nuevo_resto);
}

char	*get_next_line(int fd)
{
	static char	*resto;
	char		*linea;

	if (fd < 0)
		return (NULL);
	if (!resto || (resto && !ft_strchr_gnl(resto, '\n')))
		resto = ft_read_until_newline(fd, resto);
	if (!resto)
		return (NULL);
	linea = ft_get_new_line(resto);
	if (!linea)
		return (ft_strfree(&resto));
	resto = ft_save_rest(resto);
	return (linea);
}

/*int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		i;

	i = 1;

	//LEER DE ARCHIVO
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("linea %d: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	//

	//LEER DE STDIN
	fd = STDIN_FILENO;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("linea %d: %s", i, line);
		free(line);
		i++;
	}
	(void)argv;
	//

	(void)argc;
	return (0);
}*/
