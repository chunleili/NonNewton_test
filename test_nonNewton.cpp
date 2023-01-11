#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
// #include "Utils/mathUtils.h"
#include <Eigen/Dense>
using namespace Eigen;

class NonNewton
{
public:
    NonNewton();
    ~NonNewton()=default;

    void computeNonNewtonViscosity();
    void computeViscosityNewtonian();
    void computeViscosityPowerLaw();
    void computeViscosityCrossModel();
    void computeViscosityCassonModel();
	void computeViscosityCarreau();
	void computeViscosityBingham();
	void computeViscosityHerschelBulkley();
    void calcStrainRate();

    enum NonNewtonMethod { ENUM_NEWTONIAN, ENUM_POWER_LAW, ENUM_CROSS_MODEL, ENUM_CASSON_MODEL, ENUM_CARREAU, ENUM_BINGHAM, ENUM_HERSCHEL_BULKLEY};
    NonNewtonMethod m_nonNewtonMethod = ENUM_NEWTONIAN;

    unsigned int numParticles = 1;
    std::vector<Eigen::Matrix3f> m_strainRate;
    std::vector<float> m_strainRateNorm;

    std::vector<float> m_nonNewtonViscosity;
    float power_index = 0.3f;
    float consistency_index = 0.5;
    float m_viscosity0 = 2000.0f; //initial viscosity
    float m_viscosity_inf = 1.0f; //infinite viscosity(must lower than initial viscosity)
    // float m_muC = 0.00298f;
    // float m_tauC = 0.02876f;
    // float m_lambda = 4.020f;
    float m_muC = 10;
    float m_tauC = 40000;
    float m_lambda = 0.5;
    float m_maxViscosity = 0.0f;
    float m_avgViscosity = 0.0f;
	float critical_strainRate = 20f;

    float sample_x = 0.1f;

	void print()
	{
		std::cout << "sample_x = " << sample_x << std::endl;
		std::cout << "m_nonNewtonViscosity[0] = " << m_nonNewtonViscosity[0] << std::endl;
	}
	void printFile(std::string filename)
	{
		std::fstream fout;
		fout.open(filename, std::ios::app);
		fout << sample_x << "\t";
		fout << m_nonNewtonViscosity[0] << std::endl;
		fout.close();
	}
};

//free function 
static float FNorm(std::vector<float> & vec)
{
	float res = 0.0;
	for (int i = 0; i < vec.size(); i++)
		res += vec[i] * vec[i];
	res = sqrt(res)	;

	return res;
}


NonNewton::NonNewton()
{
    m_strainRate.resize(numParticles,Matrix3f::Zero());
    m_nonNewtonViscosity.resize(numParticles,0.0f);
	m_strainRateNorm.resize(numParticles,0.0f);
}

void NonNewton::calcStrainRate()
{
    for (unsigned int i = 0; i < numParticles; ++i)
    {
		m_strainRateNorm[i] = sample_x;
		m_strainRateNorm[i] = m_strainRate[i].norm();
    }
}

void NonNewton::computeNonNewtonViscosity()
{
	calcStrainRate();

	if(m_nonNewtonMethod == NonNewtonMethod::ENUM_POWER_LAW)
	{
		computeViscosityPowerLaw();
	}
	else if(m_nonNewtonMethod == NonNewtonMethod::ENUM_CROSS_MODEL)
	{
		computeViscosityCrossModel();
	}
	else if (m_nonNewtonMethod == NonNewtonMethod::ENUM_CASSON_MODEL)
	{
		computeViscosityCassonModel();
	}
	else if (m_nonNewtonMethod == NonNewtonMethod::ENUM_CARREAU)
	{
		computeViscosityCarreau();
	}
	else if (m_nonNewtonMethod == NonNewtonMethod::ENUM_BINGHAM)
	{
		computeViscosityBingham();
	}
	else if (m_nonNewtonMethod == NonNewtonMethod::ENUM_HERSCHEL_BULKLEY)
	{
		computeViscosityHerschelBulkley();
	}
	else
	{
		computeViscosityNewtonian();
	}

	m_maxViscosity = 0.0;
	// m_maxViscosity = maxField(m_nonNewtonViscosity, numParticles);
	// m_avgViscosity = averageField(m_nonNewtonViscosity, numParticles);
}



void NonNewton::computeViscosityNewtonian() 
{
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		m_nonNewtonViscosity[i] = m_viscosity0;
	}
}

void NonNewton::computeViscosityPowerLaw() 
{
	
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		m_nonNewtonViscosity[i] = consistency_index * pow(m_strainRateNorm[i], power_index - 1);
	}
}

void NonNewton::computeViscosityCrossModel() 
{
	assert((m_viscosity0 - m_viscosity_inf >= 0.0) && "the viscosity0 must be larger than viscosity_inf");
	if(m_viscosity0 - m_viscosity_inf < 0.0)
	{
		std::cout << "the viscosity0 must be larger than viscosity_inf" << std::endl;
		throw std::runtime_error("the viscosity0 must be larger than viscosity_inf");
	}
	for (unsigned int i = 0; i < numParticles; ++i)
	{

		m_nonNewtonViscosity[i] = m_viscosity_inf +  (m_viscosity0 - m_viscosity_inf) / (1 +  pow(consistency_index * m_strainRateNorm[i], power_index)) ;
	}
}

void NonNewton::computeViscosityCassonModel() 
{
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		m_nonNewtonViscosity[i] = sqrt(m_muC) + sqrt(m_tauC) / (sqrt(m_lambda) + sqrt(m_strainRateNorm[i]));
	}
}


void NonNewton::computeViscosityCarreau() 
{
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		m_nonNewtonViscosity[i] = m_viscosity_inf +  (m_viscosity0 - m_viscosity_inf) / (1.0f +  pow(consistency_index * m_strainRateNorm[i]*m_strainRateNorm[i], (1.0f - power_index)/2.0f)) ;
	}
}



void NonNewton::computeViscosityBingham() 
{
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		if(m_strainRateNorm[i] < critical_strainRate)
			m_nonNewtonViscosity[i] = m_viscosity0;
		else
		{
			float tau0 = critical_strainRate * (m_viscosity0 - m_viscosity_inf);
			m_nonNewtonViscosity[i] = tau0 / m_strainRateNorm[i] + m_viscosity_inf;
		}
	}
}

void NonNewton::computeViscosityHerschelBulkley() 
{
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		if(m_strainRateNorm[i] < critical_strainRate)
			m_nonNewtonViscosity[i] = m_viscosity0;
		else
		{
			float tau0 = critical_strainRate * (m_viscosity0 - m_viscosity_inf);
			m_nonNewtonViscosity[i] = tau0 / m_strainRateNorm[i] + consistency_index * pow(m_strainRateNorm[i], power_index - 1);
		}
	}
}


int main()
{
	unsigned int numSamples = 1000;
	float increment = 1e-3f;

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