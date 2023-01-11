#include <cstdlib>
#include <iostream>
#include <string>
#include "nonNewton.h"
#include "../modelBase.h"

int main()
{
    const std::string model_name = "PowerLaw";
	const std::string param_name = "power_index";
	auto ENUM_MODEL = NonNewton::ENUM_CROSS_MODEL;
    
    auto param_callBack = [](NonNewton& theCase, const std::string param_name, const unsigned int case_i) -> void
    {
        if(param_name == "consistency_index")
        {
            theCase.consistency_index = 10.0f * float(case_i);
            std::cout << param_name<<" " << theCase.consistency_index << "\t";
        }

        if(param_name == "power_index")
        {
            theCase.power_index = 0.3f + 0.1f * float(case_i);
            std::cout << param_name<<" " << theCase.power_index << "\t";
        }
    };

    model(model_name, param_name, ENUM_MODEL, param_callBack);
    return 0;
}