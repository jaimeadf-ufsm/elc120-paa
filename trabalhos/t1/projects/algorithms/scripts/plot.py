import sys
import argparse

import matplotlib.pyplot as plt

algorithm_descriptions = {
    'recursive_mergesort': ('Merge Sort Recursivo', 0),
    'iterative_mergesort': ('Merge Sort Iterativo', 1),
    'parallel_mergesort': ('Merge Sort Paralelo', 2),
    'insertionsort': ('Insertion Sort', 3),
    'quicksort': ('Quicksort', 4),
    'quicksert': ('Quicksert', 5),
}

def read_benchmark(file_path):
    results = {}
    algorithm = ""
    source = ""

    with open(file_path, 'r') as file:
        lines = file.readlines()
        
        algorithm = lines[0].strip().split(": ")[1]
        source = lines[1].strip().split(": ")[1]

        for line in lines[2:]:
            parts = line.strip().split(": ")

            if len(parts) == 2:  
                size = int(parts[0])
                times = list(map(float, parts[1].split()))

                results[size] = times
    
    return {
        'algorithm': algorithm,
        'source': source, 
        'results': results
    }

def plot_data(benchmark_files, output_file):
    plt.figure(figsize=(10, 6))
    benchmarks = []

    for file in benchmark_files:
        benchmarks.append(read_benchmark(file))

    benchmarks.sort(key=lambda x: algorithm_descriptions[x['algorithm']][1])

    for benchmark in benchmarks:
        description = algorithm_descriptions[benchmark['algorithm']]

        label = f"{description[0]}"

        sizes = list(benchmark['results'].keys())
        average_results = [sum(times) / len(times) for times in benchmark['results'].values()]

        plt.plot(sizes, average_results, label=label)
    
    plt.xlabel('Número de elementos')
    plt.ylabel('Tempo médio (ns)')
    
    plt.legend()
    plt.grid(True)
    
    plt.savefig(output_file)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Gera gráficos a partir de arquivos de benchmark.')
    parser.add_argument('output_file', metavar='saida.png', type=str)
    parser.add_argument('benchmark_files', metavar='benchmark.txt', type=str, nargs='+')
    args = parser.parse_args()
    
    plot_data(args.benchmark_files, args.output_file)

