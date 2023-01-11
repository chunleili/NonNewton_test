#include <cstdlib>
#include <iostream>
#include <string>
#include "nonNewton.h"

//针对Casson模型，测试不同参数
int main(int argc, char **argv)
{
	unsigned int numSamples = 1000;
	float increment = 1e-1f;

	unsigned numCases = 10;

	std::cout << "\nCasson model!\n--------------------------------\n";
	for (unsigned int case_i = 0; case_i < numCases; case_i++)
	{
		std::cout << "Case " << case_i<<"\t" ;
		NonNewton case4;
		case4.m_nonNewtonMethod = NonNewton::ENUM_CASSON_MODEL;

		//测试不同的muC
		// case4.m_muC = 1.0f * float(case_i);
		// std::cout << "m_muC " << case4.m_muC<< "\t" ;

		//测试不同的屈服应力
		case4.m_yieldStress = 10.0f * float(case_i);
		std::cout << "m_yieldStress " << case4.m_yieldStress<< std::endl ;


		for (unsigned int i = 0; i < numSamples; i++)
		{
			case4.sample_x = i * increment;
			case4.computeNonNewtonViscosity();
			std::string filename = "Casson_case_" + std::to_string(case_i) + ".txt";
			case4.printFile(filename);
		}
	}
	return 0;
}