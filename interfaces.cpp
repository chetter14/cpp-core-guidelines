// INTERFACES

// 4. Precise interfaces and strongly typed

// Be explicit about used arguments and their data types

void draw_rectangle(Point top_left, Point bottom_right);
void draw_rectangle(Point top_left, Size width_height);

draw_rectangle(p, Point{ 10, 20 });		// 2 corners
draw_rectangle(p, Size{ 10, 20 });		// corner and width and height info

// 7. 

void manipulate(Record& r)
{
	std::lock_guard<std::mutex> lock {m};	// ensures that lock is released after function ends
	// ...	
}

// 10. Use exceptions for errors

int val, error_code;					// need to initialize variables first
std::tie(val, error_code) = do_something();
if (error_code) 
{
	// ...
}
// ... use val ... 

auto [val, error_code] = do_something();
if (error_code) 
{
	// ...
}
// ... use val ... 

// 13. do not pass array as pointers

void copy_n(const T* p, const T* q, int n);	// from [p:p+n) to [q:q+n)

void copy_n(std::span<const T> p, std::span<T> q);	// copy p to q

void draw(std::span<Circle>);
Circle arr[10];

draw(std::span<Circle>(arr));	// deduce the number of elements
draw(arr);						// deduce the type and number of elements

// 23. Keep the number of arguments low

template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
					InputIterator2 first2, InputIterator2 last2,
					OutputIterator result, Compare compare);
					
// put first and last iterators into one structure, compare by "<"
template<class InputRange1, class InputRange2, class OutputIterator>
OutputIterator merge(InputRange1 r1, InputRange2 r2, OutputIterator result);