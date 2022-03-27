import argparse
import ipdb
import sys

# python3 ./main.py -x argument -z 25 -debug true

def get_args():
    """"""
    parser = argparse.ArgumentParser(
        description="A simple argument parser",
        epilog="This is where you might put example usage"
    )

    # required argument
    parser.add_argument('-x', "--execute", action="store", required=True,
                        help='Help text for option X')
    meg = parser.add_mutually_exclusive_group()
    # optional arguments
    parser.add_argument('-y', help='Help text for option Y', default=False)
    parser.add_argument('-z', help='Help text for option Z', type=int)

    # You can't run in debug and release mode in the same time so the user has to choose between the two options
    meg.add_argument('-debug', help="Specify -debug true if you want to run in debug mode", default=False)
    meg.add_argument('-release', help="Specify -release true if you want to run in debug mode", default=False)
    # print(parser.parse_args())
    
    # If not all arguments were provided, an exception will be raised
    result = parser.parse_args()
    command_line_arguments = {key:value for key, value 
                              in vars(result).items() if value}

    # Print the object with attribute = argument relation
    print(command_line_arguments)
    

if __name__ == '__main__':
    get_args()