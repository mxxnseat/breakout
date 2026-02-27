module;

#include <functional>
#include <typeindex>
#include <unordered_map>

export module EventBus;

export class EventBus {
    template<typename Event>
    using EventHandler = std::function<void(const Event&)>;

    public:
        template<typename Event>
        void subscribe(EventHandler<Event> handler) {
            auto& handlers = handlers_[std::type_index(typeid(Event))];
            handlers.push_back([h = std::move(handler)](const void* event) {
                h(*static_cast<const Event*>(event));
            });
        }
        template<typename Event>
        void publish(const Event& event) const {
            auto it = handlers_.find(std::type_index(typeid(Event)));
            if(it == handlers_.end()) return;
            for (const auto& handler : it->second) {
                handler(static_cast<const void*>(&event));
            }
        }

    private:
        using ErasedHandler = std::function<void(const void*)>;
        std::unordered_map<std::type_index, std::vector<ErasedHandler>> handlers_;
};
