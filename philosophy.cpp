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





