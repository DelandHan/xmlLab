// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\main.h"
#include <iostream>

int main()
{
	xml::XMLParser xp;

	xp.parseFile("iecu.xml");
	xml::XMLNode * node = xp.pickupDocument();
	xp.saveNode(node, &std::cout);


	system("pause");
    return 0;
}

