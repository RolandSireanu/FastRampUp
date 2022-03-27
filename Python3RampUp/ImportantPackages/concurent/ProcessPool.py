import multiprocessing
import subprocess

from django.forms import MultipleChoiceField




def work(arg_cmd):
    return subprocess.call(arg_cmd, shell=False)

if __name__ == "__main__":
    count = multiprocessing.cpu_count()
    pool = multiprocessing.Pool(processes=count)
    print(pool.map(work, ["ls"] * count))