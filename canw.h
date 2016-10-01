

#ifndef CanW_H
#define CanW_H

#include <JString>

class CanW
{
public:
    CanW();

    bool Init(const char *interfaceName, int &errorCode);

    void Close();

    bool SendMsg(struct can_frame msg, bool extended, bool rtr, int &errorCode);

    bool GetMsg(struct can_frame &frame, bool &extended, bool &rtr, bool &error, int &errorCode, struct timeval timeout);

    bool SetRecvBufferSize(int size);

    void EnableErrorMessages();
    struct TYPE0{
        char    ctype;
        char    clen;
    } ;
    struct TYPE1{
        char    ctype;
        char    clen;
        char    Groupnamelength;
		char    *Group_name
		char    *minValue; 
		char    *maxValue; 
    } ;
    struct TYPE2{
        char    ctype;
        char    clen;
        char    Groupnamelength ;
		char    *Group_name;
		char	nchoice ;
		char    *Value; 
        uchar   namelen;
        char    *name;
    } ;
    struct TYPE4{
        char    ctype;
        char    clen;
        char    Groupnamelength;
		char    *Group_name;
		char    *minValue; 
		char    *maxValue; 
		uint	step ;
    } ;
    struct TYPE5{
        char    ctype;
        char    clen;
        char    nchoice;
		char 	alarm;
    } ;
    struct TYPE6{
        char    ctype;
        char    clen;
        char    displayformat;
        uchar   len;
    } ;

    struct TYPE8{
        char    ctype;
        char    clen;
        char    Groupnamelength;
		char    *Group_name;
		char    *minValue; 
		char    *maxValue; 
    } ;

    struct TYPE9{
        char    ctype;
        char    clen;
        char    nchoice;
		char 	BitPosition;
        char    severity;
        char    *name;
    } ;
    struct TYPE11{
		uchar	ACK;
		uint	numPar;
		char    *CardName;
		char	CardtypeID;	
    } ;
    struct TYPE13{
		uchar	ACK;
		uint	first;
		uchar	count; 
        uint    *PID;
    } ;
    struct TYPE15{
		uchar	ACK;
        uint    PID;
        uchar   len;
        uchar   type;
        uchar   size;
        uchar   access ;
		uchar	precision;
		uchar	widget;
        uchar   namelen;
        char    *name;
        uchar   ctype;
        uchar   clen;
        char    *cdata;
    } ;
    struct TYPE16{
        uint    PID;
     } ;
    struct TYPE17{
		uchar	ACK;
        uint    PID;
        uchar   len;
        uchar   type;
        uchar   size;
        uchar   access ;
		uchar	precision;
		uchar	widget;
        uchar   namelen;
        char    *name;
        uchar   ctype;
        uchar   clen;
        char    *cdata;
    } ;
   struct TYPE18{
        uint    PID;
        uchar   dlen;
        char    *value;
     } ;
    struct TYPE19{
		uchar	ACK;
        uint    *PID;
        uchar   dlen;
        char    *value;
    } ;

    struct TYPE1b{
		uchar	ACK;
        uint    *PID;
        uchar   dlen;
        char    *value;
    } ;
    struct TYPE22{
		uchar	ACK;
        uint    *PID;
        uchar   dlen;
        char    *value;
    } ;
    struct TYPE23{
		uchar	Spare;
    } ;
    struct TYPE24{
		uchar	menu;
    } ;
    struct TYPE25{
		uchar	ACK;
		char	menu;
        uchar   namelen;
        char    *name;
    } ;
    struct TYPE26{
		uchar	menu;
    } ;
    struct TYPE27{
		uchar	ACK;
		char	menu;
		uchar	count; 
        uint    *base ;
    } ;
    struct TYPE30{
		uchar	Spare;
    } ;
    struct TYPE31{
		uchar	ACK;
        uchar   len;
        char    *value;
    } ;

    struct TYPE32{
        uint    *PID;
    } ;
    struct TYPE33{
		uchar	ACK;
        uint    *PID;
        uchar   len;
        char    *SNMPOID;
    } ;
    struct TYPE34{
        uint    *PID;
    } ;
    struct TYPE35{
		uchar	ACK;
        uint    *PID;
        uchar   Namelength ;
        char    *name ;
    } ;  
	struct TYPE36{
		uchar	Spare;
    } ;
    struct TYPE37{
		uchar	ACK;
		uchar	Spare; 
    } ;

private:
    bool m_initialized; // indicates if socket is initialized

    int m_socket;       // Socket


};

#endif // CanW_H
