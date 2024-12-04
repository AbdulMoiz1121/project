#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>

// Graph class to represent the social network
class Graph {
private:
    std::unordered_map<std::string, std::vector<std::string>> adjacencyList;

public:
    // Add a new user (node) to the graph
    void addUser(const std::string& user) {
        if (adjacencyList.find(user) == adjacencyList.end()) {
            adjacencyList[user] = {};
        }
    }

    // Add a friendship (edge) between two users
    void addEdge(const std::string& user1, const std::string& user2) {
        adjacencyList[user1].push_back(user2);
        adjacencyList[user2].push_back(user1);
    }

    // Display the graph structure
    void displayGraph() {
        std::cout << "Social Network Graph:" << std::endl;
        for (const auto& [user, friends] : adjacencyList) {
            std::cout << user << ": ";
            for (const auto& friendName : friends) {
                std::cout << friendName << " ";
            }
            std::cout << std::endl;
        }
    }

    // BFS to find the shortest path between two users
    std::vector<std::string> bfsShortestPath(const std::string& start, const std::string& end) {
        std::unordered_map<std::string, bool> visited;
        std::unordered_map<std::string, std::string> parent;
        std::queue<std::string> queue;

        queue.push(start);
        visited[start] = true;

        while (!queue.empty()) {
            std::string current = queue.front();
            queue.pop();

            if (current == end) break;

            for (const auto& neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }

        // Reconstruct path
        std::vector<std::string> path;
        if (visited[end]) {
            for (std::string at = end; at != ""; at = parent[at]) {
                path.push_back(at);
            }
            std::reverse(path.begin(), path.end());
        }
        return path;
    }

    // DFS to find any path between two users
    std::vector<std::string> dfsPath(const std::string& start, const std::string& end) {
        std::unordered_map<std::string, bool> visited;
        std::vector<std::string> path, result;
        dfsHelper(start, end, visited, path, result);
        return result;
    }

private:
    void dfsHelper(const std::string& current, const std::string& end,
                   std::unordered_map<std::string, bool>& visited,
                   std::vector<std::string>& path, std::vector<std::string>& result) {
        visited[current] = true;
        path.push_back(current);

        if (current == end) {
            result = path;  // Save the path
            return;
        }

        for (const auto& neighbor : adjacencyList[current]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, end, visited, path, result);
                if (!result.empty()) return;  // Stop if path found
            }
        }

        path.pop_back();  // Backtrack
    }
};

// Groups class for managing user groups
class Groups {
private:
    std::unordered_map<std::string, std::vector<std::string>> groupMembers;

public:
    // Add a user to a group
    void addToGroup(const std::string& groupName, const std::string& user) {
        groupMembers[groupName].push_back(user);
    }

    // Display all groups and their members
    void displayGroups() {
        std::cout << "Groups and Members:" << std::endl;
        for (const auto& [groupName, members] : groupMembers) {
            std::cout << "Group: " << groupName << std::endl;
            for (const auto& member : members) {
                std::cout << " - " << member << std::endl;
            }
        }
    }
};

int main() {
    Graph socialNetwork;

    // Add users to the network
    socialNetwork.addUser("Alice");
    socialNetwork.addUser("Bob");
    socialNetwork.addUser("Charlie");
    socialNetwork.addUser("David");
    socialNetwork.addUser("Eve");

    // Add friendships
    socialNetwork.addEdge("Alice", "Bob");
    socialNetwork.addEdge("Bob", "Charlie");
    socialNetwork.addEdge("Charlie", "David");
    socialNetwork.addEdge("Alice", "Eve");

    // Display the social network
    socialNetwork.displayGraph();

    // Find message paths
    std::cout << "\nBFS Shortest Path from Alice to David:" << std::endl;
    auto bfsPath = socialNetwork.bfsShortestPath("Alice", "David");
    if (!bfsPath.empty()) {
        for (const auto& user : bfsPath) {
            std::cout << user << " ";
        }
    } else {
        std::cout << "No path found.";
    }

    std::cout << "\n\nDFS Path from Alice to David:" << std::endl;
    auto dfsPath = socialNetwork.dfsPath("Alice", "David");
    if (!dfsPath.empty()) {
        for (const auto& user : dfsPath) {
            std::cout << user << " ";
        }
    } else {
        std::cout << "No path found.";
    }

    // Group management
    Groups groups;
    groups.addToGroup("Friends", "Alice");
    groups.addToGroup("Friends", "Bob");
    groups.addToGroup("Colleagues", "Charlie");
    groups.addToGroup("Colleagues", "David");

    std::cout << "\n\nGroups:" << std::endl;
    groups.displayGroups();

    return 0;
}

