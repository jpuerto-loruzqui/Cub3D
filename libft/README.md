<p align="end">
  <strong>🌐 Change language:</strong><br>
  <a href="/README.es.md">
   <img src="https://github.com/Nachopuerto95/multilang/blob/main/ES.png" alt="Español" width="50">
 </a>&nbsp;&nbsp;&nbsp;
 <a href="/README.md">
   <img src="https://github.com/Nachopuerto95/multilang/blob/main/EN.png" alt="English" width="50">
 </a>
</p>

# 📚 Libft (42cursus)

<img src="https://github.com/Nachopuerto95/multilang/blob/main/42-Madrid%20-%20Edited.jpg">

## 📜 About Project
> As the first project of the cursus, it is meant to familiarize us with various functions and how they are designed internally.

```html
	🚀 We will solidify our knowledge of C usage and memory, both pointer usage and
	dynamic memory. At bonus part, we will introduce ourselves to linked lists usage
```
> [!NOTE]
> Because of 42 School norm requirements:
> * Each function can't have more than 25 lines of code.
> * All variables must be declared and aligned at the top of each function.
> * Project should be created just with allowed functions.
<br>

## 📖 Description

This project is a __C library__ of useful functions that are allowed to be used in future __School 42 cursus__ projects. With access to this library, the coding proccess in incoming projects will be more effective. The aim of rewrite this functions is to get a better understanding of them, and get a whide range of utilities for the next projects.

## 📚 Index
### Functions from `<ctype.h>` library
* [`ft_isascii`](https://github.com/Nachopuerto95/libft/blob/main/ft_isascii.c) - Test a character to see if it's a 7-bit ASCII character.
* [`ft_isalpha`](https://github.com/Nachopuerto95/libft/blob/main/ft_isalpha.c) - Test a character to see if it's alphabetic.
* [`ft_isdigit`](https://github.com/Nachopuerto95/libft/blob/main/ft_isdigit.c) - Test a character to see if it's a decimal digit.
* [`ft_isalnum`](https://github.com/Nachopuerto95/libft/blob/main/ft_isalnum.c) - Test a character to see if it's alphanumeric.
* [`ft_isprint`](https://github.com/Nachopuerto95/libft/blob/main/ft_isprint.c) - Test a character to see if it's any printable character, including a space.
* [`ft_tolower`](https://github.com/Nachopuerto95/libft/blob/main/ft_tolower.c) - Convert a character to lowercase.
* [`ft_toupper`](https://github.com/Nachopuerto95/libft/blob/main/ft_toupper.c) - Convert a character to uppercase.

### Functions from `<stdlib.h>` library
* [`ft_atoi`](https://github.com/Nachopuerto95/libft/blob/main/ft_atoi.c) - Convert ASCII string to integer.
* [`ft_calloc`](https://github.com/Nachopuerto95/libft/blob/main/ft_calloc.c) - Allocate space for an array and initializes it to 0. This function and `malloc` return a void pointer, that had no associated data type with it. A void pointer can hold address of any type and can be typecasted to any type.

### Functions from `<strings.h>` library
* [`ft_bzero`](https://github.com/Nachopuerto95/libft/blob/main/ft_bzero.c) - Set the first part of an object to null bytes (filling it with zeroes).
* [`ft_memset`](https://github.com/Nachopuerto95/libft/blob/main/ft_memset.c) - Set memory to a given value.
* [`ft_memchr`](https://github.com/Nachopuerto95/libft/blob/main/ft_memchr.c) - Find the first occurrence of a character in a buffer (locate byte in byte string).
* [`ft_memcmp`](https://github.com/Nachopuerto95/libft/blob/main/ft_memcmp.c) - Compare the bytes in two buffers.
* [`ft_memmove`](https://github.com/Nachopuerto95/libft/blob/main/ft_memmove.c) - Copy bytes from one buffer to another, handling overlapping memory correctly.
* [`ft_memcpy`](https://github.com/Nachopuerto95/libft/blob/main/ft_memcpy.c) - Copy bytes from one buffer to another.

### Functions from `<string.h>` library
* [`ft_strlen`](https://github.com/Nachopuerto95/libft/blob/main/ft_strlen.c) - Get the length of a string.
* [`ft_strchr`](https://github.com/Nachopuerto95/libft/blob/main/ft_strchr.c) - Find the first occurrence of a character in a string.
* [`ft_strrchr`](https://github.com/Nachopuerto95/libft/blob/main/ft_strrchr.c) - Find the last occurrence of a character in a string.
* [`ft_strnstr`](https://github.com/Nachopuerto95/libft/blob/main/ft_strnstr.c) - Locate a substring in a string.
* [`ft_strncmp`](https://github.com/Nachopuerto95/libft/blob/main/ft_strncmp.c) - Compare two strings, up to a given length.
* [`ft_strdup`](https://github.com/Nachopuerto95/libft/blob/main/ft_strdup.c) - Create a duplicate of a string, using `malloc`.
* [`ft_strlcpy`](https://github.com/Nachopuerto95/libft/blob/main/ft_strlcpy.c) - Size-bounded string copy.
* [`ft_strlcat`](https://github.com/Nachopuerto95/libft/blob/main/ft_strlcat.c) - Size-bounded string concatenation.

### Non-standard functions
* [`ft_itoa`](https://github.com/Nachopuerto95/libft/blob/main/ft_itoa.c) - Convert integer to ASCII string.
* [`ft_substr`](https://github.com/Nachopuerto95/libft/blob/main/ft_substr.c) - Get a substring from string.
* [`ft_strtrim`](https://github.com/Nachopuerto95/libft/blob/main/ft_strtrim.c) - Trim beginning and end of string with the specified substring.
* [`ft_strjoin`](https://github.com/Nachopuerto95/libft/blob/main/ft_strjoin.c) - Concatenate two strings into a new string, using `calloc`.
* [`ft_split`](https://github.com/Nachopuerto95/libft/blob/main/ft_split.c) - Split string, with specified character as delimiter, into an array of strings.
* [`ft_strmapi`](https://github.com/Nachopuerto95/libft/blob/main/ft_strmapi.c) - Create new string from a string modified with a specified function.
* [`ft_striteri`](https://github.com/Nachopuerto95/libft/blob/main/ft_striteri.c) - Modify a string with a given function.
* [`ft_putchar_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putchar_fd.c) - Output a character to given file.
* [`ft_putstr_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putstr_fd.c) - Output string to given file.
* [`ft_putendl_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putendl_fd.c) - Output string to given file with newline.
* [`ft_putnbr_fd`](https://github.com/Nachopuerto95/libft/blob/main/ft_putnbr_fd.c) - Output integer to given file.

### Linked list functions *(bonus)*
* [`ft_lstnew`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstnew_bonus.c) - Create new list.
* [`ft_lstsize`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstsize_bonus.c) - Count elements of a list.
* [`ft_lstlast`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstlast_bonus.c) - Find last element of list.
* [`ft_lstadd_back`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstadd_back_bonus.c) - Add new element at end of list.
* [`ft_lstadd_front`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstadd_front_bonus.c) - Add new element at beginning of list.
* [`ft_lstdelone`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstdelone_bonus.c) - Delete element from list.
* [`ft_lstclear`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstclear_bonus.c) - Delete sequence of elements of list from a starting point.
* [`ft_lstiter`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstiter_bonus.c) - Apply function to content of all list's elements.
* [`ft_lstmap`](https://github.com/Nachopuerto95/libft/blob/main/ft_lstmap_bonus.c) - Apply function to content of all list's elements into new list.

## 🛠️ Instructions

### 1. Compiling the library

To compile the library, go to its path and run:

For __basic__ functions:

```shell
$ make
```

For __bonus__ functions:

```shell
$ make bonus
```

### 2. Cleaning all binary (.o) and executable files (.a)

To delete all files generated with make, go to the path and run:

```shell
$ make fclean
```

### 3. Using it in your code

To use the library functions in your code, include it in your Makefile:

```Makefile
$(NAME): $(OBJ)
	cd libft && $(MAKE)
	$(CC) $(CFLAGS) $(OBJ)  -L ./libft -lft -o $(NAME)
```

then import the library in your code
```c
#include "libft.h"
```
