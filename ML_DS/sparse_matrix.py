import collections

class SparseVector(object):
    def __init__(self, kv_list):
        self.kv_map = dict(kv_list)

    def __str__(self):
        return str(self.kv_map)

    def __getitem__(self, k):
        return self.kv_map[k]

    def __mul__(self, other):
        result = 0
        for k in self.kv_map.keys():
            if k in other.kv_map.keys():
                result += self[k] * other[k]

        return result

class SparseMatrix(object):
    '''
    Create: Ex: SparseMatrix([
        ((x, y), v),
        ((x2, y2), v2),
        ...
        ])

        =>
        kv_map:
            (x, y) : v,
            (x2, y2): v2,
            ...
    '''
    def __init__(self, kv_list):
        self.kv_map = dict(kv_list)

    def __str__(self):
        return str(self.kv_map)

    def __getitem__(self, k):
        return self.kv_map[k]

    def __mul__(self, other):
        result = collections.defaultdict(int)

        for (x1, y1) in self.kv_map.keys():
            for (x2, y2)in other.kv_map.keys():
                if y1 == x2:
                    result[(x1, y2)] += self[(x1, y1)] * other[(x2, y2)]
        return SparseMatrix(result.items())

def test():
    a = SparseVector([(0, 1), (9, 2)])
    b = SparseVector([(0, 3), (9, 1)])

    print a
    print a*b

    ma = SparseMatrix([((0, 0), 1), ((0, 1), 2), ((0, 2), 3)])
    print ma
    mb = SparseMatrix([((0, 0), 1), ((1, 0), 2), ((2, 0), 3)])
    print mb

    mc = ma * mb
    print mc


test()

