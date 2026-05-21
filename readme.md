# CampusCompass
---

A graph based campus navigation system in C++ that models a university campus as a weighted undirected graph. Students are stored with their residence location and class schedule; the system computes shortest paths, connectivity checks, and minimum spanning tree costs using Dijkstra's algorithm and Prim's algorithm over open edges.

## Features
---

### Commands
---

All eleven commands are read from stdin and dispatched to the `CampusCompass` object:

`insert "NAME" UFID LOCATION_ID N CLASS1 ... CLASSN` — Insert a student record. Validates that the name contains only letters/spaces, the UFID is exactly 8 digits, class codes match `XXX0000`, and 1–6 non duplicate valid classes are provided. Prints `successful` or `unsuccessful`

`remove UFID` — Remove a student by their 8 digit UFID. Prints `successful` or `unsuccessful`

`dropClass UFID CLASS_CODE` — Remove one class from a student's schedule. Automatically removes the student if they have no remaining classes. Prints `successful` or `unsuccessful`

`replaceClass UFID CLASS_CODE1 CLASS_CODE2` — Swap one class for another in a student's schedule. Validates that `CLASS_CODE1` is enrolled, `CLASS_CODE2` is not already enrolled, and `CLASS_CODE2` exists in the course catalog. Prints `successful` or `unsuccessful`

`removeClass CLASS_CODE` — Drop a class from every enrolled student's schedule, removing students who end up with no classes. Prints the count of affected students, or `unsuccessful`

`toggleEdgesClosure N X1 Y1 ... XN YN` — Toggle the open/closed status of N campus paths (edges). Prints `successful` or `unsuccessful`

`checkEdgeStatus LOCATION_X LOCATION_Y` — Print `open`, `closed`, or `DNE` for the path between two locations

`isConnected LOCATION_1 LOCATION_2` — DFS over open edges to determine if two locations are reachable from each other. Prints `successful` or `unsuccessful`

`printShortestEdges UFID` — Run Dijkstra's algorithm from a student's residence and print the shortest travel time (in minutes) to each of their class buildings

`printStudentZone UFID` — Compute the MST cost (Prim's) of the subgraph formed by the Dijkstra shortest-path tree connecting the student's residence to all their class locations. Prints `Student Zone Cost For NAME: COST`

`verifySchedule UFID` — For each consecutive pair of classes (sorted by start time), run Dijkstra's between the two buildings and check whether the gap time between classes is sufficient for travel. Prints per-transition `successful` or `unsuccessful`

### Graph Model
---

The campus is loaded from `data/edges.csv` as a weighted undirected graph stored in an adjacency list. Each edge carries a travel time weight and an open/closed flag that can be toggled at runtime. Closed edges are ignored by all traversal algorithms.

### Algorithms
---

| Algorithm | Used by |
|---|---|
| Dijkstra's shortest path | `printShortestEdges`, `verifySchedule` |
| Prim's MST | `printStudentZone` |
| DFS  | `isConnected` |

### Input Validation
---

- UFID must be exactly 8 numeric digits
- Name must contain only letters and spaces (validated with `std::regex`)
- Class codes must match `^[A-Z]{3}[0-9]{4}$`
- Students must enroll in 1–6 non-duplicate classes that exist in the course catalog
- Duplicate UFIDs are rejected before insertion
- Invalid location IDs and malformed commands print `unsuccessful`

## Tech Stack
---

| | |
|---|---|
| Language | C++17 |
| Build system | CMake 3.22+ |
| Testing | [Catch2 v3.5.2](https://github.com/catchorg/Catch2) |
| Graph storage | Adjacency list (`unordered_map<int, vector<Edge>>`) |
| Shortest path | Dijkstra's with `std::priority_queue` (min-heap) |
| Input parsing | `stringstream` + `std::quoted` |
| Campus data | CSV files (`data/edges.csv`, `data/classes.csv`) |

---

## Getting Started
---

### Build with CMake (CLion / VS Code)
---

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

The build automatically copies the `data/` directory into the build output so the executable can locate the CSV files at runtime.

Run the `Main` executable and pipe in a command file:

```bash
./cmake-build-debug/Main < input.txt
```

### Build with g++ (command line)

```bash
g++ -std=c++17 -Wall -Werror -o Main src/main.cpp src/CampusCompass.cpp
```

Run:

```bash
./Main < input.txt
```

### Input Format
---

```
N
command1
command2
...
```

The first line is the number of commands. Each subsequent line is one command.

Example:

```
5
insert "Alice Smith" 12345678 1 2 COP3530 CDA3101
printShortestEdges 12345678
isConnected 1 14
checkEdgeStatus 1 2
verifySchedule 12345678
```

---

## Testing
---

### Catch2 Unit Tests
---

```bash
cmake --build cmake-build-debug --target Tests
./cmake-build-debug/Tests
```

The unit tests are in [test/test.cpp](test/test.cpp) using Catch2. They cover:

| Test Case | What it checks |
|---|---|
| Incorrect Commands | Rejects duplicate UFID, remove/dropClass on non-existent students, `removeClass` on unknown class |
| Edge Cases | Remove non-existent student, auto-remove after last class is dropped, `checkEdgeStatus` on non-adjacent nodes |
| Class Management | `replaceClass`, `dropClass`, `removeClass`, and `remove` on valid records |
| Shortest Edges | `printShortestEdges` before and after toggling edge closures; verifies unreachable nodes after path closure |
