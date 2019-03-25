def new_queue():
    return []

def enqueue(a, element):
    a.append(element);
    
def dequeue(a):
    if (len(a)):
        return a.pop(0)
    
def is_empty(a):
    return True if len(a) == 0 else False