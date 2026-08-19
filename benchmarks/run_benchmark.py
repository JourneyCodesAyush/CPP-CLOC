import subprocess
import time
import statistics

COMMAND = [
    r".\cloc_cpp.exe",
    "benchmark_data",
]

RUNS = 5

times = []

for i in range(RUNS):
    start = time.perf_counter()

    result = subprocess.run(
        COMMAND,
        capture_output=True,
        text=True,
        check=True,
    )

    elapsed = time.perf_counter() - start
    times.append(elapsed)

    print(f"Run {i + 1}: {elapsed:.3f}s")

print()
print(f"Min:    {min(times):.3f}s")
print(f"Max:    {max(times):.3f}s")
print(f"Mean:   {statistics.mean(times):.3f}s")
print(f"Median: {statistics.median(times):.3f}s")
