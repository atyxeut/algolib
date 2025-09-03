# format every .cpp/.hpp file using clang-format(21+), see .clang-format for format details

from pathlib import Path
import subprocess
import time


def fmt(path: Path, dep: int = 0) -> None:
    if path.is_dir():
        if dep == 0 or dep == 1 and path.name == "src" or dep > 1:
            for item in path.iterdir():
                fmt(item, dep + 1)
    elif path.suffix == ".cpp" or path.suffix == ".hpp":
        print(f"Formatting {path}")
        subprocess.run(["clang-format", "-style=file", "-i", path])


begin_time_point = time.perf_counter()

fmt(Path(".").resolve())

end_time_point = time.perf_counter()
print(f"Done in {end_time_point - begin_time_point:.2f}s")
