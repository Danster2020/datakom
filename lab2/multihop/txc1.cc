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
	EV << "I have msg: " << msg << "\n";

	// if event
	if (msg == event)
	{
		// Send buffered message
		int n = gateSize("gate");
		int k = n - 1;
		send(multihopMsg, "gate$o", k);
		
		txVector.record(numSent);
		numSent++;
		multihopMsg = nullptr;

		// Create new message if Node 0
		if (getIndex() == 0)
		{
			msgCounter++;
			char msgname[20];
			sprintf(msgname, "DATA-%d", msgCounter);
			cMessage *newMsg = new cMessage(msgname);

			EV << "scheduling new msg: " << newMsg << "\n";
			scheduleAt(simTime() + exponential(5.0), newMsg);
		}
	}
	else
	{

		// Shall I receive it (if uniform(0,1)>lossProbability)
		//  If I shall recive, am I the last node
		if (getIndex() == 5)
		{
			// message arrived
			EV << "Message " << msg << " arrived.\n";
			rxVector.record(numReceived);
			numReceived++;
			delete msg;
		}
		//  Else, forward msg
		else
		{
			forwardMessage(msg);
		}
	}
}

void Txc1::forwardMessage(cMessage *msg)
{
	multihopMsg = msg;
	EV << "forwarding msg: " << msg << "\n";

	// processing delay
	scheduleAt(simTime() + par("processingTime"), event);
}

void Txc1::finish()
{
	EV << "Node" << getIndex() << " Sent: " << numSent << endl;
	EV << "Node" << getIndex() << " Received: " << numReceived << endl;
	EV << "\n";

	// recordScalar("#Sent", numSent);
	// recordScalar("#received", numReceived);
}