import sys
import math
from itertools import permutations, combinations
from collections import defaultdict, deque

def parse_point(s):
    y = ord(s[0]) - ord('A')
    x = int(s[1]) - 1
    return (x, y)

def main():
    input = sys.stdin.read().split()
    ptr = 0
    T = int(input[ptr])
    ptr +=1
    for case in range(1, T+1):
        N = int(input[ptr])
        ptr +=1
        edges = []
        points_set = set()
        adj = defaultdict(list)
        total = 0.0
        for _ in range(N):
            p1_str = input[ptr]
            p2_str = input[ptr+1]
            ptr +=2
            p1 = parse_point(p1_str)
            p2 = parse_point(p2_str)
            dx = p1[0] - p2[0]
            dy = p1[1] - p2[1]
            length = math.hypot(abs(dx), abs(dy))
            total += length
            edges.append((p1, p2))
            points_set.add(p1)
            points_set.add(p2)
            adj[p1].append(p2)
            adj[p2].append(p1)
        
        all_points = list(points_set)
        if not all_points:
            print(f"Case {case}: 0.00")
            continue
        
        visited = set()
        q = deque([all_points[0]])
        visited.add(all_points[0])
        while q:
            u = q.popleft()
            for v in adj[u]:
                if v not in visited:
                    visited.add(v)
                    q.append(v)
        
        if len(visited) != len(points_set):
            print(f"Case {case}: ~x(")
            continue
        
        degree = defaultdict(int)
        for u, v in edges:
            degree[u] +=1
            degree[v] +=1
        
        odd_vertices = [k for k in degree if degree[k] %2 !=0]
        if len(odd_vertices) not in (0, 2):
            print(f"Case {case}: ~x(")
            continue
        
        if len(odd_vertices) ==0 or len(odd_vertices)==2:
            print(f"Case {case}: {total:.2f}")
        else:
            print(f"Case {case}: ~x(")

if __name__ == "__main__":
    main()