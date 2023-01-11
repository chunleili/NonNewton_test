import matplotlib.pyplot as plt
import numpy as np

class DrawBase:
    def __init__(self, model_name, param_name, param_val, case_start=0, case_end=10):
        self.model_name = model_name
        self.param_name = param_name
        self.param_val = param_val
        self.case_start = case_start
        self.case_end = case_end

    def read_file(self, filename):
        with open(filename) as f:
            lines = f.readlines()
        return lines

    def draw(self, filename, color='r', label=''):
        lines = self.read_file(filename)
        x = []
        y = []
        for line in lines:
            data = line.split()
            x.append(float(data[0]))
            y.append(float(data[1]))

        handle = plt.plot(x, y, color, label=label)
        return handle

    def run(self):
        plt.figure()
        plt.xlabel('shear rate(FNorm)')
        plt.ylabel('Viscosity')

        import matplotlib.colors as mcolors
        colors=list(mcolors.TABLEAU_COLORS.keys())

        for i in range(self.case_start, self.case_end):
            filename = f"bin/{self.model_name}_case_{i}.txt"
            label_ = f"{self.param_name} = {self.param_val[i]:.1f}" #TODO:
            self.draw(filename ,color=mcolors.TABLEAU_COLORS[colors[i]], label=label_)

        plt.title(self.model_name + ' of different '+ self.param_name)
        plt.legend()
        plt.savefig(f'./{model_name}_{param_name}.jpg', dpi=300)
        plt.show()

if __name__ == '__main__':
    model_name = "PowerLaw"
    param_name = "power_index"
    param_val = [0.3 + 0.1* i for  i in range(0, 10)]
    a = DrawBase(model_name, param_name, param_val)
    a.run()