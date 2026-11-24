from pathlib import Path
import subprocess
import sys

program = Path(sys.argv[1]).resolve()
root = Path(__file__).resolve().parent.parent
valid = subprocess.run([str(program)], cwd=root, capture_output=True, text=True)
assert valid.returncode == 0, valid.stderr
assert "Program" in valid.stdout
missing = subprocess.run([str(program)], cwd=root / "tests", capture_output=True, text=True)
assert missing.returncode == 1, missing.stdout
assert "Unable to open testFiles/basicTest.txt" in missing.stderr
assert "Program" not in missing.stdout
print("Demo input success and missing-file failure passed.")
