# Benchmarks

Scripts used to measure the speedup from parallel file processing.
Both scripts use only the Python standard library — no `pip install` required.

## Reproducing the numbers

1. **Build a release binary** (parallel processing benefits most from
   `-O3`, though debug builds are also parallelized):

   ```bash
   make RELEASE=1
   ```

2. **Generate synthetic test data**:

   ```bash
   python generate_test_data.py
   ```

   This creates 5,000 `.cpp` files under `benchmark_data/`, each with a
   mix of code, single-line comments, and multi-line comments. The
   directory is git-ignored — it's regenerated locally, never committed.

3. **Run the benchmark**:

   ```bash
   python run_benchmark.py
   ```

   This runs `cloc_cpp` against `benchmark_data/` 5 times and reports
   min/max/mean/median wall-clock time. Edit `COMMAND` at the top of
   the script if your binary path or name differs (e.g. `./cloc_cpp` on
   Linux/macOS vs `.\cloc_cpp.exe` on Windows).

## Notes on methodology

- The **first run** in any batch is typically slower due to cold disk
  cache; subsequent runs benefit from OS-level file caching. Median,
  not mean, is the fairer number to quote for this reason.
- To compare against the pre-parallelization baseline, check out the
  commit before parallel processing was introduced, rebuild, and rerun
  `run_benchmark.py` — the script itself doesn't know or care which
  binary it's timing.
- Numbers will vary by hardware (core count, disk speed) and by how
  I/O-bound vs CPU-bound your specific codebase's files are. Treat any
  published number as directional, not a guarantee.

## Parallelism only kicks in above a file-count threshold

Below `PARALLEL_THRESHOLD` (200 files, see [`src/middleware.cpp`](../src/middleware.cpp)), cpp-cloc
runs sequentially on purpose. Thread-spawn overhead outweighs any
parallel gain at small scale — on a real 37-file test (this repo's own
`src`/`include`/`tests`), forcing threading made things ~75% _slower_
(0.004s → 0.007s) before the threshold guard was added.

**If you're benchmarking cpp-cloc on your own project and don't see a
speedup, check your file count first.** Below ~200 files, matching
v0.6.x speed (not exceeding it) is expected and correct.

## Reference numbers

Measured on a 16-thread system, median of 5 runs:

| Dataset                      | Files | Sequential | Parallel                                 | Speedup        |
| ---------------------------- | ----- | ---------- | ---------------------------------------- | -------------- |
| This repo's own source       | 37    | ~0.009s    | n/a — below threshold, runs sequentially | 1x (by design) |
| 5,000 synthetic `.cpp` files | 5,000 | 1.045s     | 0.207s                                   | ~5x            |

The 37-file row exists to make the threshold behavior explicit, not to
showcase a speedup — small projects are expected to see none.
