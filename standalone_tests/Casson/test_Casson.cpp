#include <cstdlib>
#include <iostream>
#include <string>
#include "nonNewton.h"

int main(int argc, char **argv)
{
	unsigned int numSamples = 1000;
	float increment = 1e-1f;

	unsigned numCases = 10;
	const std::string model_name = "PowerLaw";
	const std::string param_name = "yieldStress";
	auto ENUM_MODEL = NonNewton::ENUM_CROSS_MODEL;

	std::cout << "\n"<<model_name<<"!\n--------------------------------\n";
	for (unsigned int case_i = 0; case_i < numCases; case_i++)
	{
		std::cout << "Case " << case_i << "\t";

		NonNewton theCase;
		theCase.m_nonNewtonMethod = ENUM_MODEL;
		std::string filename = model_name + "_case_" + std::to_string(case_i) + ".txt";

		if(param_name == "consistency_index")
		{
			//TODO:
			case4.m_muC = 1.0f * float(case_i);
			std::cout << "m_muC " << case4.m_muC<< "\t" ;
		}

		if(param_name == "yieldStress")
		{
			//TODO:
			case4.m_yieldStress = 10.0f * float(case_i);
			std::cout << param_name << case4.m_yieldStress<< std::endl ;
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