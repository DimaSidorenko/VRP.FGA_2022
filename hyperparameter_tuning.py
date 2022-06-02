# "VRP.FGA_2022\VRP.FGA_2022.exe solve "TestGenerator\tests\test10.txt" 0.1 0.1 0.01"

import os
import subprocess
from subprocess import check_output
import matplotlib.pylab as plt
import math

TESTS_DIR = "TestGenerator\\tests"
ALGO_SOLVER_PATH = "VRP.FGA_2022\\VRP.FGA_2022.exe"
GLOBAL_LEARNING_RATE = 0.1


def run_algorithm(test_path, iLR, DR, gLR):
    print(test_path, iLR, DR, gLR)

    result = subprocess.run([ALGO_SOLVER_PATH, "solve", test_path, str(iLR), str(DR), str(gLR)], capture_output=True,
                            text=True)

    # print("stdout\n", result.stdout)
    # print("stderr:", result.stderr)

    metric_value = float(result.stdout.split('=')[1])
    return metric_value


# data[1] - x_axis, data[0] - y_axis
def draw_data(data):
    plt.figure(figsize=(12, 7))
    plt.plot([x[1] for x in data], [x[0] for x in data], 'ro', label='Research results')

    plt.xlabel('Скорость обучения')
    plt.ylabel('Значение метрики')
    plt.title('Качество работы алгоритма в зависимости от индивидуальной скорости обучения')
    plt.legend()
    plt.savefig("kek" + ' results.png')


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
    dr_right_border_digit = 22
    dr_step_digit = 2

    ilr_exponent_value = dr_exponent_value + 1
    ilr_factor = math.pow(10, ilr_exponent_value)

    for ilr_digit in range(1, 40, 3):
        current_ilr = ilr_digit * ilr_factor
        best_result, best_diversity_rate = find_best_diversity_rate(current_ilr, test_path, dr_left_border_digit,
                                                                    dr_right_border_digit,
                                                                    dr_step_digit, dr_exponent_value)

        results.append([best_result, current_ilr, best_diversity_rate])

    return results


def main():
    # test_filenames = os.listdir(TESTS_DIR)
    vertex_folder_pathes = [os.path.join(TESTS_DIR, filename) for filename in os.listdir(TESTS_DIR)]

    for vertex_folder_path in vertex_folder_pathes:
        vertex_count = int(vertex_folder_path.split('\\')[-1])

        if (vertex_count >= 60):
            continue

        # print(sz)
        current_test_pathes = [os.path.join(vertex_folder_path, filename) for filename in
                               os.listdir(vertex_folder_path)]
        # print(current_test_pathes)

        for test_path in current_test_pathes:
            research_result = make_research(test_path, vertex_count)

            continue
            # write results in txt file
            with open("some_result.txt", 'w') as writer:
                for result in research_result:
                    for values in result:
                        writer.write("%s " % values)
                    writer.write("\n")

            # draw plots
            draw_data(research_result)


if __name__ == "__main__":
    main()