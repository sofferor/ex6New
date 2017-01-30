
#include "Recieve.h"
#include "Point.h"

using namespace std;


Recieve::Recieve() {}

Recieve::~Recieve() {}

void Recieve::printInvalid() {
    cout << "-1" << endl;
}

Matrix2D *Recieve::recieveMatrix() {
    int sizeGridX, sizeGridY, numbersOfObstacles;

    // getting the grid.
    cin >> sizeGridX >> sizeGridY;
    if (!isdigit(sizeGridX) || !isdigit(sizeGridY) ||
            !isInRangeOfGrid(sizeGridX) || !isInRangeOfGrid(sizeGridY)) {
        return NULL;
    }

    // getting obstacles.
    cin >> numbersOfObstacles;
    if (!isdigit(numbersOfObstacles)) {
        return NULL;
    }

    matrix2D = new Matrix2D(sizeGridX, sizeGridY);


    for (int j = 0; j < numbersOfObstacles; ++j) {
        int x, y;
        cin >> x >> comma >> y;
        if (!isdigit(x) || !isdigit(y) || comma != ',') {
            delete(matrix2D);
            return NULL;
        }

        Point obstacle = Point(x, y);
        Node* node = matrix2D->getNodeInMatrix((Node*) &obstacle);
        if (node == NULL) {
            delete(matrix2D);
            return NULL;
        }

        node->setObstacle(true);
    }

    return matrix2D;
}

/*Trip *Recieve::recieveTrip() {
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

    if (start == NULL || end == NULL || *start == end) {
        return NULL;
    }

    return new Trip(start, end, ride_id, num_passengers,
                          tariff, startTime);
}*/

Trip *Recieve::recieveTrip() {
    int ride_id, x_start, y_start, x_end, y_end,
            num_passengers, startTime;
    double tariff;

    string s;
    getline(cin, s);
    vector<string> parts = split(s, ",");

    if (parts.size() != 8) {
        return NULL;
    }


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

    if (start == NULL || end == NULL || *start == end) {
        return NULL;
    }

    return new Trip(start, end, ride_id, num_passengers,
                    tariff, startTime);
}

Taxi *Recieve::recieveTaxi() {
    int taxi_id, taxi_type;
    char manufacturerer, colorOfTaxi;

    // getting details.
    cin >> taxi_id >> comma;
    if (!isdigit(taxi_id) || comma != ',') {
        return NULL;
    }
    cin >> taxi_type >> comma;
    if (!isdigit(taxi_type) || comma != ',') {
        return NULL;
    }
    cin >> manufacturerer >> comma >> colorOfTaxi;
    if (comma != ',' || !isManufacturer(manufacturerer) || !isColor(colorOfTaxi)) {
        return NULL;
    }

    Taxi* taxi;
    // checking the type of the taxi and adding it to the
    // taxi center.
    switch (taxi_type) {
        case 1: {
            taxi = new TaxiStandard(taxi_id, colorOfTaxi, manufacturerer);
            break;
        }

        case 2: {
            taxi = new TaxiLuxury(taxi_id, colorOfTaxi, manufacturerer);
        }
        default: {
            return NULL;
        }
    }
    ////dont forget to add to taxi center from the server: taxiCenter->addTaxi(taxi);
    return taxi;
}

bool Recieve::isManufacturer(char c) {
    return c == 'H' || c == 'S' || c == 'T' || c == 'F';
}

bool Recieve::isColor(char c) {
    return c == 'R' || c == 'B' || c == 'G' || c == 'P' || c == 'W';
}

bool Recieve::isInRangeOfGrid(int num) {
    return num > 0;
}

//Split a string to parts in vector as the dell string is the seperate.
vector<string> Recieve::split(const string &s, const string &dell) {
    vector<string> parts;
    int index = 0, lastIndex = 0;
    do{
        index = s.find(dell, lastIndex);
        if (index < 0) {
            index = s.length();
        }
        parts.push_back(s.substr(lastIndex, index - lastIndex));
        lastIndex = index + dell.length();
    } while (index < s.length() && lastIndex < s.length());
    return parts;
}

bool Recieve::checkIfStringIsNumber(const string &s) {
    return false;
}


