import numpy as np
import compression as comp
from sklearn.metrics import mean_squared_error
import csv

def ReadCSV(filename):
    f = open(filename, 'r')
    fulltxt = f.read()
    data = []
    num = 0
    for i in range(len(fulltxt)):
        if str(fulltxt[i]).isnumeric():
            num *= 10
            num += int(fulltxt[i])
        else:
            data.append(num)
            num = 0
        if(i % (len(fulltxt) // 100) == 0):
            print(f"Reading... {int(i/len(fulltxt)*100)}%", end="\r")


    f.close()
    del fulltxt
    del num

    print("Finished Reading...")

    Nx,Ny,Nz = data[0], data[1], data[2]

    del data[0]
    del data[0]
    del data[0]


    numbers = np.array(data, dtype=int)
    del data
    numbers.resize((Nx,Ny,Nz))

    return numbers

def SaveCSV(np_array_3d, output_path):
    np_array_1d = np_array_3d.ravel()
    np_array_1d = np.insert(np_array_1d, 0, np_array_3d.shape)
    print(np_array_1d)
    np.savetxt(output_path, np_array_1d, fmt='%i', newline=",")
    print("CSV file saved successfully.")

data = ReadCSV("../build/raw.csv")
Nx, Ny, Nz = data.shape

python_predicted, python_residuals = comp.predictor_debug(data)
SaveCSV(python_predicted, "./python_predicted.csv")
SaveCSV(python_residuals, "./python_residuals.csv")

c_predicted = ReadCSV("../build/predictor.csv")
c_vs_python = c_predicted == python_predicted
SaveCSV(c_vs_python, "./c_vs_python.csv")