from math import *

def drawShapeWrapper(n):
    col = 2**n
    ret = drawShape(n, 0, col)
    print("".join(ret))
    
def drawShape(depth, row, col):
    if depth <= 0:
        raise Exception("Not Applicable! Depth should be greater than 0")
    if depth == 1:
        return drawTriangle(col) 
    else:
        ret = []
        row_shifts = 2**(depth - 1)
        col_shifts = 2**(depth - 1)
        ret.extend(drawShape(depth-1, row, col))
        ret.append('\n')
        bottomLeft  = drawShape(depth-1, row + row_shifts, col - col_shifts)
        bottomRight = drawShape(depth-1, row + row_shifts, col_shifts)

        j = 0
        lines = 0
        modified = []
        for ch in bottomLeft:
            if ch != '\n':
                modified.append(ch)
            else:
                rightPadded = 2**(depth-1) - 1 - lines
                modified.extend([' '] * rightPadded)
                step = 0
                while j+step < len(bottomRight) and bottomRight[j+step] != '\n':
                    step+=1
                modified.extend(bottomRight[j:j+step+1])
                j+=step+1
                lines+=1
        modified.extend(bottomRight[j:])       
        # print("modified:",modified)
        ret.extend(modified)
        return ret


def drawTriangle(col):
    ret = []
    col-= 1
    pad = [' '] * col
    ret.extend(pad)
    ret.append('/')
    ret.append('\\')
    ret.append('\n')
    pad = [' '] * (col-1)
    ret.extend(pad)
    ret.extend(['/', '__', '\\'])
    return ret

def main():
    import sys
    import os
    n = sys.argv[1:][0]

    drawShapeWrapper(int(n))


if __name__ == "__main__":
    main()
