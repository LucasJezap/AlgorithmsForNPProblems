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
};

Coordinate *box;

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

int greedy_cost(Coordinate *position, Coordinate *goal) {
    return abs(position->row - goal->row) + abs(position->column - goal->column);
}

bool is_player_move_viable(Coordinate ***maze, Coordinate *position) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column]->type != WALL &&
           (maze[position->row][position->column]->row != box->row
            || maze[position->row][position->column]->column != box->column);
}

string
find_path_resursive(Coordinate ***maze, bool **visited, Move *current_move, Coordinate *player, Coordinate *target) {
    visited[player->row][player->column] = true;
    player->row = current_move->newPosition->row;
    player->column = current_move->newPosition->column;

    if (player->row == target->row && player->column == target->column)
        return current_move->path;

    vector<Move *> current_moves;
    for (int i = 0; i < 4; i++) {
        if (is_player_move_viable(maze, maze[player->row + y[i]][player->column + x[i]])
            && !visited[player->row + y[i]][player->column + x[i]]) {
            current_moves.push_back(new Move(maze[player->row + y[i]][player->column + x[i]],
                                             greedy_cost(
                                                     maze[player->row + y[i]][player->column +
                                                                              x[i]], target),
                                             current_move->path + moves[i]));
        }
    }
    sort(current_moves.begin(), current_moves.end(),
         [](const Move *m1, const Move *m2) {
             return m1->cost < m2->cost;
         });

    for (Move *move: current_moves) {
        string path = find_path_resursive(maze, visited, move, player, target);
        if (path != "ERROR")
            return path;
    }

    delete current_move;
    return "ERROR";
}

string find_path(Coordinate ***maze, Coordinate *player, Coordinate *target) {
    if (player->row == target->row && player->column == target->column)
        return "";

    bool **visited = new bool *[rows];
    for (int i = 0; i < rows; i++) {
        visited[i] = new bool[cols];
        for (int j = 0; j < cols; j++) {
            if (maze[i][j]->type == WALL)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }
    }

    vector<Move *> initial_moves;
    for (int i = 0; i < 4; i++) {
        if (is_player_move_viable(maze, maze[player->row + y[i]][player->column + x[i]])) {
            initial_moves.push_back(new Move(maze[player->row + y[i]][player->column + x[i]],
                                             greedy_cost(maze[player->row + y[i]][player->column + x[i]], target),
                                             string(1, moves[i])));
        }
    }

    sort(initial_moves.begin(), initial_moves.end(),
         [](const Move *m1, const Move *m2) {
             return m1->cost < m2->cost;
         });

    for (Move *move: initial_moves) {
        string path = find_path_resursive(maze, visited, move, player, target);
        if (path != "ERROR")
            return path;
    }

    return "ERROR";
}

bool is_box_move_viable(Coordinate ***maze, Coordinate *position, int move) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column]->type != WALL &&
           position->row + y[move] >= 0 && position->row + y[move] < rows &&
           position->column + x[move] >= 0 && position->column + x[move] < cols &&
           maze[position->row + y[move]][position->column + x[move]]->type != WALL;
}

void change_player_position(Coordinate *player, Coordinate *position) {
    player->row = position->row;
    player->column = position->column;
}

int xxx = 0;

string
solve_resursive(Coordinate ***maze, bool ***visited, Move *current_move, Coordinate *target) {
    box->row = current_move->newPosition->row;
    box->column = current_move->newPosition->column;
    change_player_position(current_move->playerPosition,
                           maze[current_move->newPosition->row + y[current_move->move]][
                                   current_move->newPosition->column + x[current_move->move]]);

    if (box->row == target->row && box->column == target->column) {
        return current_move->path;
    }

    vector<Move *> current_moves;
    for (int i = 0; i < 4; i++) {
        if (!visited[box->row + y[i]][box->column + x[i]][i] &&
            is_box_move_viable(maze, maze[box->row + y[i]][box->column + x[i]], i)) {
            auto boxPlayer = new Coordinate(current_move->playerPosition);
            string playerPath = find_path(maze, boxPlayer, maze[box->row + y[i]][box->column + x[i]]);

            if (playerPath != "ERROR") {
                visited[box->row + y[i]][box->column + x[i]][i] = true;
                current_moves.push_back(new Move(maze[box->row + y[i]][box->column + x[i]], boxPlayer,
                                                 greedy_cost(maze[box->row + y[i]][box->column + x[i]], target),
                                                 current_move->path + playerPath + (char) toupper(moves[i]), i));
            }
        }
    }

    sort(current_moves.begin(), current_moves.end(),
         [](const Move *m1, const Move *m2) {
             return m1->cost < m2->cost;
         });

    for (Move *move: current_moves) {
        string path = solve_resursive(maze, visited, move, target);
        if (path != "ERROR")
            return path;
    }

    delete current_move->playerPosition;
    delete current_move;

    return "ERROR";
}

string solve(Coordinate ***maze, Coordinate *player, Coordinate *target) {
    if (box->row == target->row && box->column == target->column)
        return "";

    bool ***visited = new bool **[rows];

    for (int i = 0; i < rows; i++) {
        visited[i] = new bool *[cols];
        for (int j = 0; j < cols; j++) {
            visited[i][j] = new bool[4];
            for (int k = 0; k < 4; k++) {
                if (maze[i][j]->type == WALL)
                    visited[i][j][k] = true;
                else
                    visited[i][j][k] = false;
            }
        }

    }

    vector<Move *> initial_moves;
    for (int i = 0; i < 4; i++) {
        if (is_box_move_viable(maze, maze[box->row + y[i]][box->column + x[i]], i)) {

            auto boxPlayer = new Coordinate(player);
            string playerPath = find_path(maze, boxPlayer, maze[box->row + y[i]][box->column + x[i]]);

            if (playerPath != "ERROR") {
                initial_moves.push_back(new Move(maze[box->row + y[i]][box->column + x[i]], boxPlayer,
                                                 greedy_cost(maze[box->row + y[i]][box->column + x[i]], target),
                                                 playerPath + (char) toupper(moves[i]), i));
            }
        }

    }

    sort(initial_moves.begin(), initial_moves.end(),
         [](const Move *m1, const Move *m2) {
             return m1->cost < m2->cost;
         });

    for (Move *move: initial_moves) {
        string path = solve_resursive(maze, visited, move, target);
        if (path != "ERROR")
            return path;
    }

    return "ERROR";
}


int main() {
    cin >> rows >> cols;
    cin.ignore();

    Coordinate *player;
    Coordinate *target;
    auto ***maze = new Coordinate **[rows];

    for (int i = 0; i < rows; i++) {
        maze[i] = new Coordinate *[cols];
        string tmp;
        getline(cin, tmp);
        for (int j = 0; j < cols; j++) {
            maze[i][j] = new Coordinate(i, j, tmp[j]);
            if (tmp[j] == BOX)
                box = new Coordinate(i, j, tmp[j]);
            else if (tmp[j] == TARGET)
                target = new Coordinate(i, j, tmp[j]);
            else if (tmp[j] == PLAYER)
                player = new Coordinate(i, j, tmp[j]);
        }
    }

    cout << solve(maze, player, target) << endl;

    for (int i = 0; i < rows; i++)
        delete maze[i];
    delete[] maze;
    delete player;
    delete target;
    delete box;
}