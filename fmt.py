import argparse
from pathlib import Path
import subprocess


# > python3 fmt.py path
#                   ↑ this is required
#   1. if path is a folder, recursively format every subpath in it
#   2. if path is a .cpp/.hpp file, format it using clang-format
#      the formatting rules are defined in .clang-format, requires clang-format 21+
parser = argparse.ArgumentParser(add_help=False)
parser.add_argument("path", type=str)
argv = parser.parse_args()


def fmt(path: Path) -> None:
    if path.is_dir():
        for item in path.iterdir():
            fmt(item)
    elif path.suffix == ".cpp" or path.suffix == ".hpp":
        print(f"formatting {path}")
        subprocess.run(["clang-format", "-style=file", "-i", path])


def main():
    fmt(Path(argv.path).resolve())
    print("format done")


if __name__ == "__main__":
    main()
