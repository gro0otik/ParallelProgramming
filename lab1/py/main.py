from pathlib import Path
import numpy as np

base = Path(__file__).resolve().parent.parent / "data"
sizes = [300, 600, 900, 1200, 1500]
for n in sizes:
    try:
        a = np.loadtxt(base / f"matrix_{n}_1.txt", dtype=np.int64).reshape(n, n)
        b = np.loadtxt(base / f"matrix_{n}_2.txt", dtype=np.int64).reshape(n, n)
        c = np.loadtxt(base / f"result_{n}.txt", dtype=np.int64, comments='#')
        if np.array_equal(a @ b, c):
            print(f"[{n}x{n}] OK")
        else:
            print(f"[{n}x{n}] FAIL")
    except FileNotFoundError as e:
        print(f"[{n}x{n}] skip ({e.filename})")
