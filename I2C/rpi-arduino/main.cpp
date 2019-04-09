#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>

int openI2CBus(int& fd){
	if((fd = open("/dev/i2c-1", O_RDWR)) < 0){
		perror("Failed to open I2C bus\n");
		return -1;
	}
	return 1;
}

void connectToSlave(int& fd, unsigned char slaveAddr){
	if(ioctl(fd, I2C_SLAVE, slaveAddr) < 0){
		perror("Failed to connect to the Arduino\n");
		return;
	}
}

void sendLong(int& fd, long value){
	unsigned char bytes[sizeof(long)];
	for(int j = 0;j < sizeof(long); ++j){
		bytes[j] = value >> 8 * j;
	}
	if(write(fd, bytes, sizeof(long)) != sizeof(long)){
		perror("Failed to send data\n");
		return;
	}
}

void receiveLong(int& fd, long& value){
	long& dataReceived = value;
	unsigned char bytes[sizeof(long)];
	if(read(fd, bytes, sizeof(long)) != sizeof(long)){
		perror("Failed to read the data\n");
		return;
	}
	
	dataReceived = 0;
	for(int j = 0;j < sizeof(long); ++j){
		dataReceived += bytes[j] << j * 8;
	}
}

int main(){
	int fd;
	openI2CBus(fd);
	connectToSlave(fd, 0x44);
	long value = 1;
	sendLong(fd, value);
	printf("%ld\n", value);
	long dataReceived = 0;
	receiveLong(fd, dataReceived);
	printf("%ld\n", dataReceived);
	close(fd);
	return 1;
}