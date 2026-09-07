#ifndef AGGREGATE_H
#define AGGREGATE_H

class Iterator;

class Aggregate {


public:
	virtual Iterator* createIterator() = 0;
	virtual ~Aggregate() {}
};

#endif
