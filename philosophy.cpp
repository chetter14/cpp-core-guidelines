// PHILOSOPHY


// 1. Express your intentions directly in code:

class Date {
public:
	Month month() const;	// it's straightforward (not ambiguous)
	int month();			// but it's not
};


// Bad one (code mimics the standard library)
void foo(std::vector<string>& v)
{
	std::string val;
	std::cin >> val;
	
	int index = -1;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] == val)
		{
			index = i;
			break;
		}
	}
}

// Good one (the intention is explicit here)
void foo(std::vector<string>& v)
{
	std::string val;
	std::cin >> val;
	
	auto p = std::find(v.begin(), v.end(), val);
}


// 3. Express intent:

// Bad one
int i = 0;
while (i < v.size())
{
	// ... do something with v[i] 
}

// Good one (explicit iteration over v and elements of v can not be modified)
for (const auto& x : v)
{
	// do something with x
}

// Or even better
std::for_each(v.begin(), v.end(), [](int x) { /* do something with value of x */ } );


// 5. Prefer compile-time checking to run-time

static_assert(sizeof(int) >= 4);		// compile-time check of integer type size

// Bad one
void read(int* p, int n);

int a[100];
read(a, 100);

// Good one
void read(std::span<int> p);

int a[100];
read(a);			// using std::span<int> we let the compiler decide the size of the 'a' array


// 6. If it cannot be checked at compile-time, make it checkable at run-time

extern void foo(std::vector<int>&);
extern void foo(std::span<int>);

void boo(int n)
{
	std::vector v(n);
	foo(v);							// we pass elements and number of them as one object
	foo(std::span<int>{v});
}


// 7. Catch run-time errors as early as possible

// Bad example

void increment(int* p, int n)
{
	for (int i = 0; i < n; ++i) ++p[i];
}

void foo()
{
	const int n = 10;
	int a[n] = { /* ... */ };
	// ...
	increment(a, m);		// made a typo, and will get an error in increment() function
	// ...
}

// Good example

void increment(std::span<int> p)
{
	for (auto& x : p) ++x;
}

void foo()
{
	const int n = 10;
	int a[n] = { /* ... */ };
	// ...
	increment(a);		// no need in number of elements to be passed
	// ...
}


