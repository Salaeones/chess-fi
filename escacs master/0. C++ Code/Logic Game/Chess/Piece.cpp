#include "Piece.h"

Piece::Piece()
{
	m_color = CPC_NONE;
	m_type = CPT_EMPTY;
	m_moved = false;
}

void Piece::graphic(int posX, int posY)
{

	if (m_color == CPC_Black)
	{
		switch (m_type)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, posX, posY);
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, posX, posY);
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, posX, posY);
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, posX, posY);
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, posX, posY);
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, posX, posY);
			break;
		}
	}
	else if (m_color == CPC_White)
	{
		switch (m_type)
		{
		case CPT_King:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, posX, posY);
			break;
		case CPT_Queen:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, posX, posY);
			break;
		case CPT_Bishop:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, posX, posY);
			break;
		case CPT_Knight:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, posX, posY);
			break;
		case CPT_Rook:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, posX, posY);
			break;
		case CPT_Pawn:
			GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, posX, posY);
			break;
		}
	}
}

string Piece::pieceToString() const
{
	string string = "";

	switch (m_color)
	{
	case CPC_White:
		string.append("w");
		break;

	case CPC_Black:
		string.append("b");
		break;

	default:
		string.append("_");
	}

	switch (m_type)
	{
	case CPT_King:
		string.append("K");
		break;

	case CPT_Queen:
		string.append("Q");
		break;

	case CPT_Rook:
		string.append("R");
		break;

	case CPT_Knight:
		string.append("H");
		break;

	case CPT_Bishop:
		string.append("B");
		break;

	case CPT_Pawn:
		string.append("P");
		break;

	default:
		string.append("_");
	}

	return string;
}


