#ifndef AGGREGATE_H
#define AGGREGATE_H

class Aggregate {


public:
	virtual Iterator* createIterator() = 0;
};

#endif
