// Состояние (State)

#include <iostream>

class Application {
    class CommandHandler *cmd_handler;

public:
    Application();

    void set_current(CommandHandler *h) {
        cmd_handler = h;
    }

    void login();

    void do_it();

    void logout();
};

class CommandHandler {
public:
    virtual void login(Application *) = 0;
    virtual void do_it(Application *) = 0;
    virtual void logout(Application *) = 0;
};

void Application::login() {
    cmd_handler->login(this);
}

void Application::do_it() {
    cmd_handler->do_it(this);
}

void Application::logout() {
    cmd_handler->logout(this);
}


class LogginedHandler : public CommandHandler {
public:
    void login(Application *) override {
        std::cout << "already login" << std::endl;
    }
    void do_it(Application *) override {
        std::cout << "success" << std::endl;
    }
    void logout(Application *m) override;
};

class Anonymous : public CommandHandler {
public:
    void login(Application *m) override {
        std::cout << "work as loggined" << std::endl;
        m->set_current(new LogginedHandler());
    }
    void do_it(Application *) override {
        std::cout << "error" << std::endl;
    }
    void logout(Application *) override {
        std::cout << "already logout" << std::endl;
    }
};

void LogginedHandler::logout(Application *m) {
    std::cout << "work as anonymous" << std::endl;
    m->set_current(new Anonymous());
}

Application::Application() {
    cmd_handler = new Anonymous();
    std::cout << std::endl;
}

int main(int, char *[]) {
    Application app;

    app.do_it();
    app.logout();
    app.login();
    app.do_it();
    app.login();
    app.logout();
    app.do_it();

    return 0;
}
