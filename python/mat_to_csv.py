import scipy
import numpy as np
import sys
import csv_io


def load_pic(file_name, header="indian_pines"):

    data = scipy.io.loadmat(file_name)
    data = data[header]  # data is dictionary, only take the array part
    data = np.array(data, dtype=np.int64)

    # data_n = np.zeros_like(data)
    # size = data_n.shape

    # for i in range(size[0]):
    #     for j in range(size[1]):
    #         for k i
    return data

if __name__ == "__main__":
    argS = sys.argv

    print(argS)
    if(len(argS) > 1):
        data = load_pic(argS[1], argS[2])
        csv_io.SaveCSV(data, f"{argS[2]}.csv")
