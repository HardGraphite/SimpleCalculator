#!/usr/bin/python

"""
Dynamic Lib Test
"""

import ctypes


class Calculator:
    """wrapper of calculator"""

    def __init__(self, dl: str):
        self._lib = ctypes.cdll.LoadLibrary(dl)
        self._fn_init = self._lib.calc_init
        self._fn_init.restype = ctypes.c_void_p
        self._fn_eval = self._lib.calc_evaluate
        self._fn_eval.restype = ctypes.c_double
        self._fn_eval.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self._fn_tryeval = self._lib.calc_try_evaluate
        self._fn_tryeval.restype = ctypes.c_double
        self._fn_tryeval.argtypes = [ctypes.c_void_p, ctypes.c_char_p,
            ctypes.c_char_p, ctypes.c_int]
        self._fn_del = self._lib.calc_cleanup
        self._fn_del.argtypes = [ctypes.c_void_p]

        self._errstrlen = 128
        self._errstr = ctypes.create_string_buffer(self._errstrlen)

        self.calc = self._fn_init()

    def __del__(self):
        self._fn_del(self.calc)
        self.calc = None

    def __call__(self, expr: str) -> float:
        """evaluate an expression"""

        if not isinstance(expr, str):
            raise TypeError(expr)

        # expr_chars = ctypes.create_string_buffer(expr.encode())
        # res = self._fn_eval(self.calc, expr_chars)
        # return float(res)

        expr_chars = ctypes.create_string_buffer(expr.encode())
        res = self._fn_tryeval(self.calc, expr_chars, self._errstr, self._errstrlen)
        if self._errstr[0] == b'\x00':
            return float(res)
        else:
            raise RuntimeError('calc: ' + ctypes.string_at(self._errstr).decode())


if __name__ == "__main__":
    caclulator = Calculator(r'../bin/libcalc.so')
    def test(expr):
        print(expr, '=', caclulator(expr))
    test('1+1')
    test('sin($pi/2)')
