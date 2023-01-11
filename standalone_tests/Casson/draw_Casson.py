import matplotlib.pyplot as plt
import numpy as np

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


import matplotlib.colors as mcolors
colors=list(mcolors.TABLEAU_COLORS.keys())


if __name__ == '__main__':
    plt.figure()
    plt.xlabel('shear rate(FNorm)')
    plt.ylabel('Viscosity')
    for i in range(1, 10):
        print('bin/Casson_case_%d.txt' % i)

        # 不同的muC
        # draw('bin/Casson_case_%d.txt' % i,color=mcolors.TABLEAU_COLORS[colors[i]], label='muC = %.0f' % (i*10000))

        # 不同的yield_stress
        draw('bin/Casson_case_%d.txt' % i,color=mcolors.TABLEAU_COLORS[colors[i]], label='yield_stress = %.0f' % (i*10))

    plt.ylim(0,500)
    plt.title('Casson of different parameters')
    plt.legend()
    plt.savefig('./demo.jpg', dpi=300)
    plt.show()