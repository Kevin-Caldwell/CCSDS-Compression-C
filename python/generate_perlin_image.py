import perlin
import matplotlib.pyplot as plt
import time
import numpy as np

if __name__ == "__main__":
    p = perlin.perlin(1000)
    img = p.three(100, 100, 100)
    frame = np.zeros(shape=(640, 512))
    start = time.clock_gettime_ns(0)
    for i in range(640):
        for j in range(512):
            frame[i, j] = p.three(i, j, 0)
    end = time.clock_gettime_ns(0)

    print((end - start) / 1000000000)
    plt.imshow(frame)
    plt.gray()
    plt.show()

    del img, frame
