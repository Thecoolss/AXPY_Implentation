import time
import numpy as np
import matplotlib.pyplot as plt

def axpy(a,x,y):
    if len(x)!=len(y):
        raise ValueError("X and Y must be the same size")
    for i in range(len(x)):
        y[i]+=a*x[i]

def generate_random_vector(n):
    return list(np.random.random(size=n))

def test_benchmark(a,size):
    repetitions=1000
    
    start_time=time.time()
    for i in range(repetitions):
        x=generate_random_vector(size)
        y=generate_random_vector(size) 
        axpy(a,x,y)
        
    end_time=time.time()
    average_duration=(end_time-start_time)/repetitions
    
    print(f"Size {size} took {average_duration} on average")
    return average_duration    
    

def plot(plot_times):
    plt.figure(figsize=(6,8))
    plt.xlabel("size")
    plt.ylabel("time")
    plt.plot(sizes,plot_times)
    plt.title("axpy time for differnt sizes")
    plt.show()

sizes=[100,1000,10000,100000,1000000]
a=2
plot_times=[]
for size in sizes:
    t=(test_benchmark(a, size))

    plot_times.append(t)
    
plot(plot_times)
    
    
    
    
    