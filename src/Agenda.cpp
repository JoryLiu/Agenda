#include "AgendaUI.hpp"
#include <csignal>
#include <istream>
using namespace std;

AgendaUI aui;

void signalHandler(int signum) {
    cout << "Interupt signal ctrl C received" << endl;
    aui.quitAgenda();
    exit(signum);
}

int main() {
    signal(SIGINT, signalHandler);
    aui.OperationLoop();
    return 0;
}
