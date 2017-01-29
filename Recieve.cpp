
#include "Recieve.h"
#include "Point.h"

using namespace std;


Recieve::Recieve(bool legal) : legal(legal) {}

Recieve::~Recieve() {}

void Recieve::printInvalid() {
    cout << "-1" << endl;
}

Matrix2D *Recieve::recieveMatrix() {
    int sizeGridX, sizeGridY, numbersOfObstacles;

    // getting the grid.
    cin >> sizeGridX >> sizeGridY;
    if (!isdigit(sizeGridX) || !isdigit(sizeGridY)) {
        return NULL;
    }

    // getting obstacles.
    cin >> numbersOfObstacles;
    if (!isdigit(numbersOfObstacles) || numbersOfObstacles > (sizeGridX * sizeGridY)) {
        return NULL;
    }

    matrix2D = new Matrix2D(sizeGridX, sizeGridY);


    for (int j = 0; j < numbersOfObstacles; ++j) {
        int x, y;
        cin >> x >> comma >> y;
        if (!isdigit(x) || !isdigit(y) || comma != ',') {
            return NULL;
        }

        Point obstacle = Point(x, y);
        Node* node = matrix2D->getNodeInMatrix((Node*) &obstacle);
        if (node == NULL || node->isObstacle()) {
            return NULL;
        }

        node->setObstacle(true);
    }

    return matrix2D;
}

Trip *Recieve::recieveTrip() {
    int ride_id, x_start, y_start, x_end, y_end,
            num_passengers, startTime;
    double tariff;

    //getting details.
    cin >> ride_id >> comma;
    if (!isdigit(ride_id) || comma != ',') {
        return NULL;
    }
    cin >> x_start >> comma;
    if (!isdigit(x_start) || comma != ',') {
        return NULL;
    }
    cin >> y_start >> comma;
    if (!isdigit(y_start) || comma != ',') {
        return NULL;
    }
    cin >> x_end >> comma;
    if (!isdigit(x_end) || comma != ',') {
        return NULL;
    }
    cin >> y_end >> comma;
    if (!isdigit(y_end) || comma != ',') {
        return NULL;
    }
    cin >> num_passengers >> comma;
    if (!isdigit(num_passengers) || num_passengers < 0 || comma != ',') {
        return NULL;
    }
    cin >> tariff >> comma >> startTime;
    if (!isdigit(startTime) || startTime < 1 || comma != ',') {
        return NULL;
    }
    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        return NULL;
    }

    Point pStart(x_start, y_start);
    Point pEnd(x_end, y_end);
    Node *start = matrix2D->getNodeInMatrix(&pStart);
    Node *end = matrix2D->getNodeInMatrix(&pEnd);

    if (start == NULL || end == NULL) {
        return NULL;
    }

    return new Trip(start, end, ride_id, num_passengers,
                          tariff, startTime);
}

Taxi *Recieve::recieveTaxi() {
    int taxi_id, taxi_type;
    char manufacturer, color;

    // getting details.
    cin >> taxi_id >> comma;
    if (!isdigit(taxi_id) || comma != ',') {
        return NULL;
    }
    cin >> taxi_type >> comma;
    if (!isdigit(taxi_type) || comma != ',') {
        return NULL;
    }
    cin >> manufacturer >> comma >> color;
    if (comma != ',' || !isManufacturer(manufacturer) || !isColor(color)) {
        return NULL;
    }

    Taxi* taxi;
    // checking the type of the taxi and adding it to the
    // taxi center.
    switch (taxi_type) {
        case 1: {
            taxi = new TaxiStandard(taxi_id, color, manufacturer);\
            break;
        }

        case 2: {
            taxi = new TaxiLuxury(taxi_id, color, manufacturer);\
        }
        default: {
            return NULL;
        }
    }
    ////dont forget to add to taxi center from the server: taxiCenter->addTaxi(taxi);
    return taxi;
}

bool Recieve::isManufacturer(int num) {
    return num >= 0 && num <= 3;
}

bool Recieve::isColor(int num) {
    return num >= 0 && num <= 4;
}


