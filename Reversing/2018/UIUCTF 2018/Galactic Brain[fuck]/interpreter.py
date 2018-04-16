from flag import flag, do_check

num_cells = 12
bound = 128

class StackMachine(object):
    def __init__(self):
        self.memory = [0 for _k in range(num_cells)]
        self.data_pointer = 0

    def memory_as_string(self):
        out = ""
        for k in self.memory[self.data_pointer:]:
            if(k == 0):
                return out
            out += chr(max(0, k))
        return out

    def mem_at(self, index):
        if(index < 0 or index >= num_cells):
            return 0
        return self.memory[index]

    def increment(self):
        self.memory[self.data_pointer] = min(bound, self.memory[self.data_pointer] + 1)

    def decrement(self):
        self.memory[self.data_pointer] = max(-1 * bound, self.memory[self.data_pointer] - 1)

    def move_left(self):
        self.data_pointer = max(0, self.data_pointer - 1)

    def move_right(self):
        self.data_pointer = min(num_cells, self.data_pointer + 1)

def printf(stack_machine):
    """Rudimentary printf function.
    Fixed a bug that allowed people to do some bad things.
    %xi: get the byte in memory at the address specified by [data_pointer - 1]
    %x: get the data pointer as a hex string
    %s: get the memory of the stack machine specified by [data_pointer - 1], represented as a string.
    """
    format_string = stack_machine.memory_as_string()

    format_string = format_string.replace('%xi', hex(stack_machine.mem_at(stack_machine.mem_at(stack_machine.data_pointer - 1)))[2:])

    format_string = format_string.replace('%x', hex(stack_machine.data_pointer)[2:])
    format_string = format_string.replace('%s', machines[stack_machine.mem_at(stack_machine.data_pointer - 1)].memory_as_string())

    format_string = format_string.replace("\\n", "\n")
    format_string = format_string.replace("\\t", "\t")

    out = str(machine.data_pointer) + ": " + format_string
    print(out)

def inc(state, _context):
    machines[state['machine']].increment()
def dec(state, _context):
    machines[state['machine']].decrement()
def shl(state, _context):
    machines[state['machine']].move_left()
def shr(state, _context):
    machines[state['machine']].move_right()
def jumpr(state, _context):
    m = machines[state['machine']]
    if(m.mem_at(m.data_pointer) == 0):
        step = state['ip'] + 1
        num_rb_needed = 1
        while(step < num_cells):
            step += 1
            if(_context[step] == '['):
                num_rb_needed += 1
            if(_context[step] == ']'):
                num_rb_needed -= 1
            if(num_rb_needed == 0):
                break
        state['ip'] = step
def jumpl(state, _context):
    m = machines[state['machine']]
    if(m.mem_at(m.data_pointer) != 0):
        step = state['ip']
        num_lb_needed = 1
        while(step > 0):
            step -= 1
            if(_context[step] == ']'):
                num_lb_needed += 1
            if(_context[step] == '['):
                num_lb_needed -= 1
            if(num_lb_needed == 0):
                break
        state['ip'] = step
def lastm(state, _context):
    state['machine'] = max(0, state['machine'] - 1)
def nextm(state, _context):
    state['machine'] = min(num_cells, state['machine'] + 1)
def out(state, _context):
    printf(machines[state['machine']])
def debug(state, _context):
    m = machines[state['machine']]
    print("Program:", _context)
    print("IP:", state['ip'])
    print("Machine:", state['machine'])
    print("Machine State:")
    print("\tData Pointer:", m.data_pointer)
    print("\tMemory:")
    for i in range(num_cells):
        print("\t\t", m.mem_at(i), "\t\t", chr(max(0, m.mem_at(i))))

def die(_state, _context):
    print("SMOL BRAIN")
    exit()

machines = [StackMachine() for _k in range(num_cells)]
operations = {
    '+': inc,
    '-': dec,
    '<': shl,
    '>': shr,
    '[': jumpr,
    ']': jumpl,
    '(': lastm,
    ')': nextm,
    '.': out,
    'x': die,
#    'D': debug
}

def interpret_program(program_string):
    timeout = 8192
    state = {'machine': 0, 'ip': 0}

    while(state['ip'] < len(program_string) and timeout > 0):
        try:
            c = program_string[state['ip']]
            if c in operations.keys():
                    operations[c](state, program_string)
        except Exception as e:
            print("Well, you managed to break it...")
            print(e)
        state['ip'] += 1
        timeout -= 1
        if program_string[-1] == 's':
            do_check()
    if(timeout == 0):
        print("You used too many cycles. Sorry.")
        exit()

def load_string(in_str, machine_num):
    program = ')'*machine_num
    program += '>'.join('+'*(ord(k)) for k in in_str)
    program += '<'*len(in_str)

    interpret_program(program)

def check_flag(user_flag):
    load_string(flag, 0)
    load_string(user_flag, 1)

    program = "[-)-(][x])[x](>)>("*len(flag) + 's'

    interpret_program(program)
    print("Ayyyy nice lol")


if(__name__ == '__main__'):
    import sys
    if len(sys.argv) >= 2:
        print(sys.argv[1])
        check_flag(sys.argv[1])
    else:
        check_flag(input("Gimme a flag > "))
