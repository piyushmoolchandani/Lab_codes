def new_stack():
    return [];

def push(a, element):
    a.append(element);
    
def pop_(a):
    if (len(a)):
        return a.pop()

def is_empty(a):
    return True if len(a) == 0 else False

