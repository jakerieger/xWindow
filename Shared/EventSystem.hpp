// Author: Jake Rieger
// Created: 12/3/24.
//

#pragma once

#include "Types.hpp"

#include <typeindex>
#include <vector>
#include <functional>
#include <map>

namespace x {
    using std::function;
    using std::map;
    using std::type_index;
    using std::vector;

    class EventDispatcher;

    template<typename EventType>
    using EventCallback = function<void(const EventType&)>;

    class IEvent {
    public:
        virtual ~IEvent() = default;
    };

    class IEventListener {
    public:
        virtual ~IEventListener()                 = default;
        virtual void onEvent(const IEvent& event) = 0;
    };

    template<typename EventType>
    class EventListener final : public IEventListener {
    public:
        explicit EventListener(EventCallback<EventType> cb) : mCallback(cb) {}

        void onEvent(const IEvent& event) override {
            mCallback(CAST<const EventType&>(event));
        }

    private:
        EventCallback<EventType> mCallback;
    };

    class EventDispatcher {
    public:
        template<typename EventType>
        void registerListener(EventCallback<EventType> callback) {
            const type_index index(typeid(EventType));
            mListeners[index].emplace_back(std::make_shared<EventListener<EventType>>(callback));
        }

        void dispatch(const IEvent& event) {
            const type_index index(typeid(event));
            if (const auto it = mListeners.find(index); it != mListeners.end()) {
                for (const auto& listener : it->second) {
                    listener->onEvent(event);
                }
            }
        }

    private:
        map<type_index, vector<Shared<IEventListener>>> mListeners;
    };
}  // namespace Xen