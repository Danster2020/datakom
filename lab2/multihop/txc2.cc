#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

class Txc2 : public cSimpleModule
{
private:
	cMessage *event = nullptr;
	cMessage *multihopMsg = nullptr;
	long msgCounter;
	long numSent;
	long numReceived;
	double timeReceived;
	double lossProbability;
	cOutVector txVector;
	cOutVector rxVector;

public:
	virtual ~Txc2();

protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *msg);
	virtual void forwardMessage(cMessage *msg);
	virtual void finish();
};

Define_Module(Txc2);

Txc2::~Txc2()
{
	cancelAndDelete(event);
	delete multihopMsg;
}

void Txc2::initialize()
{
	msgCounter = 0;
	numSent = 0;
	numReceived = 0;
	WATCH(numSent);
	WATCH(numReceived);
	event = new cMessage("event");
	txVector.setName("txVector");
	rxVector.setName("rxVector");
	lossProbability = par("lossProbability");

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

void Txc2::handleMessage(cMessage *msg)
{
	EV << "I am node" << getIndex() << "\n";
	EV << "I have msg: " << msg << "\n";

	// if event
	if (msg == event)
	{
		EV << "Timeout is over, sending msg.";
		// Send buffered message
		int n = gateSize("gate");
		int k = n - 1;

		// Create new message if Node 0
		if (getIndex() == 0)
		{
			send(multihopMsg, "gate$o", k);
			txVector.record(numSent);
			numSent++;
			multihopMsg = nullptr;

			msgCounter++;
			char msgname[20];
			sprintf(msgname, "DATA-%d", msgCounter);
			// cMessage *newMsg = new cMessage(msgname);
			multihopMsg = new cMessage(msgname);
			EV << "scheduling new msg: " << msgname << "\n";
			scheduleAt(simTime() + par("transmissionTime"), event);
		}
		else
		{
			EV << "event on non source node" << "\n";
			k = intuniform(1, n-1);
			send(multihopMsg, "gate$o", k);
			txVector.record(numSent);
			numSent++;
			multihopMsg = nullptr;
		}
	}
	else
	{
		// Shall I receive it
		if (uniform(0, 1) < lossProbability)
		{
			EV << "Message " << msg << " is lost";
			delete msg;
		}
		else
		{
			//  If I shall receive, am I the last node
			if (getIndex() == 5)
			{
				// message arrived
				EV << "Message " << msg << " arrived.\n";
				rxVector.record(numReceived);
				numReceived++;
				delete msg;
			}
			else
			{
				forwardMessage(msg);
			}
		}
	}
}

void Txc2::forwardMessage(cMessage *msg)
{
	multihopMsg = msg;
	EV << "forwarding msg: " << msg << "\n";

	// processing delay
	scheduleAt(simTime() + par("processingTime"), event);
}

void Txc2::finish()
{
	EV << "Node" << getIndex() << " Sent: " << numSent << endl;
	EV << "Node" << getIndex() << " Received: " << numReceived << endl;
	EV << "\n";

	recordScalar("#Sent", numSent);
	recordScalar("#received", numReceived);
}