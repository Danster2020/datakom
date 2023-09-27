#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

class Txc1 : public cSimpleModule
{
private:
	cMessage *event = nullptr;
	cMessage *multihopMsg = nullptr;
	long msgCounter;
	long numSent;
	long numReceived;
	double timeReceived;
	cOutVector txVector;
	cOutVector rxVector;

public:
	virtual ~Txc1();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void forwardMessage(cMessage *msg);
	virtual void finish();
};

Define_Module(Txc1);

Txc1::~Txc1()
{
	cancelAndDelete(event);
	delete multihopMsg;
}

void Txc1::initialize()
{
	msgCounter = 0;
	numSent = 0;
	numReceived = 0;
	WATCH(numSent);
	WATCH(numReceived);
	event = new cMessage("event");
	txVector.setName("txVector");
	rxVector.setName("rxVector");

	// start messaging if first node
	if (getIndex() == 0)
	{
		msgCounter++;
		EV << "Scheduling first send to a random time\n";
		char msgname[20];
		sprintf(msgname, "DATA-%d", msgCounter);
		multihopMsg = new cMessage(msgname);
		scheduleAt(par("delayTime"), event);
	}
}

void Txc1::handleMessage(cMessage *msg)
{
	EV << "I am node" << getIndex() << "\n";

	numReceived++;

	// if source node (0)
	if (getIndex() == 0 && msg == event)
	{
		msgCounter++;
		// EV << "getIndex(): " << getIndex();
		EV << "Scheduling send to a simtime + time\n";
		char msgname[20];
		sprintf(msgname, "DATA-%d", msgCounter);
		cMessage *newMsg = new cMessage(msgname);
		scheduleAt(simTime() + exponential(5.0), newMsg);
	}
	
	if (getIndex() == 5)
	{
		// message arrived
		EV << "Message " << msg << " arrived.\n";
		// numReceived++;
		rxVector.record(numReceived);
		delete msg;
	}
	else
	{
		// message has to be forwarded
		forwardMessage(msg);
		numSent++;
		txVector.record(numSent);
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
	// send(msg, "gate$o", k);
	// scheduleAt(simTime() + exponential(0.01), msg);
	sendDelayed(msg, exponential(0.01), "gate$o", k);
}

void Txc1::finish()
{
	EV << "Node" << getIndex() << " Sent: " << numSent << endl;
	EV << "Node" << getIndex() << " Received: " << numReceived << endl;
	EV << "\n";

	// recordScalar("#Sent", numSent);
	// recordScalar("#received", numReceived);
}