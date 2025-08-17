import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def plot_for_size(size,flags,plotted,values):
    plt.figure(figsize=(8,10))
    plt.title(f"{against} for size {size}")
    plt.plot(flags,values)
    plt.savefig(f"Axpy_{plotted}_{size}.png")
    plt.show()



benchmarks=pd.read_csv("axpy_benchmark.csv")
szs=[100,1000,10000,1e5,1e6,1e7,1e8]
flags=["No Flags","O0","O1","O2","O3"]
plotted=list(benchmarks.columns[1:])
#print(plotted)

sizes={}
for sz in szs:
    sizes[sz]=benchmarks[benchmarks["Size"]==sz]
    
    
#print(sizes)
for against in plotted:    
    for sz in szs:
        plotted_values=sizes[sz][against]
        plot_for_size(sz,flags,against,plotted_values)
    