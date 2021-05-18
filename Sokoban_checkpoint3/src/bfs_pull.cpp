#include <iostream>
#include <bits/stdc++.h>

#define contains(x) count(x)

using namespace std;

// Coordinate struct
struct Coordinate {
    explicit Coordinate(Coordinate *pCoordinate) {
        this->x = pCoordinate->x;
        this->y = pCoordinate->y;
    }

    int x{}, y{};

    Coordinate(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Coordinate() = default;

    bool operator==(const Coordinate &other) const {
        return (x == other.x && y == other.y);
    }
};

class CoordinateHashFunction {
public:

    size_t operator()(const Coordinate &c) const {
        return c.x * 1001 + 11 * c.y;
    }
};

// State struct
struct State {
    unordered_set<Coordinate, CoordinateHashFunction> boxes;
    Coordinate player;

    State(unordered_set<Coordinate, CoordinateHashFunction> boxes, Coordinate player) {
        this->boxes = std::move(boxes);
        this->player = player;
    }

    State() = default;

    bool operator==(const State &other) const {
        return (boxes == other.boxes && player == other.player);
    }
};

class StateHashFunction {
public:

    size_t operator()(const State &s) const {
        size_t result = 17;
        for (Coordinate b: s.boxes)
            result = 37 * result + b.x * 1001 + 11 * b.y;
        return 37 * result + s.player.x * 1001 + 11 * s.player.y;
    }
};

// Node struct
struct Node {
    struct Node *parent;
    State *state;
    int cost;
    string move;

    Node(Node *parent, State *state, int cost, string move) {
        this->parent = parent;
        this->state = state;
        this->cost = cost;
        this->move = std::move(move);
    }

    bool operator==(const Node &other) const {
        return (state == other.state);
    }
};

// problem struct
struct Problem {
    State *initialState;
    unordered_set<Coordinate, CoordinateHashFunction> walls;
    unordered_set<Coordinate, CoordinateHashFunction> goals;
    unordered_map<Coordinate, Coordinate, CoordinateHashFunction> blocked;

    Problem(unordered_set<Coordinate, CoordinateHashFunction> walls,
            unordered_set<Coordinate, CoordinateHashFunction> goals,
            State *initialState) {
        this->walls = std::move(walls);
        this->goals = std::move(goals);
        this->initialState = initialState;
    }

    bool goalTest(State *state) const {
        for (Coordinate box: state->boxes)
            if (!goals.contains(box))
                return false;
        return true;
    }

    static bool setContains(const unordered_set<Coordinate, CoordinateHashFunction> &set, int row, int col) {
        if (set.contains(*new Coordinate(row, col)))
            return true;
        return false;
    }

    vector<string> actions(const State &state) const {
        vector<string> actionList;
        int row = state.player.x;
        int col = state.player.y;
        unordered_set<Coordinate, CoordinateHashFunction> boxes = state.boxes;

        Coordinate newPlayer = *new Coordinate(row - 1, col);
        if (!walls.contains(newPlayer) && !(boxes.contains(newPlayer))) {
            actionList.emplace_back("u");
            actionList.emplace_back("U");
        }
        newPlayer = *new Coordinate(row, col + 1);
        if (!walls.contains(newPlayer) && !(boxes.contains(newPlayer))) {
            actionList.emplace_back("r");
            actionList.emplace_back("R");
        }
        newPlayer = *new Coordinate(row + 1, col);
        if (!walls.contains(newPlayer) && !(boxes.contains(newPlayer))) {
            actionList.emplace_back("d");
            actionList.emplace_back("D");
        }
        newPlayer = *new Coordinate(row, col - 1);
        if (!walls.contains(newPlayer) && !(boxes.contains(newPlayer))) {
            actionList.emplace_back("l");
            actionList.emplace_back("L");
        }

        return actionList;
    }
};

// global functions
Node *getChild(const Problem &p, Node *n, string action, bool isUcs);

string get_solution(Node *n);

string solve(const Problem &p);

bool list_contains(const list<Node *> &actions, Node *child);

// main
int main() {
    int row, col;
    unordered_set<Coordinate, CoordinateHashFunction> walls;
    unordered_set<Coordinate, CoordinateHashFunction> goals;
    unordered_set<Coordinate, CoordinateHashFunction> boxes;
    Coordinate player;

    cin >> row >> col;
    cin.ignore();
    string tmp;
    for (int i = 0; i < row; i++) {
        getline(cin, tmp);
        for (int j = 0; j < tmp.length(); j++) {
            Coordinate coordinate = *new Coordinate(i, j);
            switch (tmp[j]) {
                case '#': {
                    walls.insert(coordinate);
                    break;
                }
                case '-': {
                    player = coordinate;
                    break;
                }
                case '*': {
                    goals.insert(coordinate);
                    break;
                }
                case 'O': {
                    boxes.insert(coordinate);
                    break;
                }
            }
        }
    }

    Problem p = *new Problem(walls, goals, new State(boxes, player));

    cout << solve(p);
}

string solve(const Problem &p) {
    int totalNode = 1;
    int redundant = 0;
    Node *node = new Node(nullptr, p.initialState, 0, "");
    if (p.goalTest(node->state))
        return get_solution(node);

    unordered_set<State, StateHashFunction> explored;
    explored.insert(*node->state);
    list<Node *> fringe;
    fringe.push_back(node);
    while (!fringe.empty()) {
        node = fringe.front();
        fringe.pop_front();
        vector<string> actions = p.actions(*node->state);
        for (auto &action : actions) {
            Node *child = getChild(p, node, action, false);
            if (child != nullptr && child->state != nullptr) {
                totalNode++;
                if ((!explored.contains(*child->state)) && (!list_contains(fringe, child))) {
                    string solution = get_solution(child);
                    if (p.goalTest(child->state)) {
                        return solution;
                    }
                    fringe.push_back(child);
                    explored.insert(*child->state);
                } else
                    redundant++;
            }
        }
    }
    return "NO SOLUTION!!!";
}

string get_solution(Node *n) {
    string result;
    while (n->parent != nullptr) {
        result = n->move + result;
        n = n->parent;
    }
    return result;
}


Node *getChild(const Problem &p, Node *n, string action, bool isUcs) {
    unordered_set<Coordinate, CoordinateHashFunction> boxes = n->state->boxes;
    int row = n->state->player.x;
    int col = n->state->player.y;
    int newCost = n->cost + 1;
    Coordinate newPlayer = n->state->player;
    char choice = action[0];
    switch (choice) {
        case 'u':
        case 'U': {
            newPlayer = *new Coordinate(row - 1, col);
            if (choice == 'U') {
                Coordinate oldBox = *new Coordinate(row + 1, col);
                if (boxes.contains(oldBox)) {
                    choice = 'U';
                    Coordinate newBox = *new Coordinate(row, col);
                    boxes.erase(oldBox);
                    boxes.insert(newBox);
                    if (isUcs)
                        newCost++;
                }
            }
            break;
        }
        case 'd':
        case 'D': {
            newPlayer = *new Coordinate(row + 1, col);
            if (choice == 'D') {
                Coordinate oldBox = *new Coordinate(row - 1, col);
                if (boxes.contains(oldBox)) {
                    choice = 'D';
                    Coordinate newBox = *new Coordinate(row, col);
                    boxes.erase(oldBox);
                    boxes.insert(newBox);
                    if (isUcs)
                        newCost++;
                }
            }
            break;
        }
        case 'l':
        case 'L': {
            newPlayer = *new Coordinate(row, col - 1);
            if (choice == 'L') {
                Coordinate oldBox = *new Coordinate(row, col + 1);
                if (boxes.contains(oldBox)) {
                    choice = 'L';
                    Coordinate newBox = *new Coordinate(row, col);
                    boxes.erase(oldBox);
                    boxes.insert(newBox);
                    if (isUcs)
                        newCost++;
                }
            }
            break;
        }
        case 'r':
        case 'R': {
            newPlayer = *new Coordinate(row, col + 1);
            if (choice == 'R') {
                Coordinate oldBox = *new Coordinate(row, col - 1);
                if (boxes.contains(oldBox)) {
                    choice = 'R';
                    Coordinate newBox = *new Coordinate(row, col);
                    boxes.erase(oldBox);
                    boxes.insert(newBox);
                    if (isUcs)
                        newCost++;
                }
            }
            break;
        }
        default: {
        }
    }
    return new Node(n, new State(boxes, newPlayer), newCost, string(1, choice));
}

bool list_contains(const list<Node *> &actions, Node *child) {
    for (Node *action : actions)
        if (*action == *child)
            return true;
    return false;
}

