#include "nonNewton.h"

int main(int argc, char** argv)
{
	unsigned int numSamples = 1000;
	float increment = 1e-1f;

    NonNewton case1;
	case1.m_nonNewtonMethod = NonNewton::ENUM_NEWTONIAN;
	std::cout<<"\nNewtonian!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case1.sample_x = i * increment;
		case1.computeNonNewtonViscosity();
		// case1.print();
		case1.printFile("Newtonian.txt");
	}

	NonNewton case2;
	case2.m_nonNewtonMethod = NonNewton::ENUM_POWER_LAW;
	std::cout<<"\nPower Law!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case2.sample_x = i * increment;
		case2.consistency_index = 1000.0f;
		case2.computeNonNewtonViscosity();
		// case2.print();
		case2.printFile("PowerLaw.txt");
	}

	NonNewton case3;
	case3.m_nonNewtonMethod = NonNewton::ENUM_CROSS_MODEL;
	std::cout<<"\nCross model!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case3.sample_x = i * increment;
		case3.computeNonNewtonViscosity();
		// case3.print();
		case3.printFile("Cross.txt");
	}

	NonNewton case4;
	case4.m_nonNewtonMethod = NonNewton::ENUM_CASSON_MODEL;
	std::cout<<"\nCasson model!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case4.sample_x = i * increment;
		case4.computeNonNewtonViscosity();
		// case4.print();
		case4.printFile("Casson.txt");
	}

	NonNewton case5;
	case5.m_nonNewtonMethod = NonNewton::ENUM_CARREAU;
	std::cout<<"\nCarreu model!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case5.sample_x = i * increment;
		case5.computeNonNewtonViscosity();
		// case5.print();
		case5.printFile("Carreau.txt");
	}

	NonNewton case6;
	case6.m_nonNewtonMethod = NonNewton::ENUM_BINGHAM;
	std::cout<<"\nBingham model!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case6.sample_x = i * increment;
		case2.consistency_index = 1000.0f;
		case6.computeNonNewtonViscosity();
		// case6.print();
		case6.printFile("Bingham.txt");
	}

	NonNewton case7;
	case7.m_nonNewtonMethod = NonNewton::ENUM_HERSCHEL_BULKLEY;
	std::cout<<"\nHerschel-Bulkley model!\n--------------------------------\n";
	for(unsigned int i = 0; i < numSamples; i++)
	{
		case7.sample_x = i * increment;
		case7.computeNonNewtonViscosity();
		// case7.print();
		case7.printFile("Herschel-Bulkley.txt");
	}


    return 0;
}