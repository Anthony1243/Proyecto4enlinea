#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int numRows, numCols;

void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<char>> initializeBoard() {
    vector<vector<char>> board(numRows, vector<char>(numCols, ' '));
    return board;
}

bool checkWin(const vector<vector<char>>& board, char player) {
    // Verifica victoria en líneas horizontales
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col <= numCols - 4; col++) {
            bool win = true;
            for (int k = 0; k < 4; k++) {
                if (board[row][col + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    // Verifica victoria en líneas verticales
    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row <= numRows - 4; row++) {
            bool win = true;
            for (int k = 0; k < 4; k++) {
                if (board[row + k][col] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    // Verifica victoria en diagonal (izquierda a derecha)
    for (int row = 0; row <= numRows - 4; row++) {
        for (int col = 0; col <= numCols - 4; col++) {
            bool win = true;
            for (int k = 0; k < 4; k++) {
                if (board[row + k][col + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    // Verifica victoria en diagonal (derecha a izquierda)
    for (int row = 0; row <= numRows - 4; row++) {
        for (int col = 3; col < numCols; col++) {
            bool win = true;
            for (int k = 0; k < 4; k++) {
                if (board[row + k][col - k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }
    }

    return false;
}

bool isBoardFull(const vector<vector<char>>& board) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (board[i][j] == ' ') {
                return false; // El tablero no está lleno
            }
        }
    }
    return true; // El tablero está lleno
}

bool isValidMove(const vector<vector<char>>& board, int col) {
    // Verifica si la columna está dentro de los límites y no está llena
    return col >= 0 && col < numCols && board[0][col] == ' ';
}

void makeMove(vector<vector<char>>& board, int col, char player) {
    // Encuentra la fila disponible en la columna y coloca la ficha del jugador
    for (int row = numRows - 1; row >= 0; row--) {
        if (board[row][col] == ' ') {
            board[row][col] = player;
            break;
        }
    }
}

int getRandomMove(const vector<vector<char>>& board) {
    // Genera un movimiento aleatorio válido
    vector<int> validMoves;
    for (int col = 0; col < numCols; col++) {
        if (isValidMove(board, col)) {
            validMoves.push_back(col);
        }
    }

    if (!validMoves.empty()) {
        int randomIndex = rand() % validMoves.size();
        return validMoves[randomIndex];
    }

    return -1; // No hay movimientos válidos
}

int main() {
    cout << "Ingresa el numero de filas del tablero: ";
    cin >> numRows;
    cout << "Ingresa el numero de columnas del tablero: ";
    cin >> numCols;

    vector<vector<char>> board = initializeBoard();
    char currentPlayer = 'X';

    cout << "¿Deseas jugar contra una IA? (y/n): ";
    char playAgainstAI;
    cin >> playAgainstAI;

    while (true) {
        cout << "Tablero actual:" << endl;
        printBoard(board);

        if (checkWin(board, 'X')) {
            cout << "¡El jugador X ha ganado!" << endl;
            break;
        } else if (checkWin(board, 'O')) {
            if (playAgainstAI == 'y') {
                cout << "¡El jugador O ha ganado!" << endl;
            } else {
                cout << "¡La IA ha ganado!" << endl;
            }
            break;
        } else if (isBoardFull(board)) {
            cout << "¡Empate!" << endl;
            break;
        }

        cout << "Turno del jugador " << currentPlayer << endl;
        int col;

        if ((playAgainstAI == 'y' && currentPlayer == 'O') || playAgainstAI == 'n') {
            cout << "Ingresa el numero de columna (0-" << numCols - 1 << ") para tu movimiento: ";
            cin >> col;
        } else {
            col = getRandomMove(board);
            cout << "La IA ha elegido la columna " << col << endl;
        }

        if (isValidMove(board, col)) {
            makeMove(board, col, currentPlayer);
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            cout << "Movimiento no valido. Inténtalo de nuevo." << endl;
        }
    }

    return 0;
}