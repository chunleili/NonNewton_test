import matplotlib.pyplot as plt
import numpy as np


# TODO:
model_name = "Cross"
param_name = "power_index"
param_val = [0.3 + 0.1* i for  i in range(0, 10)]

def read_file(filename):
    with open(filename) as f:
        lines = f.readlines()
    return lines

def draw(filename, color='r', label=''):
    lines = read_file(filename)
    x = []
    y = []
    for line in lines:
        data = line.split()
        x.append(float(data[0]))
        y.append(float(data[1]))

    handle = plt.plot(x, y, color, label=label)
    return handle

def run():
    plt.figure()
    plt.xlabel('shear rate(FNorm)')
    plt.ylabel('Viscosity')

    import matplotlib.colors as mcolors
    colors=list(mcolors.TABLEAU_COLORS.keys())

    for i in range(0, 10):
        filename = f"bin/{model_name}_case_{i}.txt"
        label_ = f"{param_name} = {param_val[i]:.1f}" #TODO:
        draw(filename ,color=mcolors.TABLEAU_COLORS[colors[i]], label=label_)

    plt.title(model_name + ' of different parameters')
    plt.legend()
    plt.savefig('./demo.jpg', dpi=300)
    plt.show()

if __name__ == '__main__':
    run()