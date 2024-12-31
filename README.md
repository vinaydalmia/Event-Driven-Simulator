# Event-Driven-Simulator
• Implemented a complex wireless network simulator, using priority heaps for scheduling and moderating the event  • Established a node and packet model on a virtual clock, with packets being transmitted at a specific virtual time  • Synchronized on-air packets using a Binary Heap and analyzed the error percentage of the received packets



In this assignment, you have to implement a simple wireless network simulator, using a priority queue data structure. You can use the heap implementation from the last lab.


The simulator will be what is called an event-driven simulator. There is a notion of a virtual clock/time which starts at t=0. Different events trigger at specific virtual times. An event may create further future events. Your priority queue will consist of events, each with a different virtual trigger time.


The simulator proceeds as follows. At any point, the event to fire will be the one scheduled for the least trigger time: for this you will use the DeleteMin() operation of the priority queue. On firing, that event may schedule further future events: for this you will use various insert() operations of the priority queue. This keeps happening in a loop.


For the simulator you will build:

Consider N wireless nodes in the network (N must be a command line parameter)

Each node will generate packets destined to a random other node.

Packet generation can be periodic with a configurable period.

Each packet has a random number of bytes: between 50 and 1000.

Network speed is 1000 bytes/sec; this means that a packet of size P bytes takes P/1000 seconds to transmit (in network parlance: this is the transmission delay).

You can assume that the nodes are in close proximity to each other so that reaching from source to destination is instant (in network parlance: propagation delay is 0).

For a packet to be received successfully without error, it must be the only packet on air throughout its transmission time (of P/1000 sec).

Use a suitable data structure to determine how many packets are on air at a given time.

Your simulation must end at virtual time T sec (a command line parameter)

You will have the following different events: packet transmit (start), packet receive (end) [can be with or without error], simulation end

To begin the simulation, before entering the main event driven simulator loop, you can schedule packet transmit events at a random time between 0 and T/100, from each of the N nodes; also insert a simulation end event to trigger at T sec.

Packet transmit event: when it fires, (a) will schedule a packet receive event, (b) insert the packet into a set of currently on-air packets, and (c) will schedule the next packet transmit event. If there are on-air packets already, all of them will be marked to be received with error.

Packet receive event: when it fires, it will also modify the data structure of currently on-air packets suitably; perhaps also print whether the packet was received successfully (without error) or not (with error).

Simulation end event: will break out of the simulator loop


In the demo you will have to show how packet transmission/reception happen, with virtual time progressing independent of real time (on your watch/computer).
