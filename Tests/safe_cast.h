// 1) Negative risk only. (A & ~B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	!(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	if (src < 0)
		throw std::overflow_error("Source value is negative.");
	else
		dst = static_cast<U>(src);
}

// 2) Positive risk only. (~A & B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	!(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	if (src > static_cast<T>(std::numeric_limits<U>::max()))
		throw std::overflow_error("Source value is too high.");
	else
		dst = static_cast<U>(src);
}

// 3) Both negative and positive risks. (A & B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	if (src < 0)
		throw std::overflow_error("Source value is negative.");
	else if (src > static_cast<T>(std::numeric_limits<U>::max()))
		throw std::overflow_error("Source value is too high.");
	else
		dst = static_cast<U>(src);
}

// 4) No risk. (~A & ~B)
// If an overflow is about to happen, throws an exception.
template <typename T, typename U>
typename std::enable_if<
	!(std::is_signed<T>::value && std::is_unsigned<U>::value) &&
	!(std::is_integral<T>::value && std::is_integral<U>::value && ((sizeof(T) > sizeof(U)) || 
	(std::is_unsigned<T>::value && std::is_signed<U>::value && sizeof(T) == sizeof(U)))),
	void>::type SafeCast(const T src, U &dst)
{
	dst = static_cast<U>(src);
}

