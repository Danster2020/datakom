#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

class Txc1 : public cSimpleModule
{
private:
	long msgCounter;

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void forwardMessage(cMessage *msg);
};

Define_Module(Txc1);

void Txc1::initialize()
{
	msgCounter = 0;

	// start messaging if first node
	if (getIndex() == 0)
	{
		msgCounter++;
		EV << "Scheduling first send to a random time\n";
		char msgname[20];
		sprintf(msgname, "DATA-%d", msgCounter);
		cMessage *msg = new cMessage(msgname);
		scheduleAt(par("delayTime"), msg);
	}
}

void Txc1::handleMessage(cMessage *msg)
{
	if (getIndex() == 5)
	{
		// message arrived
		EV << "Message " << msg << " arrived.\n";
	}
	else
	{
		// message has to be forwarded
		forwardMessage(msg);
	}
}

void Txc1::forwardMessage(cMessage *msg)
{
	// for this example, we always receive in the gate with
	// a lower number out of the two we have. So we forward
	// using our higher-numbered gate.
	int n = gateSize("gate");
	int k = n - 1;
	EV << "Forwarding message  " << msg << "on gate[" << k << "\n";
	send(msg, "gate$o", k);
}
