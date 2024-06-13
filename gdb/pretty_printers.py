import gdb

class CmdPrinter:
    """Print a t_cmd structure."""

    def __init__(self, val):
        self.val = val

    def to_string(self):
        cmd = self.val['cmd'].string() if self.val['cmd'] else 'NULL'
        return "t_cmd(cmd={}, argc={})".format(cmd, self.val['argc'])

    def children(self):
        tokens = self.val['tokens']
        tokens_list = []
        i = 0
        while tokens[i]:
            token_str = tokens[i].string()
            tokens_list.append(('tokens[{}]'.format(i), token_str))
            i += 1
        return tokens_list

    def display_hint(self):
        return 'array'

def lookup_type(val):
    if str(val.type) == 't_cmd':
        return CmdPrinter(val)
    return None

def register_cmd_printer():
    gdb.pretty_printers.append(lookup_type)

register_cmd_printer()
