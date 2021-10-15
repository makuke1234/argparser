#pragma once

#include <string_view>
#include <utility>
#include <iostream>
#include <iterator>

#include <cstdint>

namespace testing
{
	template<class First, class Second, std::size_t size>
		requires std::is_pointer_v<typename std::iterator_traits<Second>::value_type>
	class unique_pair
	{
	public:
		First first;
		Second second;

		unique_pair(First f, Second s)
			: first(f), second(s)
		{}
		~unique_pair() noexcept
		{
			if (second == nullptr)
				return;
			for (std::size_t i = 0; i < size; ++i)
			{
				delete[] second[i];
			}
			delete[] second;
		}
		[[nodiscard]] operator std::pair<First, Second>() const noexcept
		{
			return std::make_pair(this->first, this->second);
		}
	};

	namespace private_
	{
		void addToArgVec(char ** argv, const char * arg1)
		{
			auto sz{ std::char_traits<char>::length(arg1) + 1 };
			*argv = new char[sz];
			std::copy(arg1, arg1 + sz, *argv);
		}
		template<class ... Args>
		void addToArgVec(char ** argv, const char * arg1, Args && ... args)
		{
			auto sz{ std::char_traits<char>::length(arg1) + 1 };
			*argv = new char[sz];
			std::copy(arg1, arg1 + sz, *argv);
			private_::addToArgVec(argv + 1, std::forward<Args>(args)...);
		}
	}
	template<class ... Args>
	testing::unique_pair<int, char **, 1 + sizeof...(Args)> makeArgVec(const char * arg1, Args && ... args)
	{
		char ** argVec = new char*[1 + sizeof...(args)];
		if (argVec == nullptr)
			return { 0, nullptr };

		private_::addToArgVec(argVec, arg1, std::forward<Args>(args)...);

		return { 1 + sizeof...(args), argVec };
	}

	template<std::size_t num, class T>
	void Test(const T & v1, const T & v2)
	{
		std::cout << "Test #" << num;
		if (v1 == v2)
			std::cout << " passed\n";
		else
			std::cout << " failed\n";
	}

}
