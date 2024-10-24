import argparse
import math

import matplotlib.pyplot as plt

algorithm_descriptions = {
    'recursive_mergesort': {
        'order': 0,
        'name': 'Merge Sort Recursivo',
        'best_case': lambda n: n * math.log2(n),
        'average_case': lambda n: n * math.log2(n),
        'worst_case': lambda n: n * math.log2(n),
    },
    'iterative_mergesort': {
        'order': 1,
        'name': 'Merge Sort Iterativo',
        'best_case': lambda n: n * math.log2(n),
        'average_case': lambda n: n * math.log2(n),
        'worst_case': lambda n: n * math.log2(n),
    },
    'parallel_mergesort': {
        'order': 2,
        'name': 'Merge Sort Paralelo',
        'best_case': lambda n: n * math.log2(n),
        'average_case': lambda n: n * math.log2(n),
        'worst_case': lambda n: n * math.log2(n),
    },
    'insertionsort': {
        'order': 3,
        'name': 'Insertion Sort',
        'best_case': lambda n: n,
        'average_case': lambda n: n ** 2,
        'worst_case': lambda n: n ** 2,
    },
    'quicksort': {
        'order': 4,
        'name': 'Quicksort',
        'best_case': lambda n: n * math.log2(n),
        'average_case': lambda n: n * math.log2(n),
        'worst_case': lambda n: n ** 2,
    },
    'quicksert': {
        'order': 5,
        'name': 'Quicksert',
        'best_case': lambda n: n * math.log2(n),
        'average_case': lambda n: n * math.log2(n),
        'worst_case': lambda n: n ** 2,
    }
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

def plot_time(args):
    plt.figure(figsize=(10, 6))
    benchmarks = []

    for file in args.benchmarks:
        benchmarks.append(read_benchmark(file))

    benchmarks.sort(key=lambda x: algorithm_descriptions[x['algorithm']]['order'])

    for benchmark in benchmarks:
        description = algorithm_descriptions[benchmark['algorithm']]

        label = f"{description['name']}"

        x = list(benchmark['results'].keys())
        y = [sum(times) / len(times) for times in benchmark['results'].values()]

        plt.plot(x, y, label=label)
    
    plt.xlabel('Número de elementos')
    plt.ylabel('Tempo médio (ns)')
    
    plt.legend()
    plt.grid(True)
    
    plt.savefig(args.output)

def plot_complexity(args):
    benchmark = read_benchmark(args.benchmark)
    description = algorithm_descriptions[benchmark['algorithm']]

    x = []

    best_case_y = []
    average_case_y = []
    worst_case_y = []

    for size, times in benchmark['results'].items():
        if size == 0:
            continue
            
        best_case_ratios = [time / description['best_case'](size) for time in times]
        average_case_ratios = [time / description['average_case'](size) for time in times]
        worst_case_ratios = [time / description['worst_case'](size) for time in times]

        x.append(size)
        best_case_y.append(sum(best_case_ratios) / len(best_case_ratios))
        average_case_y.append(sum(average_case_ratios) / len(average_case_ratios))
        worst_case_y.append(sum(worst_case_ratios) / len(worst_case_ratios))

    plt.figure(figsize=(10, 6))
    plt.plot(x, best_case_y, label=f"{description['name']} (Melhor caso)")
    plt.plot(x, average_case_y, label=f"{description['name']} (Caso médio)")
    plt.plot(x, worst_case_y, label=f"{description['name']} (Pior caso)")

    plt.xlabel('Número de elementos')
    plt.ylabel('Constante')

    plt.legend()
    plt.grid(True)

    plt.savefig(args.output)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(required=True)

    parser_time = subparsers.add_parser('time')
    parser_time.add_argument('-o', '--output', metavar='output.png', type=str, required=True)
    parser_time.add_argument('benchmarks', metavar='benchmark.txt', type=str, nargs='+')
    parser_time.set_defaults(func=plot_time)

    parser_complexity = subparsers.add_parser('complexity')
    parser_complexity.add_argument('-o', '--output', metavar='saida.png', type=str, required=True)
    parser_complexity.add_argument('benchmark', metavar='benchmark.txt', type=str)
    parser_complexity.set_defaults(func=plot_complexity)
    
    args = parser.parse_args()
    args.func(args)
