#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

class Txc1 : public cSimpleModule
{
private:
	cMessage *event = nullptr;
	cMessage *tictocMsg = nullptr;
	long numSent;
	long numReceived;

public:
	virtual ~Txc1();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void finish();
};

Define_Module(Txc1);

Txc1::~Txc1()
{
	cancelAndDelete(event);
	delete tictocMsg;
}

void Txc1::initialize()
{
	numSent = 0;
	numReceived = 0;
	event = new cMessage("event");
	tictocMsg = nullptr;
	WATCH(numSent);
	WATCH(numReceived);
	// Determine if I am Tic or Toc
	if (strcmp("tic", getName()) == 0)
	{
		EV << "Scheduling first send to a random time\n";
		tictocMsg = new cMessage("DATA");
		scheduleAt(uniform(0, 1), event);
		// cMessage *msg = new cMessage("tictocMsg");
		// send (msg, "out");
		// numSent++;
	}
}

// void Txc1::handleMessage(cMessage *msg)
// {
// 	numReceived++;
// 	send(msg, "out");
// 	numSent++;
// }

void Txc1::finish()
{
	EV << "Sent: " << numSent << endl;
	EV << "Received: " << numReceived << endl;

	recordScalar("#Sent", numSent);
	recordScalar("#received", numReceived);
}

void Txc1::handleMessage(cMessage *msg)
{
	if (msg == event)
	{
		EV << "Timeout is over, sending message";
		send(tictocMsg, "out");
		tictocMsg = nullptr;
		numSent++;
	}
	else
	{
		if (strcmp("tic", getName()) == 0)
		{
			EV << "Acknowledgement arrived";
			numReceived++;
			delete msg;
			// cancelEvent(event);
			tictocMsg = new cMessage("DATA");
			scheduleAt(simTime() + 1.0, event);
		}
		else
		{
			EV << "Message Arrived. Sending ACK";
			numReceived++;
			delete msg;
			tictocMsg = new cMessage("ACK");
			scheduleAt(simTime() + exponential(0.1), event);
		}
	}
}