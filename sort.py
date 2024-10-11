import os

def sort_files_by_second_number(input_file, output_file):
    """
    按照文件名中第二个数字排序，并将结果写入新文件。

    Args:
        input_file: 输入文件名
        output_file: 输出文件名
    """

    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        lines = f_in.readlines()

        def get_second_number(line):
            parts = line.strip().split('_')
            return int(parts[1])

        sorted_lines = sorted(lines, key=get_second_number)
        f_out.writelines(sorted_lines)

# 示例用法
input_filename = "100.list"  # 替换为您的输入文件名
output_filename = "sorted_filenames.txt"
sort_files_by_second_number(input_filename, output_filename)
