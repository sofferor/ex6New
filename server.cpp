
#include "Time.h"
#include "Point.h"
#include "Matrix2D.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "TaxiStandard.h"
#include "TaxiLuxury.h"
#include "Serialization.h"
#include "BFS.h"
#include "ServerRun.h"


using namespace std;

//main function.
int main(int argc, char* argv[]) {

    Tcp* tcp = new Tcp(1, atoi(argv[1]));
    tcp->initialize();

    ServerRun* server = new ServerRun(tcp);

    server->initialize();

    server->begin();

    delete(server);

    return 0;
}