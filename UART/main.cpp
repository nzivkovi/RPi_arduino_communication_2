#include<stdio.h>
#include<unistd.h>

#include<fcntl.h>
#include<termios.h>

// alias for /dev/ttyAMA0
#define UART_PATH "/dev/serial0"

void init_uart(int& fd){
	fd = open(UART_PATH, O_RDWR);
	if(fd == -1){
		perror("Error - Unable to open UART");
	}
	termios options{};
	tcgetattr(fd, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
}

template <size_t S>
int sendString(int& fd, unsigned char* tx_buffer){
	if(fd != -1){
		if(write(fd, tx_buffer, S) < 0) {
			perror("UART TX error");
			return -1;
		}
	}
    return 1;
}

template <size_t S>
int receiveString(int& fd){
	if(fd != -1){
		unsigned char rx_buffer[S];
		ssize_t rx_length = read(fd, (void*) rx_buffer, S);
		if(rx_length < 0) {
			perror("UART RX error");
			return -1;
		}
		printf("%s\n", rx_buffer);
		return 1;
	}
	return -1;
}

int main() {
	int fd;
	init_uart(fd);
	
	unsigned char words[] = "Hello World";
	sendString<sizeof(words)>(fd, words);
	usleep(50000);
	
	receiveString<sizeof(words)>(fd);
	close(fd);
	return 1;
}
