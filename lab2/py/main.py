from pathlib import Path
import numpy as np

base = Path(__file__).resolve().parent.parent / "data"

sizes = [200, 400, 800, 1200, 1600, 2000]
threads = [1, 2, 4, 8]

for n in sizes:
    try:
        a = np.loadtxt(base / f"matrix_{n}_1.txt", dtype=np.int64).reshape(n, n)
        b = np.loadtxt(base / f"matrix_{n}_2.txt", dtype=np.int64).reshape(n, n)

        for t in threads:
            result_file = base / f"result_{n}_t{t}.txt"
            if not result_file.exists():
                continue
            c = np.loadtxt(result_file, dtype=np.int64, comments='#')
            ok = np.array_equal(a @ b, c)
            print(f"[{n}x{n}, threads={t}] {'OK' if ok else 'FAIL'}")
    except FileNotFoundError as e:
        print(f"[{n}x{n}] skip ({e.filename})")
