#include "ChessPosition.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

ChessPosition::ChessPosition()
{
	m_posX = 0;
	m_posY = 0;
}

ChessPosition::ChessPosition(const std::string& pos_str)
{
	switch (pos_str.at(0))
	{
	case 'a':
		m_posX = 0;
		break;
	case 'b':
		m_posX = 1;
		break;
	case 'c':
		m_posX = 2;
		break;
	case 'd':
		m_posX = 3;
		break;
	case 'e':
		m_posX = 4;
		break;
	case 'f':
		m_posX = 5;
		break;
	case 'g':
		m_posX = 6;
		break;
	case 'h':
		m_posX = 7;
		break;
	}

	//posicio vertical
	switch (pos_str.at(1))
	{
	case '1':
		m_posY = 7;
		break;
	case '2':
		m_posY = 6;
		break;
	case '3':
		m_posY = 5;
		break;
	case '4':
		m_posY = 4;
		break;
	case '5':
		m_posY = 3;
		break;
	case '6':
		m_posY = 2;
		break;
	case '7':
		m_posY = 1;
		break;
	case '8':
		m_posY = 0;
		break;
	}
}

ostream& operator<<(ostream& output, const ChessPosition& pos)
{
	output << pos.toString();

	return output;
}

bool ChessPosition::operator==(ChessPosition pos) const
{
	bool iguals = false;

	if (m_posX == pos.getPosicioX() && m_posY == pos.getPosicioY())
		iguals = true;

	return iguals;
}

string ChessPosition::toString() const 
{
	string buit ="__";
	char x = m_posX + 96;
	if(m_posX < 8 && m_posX >= 1)
		buit[0] = x;

	char y = m_posY + 48;
	if(m_posY < 8 && m_posY >= 1)
		buit[1] = y;

	return buit;

}


