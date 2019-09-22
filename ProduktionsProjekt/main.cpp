#include <iostream>
#include "Graph.h"
#include"Maschine.h"
#include"Connection.h"
#include"Info.h"

using namespace std;

double optiemierungsFaktor = 1;
int lossGrosse = 0;

//Funktion to make tow way Edge.
void makeReversedConnection(Graph *ptrG, Node& rSrc, Node& rDes, double kost10, double kost100, double kost5000, double zeitBedarf, int typ = 0)
{
	ptrG->addEdge(new Connection(rSrc, rDes, kost10, kost100, kost5000, zeitBedarf, typ));
	ptrG->addEdge(new Connection(rSrc, rDes, kost10, kost100, kost5000, zeitBedarf, typ));
}
////////////////////////////////////////////////////////////

int main()
{
	Graph g;

	Node& rStart = g.addNode(new Maschine("Start", 0));
	Node& rGebauer1 = g.addNode(new Maschine("Gebauer", 1));
	Node& rMeixner = g.addNode(new Maschine("rMeixne", 1));
	Node& rGebauer2 = g.addNode(new Maschine("Gebauer", 2));
	Node& rKawasaki = g.addNode(new Maschine("Kawasaki", 3));
	Node& rMohlenberg = g.addNode(new Maschine("Moehlenberg", 3));
	Node& rGebauer4 = g.addNode(new Maschine("Gebauer", 4));
	Node& rKuka = g.addNode(new Maschine("Kuka", 5));
	Node& rABB = g.addNode(new Maschine("ABB", 5));

	makeReversedConnection(&g, rStart, rGebauer1, 0.5, 0.33, 0.25, 40, 1);
	makeReversedConnection(&g, rStart, rMeixner, 0.45, 0.36, 0.28, 45, 1);
	makeReversedConnection(&g, rGebauer1, rGebauer2, 0.12, 0.12, 0.12, 70, 2);
	makeReversedConnection(&g, rMeixner, rGebauer2, 0.12, 0.12, 0.12, 70, 2);
	makeReversedConnection(&g, rGebauer2, rKawasaki, 0.48, 0.44, 0.4, 120, 3);
	makeReversedConnection(&g, rGebauer2, rMohlenberg, 0.89, 0.7, 0.66, 30, 3);
	makeReversedConnection(&g, rKawasaki, rGebauer4, 0.15, 0.12, 0.08, 10, 4);
	makeReversedConnection(&g, rMohlenberg, rGebauer4, 0.15, 0.12, 0.08, 10, 4);
	makeReversedConnection(&g, rGebauer4, rKuka, 1.23, 1.12, 1.01, 180, 5);
	makeReversedConnection(&g, rGebauer4, rABB, 1.25, 1.00, 0.98, 195, 5);

	Info Verbindung;
	list <Info> VerbindungenListe; // liste alle Vertiegungen

	bool quit = false;
	int menu1_wahl = 0;

	while (!quit)
	{
		double gesamtKost1 = 0;
		double gesamtZeit1 = 0;

		double gesamtKost2 = 0;
		double gesamtZeit2 = 0;

		// Menue Zeigen und behandlung von falschen Eingaben

		if (menu1_wahl == 0)
		{
			while (menu1_wahl < 1 || menu1_wahl > 6)
			{
				cout << "1- Ferigungsmoeglischkeiten ausgeben:" << std::endl
					<< "2- Fertigungsauftrag erfassen, plannen and ausfuehren:" << std::endl
					<< "3-Liste ausgeben:" << std::endl
					<< "4- Programm beenden:" << std::endl
					<< "Eingabe: ";
				while (!(cin >> menu1_wahl)) // Falls Buschstabe eingetragen
				{
					cout << "Bitte Digit eingeben..." << endl;
					cin.clear();
					cin.ignore(132, '\n');
				}
			}

		}

		// Sortieren und Im Bildschirm zeigen

		else if (menu1_wahl == 1)
		{
			list<Node*> sorted = g.getNodes();
			list<Edge*> edgeList = g.getEdges();

			// Ziele sortieren und ausgeben...
			sorted.sort([](const Node* a, const Node* b) { return a->getID() < b->getID(); });

			for (auto nodeIt = sorted.begin(); nodeIt != sorted.end(); nodeIt++)
			{
				cout << " Ort:  " << (*nodeIt)->getID() << endl;
				for (auto edgeIt = g.getEdges().begin(); edgeIt != g.getEdges().end(); edgeIt++)
				{
					if ((*edgeIt)->getSrcNode().getID() == (*nodeIt)->getID())
					{
						Connection* pTeilConnection = dynamic_cast<Connection*>(*edgeIt);
						std::cout << "\t" << " :" << (pTeilConnection)->toString()
							<< " " << (pTeilConnection)->getZeitBedarf() << "Km" << endl;
					}

				}
			}
			menu1_wahl = 0;
		}
		////////////////////////////////////////////////////////
		//auswählen und beste Route finden

		else if (menu1_wahl == 2)
		{
			cout << "Bitte lossgrosse angeben: ";
			cout << "Eingabe: ";
			cin >> lossGrosse;
			cout << endl;

			//Optiemierung nach Zeit, nach Kosten optimieren.
			cout << "Bitte waelen Sie wo nach muss optiemiert werden: " << endl;
			cout << "1) nach Zeit: " << endl << "2) nach Kost: " << endl;
			cin >> optiemierungsFaktor;
			cout << endl;

			Node* rStartpunkt = NULL;
			Node* rZielpunkt1 = NULL;
			Node* rZielpunkt2 = NULL;

			rStartpunkt = &rStart;
			rZielpunkt1 = &rKuka;
			rZielpunkt2 = &rABB;

			deque<Edge*> path1;
			deque<Edge*> path2;

			g.findShortestPathDijkstra(path1, rStart, *rZielpunkt1);
			g.findShortestPathDijkstra(path2, rStart, *rZielpunkt2);
			for (std::deque<Edge*>::iterator it = path1.begin(); it != path1.end(); it++)
			{

				Connection* pTeilConnection = dynamic_cast<Connection*>(*it);

				gesamtKost1 += (pTeilConnection->getKost());
				gesamtZeit1 += (pTeilConnection->getZeitBedarf());
			}

			for (std::deque<Edge*>::iterator it = path2.begin(); it != path2.end(); it++)
			{

				Connection* pTeilConnection = dynamic_cast<Connection*>(*it);

				gesamtKost2 += (pTeilConnection->getKost());
				gesamtZeit2 += (pTeilConnection->getZeitBedarf());
			}




			for (std::deque<Edge*>::iterator it = path1.begin(); it != path1.end(); it++)
			{

				Connection* pTeilConnection = dynamic_cast<Connection*>(*it);

				cout << "Teilroute: "
					<< pTeilConnection->toString()
					<< ";  "
					<< ";  Teilzeit: "
					<< (pTeilConnection)->getZeitBedarf()
					<< " Cost: " << (pTeilConnection)->getKost()
					<< " Cent" << endl;

				gesamtKost1 += (pTeilConnection->getWeight());
				gesamtZeit1 += (pTeilConnection->getWeight());
			}
			cout << " Gesamt Kost: " << gesamtKost1 << " Euro" << endl;
			cout << "Gesamt Zeit: " << gesamtZeit1 << endl;

			Verbindung.m_gesamtKost = gesamtKost1;
			Verbindung.m_gesamtZeitBedarf = gesamtZeit1;
			Verbindung.m_losGrosse = lossGrosse;
			Verbindung.m_optiemierungsZiel = optiemierungsFaktor;

			VerbindungenListe.push_back(Verbindung);

			menu1_wahl = 0;
		}

		else if (menu1_wahl == 3)
		{
			for (auto it = VerbindungenListe.begin(); it != VerbindungenListe.end(); it++)
			{
				cout << "Lossgrosse: " << it->m_losGrosse << " ; Optiemierungsziel: "
					<< (it)->m_optiemierungsZiel << " ; Gesamtkost: " << it->m_gesamtKost
					<< " ;Dauer: " << it->m_gesamtZeitBedarf << endl;

			}
			menu1_wahl = 0;
		}

		else if (menu1_wahl == 4)
		{
			return 0;
		}
	}


	return 0;
}
