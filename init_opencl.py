#!/usr/bin/env python3

import sys
import glob
import re
import os


prototypes_file_name = "prototypes.cl"


def get_opencl_files_names():
    names = [glob.glob(sys.argv[1] + "/**/" + "*.cl", recursive=True)]
    return names


def update_opencl_header():
    cl_files_text = ""

    for names_list in cl_files_names:
        for filename in names_list:
            match = re.match(r".*" + prototypes_file_name + ".*", filename)
            if match:
                continue
            file = open(filename, 'r')
            cl_files_text += file.read()
            file.close()

    matches = re.findall(r"(([\w ]+)[\t ]+([\w*]+)\((?:[\s]*((?:[*# /]*\w+)[\s,)]))+)", cl_files_text)

    result_str = ""

    for match in matches:
        if re.match(r".*__kernel.*", match[0])\
                or re.match(r".*return.*", match[0]):
            continue
        result_str += "\n"
        result_str += match[0]
        if str(match[0][-1]) != ")":
            result_str += ")"
        result_str += ";\n"

    result_file = open(sys.argv[1] + "/" + prototypes_file_name, 'w')
    result_file.seek(0)
    result_file.write(result_str + "\n")
    result_file.close()


# def update_opencl_include_dirs():
#     updated_file_path = "./includes/rt_defines.h"
#     file = open(updated_file_path, "r")
#     file_text = file.read()
#     file.close()
#
#     all_dirs = [x[0] for x in os.walk(sys.argv[1])]
#     print(all_dirs)
#
#     matches = re.findall(r"(\" -I \.(?:\/\w+)+\"( \\)*\s*)", file_text)
#     print(matches)
#     # re.sub()
#
#     result_file = open(updated_file_path, 'w')
#     result_file.seek(0)
#     result_file.write(file_text)


cl_files_names = get_opencl_files_names()
pwd = os.path.dirname(os.path.realpath(__file__))
update_opencl_header()
# update_opencl_kernel_files()
