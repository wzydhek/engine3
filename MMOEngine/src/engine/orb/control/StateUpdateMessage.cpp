#include "engine/orb/messages/DOBServiceClient.h"
#include "StateUpdateMessage.h"

StateUpdateMessage::StateUpdateMessage(int state) : DOBMessage(STATEUPDATEMESSAGE, 20), state(state) {
	insertInt(state);
}

StateUpdateMessage::StateUpdateMessage(Packet* message) : DOBMessage(message) {
	state = message->parseInt();
}

void StateUpdateMessage::execute() {
	ObjectBrokerDirector* director = ObjectBrokerDirector::instance();

	RemoteObjectBroker* remoteBroker = getClient()->getRemoteObjectBroker();

	director->handleStateUpdate(remoteBroker, state);
}