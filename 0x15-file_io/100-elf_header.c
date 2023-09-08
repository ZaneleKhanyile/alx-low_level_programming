#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/**
 * error_exit - Print an error message to stderr and exit with status code 98.
 * @msg: The error message to display.
 */
void error_exit(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(98);
}

/**
 * print_elf_header_info - Print information from the ELF header.
 * @ehdr: Pointer to the ELF header.
 */
void print_elf_header_info(Elf64_Ehdr *ehdr)
{
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++)
        printf("%02x ", ehdr->e_ident[i]);
    printf("\n");
    
    printf("  Class:                             %s\n", (ehdr->e_ident[EI_CLASS] == ELFCLASS32) ? "ELF32" : "ELF64");
    printf("  Data:                              %s\n", (ehdr->e_ident[EI_DATA] == ELFDATA2LSB) ? "2's complement, little endian" : "Unknown");
    printf("  Version:                           %d (current)\n", ehdr->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %s\n", ehdr->e_ident[EI_OSABI] == ELFOSABI_SYSV ? "UNIX - System V" : "Other");
    printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %s\n", (ehdr->e_type == ET_EXEC) ? "EXEC (Executable file)" : "Other");
    printf("  Entry point address:               %#lx\n", ehdr->e_entry);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        error_exit("Usage: elf_header elf_filename");

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        error_exit("Error: Can't open ELF file");

    Elf64_Ehdr ehdr;
    if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) == -1)
        error_exit("Error: Can't read ELF header");

    // Check if it's a valid ELF file
    if (ehdr.e_ident[EI_MAG0] != ELFMAG0 || ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr.e_ident[EI_MAG2] != ELFMAG2 || ehdr.e_ident[EI_MAG3] != ELFMAG3)
        error_exit("Error: Not an ELF file");

    printf("ELF Header:\n");
    print_elf_header_info(&ehdr);

    close(fd);
    return 0;
}
