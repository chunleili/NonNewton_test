#include <cstdlib>
#include <iostream>
#include <string>
#include "nonNewton.h"

int main(int argc, char **argv)
{
	unsigned int numSamples = 1000;
	float increment = 1e-1f;

	unsigned numCases = 10;
	const std::string model_name = "Cross";
	const std::string param_name = "power_index";
	auto ENUM_MODEL = NonNewton::ENUM_CROSS_MODEL;

	std::cout << "\n"<<model_name<<"!\n--------------------------------\n";
	for (unsigned int case_i = 0; case_i < numCases; case_i++)
	{
		std::cout << "Case " << case_i << "\t";

		NonNewton theCase;
		theCase.m_nonNewtonMethod = ENUM_MODEL;
		std::string filename = model_name + "_case_" + std::to_string(case_i) + ".txt";

		// 测试不同的consistency_index
		if(param_name == "consistency_index")
		{
			//TODO:
			theCase.consistency_index = 10.0f * float(case_i);
			std::cout << param_name<<" " << theCase.consistency_index << "\t";
		}

		// 测试不同的power_index
		if(param_name == "power_index")
		{
			//TODO:
			theCase.power_index = 0.3f + 0.1f * float(case_i);
			std::cout << param_name<<" " << theCase.power_index << "\t";
		}

		std::cout<<std::endl;

		for (unsigned int i = 0; i < numSamples; i++)
		{
			theCase.sample_x = i * increment;

			theCase.computeNonNewtonViscosity();
			theCase.printFile(filename);
		}
	}
	return 0;
}
