#ifndef MessageRelay_h__
#define MessageRelay_h__

#include <typeinfo>
#include <functional>
#include <map>
#include <unordered_map>
#include <list>

#define EVENT_SUBSCRIBE_MEMBER(relay, handler) \
	relay = decltype(relay)(std::bind(handler, this, std::placeholders::_1)); \
	EventBroker->Subscribe(relay);

struct Event
{
protected:
	Event() { }
};

class EventBroker;

class BaseEventRelay
{
friend class EventBroker;

protected:
	BaseEventRelay(std::string contextTypeName, std::string eventTypeName)
		: m_ContextTypeName(contextTypeName)
		, m_EventTypeName(eventTypeName)
		, m_Broker(nullptr) { }
	~BaseEventRelay();

public:
	virtual bool Receive(const std::shared_ptr<Event> event) = 0;

protected:
	std::string m_ContextTypeName;
	std::string m_EventTypeName;
	EventBroker* m_Broker;
};

template <typename ContextType, typename EventType>
class EventRelay : public BaseEventRelay
{
public:
	typedef std::function<bool(const EventType&)> CallbackType;

	EventRelay()
		: m_Callback(nullptr)
		, BaseEventRelay(typeid(ContextType).name(), typeid(EventType).name()) { }
	EventRelay(CallbackType callback) 
		: m_Callback(callback)
		, BaseEventRelay(typeid(ContextType).name(), typeid(EventType).name()) { }

protected:
	bool Receive(const std::shared_ptr<Event> event) override;

private:
	CallbackType m_Callback;
};

template <typename ContextType, typename EventType>
bool EventRelay<ContextType, EventType>::Receive(const std::shared_ptr<Event> event)
{
	if (m_Callback != nullptr)
	{
		return m_Callback(*static_cast<const EventType*>(event.get()));
	}
	else
	{
		return false;
	}
}

class EventBroker
{
template <typename ContextType, typename EventType> friend class EventRelay;

public:
	EventBroker()
	{
		m_EventQueueRead = std::make_shared<EventQueue_t>();
		m_EventQueueWrite = std::make_shared<EventQueue_t>();
	}

	void Subscribe(BaseEventRelay &relay);
	template <typename EventType>
	void Publish(const EventType &event);
	// Process all events no matter the context.
	/*void Process()
	{

	}*/
	/*
		Process all events in a given context.
		Returns: Number of events processed
	*/
	template <typename ContextType>
	int Process();
	int Process(std::string contextTypeName);
	void Clear();
	void Unsubscribe(BaseEventRelay &relay);
	template <typename ContextType>
	void UnsubscribeAll();

private:
	typedef std::string ContextTypeName_t; // typeid(ContextType).name()
	typedef std::string EventTypeName_t; // typeid(EventType).name()

	typedef std::unordered_multimap<EventTypeName_t, BaseEventRelay*> EventRelays_t;
	typedef std::unordered_map<ContextTypeName_t, EventRelays_t> ContextRelays_t;
	ContextRelays_t m_ContextRelays;

	typedef std::list<std::pair<EventTypeName_t, std::shared_ptr<Event>>> EventQueue_t;
	std::shared_ptr<EventQueue_t> m_EventQueueRead;
	std::shared_ptr<EventQueue_t> m_EventQueueWrite;
};

template <typename EventType>
void EventBroker::Publish(const EventType &event)
{
	/*auto itpair = m_Subscribers.equal_range(typeid(EventType).name());
	for (auto it = itpair.first; it != itpair.second; ++it)
	{
		it->second->Receive(event);
	}*/

	m_EventQueueWrite->push_back(std::make_pair(typeid(EventType).name(), std::shared_ptr<EventType>(new EventType(event))));
}

template <typename ContextType>
int EventBroker::Process()
{
	const std::string contextTypeName = typeid(ContextType).name();
	return Process(contextTypeName);
}

template <typename ContextType>
void EventBroker::UnsubscribeAll()
{
	const std::string contextTypeName = typeid(ContextType).name();
	m_ContextRelays.erase(contextTypeName);
}

#endif // MessageRelay_h__
