#python3 python/predictor_eg.py


test_index=$1
    img_x=640
    img_y=512
    img_z=640

    test_file=_${img_x}x${img_y}x${img_z}_${test_index}


    #./generate_test_cases.sh $img_x $img_y $img_z $test_index

    #time ./run_c_predictor.sh $test_file bg
    time ./run_python_predictor.sh $test_file bg

    python3 python/file_compare.py data/results/CRESULT${test_file}_predicted.csv data/results/PYTHONRESULT${test_file}_predicted.csv
