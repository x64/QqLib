#!/usr/bin/env python3
#coding=utf-8

# use:
#    copy_to_export.py
#    or
#    copy_to_export.py <path to source dir> <path to "files_for_copy_to_export.txt">

import shutil
import os
import sys

src_dir  = "../../src/"
dest_dir = "../../export/QqLib/"

def clean_dest_dir():
	shutil.rmtree(dest_dir, True)
	os.makedirs(dest_dir)

def make_dirs(path):
	os.makedirs(dest_dir + path)


def main():
	global src_dir, dest_dir

	if len(sys.argv) == 2 or len(sys.argv) > 3:
		print("The number of command line arguments can't be equal to 2 or greater than 3.")
		exit()

	excec_from_cmake = True if len(sys.argv) == 3 else False

	file_of_list = sys.argv[2]                    if excec_from_cmake else "files_for_copy_to_export.txt"
	src_dir      = sys.argv[1] + "/src/"          if excec_from_cmake else src_dir
	dest_dir     = sys.argv[1] + "/export/QqLib/" if excec_from_cmake else dest_dir

	clean_dest_dir()

	fh = open(file_of_list, "rt")

	last_folder = ""
	for line in fh.readlines():
		path = line.strip()
		if ""  == path: continue
		if "/" == path[-1]:
			make_dirs(path)
			last_folder = path
			continue
		path = last_folder + path
		print("copying:", path)
		shutil.copy(src_dir + path, dest_dir + path)

	fh.close()

#############

main()