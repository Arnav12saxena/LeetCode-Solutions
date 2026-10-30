import numpy

units = numpy.empty(90, dtype=numpy.uint64)
units[ord('.')] = 0
units[ord('X')] = 0x100000
units[ord('Y')] = 1

def numberOfSubmatrices(grid: List[List[str]], units=units) -> int:    
    units = units[
        numpy.frombuffer(
            ''.join(chain.from_iterable(grid)).encode(),
            count=len(grid) * len(grid[0]),
            dtype=numpy.uint8
        )
    ]
    grid = units.reshape((len(grid), len(grid[0])))
    numpy.add.accumulate(
        numpy.add.accumulate(grid, axis=1, out=grid),
        axis=0, out=grid
    )
    others = units >> 20
    units &= 0xfffff    
    return numpy.count_nonzero(units[units == others]).item()
     
Solution = repeat(namedtuple('Solution', ('numberOfSubmatrices',))(
    numberOfSubmatrices
)).__next__
    