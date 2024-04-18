#include "ChessBoard.h"


VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos)
{
	VecOfPositions vecP;
	ChessPosition aux;

	switch (m_board[pos.getPosicioX()][pos.getPosicioY()].getType())
	{
	case CPT_King:
		//analitzar cada posicio al voltant del rei
		for (int i = -1; i <= 1; i++)
		{
			aux.setPosicioX(pos.getPosicioX() + i);

			for (int j = -1; j <= 1; j++)
			{
				aux.setPosicioY(pos.getPosicioY() + j);

				if (validPos(aux, pos))
					vecP.push_back(aux);
			}
		}

		break;

	case CPT_Queen:
		aDia(pos, vecP);
		aHor(pos, vecP);
		aVer(pos, vecP);

		break;

	case CPT_Rook:
		aHor(pos, vecP);
		aVer(pos, vecP);

		break;

	case CPT_Knight:
		aCavall(pos, vecP);

		break;

	case CPT_Bishop:
		aDia(pos, vecP);

		break;


	case CPT_Pawn:
		aPeo(pos, vecP);
		break;
	}
	return vecP;
}



void Chessboard::aPeo(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	
	ChessPosition pAux;
	pAux.setPosicioX(pos.getPosicioX());
	ChessPieceColor colorOp = CPC_Black;

	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOp = CPC_White;

	
	int dir = 1;
	if (GetPieceColorAtPos(pos) == CPC_White)
		dir = -1;

	//posició frontal
	pAux.setPosicioY((pos.getPosicioY() + 1 * dir));
	if (validPos(pAux, pos) && GetPieceColorAtPos(pAux) == CPC_NONE)
	{
		vectorPos.push_back(pAux);

		//2a posició frontal
		pAux.setPosicioY((pos.getPosicioY() + 2 * dir));
		if (validPos(pAux, pos) && GetPieceColorAtPos(pAux) == CPC_NONE && !getMogudaPiece(pos))
			vectorPos.push_back(pAux);
	}

	//posicions diagonals frontals 
	pAux.setPosicioY((pos.getPosicioY() + 1 * dir));
	pAux.setPosicioX(pos.getPosicioX() - 1);
	if (validPos(pAux, pos) && GetPieceColorAtPos(pAux) == colorOp)
		vectorPos.push_back(pAux);

	pAux.setPosicioX(pos.getPosicioX() + 1);
	if (validPos(pAux, pos) && GetPieceColorAtPos(pAux) == colorOp)
		vectorPos.push_back(pAux);


}

void Chessboard::aDia(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition pAux;
	ChessPieceColor colorOp = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOp = CPC_White;

	int j = 1;
	bool endL = false;
	pAux.setPosicioX(pos.getPosicioX() + j);
	pAux.setPosicioY(pos.getPosicioY() - j);

	while (validPos(pAux, pos) && !endL)
	{
		//afegir la posicio al vector
		vectorPos.push_back(pAux);

		//mirar que la posicio no sigui del color contrari
		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		
		j++;
		pAux.setPosicioX(pos.getPosicioX() + j);
		pAux.setPosicioY(pos.getPosicioY() - j);
	}


	j = 1;
	endL = false;
	pAux.setPosicioX(pos.getPosicioX() - j);
	pAux.setPosicioY(pos.getPosicioY() - j);

	while (validPos(pAux, pos) && !endL)
	{
		vectorPos.push_back(pAux);

		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		j++;
		pAux.setPosicioX(pos.getPosicioX() - j);
		pAux.setPosicioY(pos.getPosicioY() - j);
	}

	
	j = 1;
	endL = false;
	pAux.setPosicioX(pos.getPosicioX() - j);
	pAux.setPosicioY(pos.getPosicioY() + j);

	while (validPos(pAux, pos) && !endL)
	{
		vectorPos.push_back(pAux);

		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		j++;
		pAux.setPosicioX(pos.getPosicioX() - j);
		pAux.setPosicioY(pos.getPosicioY() + j);
	}

	
	j = 1;
	endL = false;
	pAux.setPosicioX(pos.getPosicioX() + j);
	pAux.setPosicioY(pos.getPosicioY() + j);

	while (validPos(pAux, pos) && !endL)
	{
		vectorPos.push_back(pAux);

		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		j++;
		pAux.setPosicioX(pos.getPosicioX() + j);
		pAux.setPosicioY(pos.getPosicioY() + j);
	}

}

void Chessboard::aHor(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition pAux;
	pAux.setPosicioY(pos.getPosicioY());

	ChessPieceColor colorOp = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOp = CPC_White;

	
	int i = 1;
	bool endL = false;
	pAux.setPosicioX(pos.getPosicioX() + i);

	while (validPos(pAux, pos) && !endL)
	{
		
		vectorPos.push_back(pAux);

		
		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;
	
		i++;
		pAux.setPosicioX(pos.getPosicioX() + i);
	}


	
	i = 1;
	endL = false;
	pAux.setPosicioX(pos.getPosicioX() - i);

	while (validPos(pAux, pos) && !endL)
	{
		vectorPos.push_back(pAux);

		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		i++;
		pAux.setPosicioX(pos.getPosicioX() - i);
	}
}

void Chessboard::aVer(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition pAux;
	pAux.setPosicioX(pos.getPosicioX());

	ChessPieceColor colorOp = CPC_Black;
	if (GetPieceColorAtPos(pos) == CPC_Black)
		colorOp = CPC_White;

	
	int j = 1;
	bool endL = false;
	pAux.setPosicioY(pos.getPosicioY() + j);

	while (validPos(pAux, pos) && !endL)
	{
		vectorPos.push_back(pAux);

		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		j++;
		pAux.setPosicioY(pos.getPosicioY() + j);
	}

	j = 1;
	endL = false;
	pAux.setPosicioY(pos.getPosicioY() - j);

	while (validPos(pAux, pos) && !endL)
	{
		vectorPos.push_back(pAux);

		if (GetPieceColorAtPos(pAux) == colorOp)
			endL = true;

		j++;
		pAux.setPosicioY(pos.getPosicioY() - j);
	}
}

void Chessboard::aCavall(const ChessPosition& pos, VecOfPositions& vectorPos)
{
	ChessPosition pAux;

	
	for (int i = -2; i <= 2; i++)
	{
		pAux.setPosicioX(pos.getPosicioX() + i);

		if (i == -2 || i == 2)
		{
			pAux.setPosicioY(pos.getPosicioY() - 1);
			if (validPos(pAux, pos))
				vectorPos.push_back(pAux);

			pAux.setPosicioY(pos.getPosicioY() + 1);
			if (validPos(pAux, pos))
				vectorPos.push_back(pAux);
		}
		else if (i == -1 || i == 1)
		{
			pAux.setPosicioY(pos.getPosicioY() - 2);
			if (validPos(pAux, pos))
				vectorPos.push_back(pAux);

			pAux.setPosicioY(pos.getPosicioY() + 2);
			if (validPos(pAux, pos))
				vectorPos.push_back(pAux);
		}
	}
}


bool Chessboard::validPos(ChessPosition posAuxiliar, ChessPosition pos)
{
	bool valid = true;

	if (posAuxiliar.getPosicioX() > NUM_COLS - 1 || posAuxiliar.getPosicioX() < 0 || posAuxiliar.getPosicioY() > NUM_ROWS - 1 || posAuxiliar.getPosicioY() < 0)
		valid = false;
	else if (GetPieceTypeAtPos(posAuxiliar) != CPT_EMPTY && GetPieceColorAtPos(posAuxiliar) == GetPieceColorAtPos(pos))
		valid = false;

	return valid;

}
