
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int s; 
struct sockaddr_can addr;
struct ifreq ifr;

void changeTerminalMode(int);
int  kbhit(void);

int can_socketCanOpen();
int can_socketCanClose();
int can_SendFrame(struct can_frame frame);
int can_ReceiveFrame(struct can_frame *frame);


int main(int argc, char **argv)
{
    int executeAppliaction = 1;
    int keyValue;
    
    int status = 0;
  
    
    changeTerminalMode(1);
    system("clear");
    printf("Campus02 CAN Sockets Demo...\r\n");

    status = can_socketCanOpen();
    if(status == 1){
        return 0;
    }

    while(executeAppliaction == 1){
        struct can_frame tx_frame;

        if(kbhit())
        {
            keyValue = getchar();

            switch (keyValue)
            {
            case 'e':
            case 'E':
                // Switch all LEDs on... 
               	tx_frame.can_id = 0x000; // ToDo ...
                tx_frame.can_dlc = 1;    // ToDo ...
                tx_frame.data[0] = 0x00; // ToDo ...
                can_SendFrame(tx_frame);
                break;
            
            case 'a':
            case 'A':
                // Switch all LEDs off...
                // ToDo ...
                break;
            case 'x':
            case 'X':
                executeAppliaction = 0;
                break;

            default:
                break;
            }

        }
        else{
            // Receive CAN Messages
            struct can_frame rx_frame;
            can_ReceiveFrame(&rx_frame);
              
            // Check for Digital Input...
            if( rx_frame.can_id == 0x701){
                if(rx_frame.data[0] == 0x08){
                    printf("JoyStick button right pressed ...\r\n");    
                }
                if(rx_frame.data[0] == 0x02){
                    printf("JoyStick button left pressed ...\r\n");    
                }                
            }


            //Check for I2C LM75 Temp. Sensor..
            if( rx_frame.can_id == 0x000){  // ToDo ...
              
                float tempValue = 0.0f;

                // Retrieve the temperature sensor value from data byte 0 and 1 (value Format: ##.##)...
                // ToDo ...

                printf("Temp.: %2.2f °C\r\n", tempValue);
              }
        }


    } 
    can_socketCanClose();
	return 0;
}


int can_socketCanOpen(){
	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		printf("Error: socket()...\r\n");
		return 1;
	}

	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		printf("Error bind()...\r\n");
		return 1;
	}
    printf("can_socketCanOpen()...\r\n");
    return 0;
}

int can_socketCanClose(){
	if (close(s) < 0) {
		printf("Error: close()...\r\n");
		return 1;
	}
    printf("can_socketCanClose()...\r\n");
    return 0;
}

int can_SendFrame(struct can_frame frame){
    	if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
		    printf("Error: write()...\r\n");
		    return 1;
	}
    printf("can_SendFrame() ID=0x%03X  DLC=%d Data=0x", frame.can_id, frame.can_dlc);
    for(int i = 0; i < frame.can_dlc;i++){
        printf("%02X ",frame.data[i]);
    }
    printf("\r\n");

    return 0;
}

int can_ReceiveFrame(struct can_frame *frame){
	int nbytes = read(s, frame, sizeof(struct can_frame));

 	if (nbytes < 0) {
		printf("Error: read()");
		return 1;
	}

	printf("can_ReceiveFrame() ID=0x%03X DLC=%d Data=0x",frame->can_id, frame->can_dlc);

	for (int i = 0; i < frame->can_dlc; i++)
		printf("%02X ", frame->data[i]);

	printf("\r\n");
}

void changeTerminalMode(int enableRawMode)
{
  static struct termios oldt, newt;

  if ( enableRawMode == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);

  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);

}