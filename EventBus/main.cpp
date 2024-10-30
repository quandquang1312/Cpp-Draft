#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>

class EventBus {
    using EventCallback = std::function<void(const std::string&)>;
public:
    EventBus() {};

    void Publish(const std::string& bus, const std::string& data) {
        for (auto &callback : events[bus]) {
            callback(data);
        }
    }

    void Subscribed(const std::string& bus, EventCallback callback) {
        events[bus].push_back(callback);
    }

private:
    std::unordered_map<std::string, std::vector<EventCallback>> events;
};

class P {
public:
    P(EventBus* eventBus) {
        m_eventBus = eventBus;
    }

    void collectedI(const std::string& i) {
        m_eventBus->Publish("Inventory", i);
    }
private:
    EventBus* m_eventBus;
};

class I {
public:
    I(EventBus* eventBus) {
        m_eventBus = eventBus;
    }

    void Subscribe(const std::string& bus) {
        m_eventBus->Subscribed(bus, [&](const std::string& data){
            std::cout << "Inventory collected: " << data.c_str() << std::endl;
            AddI(data);
        });
    }
private:
    void AddI(const std::string& data) {
        std::cout << "Items Added: " << data.c_str() << std::endl;
        items.push_back(data);
    }

    EventBus* m_eventBus;
    std::vector<std::string> items;  
};

int main() {
    EventBus* eventBus = new EventBus();
    
    P p(eventBus);
    
    I inv(eventBus);
    inv.Subscribe("Inventory");

    p.collectedI("I1");
    p.collectedI("I2"); 

    return 0;
}