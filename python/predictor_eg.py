import numpy as np
import compression as comp
#from sklearn.metrics import mean_squared_error
import csv
import sys

from csv_io import ReadCSV, SaveCSV
if __name__ == "__main__":
    print("_________PYTHON PREDICTOR_________")
    n = len(sys.argv)
    if(n > 1):
        data = ReadCSV(sys.argv[1])
        Nx, Ny, Nz = data.shape

        python_predicted = comp.predictor(data)
        SaveCSV(python_predicted, sys.argv[2])
    else:
        python_predicted = ReadCSV("data/test-images/indian_pines.csv")
        Nx, Ny, Nz = python_predicted.shape

        encoded = comp.predictor(python_predicted)
        SaveCSV(python_predicted, "data/results/PYTHONRESULT_indian_pines_predicted.csv")