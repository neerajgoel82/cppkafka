#ifndef CPPKAFKA_MOCKING_EVENT_PROCESSOR_
#define CPPKAFKA_MOCKING_EVENT_PROCESSOR_

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>
#include <cppkafka/mocking/events/event_base.h>

namespace cppkafka {
namespace mocking {

class EventProcessor {
public:
    using EventPtr = std::unique_ptr<EventBase>;

    EventProcessor();
    EventProcessor(const EventProcessor&) = delete;
    EventProcessor& operator=(const EventProcessor&) = delete;
    ~EventProcessor();

    void add_event(EventPtr event);
private:
    void process_events();

    std::thread processing_thread_;
    std::mutex events_mutex_;
    std::condition_variable events_condition_;
    std::queue<EventPtr> events_;
    bool running_{true};
};

} // mocking
} // cppkafka

#endif // CPPKAFKA_MOCKING_EVENT_PROCESSOR_
