
#include "Recieve.h"
#include "Point.h"
#include <boost/algorithm/string.hpp>

using namespace std;


Recieve::Recieve() {}

Recieve::~Recieve() {}

Recieve::Recieve(TaxiCenter *taxiCenter) : taxiCenter(taxiCenter) {}

void Recieve::printInvalid() {
    cout << "-1" << endl;
}

Matrix2D *Recieve::recieveMatrix() {
    int sizeGridX, sizeGridY, numbersOfObstacles;

    string sGrid, sObstacle, sPoint;
    //GETTING SIZE OF GRID.
    getline(cin, sGrid);
    boost::trim(sGrid);
    vector<string> parts = split(sGrid, ' ');

    if (parts.size() != 2) {
        return NULL;
    }

    if (!isInt(parts[0]) && !isInt(parts[1])) {
        return NULL;
    }

    sizeGridX = stoi(parts[0]);
    sizeGridY = stoi(parts[1]);

    // checking range of grid.
    if (!isInRangeOfGrid(sizeGridX) || !isInRangeOfGrid(sizeGridY)) {
        return NULL;
    }

    // getting obstacles.
    getline(cin, sObstacle);
    boost::trim(sObstacle);
    if (!isInt(sObstacle)) {
        return NULL;
    }
    numbersOfObstacles = stoi(sObstacle);
    //check if negative
    if (numbersOfObstacles < 0) {
        return NULL;
    }

    matrix2D = new Matrix2D(sizeGridX, sizeGridY);


    //getting location of obstacles.
    for (int j = 0; j < numbersOfObstacles; ++j) {
        int x, y;
        sPoint.clear();
        parts.clear();

        getline(cin, sPoint);
        boost::trim(sPoint);
        parts = split(sGrid, ' ');

        if (parts.size() != 2) {
            delete(matrix2D);
            return NULL;
        }

        if (!isInt(parts[0]) && !isInt(parts[1])) {
            delete(matrix2D);
            return NULL;
        }

        x = stoi(parts[0]);
        y = stoi(parts[1]);

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
    boost::trim(s);
    vector<string> parts = split(s, ',');

    if (parts.size() != 8) {
        return NULL;
    }

    if (!isInt(parts[0]) && !isInt(parts[1]) && !isInt(parts[2]) && !isInt(parts[3]) &&
            !isInt(parts[4]) && !isInt(parts[5]) && !isDouble(parts[6]) && !isInt(parts[7])) {
        return NULL;
    }

    ride_id = stoi(parts[0]);
    x_start = stoi(parts[1]);
    y_start = stoi(parts[2]);
    x_end = stoi(parts[3]);
    y_end = stoi(parts[4]);
    num_passengers = stoi(parts[5]);
    tariff = stod(parts[6]);
    startTime = stoi(parts[7]);


    //check if negative
    if (ride_id < 0 || num_passengers < 0 || startTime <= 0 || tariff < 0) {
        return NULL;
    }

    Point pStart(x_start, y_start);
    Point pEnd(x_end, y_end);
    Node *start = matrix2D->getNodeInMatrix(&pStart);
    Node *end = matrix2D->getNodeInMatrix(&pEnd);

    if (start == NULL || end == NULL || *start == end) {
        return NULL;
    }

    //check if the TRIP id is already exist.
    Trip* trip = taxiCenter->getTripByid(ride_id);
    if (trip != NULL) {
        return NULL;
    }

    return new Trip(start, end, ride_id, num_passengers,
                    tariff, startTime);
}

Taxi *Recieve::recieveTaxi() {
    int taxi_id, taxi_type;
    char manufacturerer, colorOfTaxi;

    string s;
    getline(cin, s);
    boost::trim(s);
    vector<string> parts = split(s, ',');

    if (parts.size() != 4) {
        return NULL;
    }

    if (parts[2].size() != 1 || parts[3].size() != 1) {
        return NULL;
    }

    if (!isInt(parts[0]) && !isInt(parts[1]) &&
            !isManufacturer(*parts[2].c_str()) && !isColor(*parts[3].c_str())) {
        return NULL;
    }

    taxi_id = stoi(parts[0]);
    taxi_type = stoi(parts[1]);
    manufacturerer = *parts[2].c_str();
    colorOfTaxi = *parts[3].c_str();

    //check if negative
    if (taxi_id < 0 || (taxi_type != 1 && taxi_type != 2)) {
        return NULL;
    }

    //check if the taxi id is already exist.
    Taxi* taxi = taxiCenter->getTaxiById(taxi_id);
    if (taxi != NULL) {
        return NULL;
    }


    // checking the type of the taxi and adding it to the
    // taxi center.
    switch (taxi_type) {
        case 1: {
            taxi = new TaxiStandard(taxi_id, colorOfTaxi, manufacturerer);
            break;
        }

        case 2: {
            taxi = new TaxiLuxury(taxi_id, colorOfTaxi, manufacturerer);
            break;
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

bool Recieve::isMaritalStatus(char c) {
    return c == 'S' || c == 'M' || c == 'W' || c == 'D';
}

bool Recieve::isInRangeOfGrid(int num) {
    return num > 0;
}

/*
//Split a string to parts in vector as the dell string is the seperate.
//from stackoverflow.
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
}*/

//from stackoverflow.
bool Recieve::isInt(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

//from stackoverflow.
bool Recieve::isDouble(const string& s) {
    istringstream iss(s);
    double d;
    char c;
    return iss >> d && !(iss >> c);
}

//from stackoverflow.
template<typename Out>
void Recieve::split(const std::string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

//from stackoverflow.
vector<string> Recieve::split(const std::string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

Driver *Recieve::recieveDriver() {
    int driver_id, age, xp, vehicle_id;
    char status;

    // getting details.
    string s;
    getline(cin, s);
    boost::trim(s);
    vector<string> parts = split(s, ',');

    if (parts.size() != 5) {
        return NULL;
    }

    if (parts[2].size() != 1) {
        return NULL;
    }

    if (!isInt(parts[0]) && !isInt(parts[1]) && !isMaritalStatus(*parts[2].c_str())
        && !isInt(parts[3]) && !isInt(parts[4])) {
        return NULL;
    }

    driver_id = stoi(parts[0]);
    age = stoi(parts[1]);
    status = *parts[2].c_str();
    xp = stoi(parts[3]);
    vehicle_id = stoi(parts[4]);

    //check if negative
    if (driver_id < 0 || age < 0 || xp < 0 || vehicle_id < 0) {
        return NULL;
    }

    return new Driver(driver_id, age, status, xp,
                                vehicle_id);
}
