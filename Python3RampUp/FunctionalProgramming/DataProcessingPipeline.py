import os
import itertools
import glob

# generator -> generator -> generator

# This function just instantiate the generators and make the links between them
def create_processing_pipeline(start_generator, filters):
    generator = start_generator
    for filter in filters:
        generator = filter(generator)
    return generator


def search_filter(paths):
    for path in paths:
        return itertools.chain(glob.iglob(path + '/**', recursive=True),
                               glob.iglob(path + '/.**', recursive=True))


def size_filter(files):
    for file in files:
        yield os.path.getsize(file)


# The execution starts here, this is the last generator.
# Generator object is returned to pipeline and when next(pipeline) is called sum(size) is executed
# sum function will consume the entire size generator, which will start consuming files generator and so on
def sum_filter(size):
        yield sum(size)
    


filters = [
    search_filter,
    size_filter,
    sum_filter,
]

pipeline = create_processing_pipeline(
    ['./'], filters)

#This call starts the entire pipeline
print(next(pipeline))

# Here a StopIteration exception will be thrown by sum_filter because there is nothing to execute
# next(pipeline)


