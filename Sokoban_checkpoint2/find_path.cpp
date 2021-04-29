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
int xxx = 0;
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

struct Move {
    Coordinate *newPosition{};
    Coordinate *playerPosition{};
    int cost{};
    char move{};
    bool isViable{};
    string path;

    Move(Coordinate *newPosition, int cost, char move, string path)
            : newPosition(newPosition), cost(xxx++),
              move(move),
              isViable(false), path(std::move(path)) {}

    Move(Coordinate *newPosition, Coordinate *playerPosition, int cost, char move, string path)
            : newPosition(newPosition), playerPosition(playerPosition), cost(xxx++),
              move(move),
              isViable(false), path(std::move(path)) {}

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

bool is_player_move_viable(Coordinate ***maze, Coordinate *position) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column]->type != WALL &&
           maze[position->row][position->column]->type != BOX;
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
                             moves[i], string(1, moves[i])));
        }

    }

    while (!pq.empty()) {
        Move *current_move = pq.top();
        pq.pop();

        visited[player->row][player->column] = true;
        player->row = current_move->newPosition->row;
        player->column = current_move->newPosition->column;

        if (player->row == target->row && player->column == target->column)
            return current_move->path;

        for (int i = 0; i < 4; i++) {
            if (is_player_move_viable(maze, maze[player->row + y[i]][player->column + x[i]])
                && !visited[player->row + y[i]][player->column + x[i]]) {
                pq.push(new Move(maze[player->row + y[i]][player->column + x[i]],
                                 greedy_cost(maze[player->row + y[i]][player->column + x[i]], target),
                                 moves[i], current_move->path + moves[i]));
            }
        }

        delete current_move;
    }

    return "ERROR";
}

Coordinate *player;
Coordinate *target;
Coordinate *box;


int main() {
    cin >> rows >> cols;
    cin.ignore();
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
    cout << find_path(maze, player, target);
    cout << endl << find_path(maze, target, player);

    for (int i = 0; i < rows; i++)
        delete maze[i];
    delete[] maze;
}