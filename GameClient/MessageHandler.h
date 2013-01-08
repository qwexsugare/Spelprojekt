#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "MessageQueue.h"
#include "Message.h"
#include <SFML\System.hpp>
#include <map>

using namespace std;

class MessageHandler
{
private:
	int m_nextId;
	map<int,MessageQueue*> m_queues;
	sf::Mutex m_mutex;
public:
	MessageHandler();
	~MessageHandler();

	void addQueue(MessageQueue* _queue);
	void removeQueue(int id);
	void update();
};

#endif
