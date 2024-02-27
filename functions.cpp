// FUNCTIONS

// 1. Package pieces of code into meaningful blocks

// Bad example
std::sort(a, b, [](T x, T y) { return x.rank() < y.rank() && x.value() < y.value(); });

// Good one
auto lessT = [](T x, T y) { return x.rank() < y.rank() && x.value() < y.value(); };
std::sort(a, b, lessT);

// 4. In case, use constexpr functions for compile-time known arguments

constexpr int fac(int n)
{
	constexpr int max_exp = 17;
	int x = 1;
	for (int i = 2; i <= n; ++i) x *= i;
	return x;
}

// 10. Put code into reusable blocks of code

struct Rec {
	std::string name;
	std::string address;
	int id;
};

bool same(const Rec& a, const Rec& b) { return a.id == b.id; }

// 1)
auto x = std::find_if(vr.begin(), vr.end(), 
	[&](Rec& r) {
		if (r.name.size() != n.size()) return false;				// if the length is different
		for (int i = 0; i < r.name.size(); ++i)
			if (tolower(r.name[i]) != tolower(n[i])) return false;	// if the char is different
		return true;
	}
);

// 2)
bool compare_insensitive(const std::string& a, const std::string& b)
{
	if (a.size() != b.size()) return false;						// if the length is different
	for (int i = 0; i < a.size(); ++i)
		if (tolower(a[i]) != tolower(b[i])) return false;		// if the char is different
	return true;
}

auto x = std::find_if(vr.begin(), vr.end(), 
	[&](Rec& r) { return compare_insensitive(r.name, n); } 
);

// 3)
auto cmp_to_n = [&n](const std::string& a) { return compare_insensitive(a, n); };

auto x = std::find_if(vr.begin(), vr.end(), 
	[](const Rec& r) { return cmp_to_n(r.name); }
);

// 11. Use unnamed lambdas for simple function objects

auto x = std::remove_if(users.begin(), users.end(), 
	[](const User& a) { return a.id > 100; }
);

// 20. Prefer return values to output parameters

Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix res;
	// ...
	return res;
}

Matrix x = m1 + m2;		// move constructor; no temporary object is created, the result (rvalue) is instantly passed to the constructor of 'x' 

y = m3 + m3;			// move assignment; the same

// 21. Return multiple values by struct

auto [iter, success] = my_set.insert("Hello");
if (success)
	do_something_with(iter);

// Expensive copying is avoided by explicit move
std::pair<LargeObject, LargeObject> f(const std::string& input)
{
	LargeObject l1 = g(input);
	LargeObject l2 = h(input);
	// ...
	return { std::move(l1), std::move(l2) };	// no copies, just move data
}

// Or
std::pair<LargeObject, LargeObject> f(const std::string& input)
{
	// ...
	return { g(input), h(input) };	// no copies, no moves
}

// 26. Use unique_ptr<T> to transfer ownership 

std::unique_ptr<Shape> get_shape(std::istream& in)
{
	auto kind = read_header(in);
	switch (kind)
	{
		case kCircle:
			return std::make_unique<Circle>(in);
		case kTriangle:
			return std::make_unique<Triangle>(in);
		// ...
	}
}

// 27. Use shared_ptr<T> to share ownership

// ...
std::shared_ptr<const Image> im { /* ... */ };

std::thread t0 { /* ... */ , im };
std::thread t1 { /* ... */ , im };
std::thread t2 { /* ... */ , im };
std::thread t3 { /* ... */ , im };

// the last thread safely deletes the shared_ptr