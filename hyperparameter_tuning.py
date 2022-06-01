# "VRP.FGA_2022\VRP.FGA_2022.exe solve "TestGenerator\tests\test10.txt" 0.1 0.1 0.01"

import os
import subprocess
from subprocess import check_output

TESTS_DIR = "TestGenerator\\tests"
ALGO_SOLVER_PATH = "VRP.FGA_2022\\VRP.FGA_2022.exe"

def run_algorithm(test_path, iLR, DR, gLR):
    print (test_path, iLR, DR, gLR)
    result = subprocess.run([ALGO_SOLVER_PATH, "solve", test_path, str(iLR), str(DR), str(gLR)], capture_output=True, text=True)
    
    # print("stdout\n", result.stdout)
    # print("stderr:", result.stderr) 
    
    metric_value = float(result.stdout.split('=')[1])
    return metric_value
    

def main():
    # test_filenames = os.listdir(TESTS_DIR)
    test_paths = [os.path.join(TESTS_DIR, filename) for filename in os.listdir(TESTS_DIR)]
    # print(test_filenames)

    path = test_paths[2]

    results = []


    # Шаг =  0.01, Диапазон = 0.001 до 0.200
    for iLR in range (1, 201, 30):
        best_result = -1
        best_diversity_rate = -1
        # Перебираем DR: Шаг =  0.001 Диапазон = 0.001 до 0.100
        for dR in range (1, 100, 30):
            current_iLR = iLR / 1000
            current_dR = dR / 10000
            result = run_algorithm(path, current_iLR, current_dR, 0.1)
            results.append([result, current_iLR, current_dR])
            # if (best_result == -1 or result < best_result):
            #     best_result = result
            #     best_diversity_rate = dR / 1000
        
        # results.append([best_result, iLR / 1000, best_diversity_rate])

    results.sort(key=lambda temp: temp[0]) 

    for result in results:
        print(result)

    # print(results, sep = '\n');

    # for path in test_paths:
    #     for iLR in range(1, 2, 1):
    #         run_algorithm(path, iLR / 10, iLR / 100, 0.1)


if __name__ == "__main__":
    main()