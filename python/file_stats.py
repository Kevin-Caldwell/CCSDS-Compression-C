from csv_io import ReadCSV
import sys
import compression as comp


def compression_ratio(data, compressed):
    # data16int = np.array(data, dtype=np.uint16)
    # return len(np.asarray(data16int).tobytes() * 8) / len(compressed)
    print(data.shape[0], data.shape[1], data.shape[2], comp.D, len(compressed))
    return len(compressed) / (data.size * comp.D), len(compressed) / 1000000


def file_info(file_path):
    data = ReadCSV(filename=file_path)
    encoded = comp.encoder(data)
    return compression_ratio(data, encoded)


if __name__ == "__main__":
    n = len(sys.argv)
    if n > 1:
        print("Hllo")
    else:
        print(
            "Compression Results:",
            file_info("data/results/CRESULT_640x512x640_0_predicted.csv"),
        )
        # print("Python Results:", file_info("data/results/PYTHONRESULT_100x100x100_0_predicted.csv"))
