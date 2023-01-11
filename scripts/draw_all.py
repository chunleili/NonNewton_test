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

if __name__ == '__main__':
    plt.figure()
    plt.xlabel('shear rate(FNorm)')
    plt.ylabel('Viscosity')
    draw('bin/Newtonian.txt', 'y', label='Newtonian')
    draw('bin/PowerLaw.txt', 'r', label='PowerLaw')
    draw('bin/Cross.txt', 'g', label='Cross')
    draw('bin/Casson.txt', 'b', label='Casson')
    draw('bin/Carreau.txt', 'k', label='Carreau')
    draw('bin/Bingham.txt', 'c', label='Bingham')
    draw('bin/Herschel-Bulkley.txt', 'm', label='Herschel-Bulkley')
    plt.legend()
    plt.savefig('./demo.jpg', dpi=300)
    plt.show()