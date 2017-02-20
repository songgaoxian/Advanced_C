//Singleton.h
//
//implement Singleton class and Destroyer class
//written on 2016/6/29
#ifndef Singleton_hpp
#define Singleton_hpp
#include<stddef.h>

// Forward reference for singleton
template<class TYPE> class Singleton;

template<class TYPE>
class Destroyer
{ // Class which is responsible for the destruction of another type TYPE

	friend class Singleton<TYPE>;	// Singleton is friend of mine

private:
	TYPE* doomed_object;			// The object that is to be destructed 

									// Prevent users doing funny things (e.g. double deletion)
									//	Destroyer();													// Default constructor
	Destroyer(TYPE* t) { doomed_object = t; }												// Constructor with a pointer to the doomed object
	Destroyer(const Destroyer<TYPE>& source) {};						// Copy constructor
	Destroyer<TYPE>& operator = (const Destroyer<TYPE>& source) { return *this; }	// Assignment operator

																					// Modifier
	void doomed(TYPE* t) { doomed_object = t; }

public:
	// Destructor 
	virtual ~Destroyer() { delete doomed_object; }

	// Somehow the default constructor must be public else we got a compiler error in class ctype
	Destroyer() { doomed_object = NULL; }												// Default constructor
};


template<class TYPE>
class Singleton
{ // Templated Singleton class

private:
	static TYPE* ins;
	static Destroyer<TYPE> des;

protected:
	Singleton();//default constructor
	Singleton(const Singleton<TYPE>& source);//copy constructor
	virtual ~Singleton(); //destructor
	Singleton<TYPE>& operator = (const Singleton<TYPE>& source);

public:
	static TYPE* instance();
};

#include"Singleton.cpp"
#endif // Singleton_hpp

