#pragma once
#pragma once
#include"Node.h"
#include"Edge.h"

using namespace std;

class Maschine : public Node
{
public:
	Maschine(string name, int type = 0) : Node(name), m_type(type) {
		if (type == 1)
		{
			m_typeName = "Zuschneiden";

		}
		else if (type == 2)
		{
			m_typeName = "Kanten glaetten";

		}
		else if (type == 3)
		{
			m_typeName = "Bohren";


		}
		else if (type == 4)
		{
			m_typeName = "Entgraten";

		}
		else if (type == 5)
		{
			m_typeName = "Montieren";

		}
		else if (type == 0)
		{
			m_typeName = "Start";
		}
	}

	string getTypNaame() { return m_typeName; }
	int getTyp() { return m_type; }


private:
	int m_type;
	string m_typeName;


};



