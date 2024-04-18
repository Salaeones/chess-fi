#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"
#include "ChessBoard.h"



void CurrentGame::end()
{

}


void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile)
{
   
    GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, 0, 0);
    m_initBoard = intitialBoardFile;
    m_mov = movementsFile;
    m_pGuar = "data/Games/partida_guardada.txt";
    m_casellesResaltar.clear();
    m_torn = CPC_White;
    m_opGM = 0;
}

bool CurrentGame::upAndRender(int mousePosX, int mousePosY, bool mouseStatus)
{

    switch (m_opGM)
    {
    case 1:
        jugar(mousePosX, mousePosY, mouseStatus);
        break;
    case 2:
        jugar(mousePosX, mousePosY, mouseStatus);
        break;
    default:
        menu(mousePosX, mousePosY, mouseStatus);

    }

    return m_gameOv;

}

void CurrentGame::jugar(int mousePosX, int mousePosY, bool mouseStatus)
{
    
    GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);
    pGameMode();
    m_chessBoard.graphic();
    for (int i = 0; i < m_casellesResaltar.size(); i++)
        GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + CELL_W * m_casellesResaltar.at(i).getPosicioX(), CELL_INIT_Y + CELL_H * m_casellesResaltar.at(i).getPosicioY());


    // Analitzem si el jugador pitja una casella
    int pX = 0;
    bool trb = false;
    while (pX < NUM_COLS && !trb)
    {
        int  pY = 0;

        while (pY < NUM_ROWS && !trb)
        {
            if (mouseStatus && (CELL_INIT_X + CELL_W * pX < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * (pX + 1))
                && (CELL_INIT_Y + CELL_H * pY < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * (pY + 1)))
            {
                // mirem si la casella que pitjem està resaltada
                int k = 0;
                bool moure = false;
                while (k < m_casellesResaltar.size() && !moure)
                {
                    if (m_casellesResaltar.at(k).getPosicioX() == pX && m_casellesResaltar.at(k).getPosicioY() == pY)
                        moure = true;

                    k++;
                }

                // procedim a fer diferents coses depenent si la casella estava resaltada o no
                if (!moure)
                {
                    ChessPosition pos(pX, pY);
                    if (m_chessBoard.GetPieceColorAtPos(pos) == m_torn)
                    {
                        m_chessBoard.setcSel(pos);
                        m_casellesResaltar = m_chessBoard.GetValidMoves(m_chessBoard.getcSel());
                    }
                }
                else
                {
                    ChessPosition desti(pX, pY);
                    m_chessBoard.MovePiece(m_chessBoard.getcSel(), desti, m_gameOv);
                    m_casellesResaltar.clear();

                    if (m_torn == CPC_Black)
                        m_torn = CPC_White;
                    else
                        m_torn = CPC_Black;

                  
                }

                trb = true;

            }
            pY++;
        }
        pX++;
    }

    pTorn();
}

void CurrentGame::menu(int mousePosX, int mousePosY, bool mouseStatus) {

    // imprimir missatges 
    int pTX = CELL_INIT_X;

    std::string msg = "Nova Partida";
    GraphicManager::getInstance()->drawFont(FONT_RED_30, pTX, CELL_INIT_Y + (CELL_H * 1.5), 1.2, msg);



    // calcular si es pitja un missatge
    if (mouseStatus && (CELL_INIT_X < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * 2) && (CELL_INIT_Y + (CELL_H * 1) < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * 2))
    {
        // botó new game
        m_opGM = 1;
        m_gameOv = false;
        m_chessBoard.tauler2Zero();
        m_chessBoard.LoadBoardFromFile(m_initBoard);
        m_chessBoard.setPrimerTorn(true);

        ofstream file(m_mov);
        file.clear();
        file.close();
    }
    else if (mouseStatus && (CELL_INIT_X < mousePosX) && (mousePosX < CELL_INIT_X + CELL_W * 3) && (CELL_INIT_Y + (CELL_H * 3) < mousePosY) && (mousePosY < CELL_INIT_Y + CELL_H * 4))
    {
        // botó carregar joc
        m_opGM = 2;
        ifstream file(m_pGuar);
        ifstream fileM(m_mov);
        if (file.peek() == '0' || file.peek() == '1')
        {
            m_chessBoard.tauler2Zero();
            m_chessBoard.LoadBoardFromFile(m_pGuar);
            m_chessBoard.setPrimerTorn(false);

            // busquem si segueixen vius els reis i quin no ho està
            switch (m_chessBoard.REI())
            {
            case 1:
                m_torn = CPC_Black;
                m_gameOv = true;
                break;
            case 2:
                m_torn = CPC_White;
                m_gameOv = true;
                break;
            default:
                string nextMovement, x, y, pos;

                getline(fileM, nextMovement);

                x = nextMovement.at(2);
                y = nextMovement.at(3);
                pos = x + y;

                ChessPosition posTo(pos);

                if (m_chessBoard.GetPieceColorAtPos(posTo) == CPC_Black)
                    m_torn = CPC_White;
                else
                    m_torn = CPC_Black;


                m_gameOv = false;
            }
        }
        else
        {
            m_chessBoard.setPrimerTorn(true);
            m_chessBoard.tauler2Zero();
            m_chessBoard.LoadBoardFromFile(m_initBoard);
            m_gameOv = false;
        }
        file.close();
    }
   
}

void CurrentGame::pWinner()
{
    std::string winner(m_torn == CPC_White ? "Negres" : "Blanques");
    std::string miss = "Guanyen les " + winner + "!!";

    GraphicManager::getInstance()->drawFont(FONT_RED_30, 50, 260, 2, miss);
}

void CurrentGame::pTorn()
{
    int pTX = CELL_INIT_X;
    int pTY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;

    std::string torn(m_torn == CPC_Black ? "Negres" : "Blanques");
    std::string msg = "Juguen " + torn;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, pTX, pTY, 0.8, msg);
}

void CurrentGame::pGameMode()
{
    int pTX = CELL_INIT_X;
    int pTY = CELL_INIT_Y + (CELL_H * (NUM_ROWS)) + 100;

    std::string gameMode(m_opGM == 3 ? "RePlay" : "Normal");
    std::string msg = "Mode de joc: " + gameMode;
    GraphicManager::getInstance()->drawFont(FONT_RED_30, pTX, pTY, 0.8, msg);
}




