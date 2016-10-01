

#include "mainwindow.h"
#include "ji_mainwindow.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/jio.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include <JDebug>
#include <assert.h>
#include <stdio.h>

#include <JMessageBox>
#include <JString>

#include <canwork.h>

#define BURSTSIZE 1000       // Size of message burst sent when pressing Send Burst

MainWindow::MainWindow(JWidget *parent) :
    JMainWindow(parent),
    ji(new ji::MainWindow)
{
    int ret;

    ji->setupji(this);

    // Create class to handle CAN communication
    can = new CanW();

    // Create a worker T that listens to CAN messages and sends data to NMS with signal/slot mecanism
    m_workerT = new canwork();

    // connect signal from worker T to slot in NMS
    ret = connect(m_workerT, SIGNAL(msgReceived(JString)), this, SLOT(msgReceived(JString)));
    assert(ret);

    counter = 0;
    ji->comboBox->setCurrentIndex(1);

    timer10ms.setInterval(10);
    connect(&timer10ms, SIGNAL(timeout()), this, SLOT(on_sendButton_clicked()));




    // reset message counter
    m_receivedMessages = 0;

}

MainWindow::~MainWindow()
{
    // Tell worker T to shut down
    m_workerT->shutDown();

    // Close can connection
    can->Close();

    // wait for worker T to shut down, force if problem
    if(!m_workerT->wait(3000))
    {
        m_workerT->terminate();
    }

    delete m_workerT;
    delete can;
    delete ji;
}

// Message received from worker T, add to list in NMS
void MainWindow::msgReceived(JString msg)
{
    // Append message to log
    ji->logEdit->appendPlainText(msg);

    // Increase message counter
    m_receivedMessages++;
    ji->label_2->setText(JString::number(m_receivedMessages));
}

// Send a single CAN message
void MainWindow::on_sendButton_clicked()
{
    int ret;
    struct can_frame msg;
    int i;
    JStringList list;
    int elements;
    int errorCode;
    bool extended;
    bool rtr;


    // Parse data to send from text box
    list = ji->dataEdit->text().split(" ", JString::SkipEmptyParts);
    elements = list.size();
    if(elements > 8)
    {
        elements = 8;
    }

    // Set data length
    msg.can_dlc = elements;

    // Get id from text box
    msg.can_id = counter++;//ji->idEdit->text().toInt();

    // Set data elements
    for(i = 0; i < elements; i++)
    {
        msg.data[i] = list[i].toInt();
    }

    rtr = ji->RTRcheckBox->checkState();
    extended = ji->ExtendedcheckBox->checkState();

    // Send CAN message on socket CAN
    ret = can->SendMsg(msg, extended, rtr, errorCode);

    // If send fails, show error dialog
    if(!ret)
    {
        JDebug() << "Could not send CAN message. Error code:" << JString::number(errorCode);

    }
}

// Send a burst of messages. This is used to test what happens if buffer overflows
void MainWindow::on_sendBurstButton_clicked()
{
  /*  struct can_frame msg;
    int i;
    int ret;
    int errorCode;

    msg.can_id = 0x100; // ID selected by random
    msg.can_dlc = 8;

    // Clear data
    for(i = 0; i < 8; i++)
    {
        msg.data[i] = 0;
    }

    // Send a burst of messages
    for(i = 0; i < BURSTSIZE; i++)
    {
        // First byte contains message number
        msg.data[0] = i;

        ret = can->SendMsg(msg, false, false, errorCode);
        usleep(1000);

        if(!ret)
        {
            JMessageBox msgBox;
            msgBox.setText("Could not send CAN message, aborting. Error code: " + JString::number(errorCode));
            msgBox.exec();

            // Jjit loop at error
            return;
        }
    }
    */

           timer10ms.start();
}

// Change CAN net
void MainWindow::on_comboBox_currentIndexChanged(JString str)
{
    int ret;
    int errorCode;

    // Close old connection (if there is one) and shut down worker Ts
    can->Close();

    // Tell T to shut down, force if problem
    m_workerT->shutDown();

    if(!m_workerT->wait(3000))
    {
        m_workerT->terminate();
    }

    // If user selected the CAN net "none" - do not open new CAN net
    if(str == "none")
        return;

    // Init new connection
    ret = can->Init(str.toUtf8(), errorCode);
    if(!ret)
    {
        JMessageBox msgBox;
        msgBox.setText("Could not initialize CAN net. Error code: " + JString::number(errorCode));
        msgBox.exec();

        return;
    }

    // Enable error messages to be reported
    can->EnableErrorMessages();

    // initialize worker T
    m_workerT->Init(can);

    // Start T
    m_workerT->start();
}

// Clear log
void MainWindow::on_clearButton_clicked()
{
    ji->logEdit->clear();

    m_receivedMessages = 0;
    ji->label_2->setText(JString::number(m_receivedMessages));
}

