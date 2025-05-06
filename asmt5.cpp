/*
Problem Statement : a pizza delivery company want to optimise its delivery process to minimise the delivery time and fuel cost , the company has a central pizza hub where all pizza's 
are prepared , multiple delivery location where customers are waiting for there order , a road network connecting the hub to all deleivery location , with each road segment having a 
specific distance or travel time , the goal is to determine the shorteds path from the pizza hub to each customer location so that delivery's can be made as quickly and efficintly 
as possible 
*/
#include <iostream>
#include <string>
using namespace std;

class JobSeeker {
public:
    int totalCities, totalEdges;
    string cities[10];
    int distance[10][10];
    void accept();
    void dijkstraAlgorithm();
    void displayMatrix();
};

// Object creation
JobSeeker interview;

void JobSeeker::accept() {
    // Accept total cities
    cout << "Enter Total Cities: ";
    cin >> totalCities;

    // Accept city names
    for (int i = 0; i < totalCities; i++) {
        cout << "Enter City Name: ";
        cin >> cities[i];
    }

    // Initialize distance matrix to infinity
    for (int i = 0; i < totalCities; i++) {
        for (int j = 0; j < totalCities; j++) {
            distance[i][j] = (i == j) ? 0 : 999; // 0 for same city, large value for others
        }
    }

    // Accept total edges
    cout << "Enter Total Edges: ";
    cin >> totalEdges;

    // Accept city connections and distances
    for (int i = 0; i < totalEdges; i++) {
        string city1, city2;
        int weight;
        cout << "Enter Edge " << i + 1 << " (City1, City2, Weight): ";
        cin >> city1 >> city2 >> weight;

        // Find indexes for cities
        int index1 = -1, index2 = -1;
        for (int j = 0; j < totalCities; j++) {
            if (cities[j] == city1) index1 = j;
            if (cities[j] == city2) index2 = j;
        }

        // Update the distance matrix
        if (index1 != -1 && index2 != -1) {
            distance[index1][index2] = weight;
            distance[index2][index1] = weight;
        } else {
            cout << "Invalid cities entered. Please try again." << endl;
            i--; // Re-enter this edge
        }
    }
}

void JobSeeker::dijkstraAlgorithm() {
    int source = 0; // Assume starting city is the first entered
    int shortestDistance[10];
    bool visited[10] = {false};

    // Initialize distances to infinity
    for (int i = 0; i < totalCities; i++) {
        shortestDistance[i] = 999;
    }
    shortestDistance[source] = 0; // Distance to itself is 0

    for (int count = 0; count < totalCities; count++) {
        int minDistance = 999, u = -1;

        // Find unvisited city with minimum distance
        for (int i = 0; i < totalCities; i++) {
            if (!visited[i] && shortestDistance[i] < minDistance) {
                minDistance = shortestDistance[i];
                u = i;
            }
        }

        visited[u] = true;

        // Update distances for adjacent cities
        for (int v = 0; v < totalCities; v++) {
            if (!visited[v] && distance[u][v] != 999 &&
                shortestDistance[u] + distance[u][v] < shortestDistance[v]) {
                shortestDistance[v] = shortestDistance[u] + distance[u][v];
            }
        }
    }

    // Display the shortest path
    cout << "\nShortest Distance from " << cities[source] << ":\n";
    for (int i = 0; i < totalCities; i++) {
        cout << cities[source] << " -> " << cities[i] << ": ";
        if (shortestDistance[i] == 999)
            cout << "Unreachable\n";
        else
            cout << shortestDistance[i] << " units\n";
    }
}

void JobSeeker::displayMatrix() {
    cout << "\nAdjacency Matrix (Distances between Cities):\n";
    for (int i = 0; i < totalCities; i++) {
        for (int j = 0; j < totalCities; j++) {
            cout << distance[i][j] << "\t";
        }
        cout << endl;
    }
}

int main(){
    interview.accept();
    interview.displayMatrix();
    interview.dijkstraAlgorithm();
    return 0;
}
//problem statement and program is different 