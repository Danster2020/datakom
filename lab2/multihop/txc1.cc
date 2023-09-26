#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

class Txc1 : public cSimpleModule
{
private:
	long msgCounter;
	long numSent;
	long numReceived;

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void forwardMessage(cMessage *msg);
	virtual void finish();
};

Define_Module(Txc1);

void Txc1::initialize()
{
	msgCounter = 0;
	numSent = 0;
	numReceived = 0;
	WATCH(numSent);
	WATCH(numReceived);

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
	numReceived++;

	if (getIndex() == 0)
	{
		msgCounter++;
		// EV << "getIndex(): " << getIndex();
		EV << "Scheduling send to a simtime + time\n";
		char msgname[20];
		sprintf(msgname, "DATA-%d", msgCounter);
		cMessage *msg = new cMessage(msgname);
		scheduleAt(simTime() + 1.0, msg);
	}

	if (getIndex() == 5)
	{
		// message arrived
		EV << "Message " << msg << " arrived.\n";
		delete msg;
	}
	else
	{
		// message has to be forwarded
		forwardMessage(msg);
		numSent++;
	}
}

void Txc1::forwardMessage(cMessage *msg)
{
	// for this example, we always receive in the gate with
	// a lower number out of the two we have. So we forward
	// using our higher-numbered gate.
	int n = gateSize("gate");
	int k = n - 1;
	EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
	send(msg, "gate$o", k);
}

void Txc1::finish()
{
	EV << "Node" << getIndex() << " Sent: " << numSent << endl;
	EV << "Node" << getIndex() << " Received: " << numReceived << endl;
	EV << "\n";

	recordScalar("#Sent", numSent);
	recordScalar("#received", numReceived);
}