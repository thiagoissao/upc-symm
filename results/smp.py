# tempo de execução para tamanhos 1250, 1500, 1750, 2000
sequencial = [13.994742, 31.431768, 55.609789, 86.457611]
x1threads = [13.994742, 31.431768, 55.609789, 86.457611]
x4threads = [4.760144, 10.738476, 18.206237, 29.375492]  # done
x5Threads = [8.721793, 15.604561, 25.386556, 31.812699]
x6threads = [8.140086, 14.865918, 21.104520, 37.369909]  # done
x7Threads = [6.518414, 11.823945, 19.894386, 31.528810]
x8threads = [6.836251, 12.96531, 20.829177, 32.967965]  # done

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
