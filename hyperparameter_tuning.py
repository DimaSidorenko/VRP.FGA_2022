# "VRP.FGA_2022\VRP.FGA_2022.exe solve "TestGenerator\tests\test10.txt" 0.1 0.1 0.01"

import os
import subprocess
from subprocess import check_output
import matplotlib.pylab as plt
import math
import numpy as np


TESTS_DIR = "TestGenerator\\tests"
ALGO_SOLVER_PATH = "VRP.FGA_2022\\VRP.FGA_2022.exe"
RESULTS_DIR = "RESULTS"


GLOBAL_LEARNING_RATE = 0.1
ITERATION_COUNT = 500



def run_algorithm(test_path, iLR, DR, gLR):
    print(test_path, iLR, DR, gLR)

    result = subprocess.run([ALGO_SOLVER_PATH, "solve", test_path, str(iLR), str(DR), str(gLR), str(ITERATION_COUNT)], capture_output=True,
                            text=True)

    # print("stdout\n", result.stdout)
    # print("stderr:", result.stderr)

    metric_value = float(result.stdout.split('=')[1])
    return metric_value


# data[1] - x_axis, data[0] - y_axis
# file_path without should be without file type
def draw_data(data, file_path, vertex_cnt):
    plt.figure(figsize=(12, 7))
    plt.plot([x[1] for x in data], [x[0] for x in data], 'ro', label="{} вершин".format(vertex_cnt))

    plt.xlabel('Скорость обучения')
    plt.ylabel('Значение метрики')
    plt.title('Качество работы алгоритма в зависимости от индивидуальной скорости обучения')
    plt.legend()
    plt.savefig(file_path)


def get_exponent_pow(value):
    exponent_pow = 0

    while (value < 1):
        value *= 10
        exponent_pow -= 1

    return exponent_pow


def find_best_diversity_rate(iLR, test_path, dr_left_border, dr_right_border, dr_step, dr_exponent_value):
    best_result = -1
    best_diversity_rate = -1

    dr_factor = math.pow(10, dr_exponent_value)
    for diversity_rate in range(dr_left_border, dr_right_border, dr_step):
        current_dr = diversity_rate * dr_factor

        result = run_algorithm(test_path, iLR, current_dr, GLOBAL_LEARNING_RATE)

        # results.append([result, current_iLR, current_dR])
        if (best_result == -1 or result < best_result):
            best_result = result
            best_diversity_rate = current_dr

    return best_result, best_diversity_rate


def make_research(test_path, vertexCount):
    results = []

    dr_exponent_value = get_exponent_pow(1 / vertexCount) - 2
    dr_left_border_digit = 1
    dr_right_border_digit = 20
    dr_step_digit = 2

    ilr_exponent_value = dr_exponent_value + 1
    ilr_factor = math.pow(10, ilr_exponent_value)

    ilr_left_border_digit = 15
    ilr_right_border_digit = 80
    ilr_step_digit = 4

    for ilr_digit in range(ilr_left_border_digit, ilr_right_border_digit, ilr_step_digit):
        current_ilr = ilr_digit * ilr_factor
        best_result, best_diversity_rate = find_best_diversity_rate(current_ilr, test_path, dr_left_border_digit,
                                                                    dr_right_border_digit,
                                                                    dr_step_digit, dr_exponent_value)

        results.append([best_result, current_ilr, best_diversity_rate])

    return results



def norm2(value, min, max):
    return (value) / (max)

def group_results(results):
    if (len(results) == 0):
        return []

    grouped_result = np.zeros(len(results[0]))

    for result in results:
        result = np.array(result)
        temp = result[:, 0]

        mx = np.max(temp)
        mn = np.min(temp)

        normilized_metric_values = [norm2(elem, mn, mx) for elem in temp]
        grouped_result += np.array(normilized_metric_values)

    result = results[0];
    x = np.array(result)[:, 1]

    answer = []
    for i in range(len(x)):
        answer.append([grouped_result[i], x[i]])

    # print(answer)

    return answer


def main():
    # test_filenames = os.listdir(TESTS_DIR)
    vertex_folder_pathes = [os.path.join(TESTS_DIR, filename) for filename in os.listdir(TESTS_DIR)]

    for vertex_folder_path in vertex_folder_pathes:
        vertex_count = int(vertex_folder_path.split('\\')[-1])

        if (vertex_count != 30):
            continue

        # print(sz)
        current_test_pathes = [os.path.join(vertex_folder_path, filename) for filename in
                               os.listdir(vertex_folder_path)]
        # print(current_test_pathes)

        vertex_results = []

        for test_path in current_test_pathes:
            research_result = make_research(test_path, vertex_count)
            
            vertex_results.append(research_result)

            test_filename = test_path.split('\\')[-1]
            last_point_pos = test_filename.rindex('.')
            test_filename = test_filename[0:last_point_pos]

            file_path_template = os.path.join(RESULTS_DIR, str(vertex_count), test_filename)
            
            # print(file_path_template)

            # write results in txt file
            txt_file_path = file_path_template + '_results.txt'

            with open(txt_file_path, 'w') as writer:
                for result in research_result:
                    for values in result:
                        writer.write("%s " % values)
                    writer.write("\n")

            plot_file_path = file_path_template + '_plot.png'
            # draw plots
            draw_data(research_result, plot_file_path, vertex_count)
        
        
        # plot_file_path = file_path_template + '_plot.png'
        # draw plots
        # draw_data(research_result, plot_file_path, vertex_count)


        grouped_data = group_results(vertex_results)        
        
        file_path_template = os.path.join(RESULTS_DIR, str(vertex_count), str(vertex_count))
        plot_file_path = file_path_template + '_plot.png'

        draw_data(grouped_data, plot_file_path, vertex_count)

        break

if __name__ == "__main__":
    main()