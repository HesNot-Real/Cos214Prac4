#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator {


public:
	virtual void first() = 0;

	virtual void next() = 0;

	virtual void nextPriority() = 0;

	virtual void isDone() = 0;

	void currentItem();
};

#endif
