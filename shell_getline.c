#include "shell.h"

/**
 * input_buf - Buffers a chain of commands.
 * @info: Structure containing parameters.
 * @buf: Address of the buffer.
 * @len: Address of the length variable.
 *
 * Return: The number of bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/* Clean up existing buffer if empty */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read_bytes = getline(buf, &len_p, stdin);
#else
		read_bytes = _getline(info, buf, &len_p);
#endif
		if (read_bytes >)
		{
			if ((*buf)[read_bytes - 1] == '\n') 
			{
				(*buf)[read_bytes - 1] = '\0';
				read_bytes--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* Check if a command chain is present */
			{
				*len = read_bytes;
				info->cmd_buf = buf;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - Retrieves a line without the newline character.
 * @info: Structure containing parameters.
 *
 * Return: The number of bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = input_buf(info, &buf, &len);
	if (read_bytes == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (read_bytes);
}
