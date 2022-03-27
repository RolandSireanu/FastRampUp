# Concurent.features provides the developer with a high level interface for async executin callables.

from asyncio import as_completed
from concurrent.futures import ThreadPoolExecutor
from concurrent.futures import as_completed
import urllib.request
import os
import ipdb
import time

def download(arg_url):
    """
    Downloads any webpage provided in argument
    """
    
    now = time.time();
    req = urllib.request.urlopen(arg_url)
    print(f"Download time : {time.time() - now}")
    filename = os.path.basename(arg_url);
    ext = os.path.splitext(arg_url)[1]
    if not ext:
        raise RuntimeError("URL doesn't contain an extension")
    else:
        temp = open(filename ,'wb');
        with temp as file_handle:
            while True:
                chunk = req.read(4096);
                if not chunk:
                    break;
                file_handle.write(chunk)
        return f"Finished downloading {filename}";

if __name__ == "__main__":
    urls = ["http://www.irs.gov/pub/irs-pdf/f1040.pdf",
        "http://www.irs.gov/pub/irs-pdf/f1040a.pdf",
        "http://www.irs.gov/pub/irs-pdf/f1040ez.pdf",
        "http://www.irs.gov/pub/irs-pdf/f1040es.pdf",
        "http://www.irs.gov/pub/irs-pdf/f1040sb.pdf"]

    now = time.time();
    with ThreadPoolExecutor(max_workers=5) as executor:
        futures = [executor.submit(download, url) for url in urls]
        for future in as_completed(futures):
            print(future.result())
    print(f"Total time : {time.time() - now}")

    