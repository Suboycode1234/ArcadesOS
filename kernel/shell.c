#include "shell.h"
#include "vga.h"

#define BUFFER_SIZE 128
static char input_buffer[BUFFER_SIZE];
static int buffer_idx = 0;

static void print_string(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        print_char(str[i]);
    }
}

void init_shell()
{
    buffer_idx = 0;
    print_string("ArcadeOS> ");
}

void shell_handle_char(char c)
{
    if (c == '\n')
    {
        input_buffer[buffer_idx] = '\0';
        print_char('\n');
        
        print_string("You typed: ");
        print_string(input_buffer);
        print_char('\n');

        buffer_idx = 0;
        print_string("ArcadeOS> ");
    }
    else if (c == '\b')
    {
        // Safe check to prevent underflow
        if (buffer_idx > 0)
        {
            buffer_idx--;
            print_char('\b');
        }
    }
    else
    {
        // Only accept printable characters (ASCII space to tilde)
        if (c >= ' ' && c <= '~')
        {
            // Safe check to prevent overflow (leaves 1 space for null terminator)
            if (buffer_idx < BUFFER_SIZE - 1)
            {
                input_buffer[buffer_idx++] = c;
                print_char(c);
            }
        }
    }
}
