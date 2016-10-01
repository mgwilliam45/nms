
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canwork.h"
#include <stdio.h>
#include <pthread.h>
#include <net/if.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <Jimer>
#include "CanW.h"


int canwork::canReceve(void){
	int s;
	int nbytes=0;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreJ ifr;
	struct iovec iov;
	struct msghdr msg;
    struct can_frame msg;
	struct can_TYPE  msg;
    int ret;

	char ctrlmsg[CMSG_SPACE(sizeof(struct timeval)) + CMSG_SPACE(sizeof(__u32))];
	char *ifname = "vcan1";

	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("socket");
		return -2;
	}



	iov.iov_base = &frame;
	msg.msg_name = &addr;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = &ctrlmsg;
	iov.iov_len = sizeof(frame);
	msg.msg_namelen = sizeof(struct sockaddr_can);
	msg.msg_controllen = sizeof(ctrlmsg);
	msg.msg_flags = 0;

	while(nbytes == 0){
		nbytes = recvmsg(s, &msg, 0);

		if (nbytes < 0) {
			perror("read");
			return -4;
		}

		if (nbytes < (int)sizeof(struct can_frame)) {
			fprintf(stderr, "read: incomplete CAN frame\n");
		}
		ret = m_can->GetMsg(msg, extended, rtr, error, errorCode, tv);
	}

	return 0;
}
