#include <iostream>

const unsigned long BOARD_SIZE = 8;

enum Color {
    WHITE,
    BLACK
};

// Base class
class Piece {
protected:
    Color color;

public:
    Piece(Color c) : color(c) {}
    virtual ~Piece() = default;
    virtual void display() const = 0;
    virtual void move() const = 0;
    virtual void capture() const = 0;
    virtual double value() const = 0;
    Color getColor() const { return color; }
};

// Pawn class
class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}
    
    void display() const override {
        std::cout << "Pawn" << std::endl;
    }

    void move() const override {
        std::cout << "Pawn moves one square forward, but if they're moving for the first time, they can move two squares forward.\nIf the pawn reaches the 8th rank, it promotes to a queen or underpromotes to any piece" << std::endl;
    }

    void capture() const override {
        std::cout << "Pawn captures diagonally one square, but there's en passant rule: a pawn that moves two squares forward from its starting position could be captured by an opposing pawn that is adjacent to it, but this capture must be made immediately on the next move" << std::endl;
    }

    double value() const override {
        return 1;
    }
};

// Rook class
class Rook : public Piece {
public:
    Rook(Color c) : Piece(c) {}

    void display() const override {
        std::cout << "Rook" << std::endl;
    }

    void move() const override {
        std::cout << "Rook moves vertically or horizontally any number of squares" << std::endl;
    }

    void capture() const override {
        std::cout << "Rook captures vertically or horizontally any number of squares" << std::endl;
    }

    double value() const override {
        return 5;
    }
};

// Knight class
class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}

    void display() const override {
        std::cout << "Knight" << std::endl;
    }

    void move() const override {
        std::cout << "Knight moves in an 'L' shape (two squares in one direction and one square perpendicular). It can jump over the pieces" << std::endl;
    }

    void capture() const override {
        std::cout << "Knight captures as it moves -- in an 'L' shape." << std::endl;
    }

    double value() const override {
        return 3;
    }
};

// Bishop class
class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c) {}

    void display() const override {
        std::cout << "Bishop" << std::endl;
    }

    void move() const override { 
        std::cout << "Bishop moves diagonally any number of squares" << std::endl; 
    }

    void capture() const override { 
        std::cout << "Bishop captures diagonally any number of squares" << std::endl; 
    }

    double value() const override { 
          return 3.5; // credits to Robert James Fisher :)
    }
};

// Queen class
class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}

    void display() const override { 
        std::cout << "Queen" << std::endl; 
    } 

    void move() const override { 
        std::cout << "Queen moves vertically, horizontally or diagonally any number of squares" << std::endl; 
    } 
    
    void capture() const override { 
        std::cout << "Queen captures vertically, horizontally or diagonally any number of squares" << std::endl; 
    } 
    
    double value() const override { 
        return 9;
    }
};

// King class
class King : public Piece { 
public:
    King(Color c) : Piece(c) {}
    
    void display() const override { 
        std::cout << "King" << std::endl; 
    } 
    
    void move() const override { 
        std::cout << "King moves one square in any direction. King cannot move to a square that is under attack" << std::endl; 
    } 
    
    void capture() const override { 
        std::cout << "King captures as it moves -- one square in any direction. King cannot capture directly protected piece" << std::endl; 
    } 
    
    double value() const override { 
        return 0; // King is priceless
    }
};

class ChessBoard {
private:
    Piece* board[BOARD_SIZE][BOARD_SIZE];

public:
    ChessBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                board[i][j] = nullptr;
            }
        }
    }

    ~ChessBoard() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                delete board[i][j];
            }
        }
    }

    bool placePiece(Piece* Piece, const std::string& position) {
        int x = position[0] - 'A';
        int y = BOARD_SIZE - (position[1] - '0');

        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board[y][x] == nullptr) {
            board[y][x] = Piece;
            return true;
        }
        return false;
    }

    void displayBoard() const {
        std::cout << "  A B C D E F G H\n";
        for (int i = 0; i < BOARD_SIZE; ++i) {
            std::cout << BOARD_SIZE - i << " ";
            for (int j = 0; j < BOARD_SIZE; ++j) {
                std::cout << getPieceSymbol(board[i][j]) << " ";
            }
            std::cout << "\n";
        }
    }

    char getPieceSymbol(Piece* Piece) const {
       if (dynamic_cast<Pawn*>(Piece)) return Piece->getColor() == WHITE ? 'P' : 'p';
       if (dynamic_cast<Rook*>(Piece)) return Piece->getColor() == WHITE ? 'R' : 'r';
       if (dynamic_cast<Knight*>(Piece)) return Piece->getColor() == WHITE ? 'N' : 'n';
       if (dynamic_cast<Bishop*>(Piece)) return Piece->getColor() == WHITE ? 'B' : 'b';
       if (dynamic_cast<Queen*>(Piece)) return Piece->getColor() == WHITE ? 'Q' : 'q';
       if (dynamic_cast<King*>(Piece)) return Piece->getColor() == WHITE ? 'K' : 'k';
       return '.';
   }

    std::string toFEN() const {
        std::string fen;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            int emptyCount = 0;
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] != nullptr) {
                    if (emptyCount > 0) { 
                        fen += std::to_string(emptyCount); 
                        emptyCount = 0;
                    }
                    fen += getPieceSymbol(board[i][j]);
                } else {
                    emptyCount++;
                }
            }
            if (emptyCount > 0) { 
                fen += std::to_string(emptyCount); 
            }
            if (i < BOARD_SIZE - 1) { 
                fen += '/'; 
            }
        }
        
        fen += " w KQkq - 0 1"; // Extra FEN fields: white to move, castling rules, en passant, full moves counter, current move 
        
        return fen;
    }
};

int main() {
    ChessBoard chessBoard;

    chessBoard.placePiece(new Pawn(WHITE), "A2");
    chessBoard.placePiece(new Pawn(WHITE), "B2");
    chessBoard.placePiece(new Pawn(WHITE), "C2");
    chessBoard.placePiece(new Pawn(WHITE), "D2");
    chessBoard.placePiece(new Pawn(WHITE), "E2");
    chessBoard.placePiece(new Pawn(WHITE), "F2");
    chessBoard.placePiece(new Pawn(WHITE), "G2");
    chessBoard.placePiece(new Pawn(WHITE), "H2");
    chessBoard.placePiece(new Rook(WHITE), "A1");
    chessBoard.placePiece(new Knight(WHITE), "B1");
    chessBoard.placePiece(new Bishop(WHITE), "C1");
    chessBoard.placePiece(new Queen(WHITE), "D1");
    chessBoard.placePiece(new King(WHITE), "E1");
    chessBoard.placePiece(new Bishop(WHITE), "F1");
    chessBoard.placePiece(new Knight(WHITE), "G1");
    chessBoard.placePiece(new Rook(WHITE), "H1");

    chessBoard.placePiece(new Pawn(BLACK), "A7");
    chessBoard.placePiece(new Pawn(BLACK), "B7");
    chessBoard.placePiece(new Pawn(BLACK), "C7");
    chessBoard.placePiece(new Pawn(BLACK), "D7");
    chessBoard.placePiece(new Pawn(BLACK), "E7");
    chessBoard.placePiece(new Pawn(BLACK), "F7");
    chessBoard.placePiece(new Pawn(BLACK), "G7");
    chessBoard.placePiece(new Pawn(BLACK), "H7");
    chessBoard.placePiece(new Rook(BLACK), "A8");
    chessBoard.placePiece(new Knight(BLACK), "B8");
    chessBoard.placePiece(new Bishop(BLACK), "C8");
    chessBoard.placePiece(new Queen(BLACK), "D8");
    chessBoard.placePiece(new King(BLACK), "E8");
    chessBoard.placePiece(new Bishop(BLACK), "F8");
    chessBoard.placePiece(new Knight(BLACK), "G8");
    chessBoard.placePiece(new Rook(BLACK), "H8");

    chessBoard.displayBoard();

    std::cout << std::endl << chessBoard.toFEN() << std::endl;

    return 0;
}