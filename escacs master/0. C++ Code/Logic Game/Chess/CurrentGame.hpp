#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include "GameInfo.h"

#include <Windows.h>

#include "ChessBoard.h"

using namespace std;



class CurrentGame {

public:
    CurrentGame() {};

    void init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
    bool upAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void end();


    void jugar(int mousePosX, int mousePosY, bool mouseStatus);
    void menu(int mousePosX, int mousePosY, bool mouseStatus);
   
   
    void pWinner();
    void pTorn();
    void pGameMode();
    
private:
    Chessboard m_chessBoard;
    VecOfPositions m_casellesResaltar;
    ChessPieceColor m_torn;
    bool m_gameOv;
    int m_opGM;
    string m_initBoard, m_mov, m_pGuar;
    
};

#endif
