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

    matches = re.findall(r"(([\w]+)[\t ]+([\w]+)\((?:[\s]*(?:(\*?\w+)[\s,)]){2,5})+)", cl_files_text)

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


def update_opencl_kernel_files():
    updated_file_path = "./sources/OpenCL_utils/opencl_files_parser.c"
    file = open(updated_file_path, "r")
    file_text = file.read()
    file.close()

    corrected_file_names = []

    excluded_files = re.search(r"ft_read_files\(\d{2},((?:[\s\S]+?)(?:prototypes.cl\"))", file_text).group(1)
    excluded_files = re.findall(r"\"(\./.*)\"", excluded_files)

    for name in cl_files_names[0]:
        corrected_name = re.sub(str(pwd), ".", str(name))
        if corrected_name in excluded_files:
            continue
        corrected_file_names.append(corrected_name)

    tabs_number = len(re.search(r"(\t+)\"\./sources/OpenCL_kernel_code/prototypes.cl\"", file_text).group(1))

    str_to_insert = ""
    for name in corrected_file_names:
        str_to_insert += ",\n" + "\t"[:1]*tabs_number + "\"" + name + "\""

    file_text = re.sub(re.search(r"(?:prototypes.cl\")([\s\S]+?)(?=\);)", file_text).group(1), str_to_insert, file_text)

    files_number = len(re.findall(r"(\"\./[a-zA-Z/_.]+\")", file_text))
    file_text = re.sub(r"(\d+)(?=,\s*\"\./[a-zA-Z/_.]+\")", str(files_number), file_text)

    result_file = open(updated_file_path, 'w')
    result_file.seek(0)
    result_file.write(file_text)


cl_files_names = get_opencl_files_names()
pwd = os.path.dirname(os.path.realpath(__file__))
update_opencl_header()
update_opencl_kernel_files()
