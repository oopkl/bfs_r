// #include <iostream>
// #include <vector>
// #include <map>
// #include <queue>
// #include <string>
// #include <algorithm>

// using namespace std;

// // Define the cities and their connections
// map<string, map<string, int>> graph = {
//     {"Arad", {{"Zerind", 75}, {"Timisoara", 118}, {"Sibiu", 140}}},
//     {"Zerind", {{"Arad", 75}, {"Oradea", 71}}},
//     {"Oradea", {{"Zerind", 71}, {"Sibiu", 151}}},
//     {"Timisoara", {{"Arad", 118}, {"Lugoj", 111}}},
//     {"Lugoj", {{"Timisoara", 111}, {"Mehadia", 70}}},
//     {"Mehadia", {{"Lugoj", 70}, {"Drobeta", 75}}},
//     {"Drobeta", {{"Mehadia", 75}, {"Craiova", 120}}},
//     {"Craiova", {{"Drobeta", 120}, {"Pitesti", 138}, {"Rimnicu Vilcea", 146}}},
//     {"Rimnicu Vilcea", {{"Craiova", 146}, {"Sibiu", 80}, {"Pitesti", 97}}},
//     {"Sibiu", {{"Arad", 140}, {"Oradea", 151}, {"Rimnicu Vilcea", 80}, {"Fagaras", 99}}},
//     {"Fagaras", {{"Sibiu", 99}, {"Bucharest", 211}}},
//     {"Pitesti", {{"Rimnicu Vilcea", 97}, {"Craiova", 138}, {"Bucharest", 101}}},
//     {"Bucharest", {{"Fagaras", 211}, {"Pitesti", 101}}},
// };

// // Heuristic function (straight-line distance to Bucharest) 
// map<string, int> heuristic = {
//     {"Arad", 366}, {"Zerind", 374}, {"Oradea", 380}, {"Timisoara", 329},
//     {"Lugoj", 244}, {"Mehadia", 241}, {"Drobeta", 242}, {"Craiova", 160},
//     {"Rimnicu Vilcea", 193}, {"Sibiu", 253}, {"Fagaras", 178}, {"Pitesti", 98},
//     {"Bucharest", 0}
// };

// // Best First Search function
// vector<string> bestFirstSearch(const string &start, const string &goal) {

//     priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> frontier; 
//     //element with the smallest heuristic value (closest to the goal) will be at the top of the priority queue.
//     map<string, string> cameFrom; // represents a city and the city from which it was reached

//     frontier.push({heuristic[start], start});
//     cameFrom[start] = "";

//     while (!frontier.empty()) {
//         string current = frontier.top().second;
//         frontier.pop();

//         if (current == goal) {
//             vector<string> path;
//             while (current != "") {
//                 path.push_back(current);
//                 current = cameFrom[current];
//             }
//             reverse(path.begin(), path.end());
//             return path;
//         }

//         for (const auto &neighbor : graph[current]) { //explore neighbors of current by iterating over the adjacent cities stored in graph map
//             string next = neighbor.first;

//             if (cameFrom.find(next) == cameFrom.end()) { //if next has not been visited yet (not present in cameFrom map)
//                 cameFrom[next] = current; //stores current as the previous city
//                 int priority = heuristic[next]; // calculate priority (heuristic value) of next using the heuristic map 
//                 frontier.push({priority, next}); //pushes {priority, next} onto the frontier queue
//             }
//         }
//     }

//     return {}; // no path found
// }

// int main() {
//     string start = "Arad";
//     string goal = "Bucharest";

//     vector<string> path = bestFirstSearch(start, goal);

//     if (!path.empty()) {
//         cout << "Shortest path from " << start << " to " << goal << ":\n";
//         for (const string &city : path) {
//             cout << city << " -> ";
//         }
//         cout << "Goal reached.\n";
//     } else {
//         cout << "No path found from " << start << " to " << goal << ".\n";
//     }

//     return 0;
// }

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// Define the cities and their connections
map<string, map<string, int>> graph = {
    {"A", {{"B", 2}, {"C", 4}}},
    {"B", {{"A", 2}, {"D", 3}, {"E", 1}}},
    {"C", {{"A", 4}, {"F", 5}}},
    {"D", {{"B", 3}, {"G", 7}}},
    {"E", {{"B", 1}, {"G", 2}}},
    {"F", {{"C", 5}, {"G", 1}}},
    {"G", {{"D", 7}, {"E", 2}, {"F", 1}}}
};

// Heuristic function (estimated distance to goal "G")
map<string, int> heuristic = {
    {"A", 6}, {"B", 4}, {"C", 3}, {"D", 4}, {"E", 2}, {"F", 1}, {"G", 0}
};

// Best First Search function
vector<string> bestFirstSearch(const string &start, const string &goal) {

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> frontier; 
    map<string, string> cameFrom;

    frontier.push({heuristic[start], start});
    cameFrom[start] = "";

    while (!frontier.empty()) {
        string current = frontier.top().second;
        frontier.pop();

        if (current == goal) {
            vector<string> path;
            while (current != "") {
                path.push_back(current);
                current = cameFrom[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto &neighbor : graph[current]) {
            string next = neighbor.first;

            if (cameFrom.find(next) == cameFrom.end()) {
                cameFrom[next] = current;
                int priority = heuristic[next];
                frontier.push({priority, next});
            }
        }
    }

    return {}; // no path found
}

int main() {
    string start = "A";
    string goal = "G";

    vector<string> path = bestFirstSearch(start, goal);

    if (!path.empty()) {
        cout << "Shortest path from " << start << " to " << goal << ":\n";
        for (const string &city : path) {
            cout << city << " -> ";
        }
        cout << "Goal reached.\n";
    } else {
        cout << "No path found from " << start << " to " << goal << ".\n";
    }

    return 0;
}

