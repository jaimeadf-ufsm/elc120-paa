import argparse

import matplotlib.pyplot as plt

method_names = {
    0: 'Primeiro elemento',
    1: 'Elemento do meio',
    2: 'Último elemento',
}

def read_benchmark(file_path):
    results = {}
    method = -1
    source = -1

    with open(file_path, 'r') as file:
        lines = file.readlines()
        
        method, source = map(int, lines[0].strip().split())

        for line in lines[1:]:
            parts = line.strip().split(": ")

            if len(parts) == 2:  
                size = int(parts[0])
                comparisons = list(map(float, parts[1].split()))

                results[size] = comparisons
    
    return {
        'method': method,
        'source': source, 
        'results': results
    }

def plot(args):
    plt.figure(figsize=(10, 6))
    benchmarks = []

    for file in args.benchmarks:
        benchmarks.append(read_benchmark(file))

    benchmarks.sort(key=lambda x: x['method'])

    for benchmark in benchmarks:
        label = method_names[benchmark['method']]

        x = list(benchmark['results'].keys())
        y = [sum(comparisons) / len(comparisons) for comparisons in benchmark['results'].values()]

        plt.plot(x, y, label=label)
    
    plt.xlabel('Número de elementos')
    plt.ylabel('Número de comparações médio')
    
    plt.legend()
    plt.grid(True)
    
    plt.savefig(args.output)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-o', '--output', metavar='output.png', type=str, required=True)
    parser.add_argument('benchmarks', metavar='benchmark.txt', type=str, nargs='+')
    parser.set_defaults(func=plot)

    args = parser.parse_args()
    args.func(args)
