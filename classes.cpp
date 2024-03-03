// CLASSES

// 1. Organize related data into structures

void draw(int x, int y, int x2, int y2);		// BAD
void draw(Point from, Point to);				// GOOD

// 4. Make a function a member only when it needs a direct access to the class (direct association with class) 

class Date
{
	// ... (interface)
};

// helper functions:
Date next_weekday(const Date&);
bool operator==(const Date&, const Date&);

// 12. Prefer not using data members as const or references 

class Example
{
	const int i;			// not assignable, but constructible
	std::string& s;			// the same here
};

// 20. If you can avoid defining default operations, do

class Named_map
{
public:
	// ... no default operation declared
private:
	std::string name;
	std::map<int, int> rep;
};

// no need to define any functionality because std::string and std::map already defined them
// so it'll be called automatically

Named_map nm;			// default constructor
Named_map nm2 { nm };	// copy constructor

// 21. Define either all (copy/move/destructor) operations (to express your intent) or none at all

// BAD
struct M2
{
public:
	// ... no copy or move operations
	~M2() { delete[] rep; }
private:
	std::pair<int, int>* rep;	// set of pairs
};

void use()
{
	M2 x, y;
	// ...
	x = y; 	// default copy assignment
}

// 32. If a class has T* or T&, consider its ownership

class legacy_class
{
	foo* m_owning;		// BAD: change to unique_ptr<foo>
	bar* m_observer;	// OK
};

// 35. Make destructors either public and virtual or protected and non-virtual:
// Public and virtual - to destory derived class objects via base class pointer
// Protected and non-virtual - to invoke base destructor in derived destructor (via derived object)

// 37. Declare destructors noexcept

struct X
{
	// ...
	~X() noexcept { }	// can not throw exceptions
};

// 43. Ensure that class has a default constructor

class Date
{
public:
	Date(int dd, int mm, int yyyy);
	Date() : dd(1), mm(1), yyyy(1970) { }
private:
	int dd, mm, yyyy;
};

struct X
{
	std::string s;		// default-constructed
	int i;				// not initialized
};

// Better
struct X
{
	std::string s;		// default-constructed
	int i{};			// default initialized to 0
};

// 46. Declare single-argument constructors explicit

class String
{
public:
	String(int i); 				// BAD
	explicit String(int i); 	// GOOD
	// ...
};
// Do not make move/copy constructors explicit
String s = 10;					// BAD
String s { 10 };				// GOOD

// 47. Prefer default member initilizers to member initialization in constructors

// BAD
class X
{
	int i;
	std::string s;
	int j;
public:
	X() : i{ 666 }, s{ "qqq" } { }	// j - uninitialized
	X(int ii) : i{ ii } { }			// s - initialized with "", but what about j?
};

// GOOD
class X
{					// the same value is expected to be in all constructors
	int i {666};
	std::string s {"qqq"};
	int j {0};
public:
	X() = default;					// all members are initialized to their defaults
	X(int ii) : i{ ii } { }			// s and j are initialized as well
};

