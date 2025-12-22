# 21 December 2025
import sys


def cloc_py(filename: str) -> None:

    lines_of_comment: int = 0
    lines_of_code: int = 0
    blank_lines: int = 0

    inside_multi_line_comment: bool = False

    with open(filename, "r") as f:
        line: str = f.readline()
        while line:
            modified_line: str = line.strip()

            if inside_multi_line_comment:
                lines_of_comment += 1
                # line = f.readline()
                # modified_line = line.strip()
                if modified_line.endswith("*/"):
                    inside_multi_line_comment = False

            else:
                if modified_line == "":
                    blank_lines += 1
                elif modified_line.startswith("//"):
                    lines_of_comment += 1
                elif modified_line.startswith("/*"):
                    lines_of_comment += 1
                    inside_multi_line_comment = True

                else:
                    lines_of_code += 1
            # if modified_line == "":
            #     blank_lines += 1
            # elif modified_line[0] == "/" and modified_line[1] == "/":
            #     lines_of_comment += 1
            # elif modified_line[0] == "/" and modified_line[1] == "*":
            #     lines_of_comment += 1
            # else:
            #     lines_of_code += 1
            line = f.readline()

    # print("Code | Comments | Blank lines | Total lines")
    # print(
    #     f"{lines_of_code} | {lines_of_comment} | {blank_lines} | {lines_of_code + lines_of_comment + blank_lines}"
    # )
    # Print header

    print(f"{'Code':>6} | {'Comments':>8} | {'Blank lines':>12} | {'Total lines':>11}")

    # Print values
    total_lines = lines_of_code + lines_of_comment + blank_lines
    print(
        f"{lines_of_code:6} | {lines_of_comment:8} | {blank_lines:12} | {total_lines:11}"
    )


def main():
    if len(sys.argv) > 1:
        for args in sys.argv:
            print(args)
        print(f"{sys.argv[1]}")
        cloc_py(sys.argv[1])
    else:
        print("Some error occurred")


if __name__ == "__main__":
    main()
