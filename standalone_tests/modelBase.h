#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include "nonNewton.h"

using callBackFunc = void (*)(NonNewton&, const std::string, const unsigned int);

int model(const std::string model_name, const std::string param_name, const enum NonNewton::NonNewtonMethod ENUM_MODEL, callBackFunc param_callBack)
{
	unsigned int numSamples = 1000;
	float increment = 1e-1f;
	unsigned numCases = 10;

	std::cout << "\n"<<model_name<<"!\n--------------------------------\n";
	for (unsigned int case_i = 0; case_i < numCases; case_i++)
	{
		std::cout << "Case " << case_i << "\t";

		NonNewton theCase;
		theCase.m_nonNewtonMethod = ENUM_MODEL;
		std::string filename = model_name + "_case_" + std::to_string(case_i) + ".txt";

        param_callBack(theCase, param_name, case_i);

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