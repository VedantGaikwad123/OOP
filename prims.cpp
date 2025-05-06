#include <iostream>
#include <climits>
#include <string>

using namespace std;

#define MAX 100

class Graph {
public:
    int totalCities;
    string cities[MAX]; // Stores city names
    int fuelCost[MAX][MAX]; // Adjacency matrix for fuel cost

    void accept();
    void primsMST();
};


void Graph::accept() {
    //acdept total cities
    cout << "Enter Total Cities: ";
    cin >> totalCities;

    // Accept city names
    for (int i = 0; i < totalCities; i++) {
        cout << "Enter City Name: ";
        cin >> cities[i];
    }

    // Initialize adjacency matrix
    for (int i = 0; i < totalCities; i++) {
        for (int j = 0; j < totalCities; j++) {
            if (i == j){
                fuelCost[i][j] = 0;  // If the source and destination are the same, set cost to 0
            } else {
                fuelCost[i][j] = INT_MAX;  // Otherwise, initialize with a large value (indicating no direct connection)
            }
        }
    }

    int totalRoutes;
    cout << "Enter Total Routes: ";
    cin >> totalRoutes;

    // Accept source, destination, and fuel cost
    for (int i = 0; i < totalRoutes; i++) {
        string source, destination;
        int fuel;
        cout << "Enter Route " << i + 1 << " (Source Destination Fuel_Cost): ";
        cin >> source >> destination >> fuel;

        int srcIndex = -1, destIndex = -1;
        for (int j = 0; j < totalCities; j++) {
            if (cities[j] == source) {
                srcIndex = j;
            }
            if (cities[j] == destination) {
                destIndex = j;
            }
        }

        if (srcIndex != -1 && destIndex != -1) {
            fuelCost[srcIndex][destIndex] = fuel;
            fuelCost[destIndex][srcIndex] = fuel;
        } else {
            cout << "Invalid City Name Entered. Try Again.\n";
            i--;
        }
    }
}

void Graph::primsMST() {
    int parent[MAX];  // To store the parent of each city in the MST
    int key[MAX];      // To store minimum fuel cost to connect each city
    bool visited[MAX] = {false}; // To track visited cities
    int totalFuel = 0;

    for (int i = 0; i < totalCities; i++) {  
        key[i] = INT_MAX;  // Initialize all key values with a large number (infinity)
    }
    

    key[0] = 0;
    parent[0] = -1; 

   // Loop to build the Minimum Spanning Tree (MST)
for (int count = 0; count < totalCities - 1; count++) {

    int minKey = INT_MAX;  // Initialize the minimum key value as a very large number
    int minIndex = -1;     // Initialize the index of the city with the smallest key

    // Find the city with the smallest key value that has not been visited yet
    for (int i = 0; i < totalCities; i++) {
        if (!visited[i] && key[i] < minKey) {
            minKey = key[i];  // Update the smallest key value
            minIndex = i;     // Store the index of this city
        }
    }

    visited[minIndex] = true;  // Mark the selected city as visited

    // Update the key values of the neighboring cities
    for (int i = 0; i < totalCities; i++) {
        // Check if the city is not visited, has a valid fuel cost, and is smaller than the current key value
        if (!visited[i] && fuelCost[minIndex][i] && fuelCost[minIndex][i] < key[i]) {
            key[i] = fuelCost[minIndex][i];  // Update the key value with a smaller cost
            parent[i] = minIndex;  // Store the parent of the city in MST
        }
    }
}


    cout << "\nMinimum Spanning Tree (MST) based on Fuel Cost:\n";
    cout << "Route\tFuel Cost\n";
    for (int i = 1; i < totalCities; i++) {
        cout << cities[parent[i]] << " -> " << cities[i] << " : " << fuelCost[i][parent[i]] << endl;
        totalFuel += fuelCost[i][parent[i]];
    }
    cout << "Total Fuel Required for MST: " << totalFuel << endl;
}

int main() {
    Graph g;
    g.accept();
    g.primsMST();
    return 0;
}
