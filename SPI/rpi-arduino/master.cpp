#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>

#define SPI_PATH "/dev/spidev0.0"

void initSpi(init& fd, unit8_t mode) {
	if((fd = open(SPI_PATH, O_RDWR)) < 0) {
		perror("SPI Error: Can't open device");
		return;
	}
	
	if(ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) {
		perror("SPI Error: Can't set SPI mode");
		return;
	}
	
	if(ioctl(fd, SPI_IOC_RD_MODE, &mode) == -1) {
		perror("SPI Error: Can't get SPI mode");
		return;
	}
	printf("SPI mode is: %d\n", mode)
}

int transferr(int fd,
	const unsigned char* send,
	const unsigned char* rec,
	unsigned int len) {
		spi_ioc_transfer transfer{};
		memset(&transfer, 0, sizeof(transfer));
		
		transfer.tx_buf = (unsigned long) send;
		transfer.rx_buf = (unsigned long) rec;
		transfer.len = len;
		transfer.speed_hz = 1000000;
		transfer.bits_per_word = 8;
		transfer.delay_usecs = 10;
		
		if((ioctl(fd, SPI_IOC_MESSAGE(1), &transfer) < 0) {
			perror("SPI Error: SPI_IOC_MESSAGE failed");
			return -1;
		}
		return 1;
}

int getFirstAndSecondValue(int& fd){
	// dummy data
	unsigned char dataSent = 0x00;
	
	unsigned char firstByteReceived, secondByteReceived;
	
	if((transfer(fd, &dataSent, &firstByteReceived, 1) == -1){
		perror("Failed to send the data");
		return -1;
	}
	
	usleep(5000);
	
	if((transfer(fd, &dataSent, &secondByteReceived, 1) == -1){
		perror("Failed to send the data");
		return -1;
	}
	
	usleep(5000);
	
	printf("[MASTER] - bytes received: %d\t%d\n", firstByteReceived, firstByteReceived);
}

int main() {
	int fd;
	initSpi(fd, 0);
	do {
		++index;
		getFirstAndSecondValue(fd)
	} while (index < 10);
	
	close(fd);
	return 0;
}
