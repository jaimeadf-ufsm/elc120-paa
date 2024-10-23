import sys
import argparse

import matplotlib.pyplot as plt

algorithm_labels = {
    'recursive_mergesort': 'Mergesort Recursivo',
    'parallel_mergesort': 'Mergesort Paralelo',
    'quicksort': 'Quicksort',
    'quicksert': 'Quicksert',
    'insertionsort': 'Insertionsort',
}

def parse_data(file_path):
    sizes = []
    times = []
    algorithm = ''
    source = ''
    
    with open(file_path, 'r') as file:
        lines = file.readlines()
        
        algorithm = lines[0].strip().split(': ')[1]
        source = lines[1].strip().split(': ')[1]

        for line in lines[2:]:
            size, time = line.strip().split(': ')
            sizes.append(int(size))
            times.append(float(time))
    
    return algorithm, source, sizes, times

def plot_data(files):
    plt.figure(figsize=(10, 6))
    algorithms_used = []

    for file in files:
        algorithm, source, sizes, times = parse_data(file)
        label = f'{algorithm_labels.get(algorithm, algorithm)} - {source}'
        plt.plot(sizes, times, label=label)
        algorithms_used.append(algorithm)
    
    plt.xlabel('Número de elementos')
    plt.ylabel('Tempo (ns)')
    
    plt.legend()
    plt.grid(True)
    
    file_name = 'x'.join(algorithms_used).replace(' ', '_') + '.png'
    
    plt.savefig(file_name)
    plt.show()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Gera gráficos a partir de arquivos de benchmark.')
    parser.add_argument('files', metavar='arquivo', type=str, nargs='+', help='Arquivos de dados para gerar os gráficos.')
    args = parser.parse_args()
    
    plot_data(args.files)

