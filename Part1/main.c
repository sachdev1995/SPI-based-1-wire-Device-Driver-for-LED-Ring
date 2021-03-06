#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include "spi_ioctl.h"
#include "spi_platform_device.h"


struct rgb {
	unsigned char green, blue, red;
};
struct input_data {
	int n;
	struct rgb *data;
};

/* main function to send RGB LED data
	to kernel space 
*/

int main() {
	
	int fd, i= 0, j = 0;
	char *name;
	if (!(name = malloc(sizeof(char)*40)))
	{
		printf("Bad Kmalloc\n");
		return -ENOMEM;
	}
	memset(name, 0, sizeof(char)*40);
	snprintf(name, sizeof(char)*40, "/dev/%s", Device0Name);
	fd = open(name, O_RDWR);
	
	printf("Resetting the SPI device\n");
	
	if(ioctl(fd, RESET, (unsigned long)&i) < 0){
		printf("Error while Resetting the spi \n");
		return -1;
	}

	if(ioctl(fd, CLEAR, (unsigned long)&i) < 0){
		printf("Error while Resetting the spi \n");
		return -1;
	}

/* below code will add RGB colour related data to
data structure which will be then send
to kernel space */
	
	struct input_data data;
	data.n = 3;
	data.data = malloc(sizeof(struct rgb)*data.n);
	
	data.data[0].green = 128;
	data.data[0].blue = 0;
	data.data[0].red = 255;

	data.data[1].green = 255;
	data.data[1].blue = 255;
	data.data[1].red = 51;

	data.data[2].green = 255;
	data.data[2].blue = 102;
	data.data[2].red = 102;

	data.data[3].green = 0;
	data.data[3].blue = 127;
	data.data[3].red = 255;

	data.data[4].green = 153;
	data.data[4].blue = 153;
	data.data[4].red = 0;
	
	data.data[5].green = 128;
	data.data[5].blue = 0;
	data.data[5].red = 255;

	data.data[6].green = 128;
	data.data[6].blue = 0;
	data.data[6].red = 255;

	data.data[7].green = 255;
	data.data[7].blue = 102;
	data.data[7].red = 102;

	data.data[8].green = 0;
	data.data[8].blue = 127;
	data.data[8].red = 255;

	data.data[9].green = 153;
	data.data[9].blue = 153;
	data.data[9].red = 0;

	data.data[10].green = 128;
	data.data[10].blue = 0;
	data.data[10].red = 255;

	data.data[11].green = 128;
	data.data[11].blue = 0;
	data.data[11].red = 255;

	data.data[12].green = 255;
	data.data[12].blue = 102;
	data.data[12].red = 102;

	data.data[13].green = 0;
	data.data[13].blue = 127;
	data.data[13].red = 255;

	data.data[14].green = 153;
	data.data[14].blue = 153;
	data.data[14].red = 0;

	data.data[15].green = 153;
	data.data[15].blue = 153;
	data.data[15].red = 0;

	struct rgb temp;
	
	/* loop to rotate the colours
	RGB LED */

	// creating the pattern, we can change the loop count to anything
	while(j < 3)
	{
		temp.green = data.data[0].green;
		temp.blue = data.data[0].blue;
		temp.red = data.data[0].red;
		write(fd, (void *)&data, sizeof(data));
		i = 0;
		while(i < 15)
		{		
			data.data[i].green = data.data[i+1].green;
			data.data[i].blue = data.data[i+1].blue;
			data.data[i].red = data.data[i+1].red;
			i = i+1;
		}
		data.data[i].red = temp.red;
		data.data[i].blue = temp.blue;
		data.data[i].green = temp.green;
		j = j + 1;
		//sleep(3);
	}
		
	return 1;
		
}
