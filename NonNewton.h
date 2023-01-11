#pragma once
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
    float power_index = 0.667f;
    float consistency_index = 100.0f;
    float m_viscosity0 = 2000.0f; //initial viscosity
    float m_viscosity_inf = 1.0f; //infinite viscosity(must lower than initial viscosity)
	float m_criticalStrainRate = 20.0f;
    float m_muC = 10.0f;
	// float m_yieldStress = (m_viscosity0 - m_viscosity_inf) * m_criticalStrainRate;
	float m_yieldStress = 200.0f;
    // float m_lambda = 0.5;
    float m_maxViscosity = 0.0f;
    float m_avgViscosity = 0.0f;

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
	//计算应变率，这里先更改为一个固定值
    for (unsigned int i = 0; i < numParticles; ++i)
    {
		m_strainRateNorm[i] = sample_x;
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
		float res = sqrt(m_muC) +  sqrt(m_yieldStress / m_strainRateNorm[i]);
		m_nonNewtonViscosity[i] = res * res;
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
		if(m_strainRateNorm[i] < m_criticalStrainRate)
			m_nonNewtonViscosity[i] = m_viscosity0;
		else
		{
			float tau0 = m_criticalStrainRate * (m_viscosity0 - m_viscosity_inf);
			m_nonNewtonViscosity[i] = tau0 / m_strainRateNorm[i] + m_viscosity_inf;
		}
	}
}

void NonNewton::computeViscosityHerschelBulkley() 
{
	for (unsigned int i = 0; i < numParticles; ++i)
	{
		if(m_strainRateNorm[i] < m_criticalStrainRate)
			m_nonNewtonViscosity[i] = m_viscosity0;
		else
		{
			float tau0 = m_criticalStrainRate * (m_viscosity0 - m_viscosity_inf);
			m_nonNewtonViscosity[i] = tau0 / m_strainRateNorm[i] + consistency_index * pow(m_strainRateNorm[i], power_index - 1);
		}
	}
}
