#include "pugixml-1.11/src/pugixml.hpp"
#include "pugixml-1.11/src/pugixml.cpp"

#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <set>

using namespace std;
using namespace pugi;

const double Pi = 3.141592653589793;

class Transport_stations {

public:
    Transport_stations(int ind = 0, string type_of_vehicle = "", string name_stopping = "", string the_official_name ="", vector<string> location ={}, vector<string> routes = {}, pair<double, double> coordinates = {0, 0}): _ind {ind}, _coordinates {coordinates}, _location {location}, _name_stopping {name_stopping}, _routes {routes}, _the_official_name {the_official_name}, _type_of_vehicle {type_of_vehicle} {}

    int get_ind() const {
        return _ind;
    }
    string get_type_of_vehicle() const {
        return _type_of_vehicle;
    }
    string get_name_stopping() const {
        return _name_stopping;
    }
    string get_the_official_name() const {
        return _the_official_name;
    }
    vector<string> get_location() const {
        return _location;
    }
    vector<string> get_routes () const {
        return _routes;
    }
    double get_coordinates_x() const {
        return _coordinates.first;
    }
    double get_coordinates_y() const {
        return _coordinates.second;
    }

    string routes(int i) const {
        return _routes[i];
    }

    int route_size() const {
        return _routes.size();
    }

private:
    int _ind;
    string _type_of_vehicle;
    string _name_stopping;
    string _the_official_name;
    vector<string> _location;
    vector<string> _routes;
    pair<double, double> _coordinates;
};

class Routes {
public:
    string route;
    vector<Transport_stations> Trolley;
    vector<Transport_stations> Bus;
    vector<Transport_stations> Tram;
};

double distance(const Transport_stations &first, const Transport_stations &second) {
    pair<double, double> latitude;
    latitude.first = first.get_coordinates_x() * Pi / 180;
    latitude.second = second.get_coordinates_x() * Pi / 180;
    double d_latitude = latitude.second - latitude.first;
    pair<double, double> longitude;
    longitude.first = first.get_coordinates_y() * Pi / 180;
    longitude.second = second.get_coordinates_y() * Pi / 180;
    double d_longitude = longitude.second - longitude.first;
    double dist = 2 * asin(sqrt(pow(sin(d_latitude / 2), 2) + cos(latitude.first) * cos(latitude.second) * pow(sin(d_longitude / 2), 2))) * 6371;
    return dist;
}

void separator(const string &str, string &str1, string &str2) {
    string sep = ",";
    int start = 0;
    int finish = str.find(sep);
    while (finish != -1) {
        str1 = str.substr(start, finish - start);
        start = finish + sep.length();
        finish = str.find(sep, start);
    }
    str2 = str.substr(start, finish);
}

string fix(string &str) {
    vector<string> trash {"Ул.", "УЛ.", "ул.", "Улица", "улица", "УЛИЦА", "Пер.", "ПЕР.", "пер.", "Переулок", "переулок", "ПЕРЕУЛОК", "ш.", "Ш.", "Шоссе", "шоссе", "ШОССЕ", "Бул.", "бул.", "БУЛ.", "Бульвар", "бульвар", "БУЛЬВАР", "Пр.", "ПР.", "пр.", "Проспект", "ПРОСПЕКТ", "проспект" };
    for (auto &i: trash)
        if (str.find(i) != -1) {
            int first = str.find(i);
            int second = first + i.size();
            str.erase(first, second);
        }
    if (str[str.size() - 1] == ' ')
        str.erase(str.end() - 1);
    return str;
}

void parse(vector<Transport_stations> &stop, map<string, Routes> &map_routes, set<string> &name_routes, map<string, int> &positions) {
    xml_document doc;
    doc.load_file("data1.xml");
    xml_node data = doc.child("dataset");
    for (xml_node i = data.child("transport_station"); i; i = i.next_sibling("transport_station")) {
        pair <string, string> str;
        separator(i.child_value("coordinates"), str.first, str.second);
        pair <float, float> coordinates;
        coordinates.first = stof(str.first);
        coordinates.second = stof(str.second);
        string str_routes = i.child_value("routes"), segment;
        vector<string> routes;
        stringstream temp_routes(str_routes);
        if (count(str_routes.begin(), str_routes.end(), ','))
            while (getline(temp_routes, segment, ','))
                routes.push_back(segment);
        else
            while (getline(temp_routes, segment, '.'))
                routes.push_back(segment);
        string str_location = i.child_value("location");
        vector<string> locations;
        stringstream temp_locations(str_location);
        if (count(str_location.begin(), str_location.end(), ',') && !str_location.empty())
            while (getline(temp_locations, segment, ',')) {
                if (segment[0] == ' ')
                    segment.erase(segment.begin());
                locations.push_back(fix(segment));
                positions[fix(segment)] += 1;
            }
        else if (!str_location.empty()) {
            locations.push_back(fix(str_location));
            positions[fix(str_location)] += 1;
        }
        int ind = stoi(i.child_value("number"));
        string type_of_vehicle = i.child_value("type_of_vehicle");
        string name_stopping = i.child_value("name_stopping");
        string the_official_name = i.child_value("the_official_name");
        Transport_stations Transport_station(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates);
        stop.emplace_back(Transport_station);
        if (strcmp(i.child_value("type_of_vehicle"), "Трамвай") == false)
            for (auto &j: routes) {
                map_routes[j].route = j;
                map_routes[j].Tram.emplace_back(Transport_stations(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates));
                name_routes.insert(j);
            }
        if (strcmp(i.child_value("type_of_vehicle"), "Троллейбус") == false)
            for (auto &j: routes) {
                map_routes[j].route = j;
                map_routes[j].Trolley.emplace_back(Transport_stations(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates));
                name_routes.insert(j);
            }
        if (strcmp(i.child_value("type_of_vehicle"), "Автобус") == false)
            for (auto &j: routes) {
                map_routes[j].route = j;
                map_routes[j].Bus.emplace_back(Transport_stations(ind, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates));
                name_routes.insert(j);
            }

    }
}

int main() {
    vector<Transport_stations> TransportStation;
    map<string, Routes> routes;
    set<string> name_routes;
    map<string, int> locations;
    parse(TransportStation, routes, name_routes, locations);
    map<string, int> tram_routes;
    map<string, int> bus_routes;
    map<string, int> trolley_routes;
    for (const auto& i: TransportStation) {
        if (i.get_type_of_vehicle() == "Трамвай")
            for (int j = 0; j < i.route_size(); j++)
                tram_routes[i.routes(j)]++;
        if (i.get_type_of_vehicle() == "Автобус")
            for (int j = 0; j < i.route_size(); j++)
                bus_routes[i.routes(j)]++;
        if (i.get_type_of_vehicle() == "Троллейбус")
            for (int j = 0; j < i.route_size(); j++)
                trolley_routes[i.routes(j)]++;
    }
    string max_tram_routes = "";
    string max_bus_routes = "";
    string max_trolley_routes = "";
    int k_tram_routes = 0;
    int k_bus_routes = 0;
    int k_trolley_routes = 0;
    for (const auto& i: tram_routes)
        if (i.second > k_tram_routes) {
            k_tram_routes = i.second;
            max_tram_routes = i.first;
        }
    for (const auto& i: trolley_routes)
        if (i.second > k_trolley_routes) {
            k_trolley_routes = i.second;
            max_trolley_routes = i.first;
        }
    for (const auto& i: bus_routes)
        if (i.second > k_bus_routes) {
            k_bus_routes = i.second;
            max_bus_routes = i.first;
        }
    max_tram_routes = "";
    max_trolley_routes = "";
    max_bus_routes = "";
    k_tram_routes = 0;
    k_trolley_routes = 0;
    k_bus_routes = 0;
    map<string, double> size_tram_routes;
    map<string, double> size_trolley_routes;
    map<string, double> size_bus_routes;
    for (const auto &i: name_routes) {
        if (routes[i].Tram.size() > 1)
            for (int j = 0; j < routes[i].Tram.size() - 1; j++)
                size_tram_routes[routes[i].route] += distance(routes[i].Tram[j], routes[i].Tram[j + 1]);
        if (routes[i].Trolley.size() > 1)
            for (int j = 0; j < routes[i].Trolley.size() - 1; j++)
                size_trolley_routes[routes[i].route] += distance(routes[i].Trolley[j], routes[i].Trolley[j + 1]);
        if (routes[i].Bus.size() > 1)
            for (int j = 0; j < routes[i].Bus.size() - 1; j++)
                size_bus_routes[routes[i].route] += distance(routes[i].Bus[j], routes[i].Bus[j + 1]);
    }
    for (const auto& i : size_tram_routes)
        if (i.second > k_tram_routes) {
            k_tram_routes = i.second;
            max_tram_routes = i.first;
        }
    for (const auto& i : size_trolley_routes)
        if (i.second > k_trolley_routes) {
            k_trolley_routes = i.second;
            max_trolley_routes = i.first;
        }
    for (const auto& i : size_bus_routes)
        if (i.second > k_bus_routes) {
            k_bus_routes = i.second;
            max_bus_routes = i.first;
        }
    int k_max_street = 0;
    string max_street = "";
    for (const auto& i: locations)
        if (i.second > k_max_street) {
            k_max_street = i.second;
            max_street = i.first;
        }
    cout << "=================================Task 1=========================" << endl;
    cout << max_tram_routes << ": " << k_tram_routes << "; " << max_trolley_routes << ": " << k_trolley_routes << "; " << max_bus_routes  << ": " << k_bus_routes << endl;
    cout << "=================================Task 2=========================" << endl;
    cout << max_tram_routes << ", " << max_trolley_routes << ", " << max_bus_routes<< endl;
    cout << "=================================Task 3=========================" << endl;
    cout << max_street << ": " << k_max_street  << endl;
    return 0;
}

