

# All your custome defined exceptions have to be derived from a base exception class like Exception or ValueErro etc


class NameTooLong(ValueError):
    pass


def f(name):
    if(len(name) < 10):
        raise NameTooLong(name)
    else:
        print(name)


f("Roli")
