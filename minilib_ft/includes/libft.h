/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyroshn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:02:42 by amyroshn          #+#    #+#             */
/*   Updated: 2022/01/24 11:49:59 by amyroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* char/ */
bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isascii(int c);
bool	ft_isprint(int c);
bool	ft_isspace(char c);
int		ft_toupper(int c);
int		ft_tolower(int c);
/* mem/ */
void	*ft_memset(void *destination, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *destination, const void *source, size_t size);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
/* print/ */
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl(char *s);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr(long n);
void	ft_putnbr_fd(long n, int fd);
void	ft_putnbr_base(int nbr, char *base);
void	ft_putunsigned(unsigned long n);
void	ft_putunsigned_base(unsigned long nbr, char *base);
/* string/ */
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strrev(char *str);
size_t	ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char	*dest, const char	*src, size_t	size);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strnstr(const char	*str, const char	*to_find, size_t len);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
/* utils/ */
int		ft_atoi( const char *s);
long	ft_atol_sample(char *numb);
char	*get_next_line(int fd);
size_t	ft_numblen(long numb);
/* math/ */
long	ft_pow(long nb, int power);

#endif
