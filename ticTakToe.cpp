// Tic-Tac-Toe Game in C++
#include <iostream>
#include <ctime>

void drawBoard(char *spaces);
void playerMove(char *spaces, char player);
void compMove(char *spaces, char comp);
bool checkWinner(char *spaces, char player, char comp, int &playerWins, int &compWins);
bool checkTie(char *spaces, int &ties);
void resetBoard(char *spaces);
bool askReplay();
void displayScoreboard(int playerWins, int compWins, int ties);

int main() {
    char spaces[9];
    char player = 'X';
    char comp = 'O';
    int playerWins = 0, compWins = 0, ties = 0;
    bool playAgain;

    std::cout << "=== Welcome to Tic-Tac-Toe ===\n";
    std::cout << "You're playing as 'X'. The computer is 'O'.\n";

    do {
        resetBoard(spaces);
        bool running = true;
        drawBoard(spaces);

        while (running) {
            playerMove(spaces, player);
            drawBoard(spaces);
            if (checkWinner(spaces, player, comp, playerWins, compWins) || checkTie(spaces, ties)) break;
            compMove(spaces, comp);
            drawBoard(spaces);
            if(checkWinner(spaces, player, comp, playerWins, compWins) || checkTie(spaces, ties)) break;
        }

        displayScoreboard(playerWins, compWins, ties);
        playAgain = askReplay();

    } while (playAgain);

    std::cout << "Thanks for playing!\n";
    return 0;
}

void drawBoard(char *spaces) {
    std::cout << "\n";
    for (int i = 0; i < 9; i += 3) {
        std::cout << " " << spaces[i] << " | " << spaces[i + 1] << " | " << spaces[i + 2] << " \n";
        if (i < 6) std::cout << "---|---|---\n";
    }
    std::cout << "\n";
}

void playerMove(char *spaces, char player) {
    int number;
    while (true) {
        std::cout << "Choose a spot (1-9): ";
        std::cin >> number;

        if (std::cin.fail() || number < 1 || number > 9) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        number--;
        if (spaces[number] == ' ') {
            spaces[number] = player;
            break;
        } else {
            std::cout << "That spot is taken. Try another.\n";
        }
    }
}

void compMove(char *spaces, char comp) {
    int number;
    srand(static_cast<unsigned int>(time(0)));
    while (true) {
        number = rand() % 9;
        if (spaces[number] == ' ') {
            spaces[number] = comp;
            std::cout << "Computer chooses spot " << number + 1 << "\n";
            break;
        }
    }
}

bool checkWinner(char *spaces, char player, char comp, int &playerWins, int &compWins) {
    int winPatterns[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // columns
        {0,4,8}, {2,4,6}           // diagonals
    };

    for (auto& pattern : winPatterns) {
        if (spaces[pattern[0]] != ' ' &&
            spaces[pattern[0]] == spaces[pattern[1]] &&
            spaces[pattern[1]] == spaces[pattern[2]]) {
            
            if (spaces[pattern[0]] == player) {
                std::cout << "ðŸŽ‰ You win!\n";
                playerWins++;
            } else {
                std::cout << "ðŸ’» Computer wins!\n";
                compWins++;
            }
            return true;
        }
    }
    return false;
}

bool checkTie(char *spaces, int &ties) {
    for (int i = 0; i < 9; ++i)
        if (spaces[i] == ' ')
            return false;
    
    std::cout << "ðŸ˜ It's a tie!\n";
    ties++;
    return true;
}

void resetBoard(char *spaces) {
    for (int i = 0; i < 9; ++i)
        spaces[i] = ' ';
}

bool askReplay() {
    char choice;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

void displayScoreboard(int playerWins, int compWins, int ties) {
    std::cout << "\n=== Scoreboard ===\n";
    std::cout << "You: " << playerWins << "\n";
    std::cout << "Computer: " << compWins << "\n";
    std::cout << "Ties: " << ties << "\n";
    std::cout << "==================\n\n";
}


