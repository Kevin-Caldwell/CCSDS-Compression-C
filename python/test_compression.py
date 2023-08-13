import unittest
import numpy as np
import compression as comp
import scipy.io
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

class TestComp(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # n = 5
        # cls.data = cls.load_pic()[0:n, 0:n, 0:n]
        # cls.data = cls.load_pic()

        # For Checking C vs Python
        cls.data = ReadCSV("../build/raw.csv")

        cls.Nx = cls.data.shape[0]
        cls.Ny = cls.data.shape[1]
        cls.Nz = cls.data.shape[2]

    def test_predictor(self):
        python_predicted, python_residuals = comp.predictor_debug(self.data)
        SaveCSV(python_predicted, "./python_predicted.csv")
        SaveCSV(python_residuals, "./python_residuals.csv")

        c_predicted = ReadCSV("../build/predictor.csv")
        c_vs_python = c_predicted == python_predicted
        SaveCSV(c_vs_python, "./c_vs_python.csv")
        self.assertTrue((c_vs_python).all())

    def test_unpredict(self):
        mapped = comp.predictor(self.data)
        unpredicted = comp.unpredictor(mapped, self.Nx, self.Ny, self.Nz)
        self.assertTrue((unpredicted == self.data).all())

    def test_inv_GPO2(self):
        value = 2576
        k = 0
        encoded = comp.GPO2(k, value)
        decoded, i = comp.inv_GPO2(k, encoded, 0)
        # print("value", value)
        # print("len(encoded)", len(encoded))
        # print("encoded:", encoded)
        # print("decoded", decoded)
        # print("i", i)
        self.assertTrue(value == decoded)

    def test_decompress(self):
        encoded = comp.encoder(self.data)
        decoded = comp.decoder(encoded, self.Nx, self.Ny, self.Nz)
        self.assertTrue((decoded == self.data).all())

    def test_compression_algo(self):
        mapped = comp.predictor(self.data)
        encoded = comp.encoder(mapped)
        decoded = comp.decoder(encoded, self.Nx, self.Ny, self.Nz)
        unpredicted = comp.unpredictor(decoded, self.Nx, self.Ny, self.Nz)
        self.assertTrue((unpredicted == self.data).all())

    def test_rmse(self):
        mapped = comp.predictor(self.data)
        encoded = comp.encoder(mapped)
        decoded = comp.decoder(encoded, self.Nx, self.Ny, self.Nz)
        unpredicted = comp.unpredictor(decoded, self.Nx, self.Ny, self.Nz)
        self.assertTrue((unpredicted == self.data).all())
        rmse = self.rmse(self.data, unpredicted)
        print("RMSE: ", rmse)
        self.assertTrue(rmse == 0.0)

    def test_compression_ratio(self):
        mapped = comp.predictor(self.data)
        encoded = comp.encoder(mapped)
        decoded = comp.decoder(encoded, self.Nx, self.Ny, self.Nz)
        unpredicted = comp.unpredictor(decoded, self.Nx, self.Ny, self.Nz)

        rmse = self.rmse(self.data, unpredicted)
        ratio = self.compression_ratio(self.data, encoded)

        print("RMSE: ", rmse)
        print("Compression Ratio: ", ratio)
        self.assertTrue((unpredicted == self.data).all())
        self.assertTrue(rmse == 0.0)
        self.assertTrue(ratio > 1)

    def load_pic(file_name="images/Indian_pines.mat", header="indian_pines"):

        data = scipy.io.loadmat(file_name)
        data = data[header]  # data is dictionary, only take the array part
        data = np.array(data, dtype=np.int64)

        return data

    def rmse(self, data, decompressed):
        data16int = np.array(data, dtype=np.uint16)
        Nz = data16int.shape[2]

        error = 0
        for z in range(Nz):
            error += mean_squared_error(data16int[:, :, z], decompressed[:, :, z], squared=False)
        rmse = error / Nz
        return rmse

    def compression_ratio(self, data, compressed):
        # data16int = np.array(data, dtype=np.uint16)
        # return len(np.asarray(data16int).tobytes() * 8) / len(compressed)
        return data.size * comp.D / len(compressed)

if __name__ == "__main__":
    unittest.main()
