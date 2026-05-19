#include <iostream>
#include <string>

class App {
private:
    std::string name;
    static App* instance;

    App() {
    }

public:
    static App* getInstance() {
        if(!instance) {
            instance = new App();
        }
        return instance;
    }    

    void set_name(const std::string& name) {
        this->name = name;
    }
    
    std::string get_name() const{
        return name;
    }
};

App* App::instance = nullptr;


int main() {
    App* app = App::getInstance();
    app->set_name("test");
    std::cout << app->get_name();

    return 0;
}