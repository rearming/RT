#!/usr/bin/env python3

import sys
import glob
import re
import os


meshes_dir_path = "./assets/3d_models/"
kernel_sources_path = "./sources/OpenCL_kernel_code/"
prototypes_file_name = "prototypes.cl"


def get_opencl_files_names():
    names = [glob.glob(kernel_sources_path + "**/" + "*.cl", recursive=True)]
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

    result_file = open(kernel_sources_path + "/" + prototypes_file_name, 'w')
    result_file.seek(0)
    result_file.write(result_str + "\n")
    result_file.close()


def correct_mtl_path():
    obj_files = glob.glob(meshes_dir_path + "*.obj", recursive=True)
    mtl_file_paths = glob.glob(meshes_dir_path + "*.mtl", recursive=True)

    mtl_file_names = list(map(lambda name: (re.findall(r"(?:[^/]+)\.mtl", name)[0]), mtl_file_paths))

    for obj_file in obj_files:
        file = open(obj_file, 'r')
        file_text = file.read()
        file.close()
        for i in range(len(mtl_file_names)):
            file_text = re.sub(r"(?<=mtllib[\s])((?:[^/])+\.mtl)", mtl_file_paths[i], file_text)
        file = open(obj_file, 'w')
        file.seek(0)
        file.write(file_text)
        file.close()


cl_files_names = get_opencl_files_names()
pwd = os.path.dirname(os.path.realpath(__file__))
update_opencl_header()
correct_mtl_path()
