#pragma once
#include "Piece.h"
#include "ChessPosition.h"

#define NUM_ROWS 8
#define NUM_COLS 8

typedef vector<ChessPosition> VecOfPositions;

class Chessboard
{
public:   
    
    Chessboard() : m_gameOv(false), m_fMov(true) {}
    Piece getPiece(int x, int y) { return m_board[x][y]; }
    ChessPosition getcSel() { return m_cSel; }
    void setcSel(ChessPosition casella) { m_cSel = casella; }
    bool validPos(ChessPosition posAuxiliar, ChessPosition pos);
    void graphic();
    bool posEnVect(const ChessPosition& pos, VecOfPositions vectorPos);
    void LoadBoardFromFile(const string& nomFitxer);
    VecOfPositions GetValidMoves(const ChessPosition& pos);
    string ToString() const;
    bool MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, bool& gameOver);
    void peo2reina();    
    ChessPieceColor GetPieceColorAtPos(ChessPosition pos) const;
    ChessPieceType GetPieceTypeAtPos(ChessPosition pos) const;
    bool getMogudaPiece(const ChessPosition pos);
    void setNewPiece(ChessPosition pos, ChessPieceColor color, ChessPieceType tipus, bool moguda);    
    void aDia(const ChessPosition& pos, VecOfPositions& vectorPos);
    void aVer(const ChessPosition& pos, VecOfPositions& vectorPos);
    void aHor(const ChessPosition& pos, VecOfPositions& vectorPos);
    void aPeo(const ChessPosition& pos, VecOfPositions& vectorPos);
    void aCavall(const ChessPosition& pos, VecOfPositions& vectorPos);
    int REI();
    void setPrimerTorn(bool primerTorn) { m_fMov = primerTorn; }
    void tauler2Zero();
   

   

  
   
 

private:
    Piece m_board[NUM_COLS][NUM_ROWS];
    ChessPosition m_cSel;
    bool m_gameOv;
    string m_lMov;
    bool m_fMov;
};

