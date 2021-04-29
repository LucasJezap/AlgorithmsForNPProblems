#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <utility>

#define WALL '#'
#define BOX 'O'
#define TARGET '*'
#define PLAYER '-'
#define EMPTY ' '

using namespace std;

int rows, cols;

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

    Coordinate(int row, int column) {
        this->row = row;
        this->column = column;
    }

    Coordinate() = default;

    bool operator==(const Coordinate &other) const {
        return (row == other.row && column == other.column);
    }

};

struct Move {
    Coordinate newPosition;
    Coordinate playerPosition;
    int cost{};
    char move{};
    bool isViable{};
    string path;

    Move(const Coordinate &newPosition, int cost, char move, string path)
            : newPosition(newPosition), cost(cost),
              move(move),
              isViable(false), path(std::move(path)) {}

    Move(const Coordinate &newPosition, const Coordinate &playerPosition, int cost, char move, string path)
            : newPosition(newPosition), playerPosition(playerPosition), cost(cost),
              move(move),
              isViable(false), path(std::move(path)) {}

    explicit Move(const Coordinate &playerPosition)
            : playerPosition(playerPosition) {}

    Move() = default;
};

bool operator<(const Move &m1, const Move &m2) {
    return m1.cost > m2.cost;
}

int greedy_cost(Coordinate position, Coordinate goal) {
    return abs(position.row - goal.row) + abs(position.column - goal.column);
}

Coordinate box;

bool is_player_move_viable(Coordinate **maze, Coordinate *position) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column].type != WALL &&
           maze[position->row][position->column].type != BOX;
}

vector<Move>
generate_all_player_moves(const Move &currentMove, Coordinate **maze, Coordinate position, Coordinate target) {
    int x[] = {-1, 0, 1, 0};
    int y[] = {0, -1, 0, 1};
    char moves[] = {'l', 'u', 'r', 'd'};
    vector<Move> all_moves(4);

    for (int i = 0; i < 4; i++) {
        Coordinate newPosition = *new Coordinate(position.row + y[i], position.column + x[i]);
        all_moves[i] = *new Move(newPosition, greedy_cost(newPosition, target), moves[i], currentMove.path + moves[i]);
        if (is_player_move_viable(maze, &newPosition)) {
            all_moves[i].isViable = true;
        }
    }

    return all_moves;
}

string find_path(Coordinate **maze, Coordinate *player, Coordinate target) {
    priority_queue<Move> pq;
    bool visited[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (maze[i][j].type == WALL)
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }

    }
    vector<Move> initialMoves = generate_all_player_moves(*new Move(), maze, *player, target);
    for (const Move &move: initialMoves) {
        if (move.isViable)
            pq.push(move);
    }

    while (!pq.empty()) {
        Move current_move = pq.top();
        pq.pop();

        visited[player->row][player->column] = true;
        player->row = current_move.newPosition.row;
        player->column = current_move.newPosition.column;

        if (player->row == target.row && player->column == target.column)
            return current_move.path;

        vector<Move> moves = generate_all_player_moves(current_move, maze, *player, target);
        for (const Move &move: moves) {
            if (move.isViable && !visited[move.newPosition.row][move.newPosition.column])
                pq.push(move);
        }
    }

    return "";
}

Coordinate target;
Coordinate player;

bool is_box_move_viable(Coordinate **maze, Coordinate *position, Coordinate *nextPosition) {
    return position->row >= 0 && position->row < rows &&
           position->column >= 0 && position->column < cols &&
           maze[position->row][position->column].type != WALL &&
           nextPosition->row >= 0 && nextPosition->row < rows &&
           nextPosition->column >= 0 && nextPosition->column < cols &&
           maze[nextPosition->row][nextPosition->column].type != WALL;
}


vector<Move> generate_all_box_moves(const Move &currentMove, Coordinate **maze, Coordinate position) {
    int x[] = {-1, 0, 1, 0};
    int y[] = {0, -1, 0, 1};
    char moves[] = {'L', 'U', 'R', 'D'};
    vector<Move> all_moves(4);

    for (int i = 0; i < 4; i++) {
        Coordinate newPosition = *new Coordinate(position.row + y[i], position.column + x[i]);
        Coordinate newPosition2 = *new Coordinate(position.row + 2 * y[i], position.column + 2 * x[i]);
        all_moves[i] = *new Move(newPosition, currentMove.playerPosition,
                                 greedy_cost(newPosition, target), moves[i],
                                 currentMove.path + moves[i]);
        if (is_box_move_viable(maze, &newPosition, &newPosition2)) {
            all_moves[i].isViable = true;
        }
    }

    return all_moves;
}

void change_player_position(Move &currentMove) {
    switch (currentMove.move) {
        case 'L': {
            currentMove.playerPosition.column -= 1;
            break;
        }
        case 'R': {
            currentMove.playerPosition.column += 1;
            break;
        }
        case 'U': {
            currentMove.playerPosition.row -= 1;
            break;
        }
        case 'D': {
            currentMove.playerPosition.row += 1;
            break;
        }
        default: {
        }
    }
}

string solve(Coordinate **maze) {
    priority_queue<Move> pq;
    bool visited[rows][cols];
    string beginning;

    if (maze[box.row + 1][box.column].type != WALL) {
        beginning = find_path(maze, &player, *new Coordinate(box.row + 1, box.column));
    } else if (maze[box.row - 1][box.column].type != WALL) {
        beginning = find_path(maze, &player, *new Coordinate(box.row - 1, box.column));
    } else if (maze[box.row][box.column + 1].type != WALL) {
        beginning = find_path(maze, &player, *new Coordinate(box.row, box.column + 1));
    } else {
        beginning = find_path(maze, &player, *new Coordinate(box.row, box.column - 1));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            visited[i][j] = false;
            if (maze[i][j].type == WALL)
                visited[i][j] = false;
            else
                visited[i][j] = false;
        }

    }

    vector<Move> initialMoves = generate_all_box_moves(*new Move(player), maze, box);
    for (const Move &move: initialMoves) {
        if (move.isViable)
            pq.push(move);
    }

    while (!pq.empty()) {
        Move current_move = pq.top();
        pq.pop();

        if (current_move.playerPosition.row != current_move.newPosition.row ||
            current_move.playerPosition.column != current_move.newPosition.column) {
            current_move.path.insert(current_move.path.size() - 1,
                                     find_path(maze, &current_move.playerPosition, current_move.newPosition));
        }

        visited[box.row][box.column] = true;
        maze[box.row][box.column].type = EMPTY;
        change_player_position(current_move);
        box.row = current_move.newPosition.row;
        box.column = current_move.newPosition.column;
        maze[box.row][box.column].type = BOX;

        if (box.row == target.row && box.column == target.column)
            return beginning + current_move.path;

        vector<Move> moves = generate_all_box_moves(current_move, maze, box);
        for (const Move &move: moves) {
            if (move.isViable && !visited[move.newPosition.row][move.newPosition.column]) {
                pq.push(move);
            }
        }
    }

    return "";
}

int main() {
    cin >> rows >> cols;
    cin.ignore();
    auto **maze = new Coordinate *[rows];
    for (int i = 0; i < rows; i++) {
        maze[i] = new Coordinate[cols];
        string tmp;
        getline(cin, tmp);
        for (int j = 0; j < cols; j++) {
            maze[i][j] = *new Coordinate(i, j, tmp[j]);
            if (tmp[j] == BOX)
                box = *new Coordinate(i, j, tmp[j]);
            else if (tmp[j] == TARGET)
                target = *new Coordinate(i, j, tmp[j]);
            else if (tmp[j] == PLAYER)
                player = *new Coordinate(i, j, tmp[j]);
        }
    }
    cout << solve(maze);
}