#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

class PlayWareHub {
private:
    vector<string> wordle_words = {"APPLE", "BRAVE", "CHAIR", "DRIVE", "EARTH", "FOCUS", "GRACE", "HEART", "LIGHT", "MAGIC"};
    vector<string> hangman_words = {"COMPUTER", "ELEPHANT", "RAINBOW", "JOURNEY", "FREEDOM", "MYSTERY", "ADVENTURE", "KEYBOARD", "SANDWICH", "TELEPHONE"};
    vector<string> contexto_words = {"WATER", "MUSIC", "HAPPY", "DREAM", "SPACE", "HOUSE", "QUICK", "MONEY", "SMILE", "PEACE"};
    
    // Mad Libs templates
    vector<vector<string>> madlib_templates = {
        {"The", "ADJECTIVE", "cat", "VERB", "over the", "NOUN", "and", "ADVERB", "landed on a", "ADJECTIVE", "NOUN"},
        {"I", "ADVERB", "VERB", "to the", "NOUN", "where I met a", "ADJECTIVE", "PERSON", "who was", "VERB", "a", "NOUN"},
        {"Yesterday, I", "VERB", "my", "ADJECTIVE", "NOUN", "and it", "ADVERB", "VERB", "into a", "ADJECTIVE", "NOUN"},
        {"The", "ADJECTIVE", "PERSON", "ADVERB", "VERB", "through the", "NOUN", "carrying a", "ADjective", "NOUN", "full of", "PLURAL_NOUN"}
    };
    
    // Would You Rather questions
    vector<pair<string, string>> wyr_questions = {
        {"Have the ability to fly", "Have the ability to become invisible"},
        {"Always be 10 minutes late", "Always be 20 minutes early"},
        {"Live without music", "Live without movies"},
        {"Have super strength", "Have super speed"},
        {"Always speak your mind", "Never speak again"},
        {"Be able to read minds", "Be able to predict the future"},
        {"Live in a world without colors", "Live in a world without sounds"},
        {"Have unlimited money", "Have unlimited time"},
        {"Always be too hot", "Always be too cold"},
        {"Fight 100 duck-sized horses", "Fight 1 horse-sized duck"}
    };
    
    mt19937 rng;
    
public:
    PlayWareHub() : rng(time(nullptr)) {}
    
    void displayLogo() {
        cout << "\n";
        cout << "========================================================================\n";
        cout << "                      P L A Y W A R E   H U B\n";
        cout << "========================================================================\n";
        cout << "\n                    Your Ultimate Gaming Hub!\n\n";
    }
    
    void displayMenu() {
        cout << "\n[Game] GAME MENU [Game]\n";
        cout << "================\n";
        cout << "1. Wordle\n";
        cout << "2. Hangman (Lives System)\n";
        cout << "3. Tic Tac Toe\n";
        cout << "4. Rock Paper Scissors\n";
        cout << "5. Contexto\n";
        cout << "6. Mad Libs\n";
        cout << "7. Number Guessing\n";
        cout << "8. Would You Rather\n";
        cout << "9. Reversi\n";
        cout << "10. Snake\n";
        cout << "11. Pong\n";
        cout << "12. Exit\n";
        cout << "\nChoose a game (1-12): ";
    }
    
    void playWordle() {
        string word = wordle_words[rng() % wordle_words.size()];
        string guess;
        int attempts = 6;
        vector<string> guesses;
        
        cout << "\n[Target] WORDLE [Target]\n";
        cout << "=============\n";
        cout << "Guess the 5-letter word! You have 6 attempts.\n";
        cout << "[Green] = Correct letter in correct position\n";
        cout << "[Yellow] = Correct letter in wrong position\n";
        cout << "[Gray] = Letter not in word\n\n";
        
        while (attempts > 0) {
            cout << "Attempts left: " << attempts << "\n";
            cout << "Enter your guess: ";
            cin >> guess;
            
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
            
            if (guess.length() != 5) {
                cout << "Please enter a 5-letter word!\n";
                continue;
            }
            
            guesses.push_back(guess);
            
            if (guess == word) {
                cout << "\n(Hooray!) Congratulations! You guessed it: " << word << "\n";
                cout << "You won in " << (7 - attempts) << " attempts!\n";
                return;
            }
            
            // Display feedback
            string feedback = "";
            for (int i = 0; i < 5; i++) {
                if (guess[i] == word[i]) {
                    feedback += "[Green]";
                } else if (word.find(guess[i]) != string::npos) {
                    feedback += "[Yellow]";
                } else {
                    feedback += "[Gray]";
                }
            }
            
            cout << guess << " " << feedback << "\n";
            attempts--;
        }
        
        cout << "\n(Game Over) Game Over! The word was: " << word << "\n";
    }
    
    void playHangman() {
        string word = hangman_words[rng() % hangman_words.size()];
        string guessed(word.length(), '_');
        vector<char> wrong_letters;
        int lives = 6;
        
        cout << "\n(Hangman) HANGMAN (Hangman)\n";
        cout << "===============\n";
        cout << "Guess the word letter by letter!\n";
        cout << "You have " << lives << " lives.\n\n";
        
        while (lives > 0 && guessed != word) {
            cout << "Lives: ";
            for (int i = 0; i < lives; i++) cout << "<3 ";
            cout << "\n";
            
            cout << "Word: " << guessed << "\n";
            cout << "Wrong letters: ";
            for (char c : wrong_letters) cout << c << " ";
            cout << "\n";
            
            cout << "Enter a letter: ";
            char letter;
            cin >> letter;
            letter = toupper(letter);
            
            if (word.find(letter) != string::npos) {
                cout << "(Correct) Good guess!\n";
                for (int i = 0; i < word.length(); i++) {
                    if (word[i] == letter) {
                        guessed[i] = letter;
                    }
                }
            } else {
                cout << "(Wrong) Wrong letter!\n";
                wrong_letters.push_back(letter);
                lives--;
            }
            cout << "\n";
        }
        
        if (guessed == word) {
            cout << "(Hooray!) Congratulations! You guessed: " << word << "\n";
        } else {
            cout << "(Game Over) Game Over! The word was: " << word << "\n";
        }
    }
    
    void playTicTacToe() {
        vector<vector<char>> board(3, vector<char>(3, ' '));
        char currentPlayer = 'X';
        
        cout << "\n(O) TIC TAC TOE (O)\n";
        cout << "==================\n";
        cout << "Player X vs Player O\n";
        cout << "Enter positions as row,col (1-3)\n\n";
        
        auto displayBoard = [&]() {
            cout << "   1   2   3\n";
            for (int i = 0; i < 3; i++) {
                cout << i + 1 << "  " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
                if (i < 2) cout << "  -----------\n";
            }
            cout << "\n";
        };
        
        auto checkWin = [&](char player) {
            // Check rows, columns, and diagonals
            for (int i = 0; i < 3; i++) {
                if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                    (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
                    return true;
                }
            }
            return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
                   (board[0][2] == player && board[1][1] == player && board[2][0] == player);
        };
        
        auto isBoardFull = [&]() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') return false;
                }
            }
            return true;
        };
        
        int moves = 0;
        while (moves < 9) {
            displayBoard();
            cout << "Player " << currentPlayer << "'s turn\n";
            cout << "Enter row (1-3): ";
            int row;
            cin >> row;
            cout << "Enter column (1-3): ";
            int col;
            cin >> col;
            
            row--; col--; // Convert to 0-indexed
            
            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            
            board[row][col] = currentPlayer;
            moves++;
            
            if (checkWin(currentPlayer)) {
                displayBoard();
                cout << "(Hooray!) Player " << currentPlayer << " wins!\n";
                return;
            }
            
            if (isBoardFull()) {
                displayBoard();
                cout << "(Tie) It's a tie!\n";
                return;
            }
            
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    
    void playRockPaperScissors() {
        vector<string> choices = {"Rock", "Paper", "Scissors"};
        vector<string> text_icons = {"[Rock]", "[Paper]", "[Scissors]"};
        int playerScore = 0, computerScore = 0;
        
        cout << "\n[Rock][Paper][Scissors] ROCK PAPER SCISSORS [Scissors][Paper][Rock]\n";
        cout << "===================================\n";
        cout << "Best of 5 rounds!\n";
        cout << "1 = Rock, 2 = Paper, 3 = Scissors\n\n";
        
        while (playerScore < 3 && computerScore < 3) {
            cout << "Score - You: " << playerScore << " | Computer: " << computerScore << "\n";
            cout << "Your choice (1-3): ";
            int playerChoice;
            cin >> playerChoice;
            
            if (playerChoice < 1 || playerChoice > 3) {
                cout << "Invalid choice! Try again.\n";
                continue;
            }
            
            playerChoice--; // Convert to 0-indexed
            int computerChoice = rng() % 3;
            
            cout << "You chose: " << text_icons[playerChoice] << " " << choices[playerChoice] << "\n";
            cout << "Computer chose: " << text_icons[computerChoice] << " " << choices[computerChoice] << "\n";
            
            if (playerChoice == computerChoice) {
                cout << "(Tie) It's a tie!\n";
            } else if ((playerChoice == 0 && computerChoice == 2) ||
                      (playerChoice == 1 && computerChoice == 0) ||
                      (playerChoice == 2 && computerChoice == 1)) {
                cout << "(Hooray!) You win this round!\n";
                playerScore++;
            } else {
                cout << "(Computer) Computer wins this round!\n";
                computerScore++;
            }
            cout << "\n";
        }
        
        if (playerScore > computerScore) {
            cout << "(Trophy) You won the game! Final Score: " << playerScore << "-" << computerScore << "\n";
        } else {
            cout << "(Computer) Computer won the game! Final Score: " << computerScore << "-" << playerScore << "\n";
        }
    }
    
    void playContexto() {
        string word = contexto_words[rng() % contexto_words.size()];
        string guess;
        int attempts = 8;
        vector<string> guesses;
        
        cout << "\n[Target] CONTEXTO [Target]\n";
        cout << "================\n";
        cout << "Guess the secret word based on context clues!\n";
        cout << "You have " << attempts << " attempts.\n";
        cout << "I'll give you hints based on how close your guess is!\n\n";
        
        // Context hints based on the word
        map<string, vector<string>> hints = {
            {"WATER", {"It's essential for life", "You drink it", "It's liquid", "Found in oceans"}},
            {"MUSIC", {"You hear it", "It has rhythm", "Made with instruments", "Can be sung"}},
            {"HAPPY", {"It's an emotion", "Opposite of sad", "Makes you smile", "Positive feeling"}},
            {"DREAM", {"Happens when you sleep", "Can be about the future", "Sometimes scary", "In your mind"}},
            {"SPACE", {"It's vast", "Contains stars", "Astronauts go there", "Above Earth"}},
            {"HOUSE", {"You live in it", "Has rooms", "Provides shelter", "Has a door"}},
            {"QUICK", {"It's fast", "Opposite of slow", "Rapid movement", "Speedy"}},
            {"MONEY", {"You spend it", "Can buy things", "Currency", "In your wallet"}},
            {"SMILE", {"Expression of joy", "Shows teeth", "On your face", "When happy"}},
            {"PEACE", {"Opposite of war", "Calm and quiet", "Harmony", "No conflict"}}
        };
        
        while (attempts > 0) {
            cout << "Attempts left: " << attempts << "\n";
            
            // Give progressive hints
            int hintIndex = 8 - attempts;
            if (hintIndex < hints[word].size()) {
                cout << "(Hint) Hint: " << hints[word][hintIndex] << "\n";
            }
            
            cout << "Your guess: ";
            cin >> guess;
            transform(guess.begin(), guess.end(), guess.begin(), ::toupper);
            
            if (guess == word) {
                cout << "\n(Hooray!) Excellent! You guessed it: " << word << "\n";
                cout << "You won in " << (9 - attempts) << " attempts!\n";
                return;
            }
            
            // Give feedback based on similarity
            int similarity = 0;
            for (char c : guess) {
                if (word.find(c) != string::npos) similarity++;
            }
            
            if (similarity > word.length() / 2) {
                cout << "(Hot) Very close! You're on the right track!\n";
            } else if (similarity > 0) {
                cout << "(Warm) Some letters match, but not quite there!\n";
            } else {
                cout << "(Cold) Not close at all, try thinking differently!\n";
            }
            
            attempts--;
            cout << "\n";
        }
        
        cout << "(Game Over) Game Over! The word was: " << word << "\n";
    }
    
    void playMadLibs() {
        cout << "\n(Mad Libs) MAD LIBS (Mad Libs)\n";
        cout << "================\n";
        cout << "Fill in the blanks to create a funny story!\n\n";
        
        vector<string> template_story = madlib_templates[rng() % madlib_templates.size()];
        vector<string> user_words;
        
        cout << "I need some words from you:\n";
        cin.ignore(); // Clear the input buffer
        
        for (int i = 0; i < template_story.size(); i++) {
            if (template_story[i].find("ADJECTIVE") != string::npos ||
                template_story[i].find("NOUN") != string::npos ||
                template_story[i].find("VERB") != string::npos ||
                template_story[i].find("ADVERB") != string::npos ||
                template_story[i].find("PERSON") != string::npos ||
                template_story[i].find("PLURAL") != string::npos) {
                
                cout << "Give me a " << template_story[i] << ": ";
                string word;
                getline(cin, word);
                user_words.push_back(word);
            }
        }
        
        cout << "\n(Story) Here's your Mad Lib story:\n";
        cout << "================================\n";
        
        int word_index = 0;
        for (int i = 0; i < template_story.size(); i++) {
            if (template_story[i].find("ADJECTIVE") != string::npos ||
                template_story[i].find("NOUN") != string::npos ||
                template_story[i].find("VERB") != string::npos ||
                template_story[i].find("ADVERB") != string::npos ||
                template_story[i].find("PERSON") != string::npos ||
                template_story[i].find("PLURAL") != string::npos) {
                
                cout << user_words[word_index++];
            } else {
                cout << template_story[i];
            }
            
            if (i < template_story.size() - 1) cout << " ";
        }
        cout << "!\n\n";
        cout << "(Hooray!) Hope you enjoyed your silly story!\n";
    }
    
    void playNumberGuessing() {
        cout << "\n(Numbers) NUMBER GUESSING (Numbers)\n";
        cout << "======================\n";
        cout << "I'm thinking of a number between 1 and 100!\n";
        cout << "Can you guess it?\n\n";
        
        int secret_number = (rng() % 100) + 1;
        int attempts = 0;
        int max_attempts = 7;
        int guess;
        
        while (attempts < max_attempts) {
            cout << "Attempts left: " << (max_attempts - attempts) << "\n";
            cout << "Your guess: ";
            cin >> guess;
            attempts++;
            
            if (guess == secret_number) {
                cout << "\n(Hooray!) Congratulations! You guessed it!\n";
                cout << "The number was " << secret_number << "\n";
                cout << "You won in " << attempts << " attempts!\n";
                return;
            } else if (guess < secret_number) {
                if (secret_number - guess > 20) {
                    cout << "(Higher) Too low! Way too low!\n";
                } else if (secret_number - guess > 10) {
                    cout << "(Higher) Too low! Getting warmer though!\n";
                } else {
                    cout << "(Higher) Too low! Very close!\n";
                }
            } else {
                if (guess - secret_number > 20) {
                    cout << "(Lower) Too high! Way too high!\n";
                } else if (guess - secret_number > 10) {
                    cout << "(Lower) Too high! Getting warmer though!\n";
                } else {
                    cout << "(Lower) Too high! Very close!\n";
                }
            }
            cout << "\n";
        }
        
        cout << "(Game Over) Game Over! The number was: " << secret_number << "\n";
    }
    
    void playWouldYouRather() {
        cout << "\n(Hmm) WOULD YOU RATHER (Hmm)\n";
        cout << "========================\n";
        cout << "Choose between two scenarios!\n\n";
        
        int rounds = 5;
        vector<bool> used(wyr_questions.size(), false);
        
        for (int round = 1; round <= rounds; round++) {
            cout << "Round " << round << "/" << rounds << "\n";
            cout << "================\n";
            
            // Pick a random unused question
            int question_index;
            do {
                question_index = rng() % wyr_questions.size();
            } while (used[question_index]);
            used[question_index] = true;
            
            auto question = wyr_questions[question_index];
            
            cout << "Would you rather...\n";
            cout << "1. " << question.first << "\n";
            cout << "2. " << question.second << "\n";
            cout << "\nYour choice (1 or 2): ";
            
            int choice;
            cin >> choice;
            
            if (choice == 1) {
                cout << "(Choice) You chose: " << question.first << "\n";
            } else if (choice == 2) {
                cout << "(Choice) You chose: " << question.second << "\n";
            } else {
                cout << "(Shrug) Invalid choice! Let's say you chose option 1!\n";
            }
            
            // Add some fun responses
            vector<string> responses = {
                "Interesting choice! (Hmm)",
                "Bold decision! (Strong)",
                "I can see why you'd pick that! (Hmm)",
                "That's a tough one! (Phew)",
                "Good choice! (Good)",
                "Hmm, I might have chosen differently! (Shrug)"
            };
            
            cout << responses[rng() % responses.size()] << "\n\n";
        }
        
        cout << "(Hooray!) Thanks for playing Would You Rather!\n";
        cout << "Hope you enjoyed thinking about those scenarios!\n";
    }
    
    void playReversi() {
        vector<vector<char>> board(8, vector<char>(8, '.'));
        board[3][3] = 'W'; board[3][4] = 'B';
        board[4][3] = 'B'; board[4][4] = 'W';
        
        char currentPlayer = 'B';
        
        cout << "\n(Black)(White) REVERSI (White)(Black)\n";
        cout << "==================\n";
        cout << "Black (B) vs White (W)\n";
        cout << "Capture opponent pieces by surrounding them!\n";
        cout << "Enter moves as row,col (1-8)\n\n";
        
        auto displayBoard = [&]() {
            cout << "   1 2 3 4 5 6 7 8\n";
            for (int i = 0; i < 8; i++) {
                cout << i + 1 << "  ";
                for (int j = 0; j < 8; j++) {
                    cout << board[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        };
        
        auto isValidMove = [&](int row, int col, char player) {
            if (board[row][col] != '.') return false;
            
            char opponent = (player == 'B') ? 'W' : 'B';
            
            // Check all 8 directions
            int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
            
            for (int d = 0; d < 8; d++) {
                int dr = directions[d][0], dc = directions[d][1];
                int r = row + dr, c = col + dc;
                bool foundOpponent = false;
                
                while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                    if (board[r][c] == opponent) {
                        foundOpponent = true;
                    } else if (board[r][c] == player && foundOpponent) {
                        return true;
                    } else {
                        break;
                    }
                    r += dr;
                    c += dc;
                }
            }
            return false;
        };
        
        auto makeMove = [&](int row, int col, char player) {
            board[row][col] = player;
            char opponent = (player == 'B') ? 'W' : 'B';
            
            int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
            
            for (int d = 0; d < 8; d++) {
                int dr = directions[d][0], dc = directions[d][1];
                int r = row + dr, c = col + dc;
                vector<pair<int,int>> toFlip;
                
                while (r >= 0 && r < 8 && c >= 0 && c < 8) {
                    if (board[r][c] == opponent) {
                        toFlip.push_back({r, c});
                    } else if (board[r][c] == player && !toFlip.empty()) {
                        for (auto pos : toFlip) {
                            board[pos.first][pos.second] = player;
                        }
                        break;
                    } else {
                        break;
                    }
                    r += dr;
                    c += dc;
                }
            }
        };
        
        auto hasValidMoves = [&](char player) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (isValidMove(i, j, player)) return true;
                }
            }
            return false;
        };
        
        auto countPieces = [&]() {
            int black = 0, white = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j] == 'B') black++;
                    else if (board[i][j] == 'W') white++;
                }
            }
            return make_pair(black, white);
        };
        
        while (true) {
            displayBoard();
            auto scores = countPieces();
            cout << "Score - Black: " << scores.first << " | White: " << scores.second << "\n";
            
            if (!hasValidMoves(currentPlayer)) {
                currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
                if (!hasValidMoves(currentPlayer)) {
                    cout << "\n(Game Over) Game Over! Final Score:\n";
                    cout << "Black: " << scores.first << " | White: " << scores.second << "\n";
                    if (scores.first > scores.second) {
                        cout << "(Black) Black wins!\n";
                    } else if (scores.second > scores.first) {
                        cout << "(White) White wins!\n";
                    } else {
                        cout << "(Tie) It's a tie!\n";
                    }
                    return;
                }
            }
            
            cout << "Player " << currentPlayer << "'s turn\n";
            cout << "Enter row (1-8): ";
            int row;
            cin >> row;
            cout << "Enter column (1-8): ";
            int col;
            cin >> col;
            
            row--; col--; // Convert to 0-indexed
            
            if (row < 0 || row > 7 || col < 0 || col > 7) {
                cout << "Invalid position! Try again.\n";
                continue;
            }
            
            if (!isValidMove(row, col, currentPlayer)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            
            makeMove(row, col, currentPlayer);
            currentPlayer = (currentPlayer == 'B') ? 'W' : 'B';
        }
    }
    
    void playSnake() {
        const int WIDTH = 20, HEIGHT = 10;
        vector<vector<char>> board(HEIGHT, vector<char>(WIDTH, '.'));
        vector<pair<int,int>> snake = {{HEIGHT/2, WIDTH/2}};
        pair<int,int> food = {rng() % HEIGHT, rng() % WIDTH};
        int dx = 0, dy = 1; // Start moving right
        int score = 0;
        
        cout << "\n(Snake) SNAKE (Snake)\n";
        cout << "============\n";
        cout << "Use WASD to move! Eat food (@) to grow!\n";
        cout << "Don't hit walls or yourself!\n\n";
        
        auto displayBoard = [&]() {
            // Clear board
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    board[i][j] = '.';
                }
            }
            
            // Place snake
            for (int i = 0; i < snake.size(); i++) {
                if (i == 0) {
                    board[snake[i].first][snake[i].second] = 'O'; // Head
                } else {
                    board[snake[i].first][snake[i].second] = 'o'; // Body
                }
            }
            
            // Place food
            board[food.first][food.second] = '@';
            
            // Display board
            cout << "\nScore: " << score << "\n";
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    cout << board[i][j] << " ";
                }
                cout << "\n";
            }
        };
        
        cout << "Press Enter to start, then use W/A/S/D + Enter to move...\n";
        cin.ignore();
        cin.get();
        
        for (int moves = 0; moves < 50; moves++) { // Limit moves for console version
            displayBoard();
            
            cout << "Move (W/A/S/D): ";
            char input;
            cin >> input;
            input = toupper(input);
            
            // Update direction
            if (input == 'W' && dx != 1) { dx = -1; dy = 0; }
            else if (input == 'S' && dx != -1) { dx = 1; dy = 0; }
            else if (input == 'A' && dy != 1) { dx = 0; dy = -1; }
            else if (input == 'D' && dy != -1) { dx = 0; dy = 1; }
            
            // Move snake
            pair<int,int> newHead = {snake[0].first + dx, snake[0].second + dy};
            
            // Check wall collision
            if (newHead.first < 0 || newHead.first >= HEIGHT || 
                newHead.second < 0 || newHead.second >= WIDTH) {
                cout << "\n(Game Over) Game Over! You hit a wall!\n";
                cout << "Final Score: " << score << "\n";
                return;
            }
            
            // Check self collision
            for (auto segment : snake) {
                if (newHead == segment) {
                    cout << "\n(Game Over) Game Over! You hit yourself!\n";
                    cout << "Final Score: " << score << "\n";
                    return;
                }
            }
            
            snake.insert(snake.begin(), newHead);
            
            // Check food collision
            if (newHead == food) {
                score++;
                cout << "(Food) Yum! Score: " << score << "\n";
                // Generate new food
                do {
                    food = {rng() % HEIGHT, rng() % WIDTH};
                } while (find(snake.begin(), snake.end(), food) != snake.end());
            } else {
                snake.pop_back(); // Remove tail if no food eaten
            }
        }
        
        cout << "\n(Hooray!) Great game! Final Score: " << score << "\n";
    }
    
    void playPong() {
        const int WIDTH = 40, HEIGHT = 15;
        int paddleY = HEIGHT/2, ballX = WIDTH/2, ballY = HEIGHT/2;
        int ballDX = 1, ballDY = 1;
        int playerScore = 0, computerScore = 0;
        int computerPaddleY = HEIGHT/2;
        
        cout << "\n(Pong) PONG (Pong)\n";
        cout << "===========\n";
        cout << "Use W/S to move your paddle up/down!\n";
        cout << "First to 5 points wins!\n\n";
        
        auto displayBoard = [&]() {
            vector<vector<char>> board(HEIGHT, vector<char>(WIDTH, ' '));
            
            // Draw paddles
            for (int i = 0; i < 3; i++) {
                if (paddleY + i - 1 >= 0 && paddleY + i - 1 < HEIGHT) {
                    board[paddleY + i - 1][1] = '|';
                }
                if (computerPaddleY + i - 1 >= 0 && computerPaddleY + i - 1 < HEIGHT) {
                    board[computerPaddleY + i - 1][WIDTH-2] = '|';
                }
            }
            
            // Draw ball
            if (ballX >= 0 && ballX < WIDTH && ballY >= 0 && ballY < HEIGHT) {
                board[ballY][ballX] = 'O';
            }
            
            // Draw borders
            for (int i = 0; i < WIDTH; i++) {
                board[0][i] = '-';
                board[HEIGHT-1][i] = '-';
            }
            
            cout << "Player: " << playerScore << " | Computer: " << computerScore << "\n";
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    cout << board[i][j];
                }
                cout << "\n";
            }
        };
        
        cout << "Press Enter to start, then use W/S + Enter to move...\n";
        cin.ignore();
        cin.get();
        
        while (playerScore < 5 && computerScore < 5) {
            displayBoard();
            
            cout << "Move (W/S): ";
            char input;
            cin >> input;
            input = toupper(input);
            
            // Update player paddle
            if (input == 'W' && paddleY > 1) paddleY--;
            else if (input == 'S' && paddleY < HEIGHT-2) paddleY++;
            
            // Move ball
            ballX += ballDX;
            ballY += ballDY;
            
            // Ball collision with top/bottom walls
            if (ballY <= 0 || ballY >= HEIGHT-1) {
                ballDY = -ballDY;
            }
            
            // Ball collision with paddles
            if (ballX == 2 && ballY >= paddleY-1 && ballY <= paddleY+1) {
                ballDX = -ballDX;
            }
            if (ballX == WIDTH-3 && ballY >= computerPaddleY-1 && ballY <= computerPaddleY+1) {
                ballDX = -ballDX;
            }
            
            // Scoring
            if (ballX < 0) {
                computerScore++;
                cout << "(Computer) Computer scores!\n";
                ballX = WIDTH/2; ballY = HEIGHT/2;
                ballDX = 1; ballDY = (rng() % 2) ? 1 : -1;
            } else if (ballX >= WIDTH) {
                playerScore++;
                cout << "(Hooray!) You score!\n";
                ballX = WIDTH/2; ballY = HEIGHT/2;
                ballDX = -1; ballDY = (rng() % 2) ? 1 : -1;
            }
            
            // Simple AI for computer paddle
            if (ballY < computerPaddleY && computerPaddleY > 1) {
                computerPaddleY--;
            } else if (ballY > computerPaddleY && computerPaddleY < HEIGHT-2) {
                computerPaddleY++;
            }
        }
        
        displayBoard();
        if (playerScore > computerScore) {
            cout << "(Trophy) You won! Final Score: " << playerScore << "-" << computerScore << "\n";
        } else {
            cout << "(Computer) Computer won! Final Score: " << computerScore << "-" << playerScore << "\n";
        }
    }
    
    void run() {
        displayLogo();
        
        while (true) {
            displayMenu();
            int choice;
            cin >> choice;
            
            switch (choice) {
                case 1:
                    playWordle();
                    break;
                case 2:
                    playHangman();
                    break;
                case 3:
                    playTicTacToe();
                    break;
                case 4:
                    playRockPaperScissors();
                    break;
                case 5:
                    playContexto();
                    break;
                case 6:
                    playMadLibs();
                    break;
                case 7:
                    playNumberGuessing();
                    break;
                case 8:
                    playWouldYouRather();
                    break;
                case 9:
                    playReversi();
                    break;
                case 10:
                    playSnake();
                    break;
                case 11:
                    playPong();
                    break;
                case 12:
                    cout << "\n(Bye!) Thanks for playing PlayWare! See you next time!\n";
                    return;
                default:
                    cout << "\n(Wrong) Invalid choice! Please select 1-12.\n";
            }
            
            cout << "\nPress Enter to return to main menu...";
            cin.ignore();
            cin.get();
        }
    }
};

int main() {
    PlayWareHub hub;
    hub.run();
    return 0;
}
