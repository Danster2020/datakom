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
	// numReceived++;

	// if event
	if (msg == event)
	{
		// Send buffered message
		int n = gateSize("gate");
		int k = n - 1;
		send(multihopMsg, "gate$o", k);
		multihopMsg = nullptr;
		// Create new message if Node 0
		if (getIndex() == 0)
		{
			char msgname[20];
			sprintf(msgname, "DATA-%d", msgCounter);
			cMessage *newMsg = new cMessage(msgname);

			// message has to be forwarded
			forwardMessage(multihopMsg);
			numSent++;
			txVector.record(numSent);
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
			// numReceived++;
			rxVector.record(numReceived);
			delete msg;
		}
		//  Else, forward msg
		else
		{
			forwardMessage(msg);
			numSent++;
			txVector.record(numSent);
		}
	}
	// if source node (0)
	// else if (getIndex() == 0)
	// {
	// 	msgCounter++;
	// 	// EV << "getIndex(): " << getIndex();
	// 	EV << "Scheduling send to a simtime + time\n";
	// 	char msgname[20];
	// 	sprintf(msgname, "DATA-%d", msgCounter);
	// 	cMessage *newMsg = new cMessage(msgname);
	// 	scheduleAt(simTime() + exponential(5.0), event);
	// }
	// else if (getIndex() == 5)
	// {
	// 	// message arrived
	// 	EV << "Message " << msg << " arrived.\n";
	// 	// numReceived++;
	// 	rxVector.record(numReceived);
	// 	delete msg;
	// }
	// else
	//{
	//  message has to be forwarded
	//	forwardMessage(msg);
	//	numSent++;
	//	txVector.record(numSent);
	//}
}

void Txc1::forwardMessage(cMessage *msg)
{
	// for this example, we always receive in the gate with
	// a lower number out of the two we have. So we forward
	// using our higher-numbered gate.
	// int n = gateSize("gate");
	// int k = n - 1;
	//EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
	// send(msg, "gate$o", k);
	multihopMsg = msg;
	scheduleAt(simTime() + exponential(0.01), event);
	// sendDelayed(msg, exponential(0.01), "gate$o", k);
	// sendDelayed(event, exponential(0.01), "gate$o", k);
}

void Txc1::finish()
{
	EV << "Node" << getIndex() << " Sent: " << numSent << endl;
	EV << "Node" << getIndex() << " Received: " << numReceived << endl;
	EV << "\n";

	// recordScalar("#Sent", numSent);
	// recordScalar("#received", numReceived);
}