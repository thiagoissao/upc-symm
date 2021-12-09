from matplotlib import lines
import matplotlib.pyplot as plt

# tempo de execução para tamanhos 1250, 1500, 1750, 2000
sequencial = [13.994742, 31.431768, 55.609789, 86.457611]
x1threads = [13.994742, 31.431768, 55.609789, 86.457611]

x4threads = [4.275524, 9.748319, 16.570292, 26.094554]
x5Threads = [9.463244, 18.137625, 25.655843, 40.691748]
x6threads = [8.527069, 12.201564, 18.653168, 37.474455]
x7Threads = [6.328852, 12.942266, 21.063818, 31.369637]
x8threads = [6.453619, 11.657835, 18.787399, 29.548539]

y1250 = [
    sequencial[0] / x1threads[0],
    sequencial[0] / x4threads[0],
    sequencial[0] / x5Threads[0],
    sequencial[0] / x6threads[0],
    sequencial[0] / x7Threads[0],
    sequencial[0] / x8threads[0],
]

y1500 = [
    sequencial[1] / x1threads[1],
    sequencial[1] / x4threads[1],
    sequencial[1] / x5Threads[1],
    sequencial[1] / x6threads[1],
    sequencial[1] / x7Threads[1],
    sequencial[1] / x8threads[1],
]

y1750 = [
    sequencial[2] / x1threads[2],
    sequencial[2] / x4threads[2],
    sequencial[2] / x5Threads[2],
    sequencial[2] / x6threads[2],
    sequencial[2] / x7Threads[2],
    sequencial[2] / x8threads[2],
]

y2000 = [
    sequencial[3] / x1threads[3],
    sequencial[3] / x4threads[3],
    sequencial[3] / x5Threads[3],
    sequencial[3] / x6threads[3],
    sequencial[3] / x7Threads[3],
    sequencial[3] / x8threads[3],
]


points = [1, 4, 5, 6, 7, 8]
plt.plot(points, points, label="ideal")
plt.plot(points, y1250, label="1250", linestyle='dashed', marker='.')
plt.plot(points, y1500, label="1500", linestyle='dashed', marker='.')
plt.plot(points, y1750, label="1750", linestyle='dashed', marker='.')
plt.plot(points, y2000, label="2000", linestyle='dashed', marker='.')

plt.xlabel('Number of Threads')
plt.ylabel('Speedup')

plt.title('Symm Parallel UPC - Network UDP')

plt.legend()

plt.show()
