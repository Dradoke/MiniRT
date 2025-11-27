#!/usr/bin/env bash

if [ "$#" -ne 2 ]; then
  echo "Usage: $0 input.obj output.rt"
  exit 1
fi

OBJ="$1"
RT="$2"

awk -v out="$RT" '
# Nettoyage préventif des retours chariot Windows (\r) sur chaque ligne
{ sub(/\r$/, "") }

BEGIN {
  print "# Auto conversion OBJ -> RT" > out
}

# store vertices
$1=="v" {
  verts[++nv] = $2 "," $3 "," $4
}

# triangulate faces
$1=="f" {
  nf = 0
  # read vertex indexes only (strip /../)
  for (i = 2; i <= NF; i++) {
    split($i, p, "/")
    nf++
    ids[nf] = p[1]
  }
  # fan triangulation
  for (i = 1; i < nf-1; i++) {
    printf "tr\t%s\t%s\t%s\t255,255,255\n",
      verts[ids[1]], verts[ids[i+1]], verts[ids[i+2]] >> out
  }
}
' "$OBJ"

echo "Conversion terminée → $RT 🚀"