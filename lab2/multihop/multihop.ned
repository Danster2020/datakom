simple Txc2
{
	parameters:
                volatile double transmissionTime @unit(s);
		volatile double delayTime @unit(s);
                volatile double processingTime @unit(s);
                double lossProbability;
	gates:
		inout gate[];
}

network Multihop
{
        submodules:
                node[6]: Txc1;
	connections:
                node[0].gate++ <--> { delay = 10ms; } <--> node[1].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[2].gate++;
                node[2].gate++ <--> { delay = 10ms; } <--> node[3].gate++;
                node[3].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[4].gate++ <--> { delay = 10ms; } <--> node[5].gate++;
}

network Reliability
{
        submodules:
                node[6]: Txc2;
        connections:
                node[0].gate++ <--> { delay = 10ms; } <--> node[1].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[2].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[3].gate++;
                node[2].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[3].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[4].gate++ <--> { delay = 10ms; } <--> node[5].gate++;
}

network Network1
{
        submodules:
                node[6]: Txc2;
        connections:
                node[0].gate++ <--> { delay = 10ms; } <--> node[1].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[2].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[3].gate++;
                node[2].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[2].gate++ <--> { delay = 10ms; } <--> node[3].gate++;
                node[3].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[4].gate++ <--> { delay = 10ms; } <--> node[5].gate++;
}

network Network2
{
        submodules:
                node[7]: Txc2;
        connections:
                node[0].gate++ <--> { delay = 10ms; } <--> node[1].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[2].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[3].gate++;

                node[6].gate++ <--> { delay = 10ms; } <--> node[1].gate++;
                node[6].gate++ <--> { delay = 10ms; } <--> node[2].gate++;

                node[2].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[2].gate++ <--> { delay = 10ms; } <--> node[3].gate++;
                node[3].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[4].gate++ <--> { delay = 10ms; } <--> node[5].gate++;
}

network Network3
{
        submodules:
                node[8]: Txc2;
        connections:
                node[0].gate++ <--> { delay = 10ms; } <--> node[1].gate++;
                node[0].gate++ <--> { delay = 10ms; } <--> node[2].gate++;
                
                node[1].gate++ <--> { delay = 10ms; } <--> node[4].gate++;
                node[1].gate++ <--> { delay = 10ms; } <--> node[3].gate++;

                node[2].gate++ <--> { delay = 10ms; } <--> node[4].gate++;

                node[3].gate++ <--> { delay = 10ms; } <--> node[6].gate++;
                node[3].gate++ <--> { delay = 10ms; } <--> node[7].gate++;

                node[4].gate++ <--> { delay = 10ms; } <--> node[7].gate++;

                node[6].gate++ <--> { delay = 10ms; } <--> node[5].gate++;

                node[7].gate++ <--> { delay = 10ms; } <--> node[5].gate++;





 
}