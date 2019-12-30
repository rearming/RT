#!/usr/bin/env python3

import sys
import glob
import re

prototypes_file_name = "prototypes.cl"

cl_files_text = ""

cl_files_names = []

for path in sys.argv:
    cl_files_names.append(glob.glob(path + "/" + "*.cl"))

for names_list in cl_files_names:
    for filename in names_list:
        match = re.match(r".*" + prototypes_file_name + ".*", filename)
        if match:
            continue
        file = open(filename, 'r')
        cl_files_text += file.read()
        file.close()

matches = re.findall(r"(([\w]+)[\t ]+([\w]+)\((?:[\s]*(?:(\*?\w+)[\s,)]){2,3})+)", cl_files_text)

result_str = ""

for match in matches:
    result_str += "\n"
    result_str += match[0]
    if str(match[0][-1]) != ")":
        result_str += ")"
    result_str += ";\n"

result_file = open(sys.argv[1] + "/" + prototypes_file_name, 'w')
result_file.seek(0)
result_file.write(result_str + "\n")
result_file.close()
