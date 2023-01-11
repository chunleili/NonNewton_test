#include <cstdlib>
#include <iostream>
#include <string>
#include "nonNewton.h"

int main(int argc, char **argv)
{
	const std::string model_name = "Cross";
	const std::string param_name = "power_index";
	auto ENUM_MODEL = NonNewton::ENUM_CROSS_MODEL;

	auto param_callBack = [](NonNewton &theCase, const std::string param_name, const unsigned int case_i) -> void
	{
		if (param_name == "consistency_index")
		{
			// TODO:
			theCase.consistency_index = 10.0f * float(case_i);
			std::cout << param_name << " " << theCase.consistency_index << "\t";
		}

		// 测试不同的power_index
		if (param_name == "power_index")
		{
			// TODO:
			theCase.power_index = 0.3f + 0.1f * float(case_i);
			std::cout << param_name << " " << theCase.power_index << "\t";
		}
	};

	return 0;
}