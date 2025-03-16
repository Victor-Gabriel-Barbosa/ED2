#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Structure to represent a point on the grid
struct Point {
  char y; // 'A' to 'E'
  int x;  // 1 to 5

  bool operator==(const Point &other) const {
    return y == other.y && x == other.x;
  }

  bool operator<(const Point &other) const {
    if (y != other.y)
      return y < other.y;
    return x < other.x;
  }
};

// Calculate Manhattan distance between two points
double distance(const Point &p1, const Point &p2) {
  // For this problem, the distance between adjacent rows is always 1
  // For example: Distance(A1 to B1) = 1 unit
  int rowDiff = abs(p1.y - p2.y);
  int colDiff = abs(p1.x - p2.x);
  return rowDiff + colDiff;
}

// Check if graph is connected using BFS
bool isConnected(const map<Point, vector<Point>> &graph) {
  if (graph.empty())
    return true;

  set<Point> visited;
  queue<Point> q;

  // Start BFS from the first point
  Point start = graph.begin()->first;
  q.push(start);
  visited.insert(start);

  while (!q.empty()) {
    Point current = q.front();
    q.pop();

    if (graph.find(current) != graph.end()) {
      for (const Point &neighbor : graph.at(current)) {
        if (visited.find(neighbor) == visited.end()) {
          visited.insert(neighbor);
          q.push(neighbor);
        }
      }
    }
  }

  // Check if all vertices were visited
  return visited.size() == graph.size();
}

int main() {
  int T;
  cin >> T;

  for (int caseNum = 1; caseNum <= T; caseNum++) {
    int N;
    cin >> N;

    map<Point, vector<Point>> graph;
    map<Point, int> degree;
    double totalLength = 0.0;

    for (int i = 0; i < N; i++) {
      string s1, s2;
      cin >> s1 >> s2;

      // Extract y and x from strings like "A1", "C2"
      Point p1 = {s1[0], s1[1] - '0'};
      Point p2 = {s2[0], s2[1] - '0'};

      // Add edge to graph
      graph[p1].push_back(p2);
      graph[p2].push_back(p1);

      // Update degrees
      degree[p1]++;
      degree[p2]++;

      // Calculate and add edge length to total
      totalLength += distance(p1, p2);
    }

    // Count vertices with odd degree
    int oddCount = 0;
    for (const auto &entry : degree) {
      if (entry.second % 2 != 0) {
        oddCount++;
      }
    }

    // Check if Euler path or circuit exists
    bool hasEulerPath = (oddCount == 0 || oddCount == 2) && isConnected(graph);

    if (hasEulerPath) {
      cout << "Case " << caseNum << ": " << fixed << setprecision(2)
           << totalLength << endl;
    } else {
      cout << "Case " << caseNum << ": ~ x (" << endl;
    }
  }

  return 0;
}