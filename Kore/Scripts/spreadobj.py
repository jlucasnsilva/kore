#!/usr/bin/python3.6

import sys

################################################################################
##
## Input
##
################################################################################

filename = sys.argv[1]

################################################################################
##
## Output
##
################################################################################

normals = []
vertices = []
faces = []
uvs = []

################################################################################
##
## Functions
##
################################################################################

def breakTriple(s, divider = ' '):
    arr = s.split()
    arr.pop(0) # arr[0] is either 'v', or 'vn', or 'f'
    return arr

def breakFace(s):
    triangle = []
    triples = breakTriple(s)
    for t in triples:
        parts = t.split('/')
        desc = {
            'vertex': int(parts[0]) - 1,
            'uv': int(parts[1]) - 1,
            'normal': int(parts[2]) - 1
        }
        triangle.append(desc)
    return triangle


################################################################################
##
## Script
##
################################################################################

with open(filename) as file:
    for line in file:
        s = line.strip()
        if line.startswith('v '):
            vertices.append(s.lstrip('v '))
        elif line.startswith('vt '):
            uvs.append(s.lstrip('vt '))
        elif line.startswith('vn '):
            normals.append(s.lstrip('vn '))
        elif line.startswith('f '):
            faces.append(breakFace(s))

print('triangles', len(faces))
print('schema vertex vertex vertex normal normal normal uv uv uv')
for f in faces:
    v0  = vertices[f[0]['vertex']]
    v1  = vertices[f[1]['vertex']]
    v2  = vertices[f[2]['vertex']]
    n0  = normals[f[0]['normal']]
    n1  = normals[f[1]['normal']]
    n2  = normals[f[2]['normal']]
    uv0 = uvs[f[0]['uv']]
    uv1 = uvs[f[1]['uv']]
    uv2 = uvs[f[2]['uv']]

    show = v0 + ' ' + v1 + ' ' + v2
    show = show + ' ' + n0 + ' ' + n1 + ' ' + n2
    show = show + ' ' + uv0 + ' ' + uv1 + ' ' + uv2
    print(show)
