import sys
import argparse

import matplotlib.pyplot as plt

algorithm_labels = {
    'recursive_mergesort': 'Mergesort Recursivo',
    'parallel_mergesort': 'Mergesort Paralelo',
    'quicksort': 'Quicksort',
    'quicksert': 'Quicksert',
    'insertionsort': 'Insertionsort',
    'iterative_mergesort': 'Mergesort Iterativo',
}

def read_data_from_file(file_path):
    sizes = {}
    algorithm = ""
    source = ""

    with open(file_path, 'r') as file:
        lines = file.readlines()
        
        algorithm = lines[0].strip().split(": ")[1]

        if algorithm in algorithm_labels:
            algorithm = algorithm_labels[algorithm]

        source = lines[1].strip().split(": ")[1]

        for line in lines[2:]:
            parts = line.strip().split(": ")
            if len(parts) == 2:  
                size = int(parts[0])
                times = list(map(float, parts[1].split()))
                if size not in sizes:
                    sizes[size] = []
                sizes[size].extend(times)
                print(sizes[size])
    
    avg_times = {size: sum(times) / len(times) for size, times in sizes.items()}

    return algorithm, source, list(avg_times.keys()), list(avg_times.values())


def plot_data(files):
    plt.figure(figsize=(10, 6))
    algorithms_used = []

    for file in files:
        algorithm, source, sizes, avg_times = read_data_from_file(file)
        label = f"{algorithm} - {source}"
        plt.plot(sizes, avg_times, label=label)
        algorithms_used.append(algorithm)
    
    plt.xlabel('Número de elementos')
    plt.ylabel('Tempo médio (ns)')
    
    plt.legend()
    plt.grid(True)
    
    file_name = 'x'.join(algorithms_used).replace(" ", "_") + '.png'
    
    plt.savefig(file_name)
    plt.show()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Gera gráficos a partir de arquivos de benchmark.')
    parser.add_argument('files', metavar='arquivo', type=str, nargs='+', help='Arquivos de dados para gerar os gráficos.')
    args = parser.parse_args()
    
    plot_data(args.files)

