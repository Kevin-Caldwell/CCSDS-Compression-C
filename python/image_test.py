from mat_to_csv import load_pic
import matplotlib.pyplot as plt


def load_indian_pines():
    ip = load_pic("data/test-images/Indian_pines.mat")
    return ip


if __name__ == "__main__":
    ip = load_indian_pines()
    wavelength = ip[0, 10, :]

    plt.plot(wavelength)
    plt.show()
