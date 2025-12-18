import sys
import math
import random
import functools, itertools, collections, heapq, bisect
from collections import Counter, defaultdict, deque
import copy

POS_INF = float('inf')
NEG_INF = float('-inf')
INT_MAX = sys.maxsize
INT_MIN = -sys.maxsize
WHITESPACE = ['\r', '\n','\t', '\v', '\f', ' ']
def read_int():
    return int(input())
def read_str():
    return input().strip()
def read_float():
    return float(input())
def read_int_list():
    return list(map(int, input().strip().split()))
def read_str_list():
    return [x.strip() for x in input().split()]
def read_float_list():
    return list(map(float, input().strip().split()))
def read_int_matrix(rows):
    return [read_int_list() for _ in range(rows)]
def read_float_matrix(rows):
    return [read_float_list() for _ in range(rows)]
def read_str_matrix(rows):
    return [read_str_list() for _ in range(rows)]
def create_matrix(rows, cols, default_val = 0):
    return [[copy.deepcopy(default_val) for _ in range(cols)] for _ in range(rows)]
def print_matrix(mat):
    for x in mat:
        print(x)
# ================= TEMPLATE ENDS HERE ==================

### Read first line of input
if __name__ == '__main__':
    t = read_int()
    for i in range(1, t+1):
        ### Question IO here
        ## a,b,c,d = map(int, sys.stdin.readline().split())





        ### ==========================
        ans = 0 # add answer here
        print(ans)