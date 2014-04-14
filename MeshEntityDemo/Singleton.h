#ifndef SINGLEON_H
#define SINGLEON_H

template <class T>
class Singleton
{
public:
	static T* Instance()
	{
		static T myT;
		return &myT;
	}
};

#endif