

def yell(message):
    return message.upper() + "!";

secondF = yell
print(yell.__name__);

del yell

print(secondF("Home working !"))
print(secondF.__name__);
