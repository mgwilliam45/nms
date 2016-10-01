

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <JMainWindow>
#include <Jimer>
#include <canwork.h>

namespace ji {
    class MainWindow;
}

class MainWindow : public JMainWindow
{
    J_OBJECT

public:
    explicit MainWindow(JWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(JString);

    void on_clearButton_clicked();

    void on_sendBurstButton_clicked();

    void on_sendButton_clicked();

private:
    ji::MainWindow *ji;                 // Main window

    Jimer timer10ms;
    int counter;

    CanW *can;                    // Can wrapper class

    int m_receivedMessages;             // Number of received messages

    canwork *m_workerT;    // T that blocks and listens for CAN messages

public slots:
    void msgReceived(JString msg);
};

#endif // MAINWINDOW_H
