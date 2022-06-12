import matplotlib.pylab as plt
import os
import sys

TESTS_DIR = "tests"

def printGraph(file_path):
    print(file_path)
    
    points = []
    
    with open(file_path, 'r' ,encoding = 'utf-8') as f:
        vertexCount = int(f.readline())
        
        for i in range(vertexCount):
            pts = list(map(float, f.readline().split(' ')));
            points.append((pts)) 
    
    plt.scatter([x[0] for x in points], [x[1] for x in points], cmap='hot', marker=".")
    plt.show()


def main():
     # test_filenames = os.listdir(TESTS_DIR)
    vertex_folder_pathes = [os.path.join(TESTS_DIR, filename) for filename in os.listdir(TESTS_DIR)]

    for vertex_folder_path in vertex_folder_pathes:
        vertex_count = int(vertex_folder_path.split('\\')[-1])

        if (vertex_count != 30):
            continue

        current_test_pathes = [os.path.join(vertex_folder_path, filename) for filename in
                               os.listdir(vertex_folder_path)]

        for test_path in current_test_pathes:    
            test_name = test_path.split('\\')[-1]
            if (test_name.find('special') == -1):
                continue
        
            printGraph(test_path)
            
            # research_result = make_research(test_path, vertex_count)

            # test_filename = test_path.split('\\')[-1]
            # last_point_pos = test_filename.rindex('.')
            # test_filename = test_filename[0:last_point_pos]

            # file_path_template = os.path.join(RESULTS_DIR, str(vertex_count), test_filename)
            
            # # print(file_path_template)

            # # write results in txt file
            # txt_file_path = file_path_template + '_results.txt'

            # with open(txt_file_path, 'w') as writer:
            #     for result in research_result:
            #         for values in result:
            #             writer.write("%s " % values)
            #         writer.write("\n")

            # plot_file_path = file_path_template + '_plot.png'
            # # draw plots
            # draw_data(research_result, plot_file_path, vertex_count)


if __name__ == "__main__":
    main()







