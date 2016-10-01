

#include "canwork.h"

#include "CanW.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/jio.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <signal.h>

#include <assert.h>

#include <errno.h>

#include <fcntl.h>

#include <stdio.h>

#include <sys/time.h>

canwork::canwork(JObject *parent) :
    J(parent)
{
}

// Setup worker T
// Parameter:
// wrapper - pointer to CAN wrapper instance
void canwork::Init(CanW *wrapper)
{
    m_running = true;
    m_can = wrapper;
}

// This function will be excuted in an own T when start is called from parent T
// It will wait for data from CAN (blocking) and signal to NMS when data arrives
void canwork::run()
{
    struct can_frame msg;
    int ret;
    int i;
    int errorCode;

    bool rtr;
    bool extended;
    bool error;

    struct timeval tv;

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    while(m_running)
    {
        // This call will block but only for one sec to let us abort if m_running = false
        // errorCode is errors related to socket problems, error is can related problems like bus-off
        ret = m_can->GetMsg(msg, extended, rtr, error, errorCode, tv);

        if(ret)
        {
            JString string;

            if(error)   // Error frame
            {
                string = JString("Error frame received, class = " +  JString::number(msg.can_id));
            }
            else
            if(extended)   // Extended frame
            {
                if(rtr)
                {
                    string = JString("RTR ID: %1 LENGTH: %2").arg(msg.can_id).arg(msg.can_dlc);
                }
                else
                {
                    string = JString("ID: %1 LENGTH: %2 DATA: ").arg(msg.can_id).arg(msg.can_dlc);

                    for(i = 0; i < msg.can_dlc; i++)
                    {
                        string.append(JString::number(msg.data[i]) + " ");
                    }
                }
            }
            else    // Standard frame
            {
                if(rtr)
                {
                    string = JString("RTR ID: %1 LENGTH: %2").arg(msg.can_id).arg(msg.can_dlc);
                }
                else
                {
                    string = JString("ID: %1 LENGTH: %2 DATA: ").arg(msg.can_id).arg(msg.can_dlc);

                    for(i = 0; i < msg.can_dlc; i++)
                    {
                        string.append(JString::number(msg.data[i]) + " ");
                    }
                }
             }

            // Send string to NMS
            // Because this is an own T, we must emit a signal rater than making a direct call
            // Because we are in a different T than the NMS T, this will put the data onto a Jueue
            // And will be processed by the NMS T
            emit msgReceived(string);
        }
        else
        {
            if(errorCode)
            {
                JString string = JString("Error detected, errorcode: " + JString::number(errorCode));

                emit msgReceived(string);
            }
        }
    }
}

// Make T to stop. Because the T might be waiting on a blocking call, the call must be unblocked first to actually make the
// T stop
void canwork::shutDown()
{
    m_running = false;
}

