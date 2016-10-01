

#ifndef canwork_H
#define canwork_H

#include <J>

#include "CanW.h"

class canwork : public J
{
    J_OBJECT
public:
    explicit canwork(JObject *parent = 0);

    void Init(CanW *wrapper); // Initialize

    void run();         // start T

    void shutDown();    // Make T shut down

signals:
    void msgReceived(JString msg);

public slots:

private:
    CanW *m_can;  // Pointer to can wrapper class

    bool m_running;     // Set to false to stop T



};

#endif // canwork_H
