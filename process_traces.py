import os

root_dir = os.getcwd()
trace_dir = root_dir + '/traces/'
out_dir = root_dir + '/output/'

for file in os.listdir(trace_dir):
    if file.endswith('.trace'):
        out_file = file.replace('.trace', '.dram')
        command = './src/memcon -i ' + trace_dir + \
                  file + ' -o ' + out_dir + out_file
        os.system(command)
