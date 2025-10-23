# > python3 fmt_cpp_files.py
#   format every .cpp/.hpp file using clang-format (requires clang-format 21+), using the formatting rules defined in .clang-format

from pathlib import Path
import subprocess


def fmt(path: Path, dep: int = 0) -> None:
    if path.is_dir():
        if dep == 0 or dep == 1 and path.name == "src" or dep > 1:
            for item in path.iterdir():
                fmt(item, dep + 1)
    elif path.suffix == ".cpp" or path.suffix == ".hpp":
        print(f"formatting {path}")
        subprocess.run(["clang-format", "-style=file", "-i", path])


def main():
    fmt(Path(".").resolve())
    print("formatting done")


if __name__ == "__main__":
    main()
