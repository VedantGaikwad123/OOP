/*
Problem Definition: Optimal Binary Search Tree (OBST) for a General Store

 **Objective**:  
Construct a binary search tree (BST) for a set of items (keys) in a general store such that the **total expected search cost** is minimized. Each item has a probability of being searched, and the goal is to arrange the items in the BST to reduce the average access time.
*/

#include <iostream>
#include <iomanip>
using namespace std;

class OptimalBST {
    int totalKeys; // Number of items (keys)
    string itemNames[10]; // Array to store item names (keys)
    float successfulSearchProbability[10], unsuccessfulSearchProbability[11]; // Probability values
    float weightMatrix[11][11], costMatrix[11][11]; // Matrices for dynamic programming calculations
    int rootMatrix[11][11]; // Stores optimal root positions

public:
    void acceptData(); // Accept user input
    void computeOptimalBST(); // Dynamic programming calculations
    void displayResults(); // Print matrices and tree structure
    void constructTree(int start, int end, string parentItem, string branchType); // Recursive function
};

// Function to accept input from user
void OptimalBST::acceptData() {
    cout << "Enter the number of items: ";
    cin >> totalKeys;

    // Input sorted item names
    cout << "Enter item names in sorted order:\n";
    for (int i = 0; i < totalKeys; i++) {
        cin >> itemNames[i];
    }

    // Input search probabilities
    cout << "Enter probabilities of successful searches:\n";
    for (int i = 0; i < totalKeys; i++) {
        cin >> successfulSearchProbability[i];
    }

    // Input probabilities for unsuccessful searches
    cout << "Enter probabilities of unsuccessful searches:\n";
    for (int i = 0; i <= totalKeys; i++) {
        cin >> unsuccessfulSearchProbability[i];
    }
}

// Function to compute the Optimal BST using dynamic programming
void OptimalBST::computeOptimalBST() {
    // Step 1: Initialize base cases (single-node trees)
    for (int i = 0; i <= totalKeys; i++) {
        weightMatrix[i][i] = unsuccessfulSearchProbability[i];       //q : successfull search probability
        costMatrix[i][i] = 0; // Zero cost for an empty subtree
        rootMatrix[i][i] = 0; // No root exists in an empty range
    }

    // Step 2: Compute matrices for increasing subtree sizes
    for (int gap = 1; gap <= totalKeys; gap++) { // 'gap' represents subtree length
        for (int i = 0; i <= totalKeys - gap; i++) {
            int j = i + gap; // End index of subtree
            weightMatrix[i][j] = weightMatrix[i][j - 1] + successfulSearchProbability[j - 1] + unsuccessfulSearchProbability[j];

            float minimumCost = 9999; // Initialize minimum cost tracker
            int optimalRoot = 0; // Variable to store best root index

            // Step 3: Check every possible root between i & j and find the one with minimum cost
            for (int k = i + 1; k <= j; k++) {
                float currentCost = costMatrix[i][k - 1] + costMatrix[k][j];
                if (currentCost < minimumCost) {
                    minimumCost = currentCost;
                    optimalRoot = k; // Store optimal root index
                }
            }

            // Update matrices
            costMatrix[i][j] = weightMatrix[i][j] + minimumCost;
            rootMatrix[i][j] = optimalRoot;
        }
    }
}

// Function to display matrices and tree structure
void OptimalBST::displayResults() {
    cout << fixed << setprecision(2);

    // Display weight matrix (Accumulated probabilities)
    cout << "\nWeight Matrix (W):\n";
    for (int gap = 0; gap <= totalKeys; gap++) {
        for (int i = 0; i <= totalKeys - gap; i++) {
            int j = i + gap;
            cout << "W[" << i << "][" << j << "] = " << weightMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Display cost matrix (Search costs)
    cout << "\nCost Matrix (C):\n";
    for (int gap = 0; gap <= totalKeys; gap++) {
        for (int i = 0; i <= totalKeys - gap; i++) {
            int j = i + gap;
            cout << "C[" << i << "][" << j << "] = " << costMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    // Display root matrix (Optimal tree structure)
    cout << "\nRoot Matrix (R):\n";
    for (int gap = 0; gap <= totalKeys; gap++) {
        for (int i = 0; i <= totalKeys - gap; i++) {
            int j = i + gap;
            cout << "R[" << i << "][" << j << "] = " << rootMatrix[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nMinimum cost of Optimal BST = " << costMatrix[0][totalKeys] << endl;
    
    // Display tree structure
    cout << "\nOptimal Binary Search Tree Structure:\n";
    constructTree(0, totalKeys, "None", "Root");
}

// Recursive function to construct the BST hierarchy
void OptimalBST::constructTree(int start, int end, string parentItem, string branchType) {
    int rootIndex = rootMatrix[start][end];

    // Base case: If no valid root exists, return
    if (rootIndex == 0 || rootIndex == -1) return;

    // Get the key corresponding to this root
    string currentItem = itemNames[rootIndex - 1];
    cout << currentItem << " is the " << branchType << " of " << parentItem << endl;

    // Recursively print left and right subtrees
    constructTree(start, rootIndex - 1, currentItem, "Left Child");
    constructTree(rootIndex, end, currentItem, "Right Child");
}
OptimalBST obstObject; // Object creation
// Main function
int main() {
int choice;
do
{
    cout<<"1. Accept Data \t 2.Compute OBST \t 3.Display Result \t 0. Exit Program";
cout<<"Enter the Choice : ";
cin>>choice;

switch(choice){
    case 1: obstObject.acceptData();
    break;
    case 2:obstObject.computeOptimalBST();
    cout<<"Compute successfully";
    break;
    case 3:obstObject.displayResults();
    break;
    case 0: cout<<"exiting the program..."<<endl;
    break;

    default : cout<<"Enter Valid Choice"<<endl;
}

} while (choice!=0);

    return 0;
}
