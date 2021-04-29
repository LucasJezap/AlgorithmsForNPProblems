#include <iostream>
#include <bits/stdc++.h>

#define contains(x) count(x)

#define TIMING

#ifdef TIMING
#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now();
#define START_TIMER  start = std::chrono::high_resolution_clock::now();
#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            std::chrono::high_resolution_clock::now()-start \
    ).count() << " ms " << std::endl;
#else
#define INIT_TIMER
#define START_TIMER
#define STOP_TIMER(name)
#endif

using namespace std;

int value = 0;
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
    Coordinate box;
    Coordinate player;

    State(Coordinate box, Coordinate player) {
        this->box = box;
        this->player = player;
    }

    State() = default;

    bool operator==(const State &other) const {
        return (box == other.box && player == other.player);
    }
};

class StateHashFunction {
public:

    size_t operator()(const State &s) const {
        size_t result = 17;
        result = 37 * result + s.box.x * 1001 + 11 * s.box.y;
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
    Coordinate goal;

    Problem(unordered_set<Coordinate, CoordinateHashFunction> walls,
            Coordinate goal,
            State *initialState) {
        this->walls = std::move(walls);
        this->goal = goal;
        this->initialState = initialState;
    }

    bool goalTest(State *state) const {
        if (goal == state->box)
            return true;
        return false;
    }

    vector<string> actions(const State &state) const {
        vector<string> actionList;
        int row = state.player.x;
        int col = state.player.y;
        Coordinate box = state.box;

        Coordinate newPlayer = *new Coordinate(row - 1, col);
        if (!walls.contains(newPlayer) && !(box == newPlayer)) {
            actionList.emplace_back("u");
            actionList.emplace_back("U");
        }
        newPlayer = *new Coordinate(row, col + 1);
        if (!walls.contains(newPlayer) && !(box == newPlayer)) {
            actionList.emplace_back("r");
            actionList.emplace_back("R");
        }
        newPlayer = *new Coordinate(row + 1, col);
        if (!walls.contains(newPlayer) && !(box == newPlayer)) {
            actionList.emplace_back("d");
            actionList.emplace_back("D");
        }
        newPlayer = *new Coordinate(row, col - 1);
        if (!walls.contains(newPlayer) && !(box == newPlayer)) {
            actionList.emplace_back("l");
            actionList.emplace_back("L");
        }

        return actionList;
    }
};

// global variables
Coordinate goal;

// global functions
Node *getChild(const Problem &p, Node *n, string action, bool isUcs);

string get_solution(Node *n);

string solve(const Problem &p);

bool vector_contains(const vector<Node *> &actions, Node *child);

int manhattan(Coordinate c1, Coordinate c2);

double getDist(Coordinate obj, Coordinate box);

double calculate(const State &s);

// main
int main() {
    int row, col;
    unordered_set<Coordinate, CoordinateHashFunction> walls;
    Coordinate box;
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
                    goal = coordinate;
                    break;
                }
                case 'O': {
                    box = coordinate;
                    break;
                }
            }
        }
    }

    INIT_TIMER
    START_TIMER
    Problem p = *new Problem(walls, goal, new State(box, player));
    cout << solve(p) << endl;
    STOP_TIMER("time ")
    cout << value << endl;
}

int manhattan(Coordinate c1, Coordinate c2) {
    return abs(c1.x - c2.x) + abs(c1.y - c2.y);
}

double getDist(Coordinate obj, Coordinate box) {
    double minDist = 1000000;

    double dist = manhattan(obj, box);
    if (dist < minDist)
        minDist = dist;

    return minDist;
}

double calculate(const State &s) {
    Coordinate box = s.box;
    double sum = 0;

    Coordinate player = s.player;
    double playerMin = getDist(player, box);
    sum += playerMin;

    double boxMin = getDist(box, goal);
    sum += boxMin;

    return sum;
}

struct a_star_comparator {
    bool operator()(const Node *a, const Node *b) const {
        return calculate(*a->state) + a->cost - calculate(*b->state) - b->cost > 0;
    }
};

string solve(const Problem &p) {
    int totalNode = 1;
    int redundant = 0;
    Node *initial = new Node(nullptr, p.initialState, 0, "");
    unordered_set<State, StateHashFunction> explored;
    explored.insert(*initial->state);
    vector<Node *> fringe;
    make_heap(fringe.begin(), fringe.end(), a_star_comparator());

    fringe.push_back(initial);
    push_heap(fringe.begin(), fringe.end(), a_star_comparator());
    while (!fringe.empty()) {
        Node *node = fringe.front();
        pop_heap(fringe.begin(), fringe.end(), a_star_comparator());
        fringe.pop_back();
        if (p.goalTest(node->state))
            return get_solution(node);
        vector<string> actions = p.actions(*node->state);
        for (auto &action : actions) {
            Node *child = getChild(p, node, action, true);
            if (child != nullptr && child->state != nullptr) {
                value++;
                totalNode++;
                if ((!explored.contains(*child->state)) && (!vector_contains(fringe, child))) {
                    fringe.push_back(child);
                    push_heap(fringe.begin(), fringe.end(), a_star_comparator());
                    explored.insert(*child->state);
                } else {
                    redundant++;
                    for (Node *next : fringe) {
                        if (next == child)
                            if (child->cost < next->cost) {
                                next = child;
                            }
                    }
                }
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
    Coordinate box = n->state->box;
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
                if (box == oldBox) {
                    choice = 'U';
                    Coordinate newBox = *new Coordinate(row, col);
                    box = newBox;
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
                if (box == oldBox) {
                    choice = 'D';
                    Coordinate newBox = *new Coordinate(row, col);
                    box = newBox;
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
                if (box == oldBox) {
                    choice = 'L';
                    Coordinate newBox = *new Coordinate(row, col);
                    box = newBox;
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
                if (box == oldBox) {
                    choice = 'R';
                    Coordinate newBox = *new Coordinate(row, col);
                    box = newBox;
                    if (isUcs)
                        newCost++;
                }
            }
            break;
        }
        default: {
        }
    }
    return new Node(n, new State(box, newPlayer), newCost, string(1, choice));
}

bool vector_contains(const vector<Node *> &actions, Node *child) {
    for (Node *action : actions)
        if (*action == *child)
            return true;
    return false;
}