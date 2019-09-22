#pragma once
#include"Edge.h"
using namespace std;

extern double optiemierungsFaktor;
extern int lossGrosse;

class Connection : public Edge
{
public:
	Connection(Node& rSrc, Node& rDes, double kost10, double kost100, double kost5000, double zeitBedarf, int type) : Edge(rSrc, rDes), m_kost10(kost10), m_kost100(kost100), m_kost5000(kost5000),
		m_zeitBedarf(zeitBedarf), m_type(type)
	{

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
		else
		{
			m_typeName = "Montieren";
		}
	}


	virtual double getWeight()
	{
		if (optiemierungsFaktor == 1)
		{
			return m_zeitBedarf;
		}
		else if (optiemierungsFaktor == 2)
		{
			if (lossGrosse < 10)
			{
				return m_kost10;
			}
			else if (lossGrosse > 10 && lossGrosse < 100)
			{
				return m_kost100;
			}
			else
			{
				return m_kost5000;
			}


			return 0;
		}
	}
	int getType() { return m_type; }
	string getTypeName() { return m_typeName; }
	double getZeitBedarf() { return m_zeitBedarf; }
	double getKost() { return getWeight(); }

private:
	int m_type;
	string m_typeName;
	double m_kost10;
	double m_kost100;
	double m_kost5000;
	double m_zeitBedarf;
}; 
