#include "ChessBoard.h"

//moure una peça
bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo, bool& gameOv)
{
	bool mov = false;

	if (GetPieceColorAtPos(posFrom) != CPC_NONE && posEnVect(posTo, GetValidMoves(posFrom)))
	{
		if (GetPieceTypeAtPos(posTo) == CPT_King)
			gameOv = true;
		setNewPiece(posTo, m_board[posFrom.getPosicioX()][posFrom.getPosicioY()].getColor(), m_board[posFrom.getPosicioX()][posFrom.getPosicioY()].getType(), 1);
		setNewPiece(posFrom, CPC_NONE, CPT_EMPTY, 1);
		peo2reina(); 

		mov = true;
	}

	return mov;
}


//carregar la taula
void Chessboard::LoadBoardFromFile(const string& nomFitxer)
{

	ifstream f(nomFitxer);
	string cadena;

	ChessPosition pos;
	int posVer, posHor;

	ChessPieceType type;
	ChessPieceColor color;

	do {

		getline(f, cadena);


		//comprovar el tipus de peça
		switch (cadena.at(3))
		{
		case 'R':
			type = CPT_King;
			break;

		case 'D':
			type = CPT_Queen;
			break;

		case 'T':
			type = CPT_Rook;
			break;

		case 'A':
			type = CPT_Bishop;
			break;

		case 'C':
			type = CPT_Knight;
			break;

		case 'P':
			type = CPT_Pawn;
			break;
		}

		//comprovar el color de la peça
		if (cadena.at(0) == '0')
			color = CPC_White;
		else if (cadena.at(0) == '1')
			color = CPC_Black;
		else
			color = CPC_NONE;



		//comprovar la posició vertical
		switch (cadena.at(5))
		{
		case '1':
			posVer = 7;
			break;
		case '2':
			posVer = 6;
			break;
		case '3':
			posVer = 5;
			break;
		case '4':
			posVer = 4;
			break;
		case '5':
			posVer = 3;
			break;
		case '6':
			posVer = 2;
			break;
		case '7':
			posVer = 1;
			break;
		case '8':
			posVer = 0;
			break;
		}

		//comprovar la posició horitzontal
		switch (cadena.at(4))
		{
		case 'a':
			posHor = 0;
			break;
		case 'b':
			posHor = 1;
			break;
		case 'c':
			posHor = 2;
			break;
		case 'd':
			posHor = 3;
			break;
		case 'e':
			posHor = 4;
			break;
		case 'f':
			posHor = 5;
			break;
		case 'g':
			posHor = 6;
			break;
		case 'h':
			posHor = 7;
			break;
		}

		pos.setPosicioX(posHor);
		pos.setPosicioY(posVer);

		m_board[posHor][posVer].setColor(color);
		m_board[posHor][posVer].setType(type);

	} while (!f.eof());

	f.close();
}

ChessPieceColor Chessboard::GetPieceColorAtPos(ChessPosition pos) const
{
	return m_board[pos.getPosicioX()][pos.getPosicioY()].getColor();
}

bool Chessboard::posEnVect(const ChessPosition& pos, VecOfPositions vectorPos)
{
	int i = 0;
	bool trobat = false;

	while (!trobat && i < vectorPos.size())
	{
		if (pos == vectorPos.at(i))
			trobat = true;
		else
			i++;
	}

	return trobat;
}

int Chessboard::REI()
{
	int cont = 0, g = 0;

	for (int row = 0; row < NUM_ROWS; row++) // aquests loops hourien de ser whiles
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			if (m_board[row][col].getType() == CPT_King)
			{
				cont++;

				if (m_board[row][col].getColor() == CPC_Black)
					g = 2;
				else if (m_board[row][col].getColor() == CPC_White)
					g = 1;
			}
		}
	}

	if (cont > 1)
		return 0;
	return g;
}

void Chessboard::setNewPiece(ChessPosition pos, ChessPieceColor color, ChessPieceType tipus, bool moguda)
{
	m_board[pos.getPosicioX()][pos.getPosicioY()].setColor(color);
	m_board[pos.getPosicioX()][pos.getPosicioY()].setType(tipus);
	m_board[pos.getPosicioX()][pos.getPosicioY()].setMoved(moguda);
}

bool Chessboard::getMogudaPiece(const ChessPosition pos)
{
	//les peces que necessitem saber s'han mogut previament són el rei, les torres i els peons (per els enrocs i els possibles dobles moviments dels peons)
	bool mov = m_board[pos.getPosicioX()][pos.getPosicioY()].getMoved();

	return mov;
}

ChessPieceType Chessboard::GetPieceTypeAtPos(ChessPosition pos) const
{
	return m_board[pos.getPosicioX()][pos.getPosicioY()].getType();
}



void Chessboard::peo2reina()
{
	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			if (m_board[col][(NUM_ROWS - 1) * row].getType() == CPT_Pawn)
				m_board[col][(NUM_ROWS - 1) * row].setType(CPT_Queen);
		}
	}
}



//passar la taula a una cadena de text/string
string Chessboard::ToString() const
{
	string string = "";

	for (int row = 0; row < NUM_ROWS; row++)
	{
		//afegir nom de la fila
		string.append(to_string(8 - row));

		//afegir columna a columna les peçes
		for (int column = 0; column < NUM_COLS; column++)
		{
			string.append(" ");
			string.append(m_board[row][column].pieceToString());
		}

		string.append("\n");

	}

	//afegir els noms de les files
	string.append("  a  b  c  d  e  f  g  h");
	return string;
}

void Chessboard::tauler2Zero()
{
	for (int row = 0; row < NUM_ROWS; row++)
	{
		for (int col = 0; col < NUM_COLS; col++)
		{
			ChessPosition pos(row, col);
			setNewPiece(pos, CPC_NONE, CPT_EMPTY, 0);
		}
	}
}

//grafic
void Chessboard::graphic() 
{

	for (int posX = 0; posX < NUM_COLS; posX++)
	{
		for (int posY = 0; posY < NUM_COLS; posY++)
		{
			m_board[posX][posY].graphic(CELL_INIT_X + posX * CELL_W, CELL_INIT_Y + posY * CELL_H);
		}
	}
}
