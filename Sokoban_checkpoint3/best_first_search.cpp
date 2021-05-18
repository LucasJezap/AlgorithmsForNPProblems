#include <iostream>
#include <bits/stdc++.h>
#include <string>

#define WALL '#'
#define BOX 'O'
#define TARGET '*'
#define PLAYER '-'
#define EMPTY ' '

using namespace std;

int rows, cols;
int x[] = {-1, 0, 1, 0};
int y[] = {0, -1, 0, 1};
char moves[] = {'l', 'u', 'r', 'd'};

struct Coordinate {
    explicit Coordinate(Coordinate *pCoordinate) {
        this->row = pCoordinate->row;
        this->column = pCoordinate->column;
        this->type = pCoordinate->type;
    }

    int row{}, column{};
    char type{};

    Coordinate(int row, int column, char type) {
        this->row = row;
        this->column = column;
        this->type = type;
    }

    bool operator<(const Coordinate &coord) const {
        if (this->row < coord.row) {
            return true;
        }
        if (this->row == coord.row && this->column < coord.row) {
            return true;
        }
        return false;
    }

    bool operator==(const Coordinate &coord) const {
        return this->row == coord.row && this->column == coord.column;
    }
};

vector<Coordinate *> boxes;

struct Move {
    Coordinate *newPosition{};
    Coordinate *playerPosition{};
    int cost{};
    int move{};
    bool isViable{};
    string path;

    Move(Coordinate *newPosition, int cost, string path)
            : newPosition(newPosition), cost(cost),
              isViable(false), path(std::move(path)) {}

    Move(Coordinate *newPosition, Coordinate *playerPosition, int cost, string path, int move)
            : newPosition(newPosition), playerPosition(playerPosition), cost(cost),
              isViable(false), path(std::move(path)), move(move) {}

    explicit Move(Coordinate *playerPosition)
            : playerPosition(playerPosition) {}

    Move() = default;
};

struct CompareMove {
    bool operator()(Move const *m1, Move const *m2) {
        return m1->cost > m2->cost;
    }
};


int greedy_cost(Coordinate *position, Coordinate *goal) {
    return abs(position->row - goal->row) + abs(position->column - goal->column);
}

bool vector_contains(const vector<Coordinate *> &values, Coordinate *value) {
    for (auto v: values) {
        if (v->row == value->row && v->column == value->column)
            return true;
    }
    return false;
}

bool is_player_move_viable(Coordinate ***maze, Coordinate *position) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column]->type != WALL &&
           !vector_contains(boxes, maze[position->row][position->column]);
}

string find_path(Coordinate ***maze, Coordinate *player, Coordinate *target) {
    if (player->row == target->row && player->column == target->column)
        return "";
    priority_queue<Move *, vector<Move *>, CompareMove> pq;
    bool visited[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j]->type == WALL)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }

    }

    for (int i = 0; i < 4; i++) {
        if (is_player_move_viable(maze, maze[player->row + y[i]][player->column + x[i]])) {
            pq.push(new Move(maze[player->row + y[i]][player->column + x[i]],
                             greedy_cost(maze[player->row + y[i]][player->column + x[i]], target),
                             string(1, moves[i])));
        }

    }

    while (!pq.empty()) {
        Move *current_move = pq.top();
        pq.pop();

        player->row = current_move->newPosition->row;
        player->column = current_move->newPosition->column;

        if (player->row == target->row && player->column == target->column)
            return current_move->path;

        for (int i = 0; i < 4; i++) {
            if (is_player_move_viable(maze, maze[player->row + y[i]][player->column + x[i]])
                && !visited[player->row + y[i]][player->column + x[i]]) {
                visited[player->row + y[i]][player->column + x[i]] = true;
                pq.push(new Move(maze[player->row + y[i]][player->column + x[i]],
                                 greedy_cost(maze[player->row + y[i]][player->column + x[i]], target),
                                 current_move->path + moves[i]));
            }
        }

        delete current_move;
    }

    return "ERROR";
}

bool is_box_move_viable(Coordinate ***maze, Coordinate *position, int move) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column]->type != WALL &&
           !vector_contains(boxes, maze[position->row][position->column]) &&
           position->row + y[move] >= 0 && position->row + y[move] < rows &&
           position->column + x[move] >= 0 && position->column + x[move] < cols &&
           maze[position->row + y[move]][position->column + x[move]]->type != WALL &&
           !vector_contains(boxes, maze[position->row + y[move]][position->column + x[move]]);
}

void change_player_position(Coordinate *player, Coordinate *position) {
    player->row = position->row;
    player->column = position->column;
}

string solve(Coordinate ***maze, Coordinate *player, Coordinate *target, Coordinate *box) {
    if (vector_contains(boxes, target))
        return "";

    priority_queue<Move *, vector<Move *>, CompareMove> pq;
    bool visited[rows][cols][4];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < 4; k++) {
                if (maze[i][j]->type == WALL)
                    visited[i][j][k] = true;
                else
                    visited[i][j][k] = false;
            }
        }

    }

    for (int i = 0; i < 4; i++) {
        if (is_box_move_viable(maze, maze[box->row + y[i]][box->column + x[i]], i)) {

            auto boxPlayer = new Coordinate(player);
            string playerPath = find_path(maze, boxPlayer, maze[box->row + y[i]][box->column + x[i]]);

            if (playerPath != "ERROR") {
                pq.push(new Move(maze[box->row + y[i]][box->column + x[i]], boxPlayer,
                                 greedy_cost(maze[box->row + y[i]][box->column + x[i]], target),
                                 playerPath + (char) toupper(moves[i]), i));
            }
        }

    }

    while (!pq.empty()) {
        Move *current_move = pq.top();
        pq.pop();

        box->row = current_move->newPosition->row;
        box->column = current_move->newPosition->column;
        change_player_position(current_move->playerPosition,
                               maze[current_move->newPosition->row + y[current_move->move]][
                                       current_move->newPosition->column + x[current_move->move]]);

        if (box->row == target->row && box->column == target->column) {
            player->row = current_move->playerPosition->row;
            player->column = current_move->playerPosition->column;
            return current_move->path;
        }

        for (int i = 0; i < 4; i++) {
            if (!visited[box->row + y[i]][box->column + x[i]][i] &&
                is_box_move_viable(maze, maze[box->row + y[i]][box->column + x[i]], i)) {

                auto boxPlayer = new Coordinate(current_move->playerPosition);
                string playerPath = find_path(maze, boxPlayer, maze[box->row + y[i]][box->column + x[i]]);

                if (playerPath != "ERROR") {
                    visited[box->row + y[i]][box->column + x[i]][i] = true;
                    pq.push(new Move(maze[box->row + y[i]][box->column + x[i]], boxPlayer,
                                     greedy_cost(maze[box->row + y[i]][box->column + x[i]], target),
                                     current_move->path + playerPath + (char) toupper(moves[i]), i));
                }
            }

        }

        delete current_move->playerPosition;
        delete current_move;
    }

    return "";
}

string solve_multiple(Coordinate ***maze, Coordinate *player, vector<Coordinate *> targets) {
    vector<int> box_perms;
    for (int i = 0; i < targets.size(); i++) {
        box_perms.push_back(i);
    }
    do {
        vector<int> target_perms;
        for (int i = 0; i < targets.size(); i++) {
            target_perms.push_back(i);
        }
        do {
            string result;
            string tmp;
            auto *tmp_player = new Coordinate(player);
            vector<Coordinate *> tmp_boxes;
            for (auto box: boxes) {
                tmp_boxes.push_back(new Coordinate(box));
            }
            for (int i = 0; i < targets.size(); i++) {
//                cout << "BOXES: ";
//                for (auto box: boxes) {
//                    cout << "(" << box->row << "," << box->column << ") ";
//                }
//                cout << "Player (" << tmp_player->row << "," << tmp_player->column << ") ";
//                cout << "Box (" << boxes[box_perms[i]]->row << "," << boxes[box_perms[i]]->column << ") ";
//                cout << "Target (" << targets[box_perms[i]]->row << "," << targets[box_perms[i]]->column << ")\n";
                if (!(tmp = solve(maze, tmp_player, targets[box_perms[i]], boxes[box_perms[i]])).empty()) {
                    //cout << "Possible\n";
                    result += tmp;
                    if (i == targets.size() - 1) {
                        return result;
                    }
                } else
                    break;
            }
            boxes = tmp_boxes;
        } while (next_permutation(target_perms.begin(), target_perms.end()));
    } while (next_permutation(box_perms.begin(), box_perms.end()));

    return "lllllllllllll";
}

int main(int argc, char *argv[]) {
    ifstream infile(argv[1]);
    infile >> rows >> cols;
    infile.ignore();

    Coordinate *player;
    vector<Coordinate *> targets;
    auto ***maze = new Coordinate **[rows];

    for (int i = 0; i < rows; i++) {
        maze[i] = new Coordinate *[cols];
        string tmp;
        getline(infile, tmp);
        for (int j = 0; j < cols; j++) {
            maze[i][j] = new Coordinate(i, j, tmp[j]);
            if (tmp[j] == BOX)
                boxes.push_back(new Coordinate(i, j, tmp[j]));
            else if (tmp[j] == TARGET)
                targets.push_back(new Coordinate(i, j, tmp[j]));
            else if (tmp[j] == PLAYER)
                player = new Coordinate(i, j, tmp[j]);
        }
    }
    cout << solve_multiple(maze, player, targets) << endl;

    for (int i = 0; i < rows; i++)
        delete maze[i];
    delete[] maze;
    delete player;
    for (auto target: targets)
        delete target;
    for (auto box: boxes)
        delete box;
}