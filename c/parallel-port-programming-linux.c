/*
    Write to (or read from) parallel port in C on Linux (Ubuntu 8.04).
    Compile with:
                    gcc -Wall -O2 pp.c -o pp

    The -O option is important: the level doesn't matter but it must be there
    to get the outb() and inb() macros (-O, -O1, -O3 can also be used).
    Execute with:
                    sudo ./pp

    Pieter Suurmond, august 4, 2009.
*/

#include <stdio.h>
#include <unistd.h>     /* For sleep(), ioperm(), inb() and outb(). */
#include <sys/io.h>     /* Perhaps asm/io.h on other systems. */

/* Address of the first parallel port. You can find this (hex) base-address
   in your BIOS settings. */
#define kDATA_REG (0x0378)          /* Base address = data register. */
#define kSTAT_REG (DATA_REG + 1)    /* Status register. */
#define kCONT_REG (DATA_REG + 2)    /* Control register. */

int main()
{
    int i;

    if (ioperm(kDATA_REG, 1, 1))    /* Get permission to access this port. */
        {
        printf("ioperm(%x) failed.\nYou must be root to execute!\n", kDATA_REG);
        return 1;
        }

    /* Assume port is already in output mode (bit 5 in control register). */
    for (i = 0; i < 10; i++)        /* Let the LED(s) blink. */
        {
        outb(255, kDATA_REG);       /* All 8 datalines high. */
        sleep(1);
        outb(0, kDATA_REG);         /* All 8 datalines low.  */
        sleep(1);
        }

    return 0;
}

