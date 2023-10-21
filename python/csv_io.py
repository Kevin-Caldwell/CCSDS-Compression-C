import numpy as np

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
    numbers.resize((Nz, Ny, Nx))
    numbers = np.transpose(numbers, (2, 1, 0))

    return numbers

def SaveCSV(np_array_3d, output_path):
    Nx, Ny, Nz = np_array_3d.shape
    np_array_3d = np.transpose(np_array_3d, (2, 1, 0))
    np_array_1d = np_array_3d.ravel()
    np_array_1d = np.insert(np_array_1d, 0, (Nx, Ny, Nz))
    print(np_array_1d)
    np.savetxt(output_path, np_array_1d, fmt='%i', newline=",")
    print("CSV file saved successfully.")