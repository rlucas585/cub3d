#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int			main(void)
{
	int		fd;
	int		w;
	int		h;
	unsigned int		size;

	w = 5;
	h = 5;
	size = w * h * 3 + 54;
	printf("size = %u\n", size);
	fd = open("bmptest2.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, "BM", 2); // the filetype (2 bytes)
	write(fd, &size, 4);
	write(fd, "\x00\x00\x00\x00", 4); // reserved bytes for image processing
	write(fd, "\x36\x00\x00\x00", 4); // Pixel Data offset
	write(fd, "\x28\x00\x00\x00", 4); // Size of bitmap header
	write(fd, &w, 4); // Image width
	write(fd, &h, 4); // Image height
	write(fd, "\x01\x00", 2); // Number of color planes
	write(fd, "\x18\x00\x00\x00", 2); // Bits per pixel
	write(fd, "\x00\x00\x00\x00", 4); // Compression (set to 0)
	write(fd, "\x00\x00\x00\x00", 4); // Image Size - set to 0 when no compression
	write(fd, "\x00\x00\x00\x00", 4); // xpixels res of target dev, 0 = no preference
	write(fd, "\x00\x00\x00\x00", 4); // ypixels, as above
	write(fd, "\x00\x00\x00\x00", 4); // Total colors in pallet, uses bpp if blank
	write(fd, "\x00\x00\x00\x00", 4); // Important colors, 0 = ignore
	int		i = 2;
	write(fd, "\x00\xff\x00", 3);
	while (i <= 23)
	{
		write(fd, "\xff\x00\x00", 3);
		if (i % 5 == 0)
			write(fd, "\x00", 1);
		i++;
	}
	while (i <= 25)
	{
		write(fd, "\x00\x00\xff", 3);
		if (i % 5 == 0)
			write(fd, "\x00", 1);
		i++;
	}
	close(fd);
}
