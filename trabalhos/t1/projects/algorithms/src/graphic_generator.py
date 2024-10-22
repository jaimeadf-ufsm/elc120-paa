import matplotlib.pyplot as plt
import sys

algorithm_map = {
    "recursive_mergesort": "Mergesort Recursivo",
    "parallel_mergesort": "Mergesort Paralelo",
    "quicksort": "Quicksort",
    "quicksert": "Quicksert",
    "insertionsort": "Insertionsort",
}

def read_data_from_file(file_path):
    sizes = []
    times = []
    algorithm = ""
    source = ""
    
    with open(file_path, 'r') as file:
        lines = file.readlines()
        
        algorithm = lines[0].strip().split(": ")[1]

        if algorithm in algorithm_map:
            algorithm = algorithm_map[algorithm]

        source = lines[1].strip().split(": ")[1]

        for line in lines[2:]:
            size, time = line.strip().split(": ")
            sizes.append(int(size))
            times.append(float(time))
    
    return algorithm, source, sizes, times

def plot_data(files):
    plt.figure(figsize=(10, 6))
    algorithms_used = []

    for file in files:
        algorithm, source, sizes, times = read_data_from_file(file)
        label = f"{algorithm} - {source}"
        plt.plot(sizes, times, label=label)
        algorithms_used.append(algorithm)
    
    plt.xlabel('Número de elementos')
    plt.ylabel('Tempo (ns)')
    
    plt.legend()
    plt.grid(True)
    
    file_name = 'x'.join(algorithms_used).replace(" ", "_") + '.png'
    
    plt.savefig(file_name)
    plt.show()



files = sys.argv[1:]

if not files:
    print("uso: python graphic_generator.py arquivo1.txt arquivo2.txt ...")
else:
    plot_data(files)

