#include "../argparser.hpp"

#include "testing.hpp"

#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] const char * const argv[])
{
	/*argparser::Tokeniser cmdline{ argc, argv };

	if (auto token{ cmdline.tokenise(argparser::regex::dashTemplate("output=", "out=")) }; token == true)
	{
		std::cout << "Match: " << token.get() << '\n';
	}
	std::cout << std::flush;*/

	{
		auto av{ testing::makeArgVec("-out=string", "-input=output") };
		argparser::Tokeniser token(av);
		testing::Test<1>(
			token.tokenise(
				argparser::regex::dashTemplate("output=", "out=")
			).get(),
			std::string("string")
		);
		testing::Test<2>(
			token.tokenise(
				argparser::regex::dashTemplate("input=")
			).get(),
			std::string("output")
		);
		testing::Test<3>(
			token.tokenise(
				argparser::regex::dashTemplate(".+=")
			).get(),
			std::string("string")
		);
		testing::Test<4>(
			token.tokenise(
				argparser::regex::dashTemplate(".+="),
				1
			).get(),
			std::string("output")
		);

	}

	return 0;
}
