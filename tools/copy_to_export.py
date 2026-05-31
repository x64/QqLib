#!/usr/bin/env python3
# coding=utf-8

import shutil
import os

src_dir  = "../src/"
dest_dir = "../export/QqLib/"

def clean_dest_dir():
	shutil.rmtree(dest_dir, True)
	os.makedirs(dest_dir)

def make_dirs(path):
	os.makedirs(dest_dir + path)


def main():
	clean_dest_dir()

	fh = open("./files_for_copy_to_export.txt", "rt")

	last_folder = ""
	for line in fh.readlines():
		path = line.strip()
		if path == "" : continue
		if path[-1] == "/":
			make_dirs(path)
			last_folder = path
			continue
		path = last_folder + path
		print("path: ", path)
		shutil.copy(src_dir + path, dest_dir + path)

	fh.close()

#############

main()