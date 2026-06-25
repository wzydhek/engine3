#include "ControlMessage.h"

ControlMessage::ControlMessage(int command, int flags) : DOBMessage(CONTROLMESSAGE, 20), command(command) {
	insertInt(command);
	insertInt(flags);
}

ControlMessage::ControlMessage(Packet* message) : DOBMessage(message) {
	command = message->parseInt();
	flags = message->parseInt();
}

void ControlMessage::execute() {
	ObjectBrokerAgent* agent = ObjectBrokerAgent::instance();

	agent->doCommand((ObjectBrokerDirector::Command)command, flags);
}