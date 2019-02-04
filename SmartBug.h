#ifndef _SMARTBUG_H
#define _SMARTBUG_H

#include "Bug.h"
class SmartBug :
	public Bug
{
public:

	virtual Position Update(Board * board, int ch, const std::vector<Character*>& cvec);

	SmartBug();
	~SmartBug();
private:
	bool chasing_ = false;
};

#endif
