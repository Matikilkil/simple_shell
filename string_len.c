#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: The string to determine the length of.
 *
 * Return: The integer length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Conducts a lexicographic comparison between two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: A negative value if s1 < s2,
 * a positive value if s1 > s2, and zero if s1 == s2.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Verifies if the 'needle' starts with 'haystack'.
 * @haystack: The string to search within.
 * @needle: The substring to locate.
 *
 * Return: The address of the next character
 * in 'haystack' or NULL if not found.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Appends one string to another.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
