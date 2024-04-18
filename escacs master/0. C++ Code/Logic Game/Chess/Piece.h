#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "ChessPosition.h"

#include "GameInfo.h"
#include "../GraphicManager.h"


using namespace std;

typedef enum
{
	CPC_Black,
	CPC_White,
	CPC_NONE
}ChessPieceColor;

typedef enum
{
	CPT_King,
	CPT_Queen,
	CPT_Rook,
	CPT_Bishop,
	CPT_Knight,
	CPT_Pawn,
	CPT_EMPTY
}ChessPieceType;




class Piece
{
public:
	
	Piece();
	ChessPieceColor getColor() const { return m_color; }
	ChessPieceType getType() const { return m_type; }
	void setColor(ChessPieceColor color) { m_color = color; }
	void setType(ChessPieceType tipus) { m_type = tipus; }
	void setMoved(bool moguda) { m_moved = moguda; }	
	bool getMoved() const { return m_moved; }
	string pieceToString() const;
	void graphic(int posX, int posY);


private:
	ChessPosition m_pos;
	ChessPieceType m_type;
	ChessPieceColor m_color;
	bool m_moved;

};