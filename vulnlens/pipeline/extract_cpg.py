import subprocess

def extract_cpg(c_file_path, output_dir):
    subprocess.run([
        "joern-parse", c_file_path,
        "--output", output_dir
    ], check=True)