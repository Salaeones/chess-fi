#pragma once
#include <iostream>
using namespace std;

class ChessPosition
{
public:
	ChessPosition();
	ChessPosition(const std::string& pos_str);
	ChessPosition(const int x, const int y) { m_posX = x; m_posY = y; }
	int getPosicioX() const { return m_posX; }
	int getPosicioY() const { return m_posY; }
	void setPosicioX(int num) { m_posX = num; }
	void setPosicioY(int num) { m_posY = num; }
	bool operator==(const ChessPosition pos) const;
	string toString() const;

private:
	int m_posX, m_posY;
};

ostream& operator<<(ostream& output, const ChessPosition& pos);