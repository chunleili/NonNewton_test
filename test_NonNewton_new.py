import matplotlib.pyplot as plt
import numpy as np

class NonNewton():
    def __init__(self, viscosity0=2000.0, viscosity_inf=1.0, consistency_index=1000.0, power_index=0.667, muC=10.0, yieldStress=200.0, criticalStrainRate=20.0):
        self.viscosity0 = viscosity0
        self.viscosity_inf = viscosity_inf
        self.consistency_index = consistency_index
        self.power_index = power_index
        self.muC = muC
        self.yieldStress = yieldStress
        self.criticalStrainRate = criticalStrainRate
    
    def computeViscosityNewtonian(self):
        return self.viscosity0
    
    def computeViscosityPowerLaw(self, strainRateNorm):
        return self.consistency_index * np.power(strainRateNorm, self.power_index - 1)
    
    def computeViscosityCrossModel(self, strainRateNorm):
        return self.viscosity_inf +  (self.viscosity0 - self.viscosity_inf) / (1 +  np.power(self.consistency_index * strainRateNorm, self.power_index))
    
    def computeViscosityCassonModel(self, strainRateNorm):
        return np.power(np.sqrt(self.muC) +  np.sqrt(self.yieldStress / strainRateNorm), 2)
    
    def computeViscosityCarreau(self, strainRateNorm):
        return self.viscosity_inf +  (self.viscosity0 - self.viscosity_inf) / (1.0 +  np.power(self.consistency_index * strainRateNorm * strainRateNorm, (1.0 - self.power_index)/2.0))
    
    def computeViscosityBingham(self, strainRateNorm):
        if strainRateNorm < self.criticalStrainRate:
            return self.viscosity0
        else:
            tau0 = self.criticalStrainRate * (self.viscosity0 - self.viscosity_inf)
            return tau0 / strainRateNorm + self.viscosity_inf
    
    def computeViscosityHerschelBulkley(self, strainRateNorm):
        if strainRateNorm < self.criticalStrainRate:
            return self.viscosity0
        else:
            tau0 = self.criticalStrainRate * (self.viscosity0 - self.viscosity_inf)
            return tau0 / strainRateNorm + self.consistency_index * pow(strainRateNorm, self.power_index - 1)


def test_NonNewton(model_name:str, viscosity0=2000.0, viscosity_inf=1.0, consistency_index=1000.0, power_index=0.667, muC=10.0, yieldStress=200.0, criticalStrainRate=20.0)->list:
    # TODO:更改参数！

    strainRateNorms = np.array([i*.1 for i in range(1,1000)])

    nonNewton = NonNewton(viscosity0, viscosity_inf, consistency_index, power_index, muC, yieldStress, criticalStrainRate)

    viscosity = []
    for strainRateNorm in strainRateNorms:
        if model_name == 'Newtonian':
            viscosity.append(nonNewton.computeViscosityNewtonian())
        elif model_name == 'PowerLaw':
            viscosity.append(nonNewton.computeViscosityPowerLaw(strainRateNorm))
        elif model_name == 'Cross':
            viscosity.append(nonNewton.computeViscosityCrossModel(strainRateNorm))
        elif model_name == 'Casson':
            viscosity.append(nonNewton.computeViscosityCassonModel(strainRateNorm))
        elif model_name == 'Carreau':
            viscosity.append(nonNewton.computeViscosityCarreau(strainRateNorm))
        elif model_name == 'Bingham':
            viscosity.append(nonNewton.computeViscosityBingham(strainRateNorm))
        elif model_name == 'HerschelBulkley':
            viscosity.append(nonNewton.computeViscosityHerschelBulkley(strainRateNorm))
        elif model_name == 'All':
            viscosity.append([
                nonNewton.computeViscosityNewtonian(),
                nonNewton.computeViscosityPowerLaw(strainRateNorm),
                nonNewton.computeViscosityCrossModel(strainRateNorm),
                nonNewton.computeViscosityCassonModel(strainRateNorm),
                nonNewton.computeViscosityCarreau(strainRateNorm),
                nonNewton.computeViscosityBingham(strainRateNorm),
                nonNewton.computeViscosityHerschelBulkley(strainRateNorm)])

    # 转置一下，方便画图
    if model_name == 'All':
        v_ = np.array(viscosity)
        viscosity = v_.transpose().tolist()
        
    return strainRateNorms, viscosity



def draw(x, y, color='r', label=''):
    plt.xlabel('shear rate(FNorm)')
    plt.ylabel('Viscosity')
    handle = plt.plot(x, y, color, label=label)
    return handle



if __name__ == "__main__":

    # 测试所有模型
    [x,y] = test_NonNewton('All')
    plt.figure()
    draw(x, y[0], 'y', label='Newtonian')
    draw(x, y[1], 'r', label='PowerLaw')
    draw(x, y[2], 'g', label='Cross')
    draw(x, y[3], 'b', label='Casson')
    draw(x, y[4], 'k', label='Carreau')
    draw(x, y[5], 'c', label='Bingham')
    draw(x, y[6], 'm', label='Herschel-Bulkley')
    plt.legend()
    plt.savefig('./pics/demo_All.jpg', dpi=300)


    # 测试单个模型
    # 测试Newtonian模型
    plt.figure()
    [x,y] = test_NonNewton('Newtonian')
    draw(x, y, 'y', label='Newtonian')
    plt.legend()
    plt.savefig('./pics/demo_Newtonian.jpg', dpi=300)

    # 测试PowerLaw模型
    plt.figure()
    [x,y] = test_NonNewton('PowerLaw', power_index=0.667) #通过给定不同参数来测试
    draw(x, y, 'r', label='power_index=0.667')
    [x,y] = test_NonNewton('PowerLaw', power_index=0.8) 
    draw(x, y, 'g', label='power_index=0.8')
    [x,y] = test_NonNewton('PowerLaw', power_index=1.1)
    draw(x, y, 'b', label='power_index=1.1')
    # TODO:测试更多参数！
    plt.legend()
    plt.savefig('./pics/demo_PowerLaw.jpg', dpi=300)

    # 测试Cross模型
    # TODO:...

    plt.show()