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
	long msgCounter;
	
	double lossProbability;
	simsignal_t transmissionSignal;
	simsignal_t receptionSignal;

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
	msgCounter = 0;

	event = new cMessage("event");
	tictocMsg = nullptr;
	lossProbability = par("lossProbability");
	WATCH(numSent);
	WATCH(numReceived);
	transmissionSignal = registerSignal("transmissionSignal");
	receptionSignal = registerSignal("receptionSignal");

	// if tic
	if (strcmp("tic", getName()) == 0)
	{
		EV << "Scheduling first send to a random time\n";
		tictocMsg = new cMessage("DATA");
		//scheduleAt(par("delayTime"), event);
		scheduleAt(uniform(0,1), event);
		// cMessage *msg = new cMessage("tictocMsg");
		// send (msg, "out");
		// numSent++;
	}
}

void Txc1::handleMessage(cMessage *msg)
{
	// if transmit
	if (msg == event)
	{
		EV << "Timeout is over, sending message";
		send(tictocMsg, "out");
		tictocMsg = nullptr;
		numSent++;
		emit(transmissionSignal, msgCounter);
		
		// if tic sent failed?
		if (strcmp("tic", getName()) == 0)
		{
			tictocMsg = new cMessage("DATA");
			scheduleAt(simTime() + 1.0, event); // fixed transmission intervall
		}
	}
	else
	{
		// if reception from toc
		if (strcmp("tic", getName()) == 0)
		{
			EV << "Acknowledgement arrived";
			numReceived++;
			msgCounter++;
			emit(receptionSignal, msgCounter);
			delete msg;
			delete tictocMsg;
			cancelEvent(event);
			tictocMsg = new cMessage("DATA");
			scheduleAt(simTime() + par("delayTime"), event);
		}
		else
		{
			// if message is lost by probability
			if (uniform(0, 1) < lossProbability)
			{
				EV << "Message is lost";
				delete msg;
			}
			else // toc receive msg from tic
			{
				EV << "Message Arrived. Sending ACK";
				numReceived++;
				msgCounter++; //add this line to increase from 0
				emit(receptionSignal, numReceived);
				delete msg;
				tictocMsg = new cMessage("ACK");
				//scheduleAt(simTime() + exponential(0.1), event); // TODO change to? scheduleAt(simTime() + par("delayTime"), event);
				scheduleAt(simTime() + par("delayTime"), event);
			}
		}
	}
}

void Txc1::finish()
{
	EV << "Sent: " << numSent << endl;
	EV << "Received: " << numReceived << endl;

	recordScalar("#Sent", numSent);
	recordScalar("#received", numReceived);
}