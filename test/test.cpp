// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\main.h"
#include <iostream>
#include <fstream>
using namespace std;

void work(xml::XMLNode *source, xml::XMLNode * re)
{
	xml::XMLNode* node = source;
	while (node!=source->getNextByChain(false))
	{
		if (node->getString() == "TD")
		{
			xml::XMLNode * child = node->getFirstChild();
			while (child)
			{
				re->append(child->clone());
				child = child->getNext();
			}
			node = node->getNextByChain();
		}
		else 
			node = node->getNextByChain();
	}
}

int main()
{
	xml::XMLParser xp;

	xp.parseFile("iecu.xml");
	xml::XMLNode * docu = xp.pickupDocument();

	xml::XMLNode *re = new xml::XMLNode;
	xml::XMLNode* node = docu;

	while (node)
	{

		if (node->getString() == "table")
		{
			work(node, re);
			xml::XMLNode *cl = re->clone();
			node->insert(cl, false);
			delete re;
			re = new xml::XMLNode;
			xml::XMLNode * temp = node;
			node = node->getNextByChain(false);
			delete temp;
		}
		else
		{
			node = node->getNextByChain();
		}
	}
	
	std::ofstream of("out.xml");
	xp.saveNode(docu, &of);
	of.close();

	system("pause");
    return 0;
}

