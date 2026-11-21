*This project has been created as part of the 42 curriculum by helabiad.*

# Get Next Line

## Repository

[ft_get_next_line](https://github.com/helabiad/ft_get_next_line)

## Description

**Get Next Line (GNL)** is a 42 School project that focuses on file handling, memory management, and static variables in C.

The goal is to implement a function called `get_next_line()` that reads and returns one line at a time from a given file descriptor.

The function uses a static variable to preserve unread data between successive calls, allowing the program to continue reading from where it left off.

This project introduces important concepts such as file descriptors, the `read()` system call, dynamic memory allocation, and static storage duration.

## Features

### Mandatory Part

- Reads one line at a time from a file descriptor.
- Preserves unread data between successive calls using a static pointer.
- Returns the newline character (`\n`) when it is present.
- Handles EOF, including files that do not end with a newline.
- Supports standard input.
- Supports configurable `BUFFER_SIZE`.

### Bonus Part

- Uses only one static variable.
- Supports multiple file descriptors simultaneously.
- Maintains independent reading states using an array of static pointers.
- Allows switching between file descriptors without mixing their stored data.

## Instructions

### Clone the Repository

```bash
git clone https://github.com/helabiad/ft_get_next_line.git
cd ft_get_next_line
```

### Compilation

Compile the mandatory part:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c
```

Compile the bonus part:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

You can change `BUFFER_SIZE` to test different reading sizes.

If `BUFFER_SIZE` is not defined during compilation, the default value is `1`.

### Usage

Include the appropriate header:

```c
#include "get_next_line.h"
```

Function prototype:

```c
char *get_next_line(int fd);
```

Example:

```c
char *line;

line = get_next_line(fd);
while (line)
{
    printf("%s", line);
    free(line);
    line = get_next_line(fd);
}
```

The function returns:

- A dynamically allocated string containing the next line.
- `NULL` when there is nothing left to read or when an error occurs.

Remember to free every returned line.

## Project Structure

### Mandatory Files

| File                    | Description                                                 |
| ----------------------- | ----------------------------------------------------------- |
| `get_next_line.c`       | Handles reading, storing unread data, and extracting lines. |
| `get_next_line_utils.c` | Contains string manipulation helper functions.              |
| `get_next_line.h`       | Contains the function prototype, includes, and definitions. |

### Bonus Files

| File                          | Description                                             |
| ----------------------------- | ------------------------------------------------------- |
| `get_next_line_bonus.c`       | Implements multiple file descriptor support.            |
| `get_next_line_utils_bonus.c` | Contains helper functions for the bonus implementation. |
| `get_next_line_bonus.h`       | Contains bonus declarations and definitions.            |

## Algorithm

### Mandatory Part

The implementation separates the reading process from line extraction using two main functions.

**1. Reading – `read_until_line()`**

- Allocates a temporary buffer of `BUFFER_SIZE + 1` bytes.
- Uses `read()` to retrieve data from the file descriptor.
- Appends the retrieved data to the previously saved content using `ft_strjoin()`.
- Continues reading until a newline is found or EOF is reached.
- Returns the accumulated content.

**2. Line Extraction – `ft_get_line()`**

- Calls `read_until_line()` to obtain the accumulated content.
- Searches for the first newline character.
- Allocates memory for the next line and copies the extracted content.
- Allocates new storage for the remaining unread content.
- Returns the extracted line while preserving the remaining data.

**3. Main Function – `get_next_line()`**

- Maintains a static pointer called `saved`.
- Passes its address to `ft_get_line()`.
- Preserves the unread content between successive calls.
- Returns the extracted line or `NULL`.

**Algorithm justification:**

Separating reading and extraction makes the implementation easier to organize and understand.

Using a static pointer allows unread data to survive after the function returns, while dynamic memory allocation allows the function to handle lines of different lengths.

### Bonus Part

The bonus implementation extends the mandatory algorithm to support multiple file descriptors.

Instead of one static pointer, it uses a static array of pointers:

`static char *saved[FD_MAX];`

Each array element stores the unread content associated with a particular file descriptor.

When `get_next_line(fd)` is called:

1. The function checks whether the file descriptor is valid.
2. It accesses the saved content associated with that descriptor.
3. It reads and extracts the next line using the same algorithm as the mandatory part.
4. It preserves the remaining content in the corresponding array element.

**Algorithm justification:**

Using an array of pointers allows each file descriptor to maintain its own independent reading state.

This makes it possible to alternate between multiple file descriptors without mixing their buffered content.

## Resources

The following resources helped develop an understanding of the concepts used in this project:

- [Linux Manual Pages – read()](https://man7.org/linux/man-pages/man2/read.2.html)
- [Linux Manual Pages – open()](https://man7.org/linux/man-pages/man2/open.2.html)
- [Linux Manual Pages – malloc()](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/)
- [Beej's Guide to C Programming](https://beej.us/guide/bgc/)
- [cppreference – C](https://en.cppreference.com/w/c)
- [42 School](https://42.fr/)

### AI Usage

AI tools were used as learning support throughout this project.

They helped with:

- Understanding file descriptors and the `read()` system call.
- Understanding static variables and memory management.

All implementation, testing, and debugging were done by me.

AI was used as a learning resource rather than as a source of ready-made implementation.