import gdb

class PointPrinter:
    def __init__(self, val, is_pointer=False):
        self.val = val
        self.is_pointer = is_pointer

    def to_string(self):
        return '\n{point}({x}, {y}) -> {l}'.format(
            point = '*' if self.is_pointer else '',
            x = self.val['x'],
            y = self.val['y'],
            l = self.val['len'],
        )

def my_pp_func(val):
    if str(val.type) == 'Point': return PointPrinter(val)
    if str(val.type) == 'Point *': return PointPrinter(val.dereference(), True)
    return None

gdb.pretty_printers.append(my_pp_func)

