from pathlib import Path

OUTPUT = Path("benchmark_data")
FILE_COUNT = 5_000

OUTPUT.mkdir(exist_ok=True)

template = """\
#include <iostream>
#include <vector>
#include <string>

// Single line comment

int calculate(int value)
{
    /*
       This is a multi-line comment.
       It contains several lines.
    */

    int result = value * 2;

    // More comments
    if (result > 100)
    {
        return result;
    }

    return result + 10;
}

"""

content = template * 100

for i in range(FILE_COUNT):
    (OUTPUT / f"file_{i:05d}.cpp").write_text(content)

print(f"Created {FILE_COUNT} files")
